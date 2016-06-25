if (!Array.prototype.indexOf) {
    Array.prototype.indexOf = function (searchElement /*, fromIndex */ ) {
        "use strict";
        if (this == null) {
            throw new TypeError();
        }
        var t = Object(this);
        var len = t.length >>> 0;
        if (len === 0) {
            return -1;
        }
        var n = 0;
        if (arguments.length > 1) {
            n = Number(arguments[1]);
            if (n != n) { // shortcut for verifying if it's NaN
                n = 0;
            } else if (n != 0 && n != Infinity && n != -Infinity) {
                n = (n > 0 || -1) * Math.floor(Math.abs(n));
            }
        }
        if (n >= len) {
            return -1;
        }
        var k = n >= 0 ? n : Math.max(len - Math.abs(n), 0);
        for (; k < len; k++) {
            if (k in t && t[k] === searchElement) {
                return k;
            }
        }
        return -1;
    }
}

function isNumber(n) {
  return !isNaN(parseFloat(n)) && isFinite(n);
}

(function(e) {
	e(document).ready(function() {

		var acquiaSlider = {
			domain : 'acquiaSlider',
			uploadInput : null,
			dragContainer : null,
			dragIndex : 0,
			newIndex : 0,
			timeout : 0,
			counter : 0,
			container : 0,
			g_startTime : 500,
			g_stepTime : 300,
			g_slideTime : 0,
			initArrCaptionClasses : 0,
			rulewidth : 7,
			activePanel : jQuery(".ac-layer-box.active"),

			selectMainTab : function(el) {
				// Remove highlight from the other tabs
				e('#ac-main-nav-bar a').removeClass('active');

				// Highlight selected tab
				e(el).addClass('active');

				// Hide other pages
				e('#ac-pages .ac-page').removeClass('active');

				// Show selected page
				e('#ac-pages .ac-page').eq( e(el).index() ).addClass('active')
			},

			addLayer : function() {

				// Clone the sample layer page
				var clone = e('#ac-sample > div').clone();

				// Append to place
				clone.appendTo('#ac-layers');

				// Close other layers
				e('#ac-layer-tabs a').removeClass('active');

				// Get layer index
				var index = clone.index();

				// Add layer tab
				var tab = e('<a href="#">Slide #'+(index+1)+'<span class="ac-icon-layer-remove">x</span></a>').insertBefore('#ac-add-layer');

				// Open new layer
				tab.click();

				// Add sortables
				acquiaSlider.addSortables();

				// Generate preview
				acquiaSlider.generatePreview(index);
			},

			removeLayer : function(el) {

				if(confirm('Are you sure you want to remove this slide?')) {

					// Get menu item
					var item = e(el).parent();

					// Get layer
					var layer = e(el).closest('#ac-layer-tabs').next().children().eq( item.index() );

					// Open next or prev layer
					if(layer.next().length > 0) {
						item.next().click();

					} else if(layer.prev().length > 0) {
						item.prev().click();
					}

					// Remove menu item
					item.remove();

					// Remove the layer
					layer.remove();

					// Reindex layers
					acquiaSlider.reindexLayers();
				}
			},

			selectLayer : function(el) {
				
				// Close other layers
				e('#ac-layer-tabs a').removeClass('active');
				e('#ac-layers .ac-layer-box').removeClass('active');

				// Open new layer
				e(el).addClass('active');
				e('#ac-layers .ac-layer-box').eq( e(el).index() ).addClass('active');

				// Open first sublayer
				e('#ac-layers .ac-layer-box').eq( e(el).index() ).find('.ac-sublayers td:first').click();

				// Update preview
				acquiaSlider.generatePreview( e(el).index() );

				// Stop preview
				acquiaSlider.stop();
			},

			duplicateLayer : function(el) {

				// Clone fix
				acquiaSlider.cloneFix();

				// Get layer index
				var index = e(el).closest('.ac-layer-box').index();

				// Append new tab
				e('<a href="#">Slide #0<span>x</span></a>').insertBefore('#ac-layer-tabs a:last');

				// Rename tab
				acquiaSlider.reindexLayers();

				// Clone layer
				var clone = e(el).closest('.ac-layer-box').clone();

				// Append new layer
				clone.appendTo('#ac-layers');

				// Remove active class if any
				clone.removeClass('active');

				// Add sortables
				acquiaSlider.addSortables();


			},

			addSublayer : function(el) {
				// Assign start time
				var time = acquiaSlider.getNextTime(e(el).closest('.ac-layer-box').index());

				// Get clone from sample
				var clone = e('#ac-sample .ac-sublayers > tr').clone();

				// Appent to place
				clone.appendTo( e(el).prev().find('.ac-sublayers') );

				// Get sublayer index
				var index = clone.index();

				// Rewrite sublayer number
				clone.find('.ac-sublayer-number').html( index + 1);
				clone.find('.ac-sublayer-title').val('Layer #' + (index + 1) );
				clone.find('input[name="start"]').val(time);

				// Open it
				clone.click();
			},

			selectSubLayer : function(el) {

				if(e(el).index() == e(el).parent().children('.active:first').index() ) {
					return;
				}

				// Close other sublayers
				e(el).parent().children().removeClass('active');

				// Open the new one
				e(el).addClass('active');
			},

			selectSublayerPage : function(el) {

				// Close previous page
				e(el).parent().children().removeClass('active');
				e(el).parent().next().find('.ac-sublayer-page').removeClass('active');

				// Open the selected one
				e(el).addClass('active');
				e(el).parent().next().find('.ac-sublayer-page').eq( e(el).index() ).addClass('active');
			},

			removeSublayer : function(el) {

				if(!confirm('Are you sure you want to remove this layer?')) {
					return;
				}

				// Get sublayer
				var sublayer = e(el).closest('tr');

				// Get layer index
				var layer = e(el).closest('.ac-layer-box');

				// Open the next or prev sublayer
				if(sublayer.next().length > 0) {
					sublayer.next().click();

				} else if(sublayer.prev().length > 0) {
					sublayer.prev().click();
				}

				// Remove menu item
				e(el).remove();

				// Remove sublayer
				sublayer.remove();

				// Update preview
				acquiaSlider.generatePreview( layer.index() );
			},

			highlightSublayer : function(el) {

				if(e(el).prop('checked') == true) {

					// Deselect other checkboxes
					e('.ac-highlight input').not(el).prop('checked', false);

					// Restore sublayers in the preview
					e(el).closest('.ac-layer-box').find('.draggable').children().css({ opacity : 0.5 });

					// Get element index
					var index = e(el).closest('tr').index();

					// Highlight selected one
					e(el).closest('.ac-layer-box').find('.draggable').children().eq(index).css({ zIndex : 1000, opacity : 1 });

				} else {

					// Restore sublayers in the preview
					e(el).closest('.ac-layer-box').find('.draggable').children().each(function(index) {
						e(this).css({ zIndex : 10 + index });
						e(this).css('opacity', 1);
					});
				}
			},

			eyeSublayer : function(el) {

				if(e(el).hasClass('active')) {

					e(el).removeClass('active');
				} else {
					e(el).addClass('active');
				}

				// Update preview
				acquiaSlider.generatePreview( e('.ac-box.active').index() );
			},

			lockSublayer : function(el) {

				if(e(el).hasClass('active')) {
					e(el).removeClass('active');
				} else {
					e(el).addClass('active');
				}

				// Update preview
				acquiaSlider.generatePreview( e('.ac-box.active').index() );
			},

			duplicateSublayer : function(el) {
				// Assign start time
				var time = acquiaSlider.getNextTime(e(el).closest('.ac-layer-box').index());
				
				// Clone fix
				acquiaSlider.cloneFix();

				// Clone sublayer
				var clone = e(el).closest('.ac-sublayer-wrapper').closest('tr').clone();

				// Remove active class
				clone.removeClass('active');

				// Append
				clone.appendTo( e(el).closest('.ac-sublayers')  );

				// Rename sublayer
				clone.find('.ac-sublayer-title').val( clone.find('.ac-sublayer-title').val() + ' copy' );
				acquiaSlider.reindexSublayers( e(el).closest('.ac-layer-box') );

				// Update preview
				acquiaSlider.generatePreview( e(el).closest('.ac-layer-box').index() );
				
				clone.find('input[name="start"]').val(time);

			},

			skipSublayer : function(el) {

				acquiaSlider.generatePreview( e(el).closest('.ac-layer-box').index()  );
			},

			selectMediaType : function(el) {

				// Remove highlight from the others
				e(el).parent().children().removeClass('active');

				// Highlight the selected one
				e(el).addClass('active');

				// Deselect old elements
				e(el).closest('.ac-sublayer-basic').find('select option').attr('selected', false);

				// Change the select option
				var option = e(el).closest('.ac-sublayer-basic').find('select option').eq( e(el).index() ).prop('selected', true);
				
				e(el).closest('.ac-sublayer-basic').find('.layer-content-items .ac-item').hide();

				// Show / hide image upload field
				if(option.val() == 'img') {
					e(el).closest('.ac-sublayer-basic').find('.layer-content-items .ac-image-uploader').show();
				}else if(option.val() == 'video') {
					e(el).closest('.ac-sublayer-basic').find('.layer-content-items .ac-video-data').show();
				}else {
					e(el).closest('.ac-sublayer-basic').find('.layer-content-items .ac-html-code').show();
				}
				
			},

			didSelectMediaType : function(el) {
				acquiaSlider.selectMediaType(el);
				acquiaSlider.generatePreview( e(el).closest('.ac-layer-box').index() );
			},

			setCallbackBoxesWidth : function() {

				e('.ac-callback-box').width( (e('.wrap').width() - 26) / 3);
			},

			willGeneratePreview : function(index) {
				clearTimeout(acquiaSlider.timeout);
				acquiaSlider.timeout = setTimeout(function() {

					if(index == -1) {
						e('#ac-layers .ac-layer-box').each(function( index ) {
							acquiaSlider.generatePreview(index);
						});
					} else {
						acquiaSlider.generatePreview(index);
					}
				}, 1000);
			},

			generatePreview : function(index) {

				// Get preview element
				var preview = e('.ac-preview').eq( index + 1 );

				// Get the draggable element
				var draggable = preview.find('.draggable');
				
				// Assign contaier
				acquiaSlider.container = draggable;
				
				// Get sizes
				var width = e('.ac-settings input[name="width"]').val();
				
				var fullwidth = e('.ac-settings input[name="fullwidth"]').prop('checked');
				if (fullwidth === true) {
					width = '100%';
				}
				var height = e('.ac-settings input[name="height"]').val();

				// Set sizes
				preview.add(draggable).css({ width : width, height : height });
				preview.parent().css({ width : width });

				// Get backgrounds
				var bgColor = e('.ac-settings input[name="background_color"]').val();
				var bgImage = e('.ac-settings input[name="background_image"]').val();

				// Set backgrounds
				if(bgColor != '') {
					preview.css({ backgroundColor : bgColor });
				} else {
					preview.css({ backgroundColor : 'transparent' });
				}

				if(bgImage != '') {
					preview.css({ backgroundImage : 'url('+bgImage+')' });
				} else {
					preview.css({ backgroundImage : 'none' });
				}

				// Get yourLogo
				var yourLogo = e('.ac-settings input[name="yourlogo"]').val();
				var yourLogoStyle = e('.ac-settings input[name="yourlogostyle"]').val();

				// Remove previous yourLogo
				preview.parent().find('.yourlogo').remove();

				// Set yourLogo
				if(yourLogo && yourLogo != '') {
					var logo = e('<img src="'+yourLogo+'" class="yourlogo">').prependTo( e(preview).parent() );
					logo.attr('style', yourLogoStyle);

					var oL = oR = oT = oB = 'auto';

					if( logo.css('left') != 'auto' ){
						var logoLeft = logo[0].style.left;
					}
					if( logo.css('right') != 'auto' ){
						var logoRight = logo[0].style.right;
					}
					if( logo.css('top') != 'auto' ){
						var logoTop = logo[0].style.top;
					}
					if( logo.css('bottom') != 'auto' ){
						var logoBottom = logo[0].style.bottom;
					}

					if( logoLeft && logoLeft.indexOf('%') != -1 ){
						oL = width / 100 * parseInt( logoLeft ) - logo.width() / 2;
					}else{
						oL = parseInt( logoLeft );
					}

					if( logoRight && logoRight.indexOf('%') != -1 ){
						oR = width / 100 * parseInt( logoRight ) - logo.width() / 2;
					}else{
						oR = parseInt( logoRight );
					}

					if( logoTop && logoTop.indexOf('%') != -1 ){
						oT = height / 100 * parseInt( logoTop ) - logo.height() / 2;
					}else{
						oT = parseInt( logoTop );
					}

					if( logoBottom && logoBottom.indexOf('%') != -1 ){
						oB = height / 100 * parseInt( logoBottom ) - logo.height() / 2;
					}else{
						oB = parseInt( logoBottom );
					}

					logo.css({
						left : oL,
						right : oR,
						top : oT,
						bottom : oB
					});
				}

				// Get layer background
				var background = e('#ac-layers .ac-layer-box').eq(index).find('input[name="background"]').val();

				// Get layer background color
				var bgColor = e('#ac-layers .ac-layer-box').eq(index).find('input[name="bgColor"]').val();
				bgColor = bgColor !='' ? bgColor : 'transparent';
				
				// Set layer background
				if(background != '' || background != undefined) {
					draggable.css({
						backgroundImage : 'url('+background+')',
						backgroundPosition : 'center center',
						backgroundColor : bgColor,
					});
				} else {
					draggable.css({
						backgroundImage : 'none',
						backgroundColor : bgColor,
					});
				}

				// Empty draggable
				draggable.children().remove();
				
				// Iterate over the sublayers
				e('#ac-layers .ac-layer-box').eq(index).find('.ac-sublayers > tr').each(function() {

					// Get sublayer type
					var type = e(this).find('select[name="type"] option:selected').val()

					// Get image URL
					var url = e(this).find('input[name="image"]').val();

					// Skip?
					var skip = e(this).find('input[name="skip"]').prop('checked');

					// Visibility
					var visibility = e(this).find('.ac-icon-eye').hasClass('active');

					// Lock
					var lock = e(this).find('.ac-icon-lock').hasClass('active');

					// WordWrap
					var wordWrap = e(this).find('input[name="wordwrap"]').prop('checked');

					// Get attribtes
					var id = e(this).find('input[name="id"]').val();
					var classes = 'tp-caption';
					classes += e(this).find('input[name="class"]').val() ? ' ' + e(this).find('input[name="class"]').val() : '';

					// Append element
					if(skip || visibility) {
						e('<div>').appendTo(draggable);
						return true;

					}
					
					/* + START
					------------------------------------------------------------*/
					var fullWidthVide = false;
					//add layer specific html
					switch(type){
						case "img":
							if(url != '') {
								var item = e('<img src="'+url+'">').appendTo(draggable);
							} else {
								var item =e('<div>').appendTo(draggable);
							}
						break;
							// Append the element
							var item = e('<div>').appendTo(draggable);
							item.html(html);
						break;
						
						default:
							// Get HTML content
							var html = e(this).find('textarea[name="html"]').val();

							// Append the element
							var item =e('<'+type+'>').appendTo(draggable);

							// Set HTML
							if(html != '') {
								item.html(html);
							}
						break;
					}
					/* + END
					------------------------------------------------------------*/

					if(lock) {
						item.addClass('disabled');
					}

					// Abs pos
					item.css('position', 'absolute');

					// Get style settings
					var top = e(this).find('input[name="top"]').val();
					var left = e(this).find('input[name="left"]').val();
					var custom = e(this).find('textarea[name="style"]').val();

					// Styles
					var styles = {};
					e(this).find('.ac-sublayer-style input.auto').each(function() {
						if(e(this).val() != '') {
							if(isNumber(e(this).val())) {
								styles[e(this).attr('name')] = ''+e(this).val()+'px';
							} else {
								styles[e(this).attr('name')] = e(this).val();
							}
						}
					});

					item.attr('style', custom);

					// Set predefined styles
					item.css(styles);

					// Apply attributes
					item.attr('id', id);
					item.addClass(classes);

					// Word wrap
					if(wordWrap == false) {
						item.css('white-space', 'nowrap');
					}

					var pt = isNaN( parseInt( item.css('padding-top') ) ) ? 0 : parseInt( item.css('padding-top') );
					var pl = isNaN( parseInt( item.css('padding-left') ) ) ? 0 : parseInt( item.css('padding-left') );
					var bt = isNaN( parseInt( item.css('border-top-width') ) ) ? 0 : parseInt( item.css('border-top-width') );
					var bl = isNaN( parseInt( item.css('border-left-width') ) ) ? 0 : parseInt( item.css('border-left-width') );

					var setPositions = function(){
						top = top != '' ? '' + top : '0px';
						left = left != '' ? '' + left : '0px';
						// Position the element
						if(top.indexOf('%') != -1) {
							item.css({ top : draggable.height() / 100 * parseInt( top ) - item.height() / 2 - pt - bt });
						} else {
							item.css({ top : parseInt(top) });
						}

						if(left.indexOf('%') != -1) {
							item.css({ left : draggable.width() / 100 * parseInt( left ) - item.width() / 2 - pl - bl });
						} else {
							item.css({ left : parseInt(left) });
						}
					};

					if( item.is('img') ){

						item.load(function(){
							setPositions();
						}).attr('src',item.attr('src') );
					}else{
						if (type == 'video' && fullWidthVide == true) {
							top = '';
							left = '';
						}
						setPositions();
					}

					// Z-index
					item.css({ zIndex : 10 + item.index() });
				});


				// Add draggable
				acquiaSlider.addDraggable();
			},

			openMediaLibrary : function() {

				// Bind upload button to show media uploader
				e('.ac-upload').live('click', function() {
					uploadInput = this;
					
					Drupal.media.popups.mediaBrowser(function(t) {
					
						var mediaFile = t[0];
						e(uploadInput).val(mediaFile.url);
						e(uploadInput).prev('.fid').val(mediaFile.fid);

						// Generate preview
						e('#ac-layers .ac-layer-box').each(function( index ) {
							acquiaSlider.generatePreview(index);
						});
						
						if(e(uploadInput).attr('name') == 'image'){
							e('.ac-sublayer-pages .ac-sublayer-page').each(function(index){
								tmp_ls = e(this);
								tmp_ls.find('.ac-upload').attr('id', 'ac-upload-img'+index);
							});
						}
						
						// Image sublayer
						if(e(uploadInput).is('input[name="image"]')) {
							e(uploadInput).prev().prev('img').attr('src', mediaFile.url);
						}
						
					});
						return false;
				});

			},

			insertUpload : function() {

				// Bind an event to image url insert
				window.send_to_editor = function(html) {

					// Get the image URL
					var img = e('img',html).attr('src');

					// Set image URL
					e(uploadInput).val( img );

					// Generate preview
					e('#ac-layers .ac-layer-box').each(function( index ) {
						acquiaSlider.generatePreview(index);
					});

					// Image sublayer
					if(e(uploadInput).is('input[name="image"]')) {
						e(uploadInput).prev().attr('src', img);
					}
				};
			},

			addSortables : function() {

				// Bind sortable function
				e('.ac-sublayer-sortable').sortable({
					axis : 'y',
					helper: function(ev, tr) {
						var $originals = tr.children();
						var $helper = tr.clone();
						$helper.children().each(function(index) {
							// Set helper cell sizes to match the original sizes
							e(this).width($originals.eq(index).width());
						});
						return $helper;
					},
					sort : function(event, ui){
						acquiaSlider.dragContainer = e('.ui-sortable-helper').closest('.ac-layer-box');
					},
					stop : function(event, ui) {
						acquiaSlider.generatePreview( acquiaSlider.dragContainer.index() );
						acquiaSlider.reindexSublayers( acquiaSlider.dragContainer );
								},
								containment : 'parent',
					tolerance : 'pointer'
						});
			},

			addLayerSortables : function() {

				// Bind sortable function
				e('#ac-layer-tabs').sortable({
					//axis : 'x',
					start : function() {
						acquiaSlider.dragIndex = e('.ui-sortable-placeholder').index() - 1;
					},
					change: function() {
						e('.ui-sortable-helper').addClass('moving');
					},
					stop : function(event, ui) {

						// Get old index
						var oldIndex = acquiaSlider.dragIndex;

						// Get new index
						var index = e('.moving').index();

						if( index > -1 ){

							// Rearraange layer pages

							if(index == 0) {
								e('#ac-layers .ac-layer-box').eq(oldIndex).prependTo('#ac-layers');
							}else{
								var layerObj = e('#ac-layers .ac-layer-box').eq(oldIndex);
								e('#ac-layers .ac-layer-box').eq(oldIndex).remove();

								layerObj.insertAfter('#ac-layers .ac-layer-box:eq('+(index-1)+')');
							}
						}

						e('.moving').removeClass('moving');

						// Reindex layers
						acquiaSlider.reindexLayers();

						// Sortable
						acquiaSlider.addSortables();
								},
								containment : 'parent',
					tolerance : 'pointer',
					items : 'a:not(.unsortable)'
						});
			},

			addDraggable : function() {

				// Add dragable
				e('.draggable').children().draggable({
							drag : function() {

								acquiaSlider.dragging();
							},
							stop : function() {

								acquiaSlider.dragging();
							}
						});

						e('.draggable .disabled').draggable('disable');
			},

			dragging : function() {

				// Get positions
				var top = parseInt(e('.ui-draggable-dragging').position().top);
				var left = parseInt(e('.ui-draggable-dragging').position().left);

				// Get index
				var wrapper = e('.ui-draggable-dragging').closest('.ac-layer-box');
				var index = e('.ui-draggable-dragging').index();

				// Set positions
				wrapper.find('input[name="top"]').eq(index).val(top + 'px');
				wrapper.find('input[name="left"]').eq(index).val(left + 'px');
			},

			selectDragElement : function(el) {

				e(el).closest('.ac-layer-box').find('.ac-sublayers > tr').eq( e(el).index() ).click();
				e(el).closest('.ac-layer-box').find('.ac-sublayers > tr').eq( e(el).index() ).find('.ac-sublayer-nav a:eq(1)').click();
			},

			reindexSublayers : function(el) {

				e(el).find('.ac-sublayers > tr').each(function(index) {
					// Reindex sublayer number
					e(this).find('.ac-sublayer-number').html( index + 1 );

					// Reindex sublayer title if it is untoched
					if(
						e(this).find('.ac-sublayer-title').val().indexOf('Sublayer') != -1 &&
						e(this).find('.ac-sublayer-title').val().indexOf('Layer') != -1 &&
						e(this).find('.ac-sublayer-title').val().indexOf('copy') == -1
					) {
						e(this).find('.ac-sublayer-title').val('Layer #' + (index + 1) );
					}
				});
			},

			reindexLayers : function() {
				e('#ac-layer-tabs a:not(.unsortable)').each(function(index) {
					e(this).html('Slide #' + (index + 1) + '<span>x</span>');
				});
			},

			play : function( index ) {

				// Get acquiaSlider contaier
				var previewBox = e('#ac-layers .ac-layer-box').eq(index).find('.ac-real-time-preview');

				// Stop
				if(previewBox.children().length > 0) {
					// Set edit state
					e('input[name="slider_edit"]').val("1");
					e('input[name="slider_play"]').val("0");
					
					e('#ac-layers .ac-layer-box').eq(index).find('.ac-preview').show();
					//acquiaSlider.find('.ac-container').acquiaSlider('stop'); STOP 
					previewBox.html('').hide();
					e('#ac-layers .ac-layer-box').eq(index).find('.ac-preview-button').html('Enter Preview').removeClass('playing');
					
					// Update preview
					acquiaSlider.generatePreview( index );

					// Stop preview
					acquiaSlider.stop();
					return;
				}

				// Show the acquiaSlider
				previewBox.show();
				previewBox = e('<div class="acquiaSlider">').appendTo(previewBox);
				previewBox.css({height : e('.ac-settings input[name="height"]').val()});
				// Hide the preview
				e('#ac-layers .ac-layer-box').eq(index).find('.ac-preview').hide();

				// Change button status
				e('#ac-layers .ac-layer-box').eq(index).find('.ac-preview-button').html('Exit Preview').addClass('playing');

				
				// Set Play state
				e('input[name="slider_edit"]').val("0");
				e('input[name="slider_play"]').val("1");

				// Iterate over the settings
				e('.ac-settings input:not(.nochange), .ac-settings select').each(function() {

					// Save original name attr to element's data
					e(this).data('name', e(this).attr('name') );

					// Rewrite the name attr
					e(this).attr('name', 'acquiaSlider[properties]['+e(this).attr('name')+']');
				});

				// Iterate over the layers
				e('#ac-layers .ac-layer-box').each(function(layer) {

					// Iterate over layer settings
					e(this).find('.ac-slide-options input, .ac-slide-options select').each(function() {

						// Save original name attr to element's data
						e(this).data('name', e(this).attr('name') );

						// Rewrite the name attr
						e(this).attr('name', 'acquiaSlider[layers]['+layer+'][properties]['+e(this).attr('name')+']');

					});

					// Iterate over the sublayers
					e(this).find('.ac-sublayers > tr').each(function(sublayer) {

						// JSON object for styles
						var styles = {};

						// Iterate over the sublayer properties
						e(this).find('input.auto').each(function() {

							if(e(this).val() != '') {
								styles[e(this).attr('name')] = e(this).val();
							}

							// Save original name attr to element's data
							e(this).data('name', e(this).attr('name') );

							// Remove name
							e(this).attr('name', '');
						});

						// Generate styles object
						e(this).find('.ac-sublayer-style input[name="styles"]').val( JSON.stringify(styles) );

						// Iterate over the sublayer properties
						e(this).find('input:not(.auto), select, textarea').each(function() {

							// Save original name attr to element's data
							e(this).data('name', e(this).attr('name') );

							// Rewrite the name attr
							e(this).attr('name', 'acquiaSlider[layers]['+layer+'][sublayers]['+sublayer+']['+e(this).attr('name')+']');
						});
					});
				});

				// Iterate over the callback functions
				e('.ac-callback-page textarea').each(function() {

					// Save original name attr to element's data
					e(this).data('name', e(this).attr('name') );

					// Rewrite the name attr
					e(this).attr('name', 'acquiaSlider[properties]['+e(this).attr('name')+']');
				});

				
				setTimeout(function() {
				
					$data = e('#ac-slider-form > input');
					// Iterate over the layers
					e('#ac-layers .ac-layer-box').each(function(layer) {

						// Reindex layerkey
						e(this).find('input[name="layerkey"]').val(layer);

						// Data to send
						$data = $data.add( e('#ac-layers .ac-layer-box').eq(layer).find('input, textarea, select') );
						$data = $data.add( e('.ac-settings').find('input, textarea, select') );
					});
					
					$data = $data.serialize();

					// Post layer
					jQuery.ajax({
						type : 'POST',
						data :$data,
						async : false,
						success : function(previewHTML) {
							previewBox.html(previewHTML);
							

							// Rewrote original name attr

							// Global settings
							e('.ac-settings input, .ac-settings select').each(function() {
								e(this).attr('name', e(this).data('name'));
							});

							// Layers
							e('#ac-layers .ac-layer-box').each(function(layer) {

								// Layer settings
								e(this).find('.ac-slide-options input, .ac-slide-options select').each(function() {
									e(this).attr('name', e(this).data('name'));
								});

								// Sublayers
								e(this).find('.ac-sublayers > tr').each(function(sublayer) {
									e(this).find('input, select, textarea').each(function() {
										e(this).attr('name', e(this).data('name'));
									});
								});
							});

							// Iterate over the callback functions
							e('.ac-callback-page textarea').each(function() {
								e(this).attr('name', e(this).data('name'));
							});
							
						}
					});
						
					
				}, 500);
			},

			stop : function() {
				
				// Set edit state
				e('input[name="slider_edit"]').val("1");
				e('input[name="slider_play"]').val("0");
				
				// Get acquiaSlider contaier
				var previewBox = e('#ac-layers .ac-layer-box .ac-real-time-preview');

				// Stop the preview if any
				if(previewBox.children().length > 0) {

					// Show the editor
					e('#ac-layers .ac-layer-box .ac-preview').show();

					// Stop acquiaSlider
					//acquiaSliders.find('.ac-container').acquiaSlider('stop');

					// Empty and hide the Preview
					previewBox.html('').hide();

					// Rewrote the Preview button text
					e('#ac-layers .ac-layer-box .ac-preview-button').text('Enter Preview').removeClass('playing');
				}
			},

			save : function(el) {

				// Temporary disable submit button
				e('.ac-publish button').text('Saving ...').addClass('saving').attr('disabled', true);
				e('.ac-saving-warning').text('Please do not navigate away from this page while acquiaSlider WP saving your layers!');

				// Iterate over the settings
				e('.ac-settings input:not(.nochange), .ac-settings select').each(function() {

					// Save original name attr to element's data
					e(this).data('name', e(this).attr('name') );
					// Rewrite the name attr
					e(this).attr('name', 'acquiaSlider[properties]['+e(this).attr('name')+']');
				});

				// Iterate over the layers
				e('#ac-layers .ac-layer-box').each(function(layer) {

					// Iterate over layer settings
					e(this).find('.ac-slide-options input, .ac-slide-options select').each(function() {

						// Save original name attr to element's data
						e(this).data('name', e(this).attr('name') );

						// Rewrite the name attr
						e(this).attr('name', 'acquiaSlider[layers]['+layer+'][properties]['+e(this).attr('name')+']');

					});

					// Iterate over the sublayers
					e(this).find('.ac-sublayers > tr').each(function(sublayer) {

						// JSON object for styles
						var styles = {};

						// Iterate over the sublayer properties
						e(this).find('input.auto').each(function() {

							if(e(this).val() != '') {
								styles[e(this).attr('name')] = e(this).val();
							}

							// Save original name attr to element's data
							e(this).data('name', e(this).attr('name') );

							// Remove name
							e(this).attr('name', '');
						});

						// Generate styles object
						e(this).find('.ac-sublayer-style input[name="styles"]').val( JSON.stringify(styles) );

						// Iterate over the sublayer properties
						e(this).find('input:not(.auto), select, textarea').each(function() {

							// Save original name attr to element's data
							e(this).data('name', e(this).attr('name') );

							// Rewrite the name attr
							e(this).attr('name', 'acquiaSlider[layers]['+layer+'][sublayers]['+sublayer+']['+e(this).attr('name')+']');
						});
					});
				});


				// Reset layer counter
				acquiaSlider.counter = 0;
				
				setTimeout(function() {
				
					$data = e('#ac-slider-form > input');
					
					// Iterate over the layers
					e('#ac-layers .ac-layer-box').each(function(layer) {
						// Reindex layerkey
						e(this).find('input[name="layerkey"]').val(layer);

						// Data to send
						$data = $data.add( e('#ac-layers .ac-layer-box').eq(layer).find('input, textarea, select') );
						$data = $data.add( e('.ac-settings').find('input, textarea, select') );
					});
					$data = $data.serialize();
					// Post layer
					jQuery.ajax(e(el).attr('action'), {
						type : 'POST',
						data :$data,
						async : false,
						success : function(id) {

							// Give feedback
							e('.ac-publish button').text('Saved').removeClass('saving').addClass('saved');
							e('.ac-saving-warning').text('');

							// Re-enable the button
							setTimeout(function() {
								e('.ac-publish button').text('Save changes').attr('disabled', false).removeClass('saved');
							}, 2000);

							// Rewrote original name attr

								// Global settings
								e('.ac-settings input, .ac-settings select').each(function() {
									e(this).attr('name', e(this).data('name'));
								});

								// Layers
								e('#ac-layers .ac-layer-box').each(function(layer) {

									// Layer settings
									e(this).find('.ac-slide-options input, .ac-slide-options select').each(function() {
										e(this).attr('name', e(this).data('name'));
									});

									// Sublayers
									e(this).find('.ac-sublayers > tr').each(function(sublayer) {
										e(this).find('input, select, textarea').each(function() {
											e(this).attr('name', e(this).data('name'));
										});
									});
								});

								// Iterate over the callback functions
								e('.ac-callback-page textarea').each(function() {
									e(this).attr('name', e(this).data('name'));
								});

						}
					});
						
					
				}, 500);
			},

			cloneFix : function() {

				e('textarea').each(function() {
					e(this).text( e(this).val() );
				});

				// Select clone fix
				e('select').each(function() {

					// Get selected index
					var index = e(this).find('option:selected').index();

					// Deselect old options
					e(this).find('option').attr('selected', false);

					// Select the new one
					e(this).find('option').eq( index ).attr('selected', true);
				});
			},

			enableSliderViewResponsitiveFields : function(st) {
				//enable / disable responsitive fields
				if(st == 'responsitive'){	
					e(".responsitive-row").fadeIn();
					e(".responsitive-row input").prop("disabled","");
				}else{
					e(".responsitive-row").hide();
					e(".responsitive-row input").prop("disabled","disabled");
				}
				
				if (st == 'fullscreen') {
					e(".fullscreen_tr").fadeIn().find('input').prop("disabled","");
				}else {
					e(".fullscreen_tr").hide().find('input').prop("disabled","disabled");
				}
					
			},	

			enableSlideMargins : function(val) {
				//enable / disable responsitive fields
				if(val == 'center'){	
					e("#hor-margin").find('td').addClass('disabled').find('input').prop("disabled","disabled");;
				}else{
					e("#hor-margin").find('td').removeClass('disabled').find('input').prop("disabled","");;
				}
			},
			
			/* + START
			--------------------------------------------------------------*/
			/**
			 * init captions classes array (from the captions.css)
			 */
			initCaptionClasses : function(captionClasses){
				acquiaSlider.initArrCaptionClasses = jQuery.parseJSON(captionClasses);
			},

			bindAsController : function(selector) {
				// Checkbox event
				e('input[name="'+selector+'"]').next().click(function(ev){
				
					if( e(this).hasClass('on') ) {
						e('td[data-controller="'+selector+'"]').addClass('disabled').find('input, select').prop("disabled","disabled");
					} else {
						e('td[data-controller="'+selector+'"]').removeClass('disabled').find('input, select').prop("disabled","");
					}

				});
			
			},	

			/**
			 * get video layer object from video data
			 */
			getVideoObjLayer : function(videoData){
				var videoData = videoData;
				var objLayer = {
						type:"video",
						style : "",
						video_type: videoData.video_type,
						video_width:videoData.width,
						video_height:videoData.height,
						video_data:videoData
					};
				
				if(objLayer.video_type == "youtube" || objLayer.video_type == "vimeo"){
					objLayer.video_id = videoData.id;
					objLayer.video_title = videoData.title;
					objLayer.video_image_url = videoData.thumb_medium.url;
					objLayer.video_args = videoData.args;
				}
				
				//set sortbox text
				switch(objLayer.video_type){			
					case "youtube":
						objLayer.text = "Youtube: " + videoData.title;
					break;
					case "vimeo":
						objLayer.text = "Vimeo: " + videoData.title;
					break;
					case "html5":
						objLayer.text = "Html5 Video";
						objLayer.video_title = objLayer.text;
						objLayer.video_image_url = "";
						
						if(videoData.urlPoster != "")
							objLayer.video_image_url = videoData.urlPoster;
							
					break;
				}
				
				return(objLayer);
			},

			/**
			 * get video layer object from video data
			 */
			addLayerVideo : function(el, videoData){
				oObjLayer = acquiaSlider.getVideoObjLayer(videoData);
				
				e(el).closest('.ac-video-data').find('textarea[name="video_data"]').val(JSON.stringify(videoData));
				e(el).closest('.ac-video-data').find('img').attr('src', oObjLayer.video_image_url);
				
				// show edit/remove buttons
				e(el).closest('.ac-video-data').find('button.button_add_layer_video, p').hide();
				e(el).closest('.ac-video-data').find('button.button_edit_layer_video, button.button_del_layer_video').show().next('p').show();
				if (videoData.fullwidth == true) {
					e(el).closest('.ac-sublayer-pages').find('input[name="top"]').val("0px");
					e(el).closest('.ac-sublayer-pages').find('input[name="left"]').val("0px");
				}
				acquiaSlider.willGeneratePreview( e(el).closest('.ac-layer-box').index() );
			},

			/**
			 * get video layer object from video data
			 */
			deleteLayerVideo : function(el){

				e(el).closest('.ac-video-data').find('textarea[name="video_data"]').val('');
				var _img = e(el).closest('.ac-video-data').find('img');
				_img.attr('src', _img.data('src'));
				
				// show edit/remove buttons
				e(el).closest('.ac-video-data').find('button.button_edit_layer_video, button.button_del_layer_video, p').hide();
				e(el).closest('.ac-video-data').find('button.button_add_layer_video').show().next('p').show();
				
				acquiaSlider.willGeneratePreview( e(el).closest('.ac-layer-box').index() );
			},
			
			/**
			 * check / update full width video position and size
			 */
			checkUpdateFullwidthVideo : function(objLayer){
				if(objLayer.type != "video")
					return(objLayer);
				
				if(objLayer.video_data && objLayer.video_data.fullwidth && objLayer.video_data.fullwidth == true){
					objLayer.top = 0;
					objLayer.left = 0;
					objLayer.align_hor = "left";
					objLayer.align_vert = "top";
					objLayer.video_width = acquiaSlider.container.width();
					objLayer.video_height = acquiaSlider.container.height();
				}
						
				return(objLayer);
			},
			
			/**
			 * Update video fields of a sublayer
			 */
			updateVideoFields : function(el){
				var oObjLayer = acquiaSlider.getVideoObjLayer(jQuery.parseJSON(el.val()));
				e(el).closest('.ac-video-data').find('img').attr('src', oObjLayer.video_image_url);
				
				// show edit/remove buttons
				e(el).closest('.ac-video-data').find('button.button_add_layer_video, p').hide();
				e(el).closest('.ac-video-data').find('button.button_edit_layer_video, button.button_del_layer_video').show().next('p').show();
				
				acquiaSlider.willGeneratePreview( e(el).closest('.ac-layer-box').index() );
				
			},
			
			/**
			 * Set Auto complete on CSS captions
			 */
			setAutoCompleteCaptions : function(){
				e('.ac-sublayers input[name="class"]').autocomplete({
					source: acquiaSlider.initArrCaptionClasses,
					minLength:0,
					close: function(){
						acquiaSlider.willGeneratePreview( e(this).closest('.ac-layer-box').index() );
					}
				});
			},

		//======================================================
		//			Time Functions
		//======================================================	

		/**
		 * get next available time
		 */
		getNextTime : function(index){
			var maxTime = 0,
			layerTime = 0;
			
			e('#ac-layers .ac-layer-box').eq(index).find('.ac-sublayers > tr').each(function() {
				
				layerTime = e(this).find('input[name="start"]').val();
				layerTime = (layerTime) ? Number(layerTime) : 0;
				
				if(layerTime > maxTime)
						maxTime = layerTime;
			});

			var outputTime;
			if(maxTime == 0)
				outputTime = acquiaSlider.g_startTime;
			else
				outputTime = Number(maxTime) + Number(acquiaSlider.g_stepTime);
							
			return(outputTime);
		}

			/* + END
			--------------------------------------------------------------*/
		};

		e(document).ready(function() {
			// Main tab bar page select
			e('#ac-main-nav-bar a:not(.unselectable)').click(function(ev) {
				ev.preventDefault();
				acquiaSlider.selectMainTab( this );
			});

			// Generate preview if user resizes the browser
			e(window).resize(function(){
				acquiaSlider.willGeneratePreview( e('.ac-box.active').index() );
			});

			// Support menu
			e('#ac-main-nav-bar a.support').click(function(ev) {
				ev.preventDefault();
				e('#contextual-help-link').click();
			});

			// Settings: checkboxes
			//e('.ac-settings :checkbox, .ac-layer-box :checkbox:not(.noreplace), #dialog_video :checkbox').customCheckbox();

			// Checkbox event
			e(document).on('click', '.ac-checkbox', function(ev){

				// Prevent browers default submission
				ev.preventDefault();

				// Get checkbox
				var el = e(this).prev()[0];

				if( e(el).is(':checked') ) {
					e(el).prop('checked', false);
					e(this).removeClass('on').addClass('off');
				} else {
					e(el).prop('checked', true);
					e(this).removeClass('off').addClass('on');
				}

				// Trigger events
				e('#ac-layers').trigger( jQuery.Event('click', { target : el } ) );
				e(document).trigger( jQuery.Event('click', { target : el } ) );

			});

			e('input, select, textarea, .ac-checkbox').each(function(){
				if (typeof(e(this).attr('data-help')) !='undefined' && e(this).attr('data-help') !='') {
					e(this).addClass('tooltip').acquiaTooltip();
				}
			});
			
			e('.ac-colorpicker').acquiaColorPicker();

			// Generate preview
			e(window).load(function() {
				acquiaSlider.generatePreview( e('.ac-box.active').index() );
			});

			// Caption Classes
			acquiaSlider.initCaptionClasses(Drupal.settings.captionClasses);
			
			// Uploads
			acquiaSlider.openMediaLibrary();
			acquiaSlider.insertUpload();

			// Settings: width, height
			e('.ac-settings').find('input[name="width"], input[name="height"], input[name="fullscreen_offset_container"]').keyup(function() {
				acquiaSlider.willGeneratePreview( e('.ac-box.active').index() );
			});

			// Settings: backgroundColor
			e('.ac-settings input[name="background_color"]').keyup(function() {
				acquiaSlider.willGeneratePreview( e('.ac-box.active').index() );
			});

			// Settings: reset button
			e(document).on('click', '.ac-reset', function() {

				// Empty field
				e(this).prev().val('');

				// Generate preview
				acquiaSlider.generatePreview( e('.ac-box.active').index() );
			});

			// Settings: yourLogoStyle
			e('.ac-settings input[name="yourlogostyle"]').keyup(function() {
				acquiaSlider.willGeneratePreview( e('.ac-box.active').index() );
			});

			// Add layer
			e('#ac-add-layer').click(function(ev) {
				ev.preventDefault();
				acquiaSlider.addLayer();
				acquiaSlider.setAutoCompleteCaptions();

			});

			// Select layer
			e('#ac-layer-tabs').on('click', 'a:not(.unsortable)', function(ev) {
				ev.preventDefault();
				acquiaSlider.selectLayer(this);
			});

			// Duplicate layer
			e('#ac-layers').on('click', '.ac-layer-options-thead .duplicate', function(ev){
				ev.preventDefault();
				acquiaSlider.duplicateLayer(this);
			});

			// Add sublayer
			e('#ac-layers').on('click', '.ac-add-sublayer', function(ev) {
				ev.preventDefault();
				acquiaSlider.addSublayer(this);
			});

			// Remove layer
			e('#ac-layer-tabs').on('click', 'a span', function(ev) {
				ev.preventDefault();
				ev.stopPropagation();
				acquiaSlider.removeLayer(this);
			});

			// Select sublayer
			e('#ac-layers').on('click', '.ac-sublayers tr', function() {
				acquiaSlider.selectSubLayer(this);
			});

			// Sublayer pages
			e('#ac-layers').on('click', '.ac-sublayer-nav a:not(:last-child)', function(ev) {
				ev.preventDefault();
				acquiaSlider.selectSublayerPage(this);
			});

			// Remove sublayer
			e('#ac-layers').on('click', '.ac-sublayer-nav a:last-child', function(ev) {
				ev.preventDefault();
				acquiaSlider.removeSublayer(this);
			});

				
			// Highlight sublayer
			e('#ac-layers').on('click', '.ac-highlight input', function(ev) {
				ev.stopPropagation();
				acquiaSlider.highlightSublayer(this);
			});

			// Sublayer media type
			e('#ac-layers').on('click', '.ac-sublayer-types > span', function(ev) {
				ev.preventDefault();
				acquiaSlider.didSelectMediaType(this);
			});

			// Restore sublayer media type
			e('.ac-sublayer-basic select').each(function() {

				// Get selected element
				var index = e(this).find('option:selected').index();

				// Restore
				acquiaSlider.selectMediaType(e(this).parent().find('.ac-sublayer-types > span').eq(index));
			});

			// Sublayer: Style
			e('#ac-layers').on('keyup', '.ac-sublayer-style input, .ac-sublayer-style select, .ac-sublayer-style textarea', function() {
				acquiaSlider.willGeneratePreview( e(this).closest('.ac-layer-box').index() );
			});

			// Sublayer: WordWrap
			e('#ac-layers').on('click', '.ac-sublayers input[name="wordwrap"]', function() {
				acquiaSlider.generatePreview( e(this).closest('.ac-layer-box').index() );
			});

			// Sublayer: HTML
			e('#ac-layers').on('keyup', '.ac-sublayers textarea[name="html"]', function() {
				acquiaSlider.willGeneratePreview( e(this).closest('.ac-layer-box').index() );
			});

			// Sublayer: sortables, draggable, etc
			acquiaSlider.addSortables();
			acquiaSlider.addDraggable();
			acquiaSlider.setAutoCompleteCaptions();

			// Sublayer: skip
			e('#ac-layers').on('click', '.ac-sublayer-options input[name="skip"]', function() {
				acquiaSlider.skipSublayer(this);
			});

			// Preview
			e('#ac-layers').on('click', '.ac-preview-button', function(ev) {
				ev.preventDefault();
				acquiaSlider.play( e(this).closest('.ac-layer-box').index() );
			});

			// Preview drag element select
			e('#ac-layers').on('click', '.draggable > *', function() {
				acquiaSlider.selectDragElement(this);
			});

			// Save changes
			e('#button-save').click(function(ev) {
				ev.preventDefault();
				acquiaSlider.save(this);
			});

			// Callback boxes
			acquiaSlider.setCallbackBoxesWidth();
			e(window).resize(function() {
				acquiaSlider.setCallbackBoxesWidth();
			});


			// Show color picker on focus
			e('.color').focus(function() {
				e(this).next().slideDown();
			});

			// Show color picker on blur
			e('.color').blur(function() {
				e(this).next().slideUp();
			});

			// Eye icon for layers
			e('#ac-layers').on('click', '.ac-icon-eye', function(ev) {
				ev.stopPropagation();
				acquiaSlider.eyeSublayer(this);
			});

			// Lock icon for layers
			e('#ac-layers').on('click', '.ac-icon-lock', function(ev) {
				ev.stopPropagation();
				acquiaSlider.lockSublayer(this);
			});	
			
			// Duplicate sublayer
			e('#ac-layers').on('click', '.ac-icon-duplicate button', function(ev) {
				ev.preventDefault();
				acquiaSlider.duplicateSublayer(this);
			});
			
			// Change layer BG Color
			e('#ac-layers').on('keyup', 'input[name="bgColor"]', function(ev) {
				acquiaSlider.willGeneratePreview( e(this).closest('.ac-layer-box').index() );
			});	

			/* + START
			--------------------------------------------------------------*/
			// Responsitive Fields display
			e('select[name="slider_type"]').change( function(ev) {
				acquiaSlider.enableSliderViewResponsitiveFields(e(this).val());
			});
			acquiaSlider.enableSliderViewResponsitiveFields(e('select[name="slider_type"]').val());
			
			e('td').each(function(){
				if (ct = e(this).data('controller')) {
					acquiaSlider.bindAsController(ct);
					if( e('input[name="'+ct+'"]').next().hasClass('on') ) {
						e(this).removeClass('disabled').find('input, select').prop("disabled","");
					} else {
						e(this).addClass('disabled').find('input, select').prop("disabled","disabled");
					}
				}
			});
			
			// Responsitive Fields display
			e('select[name="position"]').change( function(ev) {
				acquiaSlider.enableSlideMargins(e(this).val());
			});
			acquiaSlider.enableSlideMargins(e('select[name="position"]').val());		

		});

	});

})(jQuery);