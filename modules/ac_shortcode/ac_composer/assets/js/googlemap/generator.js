

(function($){

Drupal.behaviors.acGoogleMapGenerator = {
	attach: function (context, settings) {
	
	$("#mgl_map_generator").once('acGoogleMapGenerator', function(){
	

		var mgl_map_defaults = {'address' : 'san vito, italy', 'zoom' : 13},
		$form = $('#ac-google-map-generator'),
		opts = {
			zoom: $('select[name="zoom"]', $form).val() != '' ? Number($('select[name="zoom"]', $form).val()) : Number(mgl_map_defaults.zoom),
			controls: { 
				mapTypeControl: false, 
				zoomControl: true, 
				panControl: true,
				streetViewControl: true 
			},
		};
		
		if ($('input[name="address"]', $form).attr('value') != '') {
			opts.address = $('input[name="address"]', $form).attr('value');
		}else if ($('input[name="lat"]', $form).attr('value') != '' &&
							$('input[name="long"]', $form).attr('value') != '') {
			opts.latitude = $('input[name="lat"]', $form).attr('value');
			opts.longitude = $('input[name="long"]', $form).attr('value');
		}else {
			opts.address = mgl_map_defaults.address;
		}

		// Load map
		$("#mgl_map_generator").gMap(opts);
			
		skins();
		
		// Check for zoom
		if( $('select[name="zoom"]', $form).attr('value') == '') { 
				$('select[name="zoom"]', $form).attr('value', Number(mgl_map_defaults.zoom)); 
		} else if (gmapAdded()) {
				$("#mgl_map_generator").data("gMap.reference").setZoom(Number($('select[name="zoom"]', $form).attr('value')));
		}

			
			 // Bind zoom selector
			 $('select[name="zoom"]', $form).on('change', function() {
					$("#mgl_map_generator").data("gMap.reference").setZoom(Number($(this).val()));
			});

			 // Bind type selector
			 $('select[name="type"]', $form).on('change', function() {
					type =  $(this).val();
					if(type != 'custom') {
							loadType(type);
					}
			});

        // Search for the address
        $('input[name="address"]', $form).keyup(function() {
            address = $('input[name="address"]', $form).attr('value');
            var geo = new google.maps.Geocoder;
            geo.geocode({'address':address},function(results, status){
                  if (status == google.maps.GeocoderStatus.OK) {
                    $("#mgl_map_generator").data("gMap.reference").setCenter(results[0].geometry.location);
										$('input[name="lat"]', $form).attr('value', Number(results[0].geometry.location.lat()));
										$('input[name="long"]', $form).attr('value', Number(results[0].geometry.location.lng()));
                  }
           });
        });
				
        // If lat long center map
        $('input[name="lat"], input[name="long"]', $form).keyup(setMapCenter);

        $('input[name="width"]', $form).keyup(function() {
            
            map_width = $('input[name="width"]', $form).attr('value');

            if(map_width == '') { map_width = '100%'; }

            $("#mgl_map_generator").animate({'width' : map_width}, 200, function(){
                 google.maps.event.trigger($("#mgl_map_generator").data("gMap.reference"), 'resize');
            });

        });

        $('input[name="height"]', $form).keyup(function() {
            
            map_height = $('input[name="height"]', $form).attr('value');

            if(map_height == '') { map_height = '100%'; }

            $("#mgl_map_generator").animate({'height' : map_height}, 200, function(){
                 google.maps.event.trigger($("#mgl_map_generator").data("gMap.reference"), 'resize');
            });

        });

        $('input[name="color"]', $form).on('colorChanged', function(){
            if(/^#[0-9A-F]{6}$/i.test($(this).attr('value'))) {

                var one_color_styles = [ 
                    { "stylers": [ { "hue": $(this).attr('value') }, { "saturation": 1 }, { "lightness": 1 } ] }
                  ];
                
                var one_colorstyledMap = new google.maps.StyledMapType(one_color_styles, {name: "OneColor_style"});
                
                jQuery("#mgl_map_generator").data("gMap.reference").mapTypes.set('OneColor_style', one_colorstyledMap);

                $("#mgl_map_generator").data("gMap.reference").setMapTypeId('OneColor_style');
            }
        });
				
			  $('fieldset.ac-gmap-marker', $form).each(function(i){
				if (typeof window['marker'+i] !=undefined && gmapAdded()) {
					window['marker'+i].setMap($("#mgl_map_generator").data("gMap.reference"));
					console.log(window['marker'+i]);
				}else {
				
					window['marker'+i] = new google.maps.Marker({
						position : $("#mgl_map_generator").data("gMap.reference").getCenter(),
						draggable: true,
					});
					
					// first search by address
					if ($('.ac-gmap-marker-address', this).attr('value') != '') {
						address = $('.ac-gmap-marker-address', this).attr('value');
						var geo = new google.maps.Geocoder;
							geo.geocode({'address':address},function(results, status){
										if (status == google.maps.GeocoderStatus.OK) {
											window['marker'+i].setPosition(results[0].geometry.location);
											$('.ac-gmap-marker-lat-'+i, $form).attr('value',results[0].geometry.location.lat());
											$('.ac-gmap-marker-long-'+i, $form).attr('value',results[0].geometry.location.lng());
										}
						 });
					}else if ($('.ac-gmap-marker-lat', this).attr('value') != '' && 
										$('.ac-gmap-marker-long', this).attr('value') != '') {
						// search by latitude and longtitude
						var geo = new google.maps.Geocoder,
						latLong = new google.maps.LatLng($('.ac-gmap-marker-lat', this).attr('value'), $('.ac-gmap-marker-long', this).attr('value'));
							geo.geocode({'location':latLong},function(results, status){
										if (status == google.maps.GeocoderStatus.OK) {
											window['marker'+i].setPosition(results[0].geometry.location);
										}
						 });
					}else {
						addFormMarker(i);
					}
					
					
					initMarker(i);

				}
			});
			
        /* Markers */
        $('#add-marker input[type="submit"]', $form).click(function(){
            var i = $('.ac-gmap-marker').length;
						console.log(i);
            addFormMarker(i);
        });

        // Marker Address
        $('.ac-gmap-marker-address', $form).on('keyup', function(e){
            
						i = $(this).closest('fieldset.ac-gmap-marker').data('markerid'),
            address = $(this).attr('value');
            var geo = new google.maps.Geocoder;

            geo.geocode({'address':address},function(results, status){
                  if (status == google.maps.GeocoderStatus.OK) {
                    window['marker'+i].setPosition(results[0].geometry.location);
                    $('.ac-gmap-marker-lat-'+i, $form).attr('value',results[0].geometry.location.lat());
                    $('.ac-gmap-marker-long-'+i, $form).attr('value',results[0].geometry.location.lng());
                  } else {
                    window['marker'+i].setPosition($("#mgl_map_generator").data("gMap.reference").getCenter());
                  }
           });
        });
				
        // Marker Content
				$('.ac-gmap-marker-content', $form).on('keyup', function(e){
				
/*  */

        });
        // Load previous markers
         google.maps.event.addListenerOnce($("#mgl_map_generator").data("gMap.reference"), 'idle', initialize);
	});
			
	}
}


function initialize() {
		var $form = $('#ac-google-map-generator');
    // Setup map widht & height

    map_width = $('input[name="width"]', $form).attr('value');
    if(map_width == '') { map_width = '100%'; }
    $("#mgl_map_generator").css({'width' : map_width});

    map_height = $('input[name="height"]', $form).attr('value');
    if(map_height == '') { map_height = '100%'; }
    $("#mgl_map_generator").css({'height' : map_height});
        
    // Load current skin

    var skin = $('select[name="type"]', $form).val();
            
    if(skin != '') { loadType(skin); }

    // Add previous Markers

/*     $('#markersForm #markersCont > div').each(function( index ) {

        var i = Number($(this).attr('id').replace("markerForm_", ""));

        // If marker has address load by it
        if($('#markerForm_'+i+ ' .marker_address').attr('value') != '') {
            
            // Check if is a valid address
            var geo = new google.maps.Geocoder;

            geo.geocode({'address':$('#markerForm_'+i+ ' .marker_address').attr('value')},function(results, status){
                  if (status == google.maps.GeocoderStatus.OK) {
                    
                    // If it is, put the marker there
                    window['marker'+i] = new google.maps.Marker({
                        position : results[0].geometry.location,
                        draggable: true,
                    });
                    console.log(i+' - position found!');

                    initMarker(i);
                  } else {

                    //Ifnot center it in the map
                    window['marker'+i] = new google.maps.Marker({
                        position : $("#mgl_map_generator").data("gMap.reference").getCenter(),
                        draggable: true,
                    });

                    initMarker(i);
                  }
           });
        } else if($('#markerForm_'+i+ ' .marker_lat').attr('value') != '')  {
            console.log(i+' - LatLong!');
            // Setup by latLong
            
            var latlng = new google.maps.LatLng($('#markerForm_'+i+ ' .marker_lat').attr('value'), $('#markerForm_'+i+ ' .marker_long').attr('value'));
            
            window['marker'+i] = new google.maps.Marker({
                position : latlng,
                draggable: true,
            });

            initMarker(i);
        } else {
  
            map_center = $("#mgl_map_generator").data("gMap.reference").getCenter();
            if(map_center == undefined) {
                map_center = new google.maps.LatLng( Number($('#mgl_lat').attr('value')), Number($('#mgl_long').attr('value')));
            }
            // By default set it in center
            window['marker'+i] = new google.maps.Marker({
                position : map_center,
                draggable: true,
            });

            initMarker(i);
        }

        
     }); */


    // Bind fields to events in case the map center or zoom chantes
        
    google.maps.event.addListener($("#mgl_map_generator").data("gMap.reference"), 'center_changed', function(event) {
      $('input[name="lat"]').attr('value',$("#mgl_map_generator").data("gMap.reference").getCenter().lat());
      $('input[name="long"]').attr('value',$("#mgl_map_generator").data("gMap.reference").getCenter().lng());
    });

    google.maps.event.addListener($("#mgl_map_generator").data("gMap.reference"), 'dragend', function(event) {
      $('input[name="address"]', $form).attr('value', '');
    });

    google.maps.event.addListener($("#mgl_map_generator").data("gMap.reference"), 'zoom_changed', function(event) {
			console.log($("#mgl_map_generator").data("gMap.reference").getZoom());
      $('select[name="zoom"]', $form).attr('value',$("#mgl_map_generator").data("gMap.reference").getZoom());
    });
}

/**
 * center Map By Physical Address
 */
function setlatLongByAddress(address){
	if (address == '' || !gmapAdded()) {
		return;
	}
	var geo = new google.maps.Geocoder;
	geo.geocode({'address':address},function(results, status){
		if (status == google.maps.GeocoderStatus.OK) {
			$('input[name="lat"]', $form).attr('value', Number(results[0].geometry.location.lat()));
			$('input[name="long"]', $form).attr('value', Number(results[0].geometry.location.lng()));
		}
 });
}

function loadType(type) {
		var $form = $('#ac-google-map-generator');
    switch(type) {
        case 'satellite':
        case 'roadmap':
            $("#mgl_map_generator").data("gMap.reference").setMapTypeId(type);
        break;
        case 'hybrid':
            $("#mgl_map_generator").data("gMap.reference").setMapTypeId(google.maps.MapTypeId.HYBRID);
        break;
        case 'terrain':
            $("#mgl_map_generator").data("gMap.reference").setMapTypeId(google.maps.MapTypeId.TERRAIN);
        break;
        case 'custom':
            
            var one_color_styles = [ 
                { "stylers": [ { "hue": $('input[name="color"]', $form).attr('value') }, { "saturation": 1 }, { "lightness": 1 } ] }
            ];   
            
            var one_colorstyledMap = new google.maps.StyledMapType(one_color_styles, {name: "OneColor_style"});
                
            $("#mgl_map_generator").data("gMap.reference").mapTypes.set('OneColor_style', one_colorstyledMap);
            $("#mgl_map_generator").data("gMap.reference").setMapTypeId('OneColor_style');
        break;
        default:
            $("#mgl_map_generator").data("gMap.reference").setMapTypeId(type+'_style');
        break;
    }
}

function addFormMarker(i) {

    while($(".ac-gmap-marker-"+ i).length > 0) { i++; } 

    window['marker'+i] = new google.maps.Marker({
        position : $("#mgl_map_generator").data("gMap.reference").getCenter(),
        draggable: true,
    });

    initMarker(i);
    
}

function initMarker(i) {
		console.log('added marker '+ i);
    window['marker'+i].setMap($("#mgl_map_generator").data("gMap.reference"));
    google.maps.event.addListener(window['marker'+i],'dragend',function(event) {
        $('.ac-gmap-marker-'+i+ ' .ac-gmap-marker-lat').attr('value',event.latLng.lat());
        $('.ac-gmap-marker-'+i+ ' .ac-gmap-marker-long').attr('value',event.latLng.lng());
        $('.ac-gmap-marker-'+i+ ' .ac-gmap-marker-address').attr('value','');
    }); 

 /*    if($('.ac-gmap-marker-'+i+ ' .marker_icon').attr('value') != '')  {
        window['marker'+i].setIcon($('#markerForm_'+i).find('.marker_selected').attr('src'));
    } */
}

function setMapCenter() {
		var $form = $('#ac-google-map-generator');
    mgl_lat = Number($('input[name="lat"]', $form).attr('value'));
    mgl_long = Number($('input[name="lat"]', $form).attr('value'));
    if($.isNumeric(mgl_lat) && $.isNumeric(mgl_long) && mgl_lat != '' && mgl_long != '') {
        $("#mgl_map_generator").gMap('centerAt', { latitude: mgl_lat, longitude: mgl_long, zoom: $("#mgl_map_generator").data("gMap.reference").getZoom() });
    }
}

function gmapAdded() {
	return typeof jQuery("#mgl_map_generator").data("gMap.reference") == Object;
}

function skins() {
     // Cartoon
      var cartoon_styles = [ 
          { "featureType": "landscape", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "transit", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "poi.park", "elementType": "labels", "stylers": [ { "visibility": "off" }] 
        },{ "featureType": "poi.park", "elementType": "geometry.fill", "stylers": [ { "color": "#d3d3d3" }, { "visibility": "on" } ]
        },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "landscape", "stylers": [ { "visibility": "on" }, { "color": "#b1bc39" } ]
        },{ "featureType": "landscape.man_made", "stylers": [ { "visibility": "on" }, { "color": "#ebad02" } ] 
        },{ "featureType": "water", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#416d9f" } ] 
        },{ "featureType": "road", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#000000" } ]
        },{ "featureType": "road", "elementType": "labels.text.stroke", "stylers": [ { "visibility": "off" }, { "color": "#ffffff" } ]
        },{ "featureType": "administrative", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#000000" } ]
        },{ "featureType": "road", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#ffffff" } ] 
        },{ "featureType": "road", "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "water", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "poi", "elementType": "geometry.fill", "stylers": [ { "color": "#ebad02" } ]
        },{ "featureType": "poi.park", "elementType": "geometry.fill", "stylers": [ { "color": "#8ca83c" } ]
        } 
      ];

      // Grey Scale
      var grey_styles = [ 
          { "featureType": "road.highway", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "landscape", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "transit", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "poi", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "poi.park", "stylers": [ { "visibility": "on" } ] 
        },{ "featureType": "poi.park", "elementType": "labels", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "poi.park", "elementType": "geometry.fill", "stylers": [ { "color": "#d3d3d3" }, { "visibility": "on" } ]
        },{ "featureType": "poi.medical", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "poi.medical", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "color": "#cccccc" } ] 
        },{ "featureType": "water", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#cecece" } ] 
        },{ "featureType": "road.local", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#808080" } ]
        },{ "featureType": "administrative", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#808080" } ]
        },{ "featureType": "road", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#fdfdfd" } ] 
        },{ "featureType": "road", "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "water", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "poi", "elementType": "geometry.fill", "stylers": [ { "color": "#d2d2d2" } ]
        } 
      ];

      // Black & White
      var bw_styles = [ 
          { "featureType": "road.highway", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "landscape", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "transit", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "poi.park", "elementType": "labels", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "poi.park", "elementType": "geometry.fill",  "stylers": [ { "color": "#d3d3d3" }, { "visibility": "on" } ]
        },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "landscape", "stylers": [ { "visibility": "on" }, { "color": "#ffffff" } ] 
        },{ "featureType": "water", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#cecece" } ] 
        },{ "featureType": "road", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#000000" } ]
        },{ "featureType": "road", "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#ffffff" } ]
        },{ "featureType": "administrative", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#000000" } ]
        },{ "featureType": "road", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#000000" } ] 
        },{ "featureType": "road", "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "water", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "poi", "elementType": "geometry.fill", "stylers": [ { "visibility": "off" } ]
        } 
      ];

      // Retro
      var retro_styles = [ 
        { "featureType": "transit", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "poi.park", "elementType": "geometry.fill", "stylers": [ { "color": "#d3d3d3" }, { "visibility": "on" } ]
        },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "landscape", "stylers": [ { "visibility": "on" }, { "color": "#eee8ce" } ] 
        },{ "featureType": "water", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#b8cec9" } ] 
        },{ "featureType": "road", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#000000" } ]
        },{ "featureType": "road", "elementType": "labels.text.stroke", "stylers": [ { "visibility": "off" }, { "color": "#ffffff" } ]
        },{ "featureType": "administrative", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#000000" } ]
        },{ "featureType": "road", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#ffffff" } ] 
        },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "road", "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "water", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "poi", "elementType": "geometry.fill", "stylers": [ { "color": "#d3cdab" } ]
        },{ "featureType": "poi.park", "elementType": "geometry.fill", "stylers": [ { "color": "#ced09d" } ]
        },{ "featureType": "poi", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
        } 
      ];

      // Night
      var night_styles = [ 
        { "featureType": "landscape", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "transit", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "poi.park", "elementType": "labels", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "poi.park", "elementType": "geometry.fill", "stylers": [ { "color": "#d3d3d3" }, { "visibility": "on" } ]
        },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "landscape", "stylers": [ { "visibility": "on" }, {  "hue": "#0008ff" }, { "lightness": -75 }, { "saturation": 10 } ]
        },{ "elementType": "geometry.stroke", "stylers": [ { "color": "#1f1d45" } ]
        },{ "featureType": "landscape.natural", "stylers": [ { "color": "#1f1d45" } ]
        },{ "featureType": "water", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#01001f" } ] 
        },{ "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#e7e8ec" } ]
        },{ "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#151348" } ]
        },{ "featureType": "administrative", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#f7fdd9" } ]
        },{ "featureType": "administrative", "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#01001f" } ]
        },{ "featureType": "road", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#316694" } ] 
        },{ "featureType": "road", "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "water", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "poi", "elementType": "geometry.fill", "stylers": [ { "color": "#1a153d" } ]
        
        } 
      ];   

      // Night Light
      var night_light_styles = [ 
          {"elementType": "geometry", "stylers": [ { "visibility": "on" }, { "hue": "#232a57" } ]
        },{ "featureType": "road.highway", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "landscape", "elementType": "geometry.fill", "stylers": [ { "hue": "#0033ff" }, { "saturation": 13 }, { "lightness":-77 } ]
        },{ "featureType": "landscape", "elementType": "geometry.stroke", "stylers": [ { "color": "#4657ab" } ] 
        },{ "featureType": "transit", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "water", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#0d0a1f" } ] 
        },{ "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#d2cfe3" } ]
        },{ "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#0d0a1f" } ]
        },{ "featureType": "administrative", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#ffffff" } ]
        },{ "featureType": "administrative", "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#0d0a1f" } ]
        },{ "featureType": "road", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#ff9910" } ] 
        },{ "featureType": "road.local", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#4657ab" } ] 
        },{ "featureType": "road", "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "water", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "poi", "elementType": "geometry.fill", "stylers": [ { "color": "#232a57" } ]
        },{ "featureType": "poi.park", "elementType": "geometry.fill", "stylers": [ { "color": "#232a57" } ]
        },{ "featureType": "poi", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
        } 
      ]; 

      // Papiro  
      var papiro_styles = [ 
          {"elementType": "geometry", "stylers": [ { "visibility": "on" }, { "color": "#f2e48c" } ]
        },{ "featureType": "road.highway", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "transit", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "poi.park", "elementType": "labels", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "poi.park", "elementType": "geometry.fill",  "stylers": [ { "color": "#d3d3d3" }, { "visibility": "on" } ]
        },{ "featureType": "road", "elementType": "geometry.stroke", "stylers": [ { "visibility": "off" } ] 
        },{ "featureType": "landscape", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#f2e48c" } ] 
        },{ "featureType": "landscape", "elementType": "geometry.stroke", "stylers": [ { "visibility": "on" }, { "color": "#592c00" } ] 
        },{ "featureType": "water", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#a77637" } ] 
        },{ "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#592c00" } ]
        },{ "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#f2e48c" } ]
        },{ "featureType": "administrative", "elementType": "labels.text.fill", "stylers": [ { "visibility": "on" }, { "color": "#592c00" } ]
        },{ "featureType": "administrative", "elementType": "labels.text.stroke", "stylers": [ { "visibility": "on" }, { "color": "#f2e48c" } ]
        },{ "featureType": "road", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#a5630f" } ] 
        },{ "featureType": "road.highway", "elementType": "geometry.fill", "stylers": [ { "visibility": "on" }, { "color": "#592c00" } ] 
        },{ "featureType": "road", "elementType": "labels.icon", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "water", "elementType": "labels", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "poi", "elementType": "geometry.fill", "stylers": [ { "visibility": "off" } ]
        },{ "featureType": "poi", "elementType": "labels", "stylers": [ { "visibility": "off" } ] 
        } 
      ];

    var styledMap = new google.maps.StyledMapType(grey_styles, {name: "Grey"});
    var bwstyledMap = new google.maps.StyledMapType(bw_styles, {name: "Black & White"});
    var retrostyledMap = new google.maps.StyledMapType(retro_styles, {name: "Retro"});
    var nightstyledMap = new google.maps.StyledMapType(night_styles, {name: "Night"});
    var nightlightstyledMap = new google.maps.StyledMapType(night_light_styles, {name: "Night Light"});
    var papirostyledMap = new google.maps.StyledMapType(papiro_styles, {name: "Papiro"});
    var cartoonstyledMap = new google.maps.StyledMapType(cartoon_styles, {name: "Cartoon"});

		if (typeof jQuery("#mgl_map_generator").data("gMap.reference") == Object) {
			jQuery("#mgl_map_generator").data("gMap.reference").mapTypes.set('cartoon_style', cartoonstyledMap);
			jQuery("#mgl_map_generator").data("gMap.reference").mapTypes.set('grey_style', styledMap);
			jQuery("#mgl_map_generator").data("gMap.reference").mapTypes.set('bw_style', bwstyledMap);
			jQuery("#mgl_map_generator").data("gMap.reference").mapTypes.set('retro_style', retrostyledMap);
			jQuery("#mgl_map_generator").data("gMap.reference").mapTypes.set('night_style', nightstyledMap);
			jQuery("#mgl_map_generator").data("gMap.reference").mapTypes.set('night_light_style', nightlightstyledMap);
			jQuery("#mgl_map_generator").data("gMap.reference").mapTypes.set('papiro_style', papirostyledMap);
		}


}

})(jQuery);