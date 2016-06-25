<?php
$uploadClass = 'ac-upload';
?>
<!-- [Sample layer box]-->
<div id="ac-sample" class='ac-admin raw-attach'>
	<div class="ac-box ac-layer-box">
		<!-- [Slide Options] -->
		<table>
			<thead class="ac-layer-options-thead">
				<tr>
          <td colspan="7">
            <span id="ac-icon-layer-options"></span>
            <h4>
              <?php print t('Slide Options') ?>
            </h4>
            <button class="button duplicate ac-layer-duplicate"><?php print t('Duplicate this slide') ?></button>
          </td>
				</tr>
			</thead>
			<tbody class="ac-slide-options">
				<tr>
					<td class="right"><?php print t('Slide options') ?></td>
					<td class="right"><?php print t('Image') ?></td>
					<td>
						<div class="reset-parent">
							<input type="hidden" name="background_fid" class="fid" value="">
							<input type="text" name="background" class="<?php print $uploadClass?>" value="" data-help="<?php print t('The slide image/background. Click into the field to open the Drupal Media Library to choose or upload an image.') ?>">
							<span class="ac-reset">x</span>
						</div>
					</td>

					<td class="right"><?php print t('background color') ?></td>
					<td>
						<div class="reset-parent">
							<input type="text" name="bgColor" class="auto ac-colorpicker" value="" data-help="<?php print t("The background color of slide. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF") ?>">
							<span class="ac-reset">x</span>
						</div>
					</td>

					<td class="right"><?php print t('Thumbnail') ?></td>
					<td>
						<div class="reset-parent">
							<input type="hidden" name="thumbnail_fid" class="fid" value="">
							<input type="text" name="thumbnail" class="<?php print $uploadClass?>" value="" data-help="<?php print t('The thumbnail image of this slide. Click into the field to open the Drupal Media Library to choose or upload an image. If you leave this field empty, the slide image will be used.') ?>">
							<span class="ac-reset">x</span>
						</div>
					</td>
				</tr>
         <tr>
            <td class="right"></td>
            <td class="right"><?php print t('Video') ?></td>
            <td colspan="5">
              <div class="reset-parent">
								<input type="hidden" name="video_fid" class="fid" value="">
                <input type="text" name="video" class="<?php print $uploadClass?>" value="" data-help="<?php print t('The slide Video. Click into the field to open the Drupal Media Library to choose or upload an video.') ?>">
                <span class="ac-reset">x</span>
              </div>
            </td>
          </tr>

          <tr>
            <td class="right"><?php print t('Link options') ?></td>
            <td class="right"><?php print t('Enable Link') ?></td>
            <td><input type="checkbox" name="enable_link" class="checkbox" data-help="<?php print t('Turn it on to enable link on image') ?>"></td>
            <td class="right" data-controller="enable_link"><?php print t('Link') ?></td>
            <td data-controller="enable_link"><input type="text" name="link" value="" data-help="<?php print t('A link to a url or a slide (you can use \'prev\' and \'next\' or slider number.)') ?>"></td>
            <td class="right notfirst" data-controller="enable_link"><?php print t('Link target') ?></td>
            <td data-controller="enable_link">
              <select name="link_open_in" data-help="<?php print t('You can control here the link behaviour: _self means the linked page will open in the current tab/window, _blank will create a new tab/window.') ?>">
                <option>_self</option>
                <option>_blank</option>
                <option>_parent</option>
                <option>_top</option>
              </select>
            </td>
          </tr>
          <tr>
            <td class="right"><?php print t('Misc') ?></td>
            <td class="right"><?php print t('Slide caption') ?></td>
            <td colspan="5">
              <textarea name="caption" cols="100" rows="5" data-help="<?php print t('Type here the caption of your slide. You can use any HTML codes in this field to insert other contents then text. This field is also shortcode-aware, so you can insert content from other plugins as well as video embed codes.') ?>"></textarea>
            </td>
          </tr>
			</tbody>
		</table>
		<!-- [Slide Preview] -->
		<table>
			<thead>
				<tr>
					<td>
						<span id="ac-icon-preview"></span>
						<h4><?php print t('Preview') ?></h4>
						<button class="button ac-preview-button"><?php print t('Enter Preview') ?></button>
					</td>
				</tr>
			</thead>
			<tbody>
				<tr>
					<td class="ac-preview-td">
						<div class="ac-preview-wrapper">
							<div class="ac-preview">
								<div class="draggable resizable ac-layer"></div>
							</div>
							<div class="ac-real-time-preview"></div>
						</div>
					</td>
				</tr>
			</tbody>
		</table>
		<!-- [Slide Sublayers] -->
	</div>
</div>



<!-- [Slider form] -->
<form action="<?php echo $_SERVER['REQUEST_URI'] ?>" method="post" class="wrap ac-admin" id="ac-slider-form">

  <input type="hidden" name="slid" value="<?php print $slid?>">
  <input type="hidden" name="slider_edit" value="1">
  <input type="hidden" name="slider_play" value="0">

	<!-- [Title] -->
	<div class="ac-icon-layers"></div>
	<h2>
		<?php print t('Edit this flexSlider') ?>
		<a href="<?php print url(SLIDER_LIST_PATH)?>" class="add-new-h2"><?php print t('Back to the list') ?></a>
	</h2>

	<!-- [Main menu bar] -->
	<div id="ac-main-nav-bar">
		<a href="#" class="settings"><?php print t('Global Settings') ?></a>
		<a href="#" class="layers active"><?php print t('Slides') ?></a>
		<a href="#" class="clear unselectable"></a>
	</div>

	<!-- [Pages] -->
	<div id="ac-pages">

		<!-- [Global Settings] -->
		<div class="ac-page ac-settings">

			<div id="post-body-content">
				<div id="titlediv">
					<div id="titlewrap">
						<input type="text" name="title" value="<?php echo $slider['properties']['title'] ?>" id="title" autocomplete="off" placeholder="<?php print t('Type your slider name here') ?>">
					</div>
				</div>
			</div>
			<div class="ac-box" id="global-settings">
				<h3 class="header"><?php print t('Global Settings') ?></h3>
				<table>
					<thead>
						<tr>
							<td colspan="7">
								<span id="ac-icon-basic"></span>
								<h4><?php print t('Slider Layout') ?></h4>
							</td>
						</tr>
					</thead>
					<tbody>
						<tr>
							<td class="right"></td>
							<td class="right" colspan="1"><?php print t('Slider Width') ?></td>
							<td colspan="5"><input type="text" name="width" value="<?php echo $slider['properties']['width'] ?>"> The slider width in pixel or percentage.</td>
						</tr>
            <tr>
             <td class="right"></td>
             <td class="right"><?php print t('Slides background color') ?></td>
             <td>
               <div class="reset-parent">
                 <input type="text" name="bgColor" class="auto ac-colorpicker" value="<?php echo isset($slider['properties']['bgColor']) ? $slider['properties']['bgColor'] : '' ?>" data-help="<?php print t("The background color of slide. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF") ?>">
                 <span class="ac-reset">x</span>
               </div>
             </td>
            </tr>
            <tr>
						  <td class="right"></td>
              <td class="right"><?php print t('Background image style') ?></td>
              <td colspan="5">
                <select name="bg_style">
                    <?php foreach(image_style_options() as $mn => $type):?>
                      <option value="<?php print $mn?>"<?php echo ($slider['properties']['bg_style'] == $mn) ? 'selected="selected"' : '' ?>><?php print $type ?></option>
                    <?php endforeach?>
                </select>
              </td>
            </tr>
            <tr>
						  <td class="right"></td>
              <td class="right"><?php print t('Thumbnail image style') ?></td>
              <td colspan="5">
                <select name="thumb_style">
                    <?php foreach(image_style_options() as $mn => $type):?>
                      <option value="<?php print $mn?>"<?php echo ($slider['properties']['thumb_style'] == $mn) ? 'selected="selected"' : '' ?>><?php print $type ?></option>
                    <?php endforeach?>
                </select>
              </td>
            </tr>

						<tr>
							<td class="right"></td>
							<td class="right"><?php print t('Full-width slider?') ?></td>
							<td colspan="5"><input type="checkbox" name="fullwidth" <?php echo ( isset($slider['properties']['fullwidth']) && $slider['properties']['fullwidth'] != 'false') ? 'checked="checked"' : '' ?>></td>
						</tr>
						<tr>
							<td class="right"></td>
							<td class="right"><?php print t('Compact style?') ?></td>
							<td colspan="5"><input type="checkbox" name="compact" <?php echo ( isset($slider['properties']['compact']) && $slider['properties']['compact'] != 'false') ? 'checked="checked"' : '' ?>></td>
						</tr>
						<tr>
							<td class="right"></td>
							<td class="right"><?php print t('Free caption style?') ?></td>
							<td colspan="5"><input type="checkbox" name="free_caption" <?php echo ( isset($slider['properties']['free_caption']) && $slider['properties']['free_caption'] == 'true') ? 'checked="checked"' : '' ?> data-help="<?php print t("turn it on if you wish to add HTML text in caption.")?>"></td>
						</tr>
					</tbody>
					
					<thead>
						<tr>
							<td colspan="7">
								<span id="ac-icon-general"></span>
								<h4><?php print t('General Settings') ?></h4>
							</td>
						</tr>
					</thead>
					<tr>
						<td class="right"></td>
						<td class="right"><?php print t('Slider animation') ?></td>
						<td>
							<select name="animation">
									<?php foreach(flexslider_animation_types() as $mn => $type):?>
										<option value="<?php print $mn?>"<?php echo ($slider['properties']['animation'] == $mn) ? 'selected="selected"' : '' ?>><?php print $type ?></option>
									<?php endforeach?>
							</select>
						</td>
						
						<td class="right"><?php print t('Easing') ?></td>
						<td>
							<select name="easing">
									<?php foreach(acquia_easing_types() as $mn => $type):?>
										<option value="<?php print $mn?>"<?php echo ($slider['properties']['easing'] == $mn) ? 'selected="selected"' : '' ?>><?php print $type ?></option>
									<?php endforeach?>
							</select>
						</td>
            
						<td class="right"><?php print t('direction') ?></td>
						<td>
							<select name="direction">
									<?php foreach(flexslider_directions() as $mn => $type):?>
										<option value="<?php print $mn?>"<?php echo ($slider['properties']['direction'] == $mn) ? 'selected="selected"' : '' ?>><?php print $type ?></option>
									<?php endforeach?>
							</select>
						</td>
  				</tr>
					
					<tr>
           	<td class="right"></td>
						<td class="right"><?php print t('Reverse') ?></td>
						<td><input type="checkbox" class="checkbox" name="reverse"<?php echo isset($slider['properties']['reverse']) && $slider['properties']['reverse'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print print t('if turned On the slider reverses the animation direction on each slide')?>"></td>
						
            <td class="right"><?php print t('Animation Loop') ?></td>
						<td><input type="checkbox" class="checkbox" name="animationLoop"<?php echo isset($slider['properties']['animationLoop']) && $slider['properties']['animationLoop'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print print t('Should the animation loop? If false, directionNav will received "disable" classes at either end')?>"></td>
           
            <td class="right"><?php print t('smooth Height') ?></td>
						<td><input type="checkbox" class="checkbox" name="smoothHeight"<?php echo isset($slider['properties']['smoothHeight']) && $slider['properties']['smoothHeight'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print print t('Allow height of the slider to animate smoothly in horizontal mode ?')?>"></td>
          </tr>
					
					<tr>
						<td class="right"></td>
						<td class="right"><?php print t('start At') ?></td>
						<td><input type="text" name="startAt" value="<?php echo $slider['properties']['startAt']?>" data-help="<?php print t('The slide that the slider should start on. Array notation (0 = first slide)')?>"></td>
	          
            <td class="right"><?php print t('slideshow?') ?></td>
						<td><input type="checkbox" class="checkbox" name="slideshow"<?php echo isset($slider['properties']['slideshow']) && $slider['properties']['slideshow'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print print t('Animate slider automatically?')?>"></td>
						
            <td class="right"><?php print t('slideshow Speed') ?></td>
						<td><input type="text" name="slideshowSpeed" value="<?php echo $slider['properties']['slideshowSpeed']?>" data-help="<?php print t('Set the speed of the slideshow cycling, in milliseconds')?>"></td>
					</tr>
					
					<tr>
            <td class="right"></td>
            <td class="right"><?php print t('animation Speed') ?></td>
						<td><input type="text" name="animationSpeed" value="<?php echo $slider['properties']['animationSpeed']?>" data-help="<?php print t('Set the speed of animations, in milliseconds')?>"></td>
            
            <td class="right"><?php print t('init Delay') ?></td>
						<td><input type="text" name="initDelay" value="<?php echo $slider['properties']['initDelay']?>" data-help="<?php print t('Set an initialization delay, in milliseconds')?>"></td>
            
            <td class="right"><?php print t('randomize') ?></td>
						<td><input type="checkbox" class="checkbox" name="randomize"<?php echo isset($slider['properties']['randomize']) && $slider['properties']['randomize'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print print t('Randomize slide order?')?>"></td>
					</tr>
          
					<thead>
						<tr>
							<td colspan="7">
								<span id="ac-icon-basic"></span>
								<h4><?php print t('Usability features') ?></h4>
							</td>
						</tr>
					</thead>
					<tr>
            <td class="right"></td>
            <td class="right"><?php print t('pause On Action') ?></td>
						<td><input type="checkbox" class="checkbox" name="pauseOnAction"<?php echo isset($slider['properties']['pauseOnAction']) && $slider['properties']['pauseOnAction'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print print t(' Pause the slideshow when interacting with control elements, highly recommended.')?>"></td>

            <td class="right"><?php print t('pause On Hover') ?></td>
						<td><input type="checkbox" class="checkbox" name="pauseOnHover"<?php echo isset($slider['properties']['pauseOnHover']) && $slider['properties']['pauseOnHover'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print print t('Pause the slideshow when hovering over slider, then resume when no longer hovering')?>"></td>
            
            <td class="right"><?php print t('use CSS3 transitions') ?></td>
						<td><input type="checkbox" class="checkbox" name="useCSS"<?php echo isset($slider['properties']['useCSS']) && $slider['properties']['useCSS'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print print t('Slider will use CSS3 transitions if available')?>"></td>
					</tr>
          
          <tr>
            <td class="right"></td>
            <td class="right"><?php print t('touch') ?></td>
						<td><input type="checkbox" class="checkbox" name="touch"<?php echo isset($slider['properties']['touch']) && $slider['properties']['touch'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print print t('Allow touch swipe navigation of the slider on touch-enabled devices.')?>"></td>

            <td class="right"><?php print t('video') ?></td>
						<td colspan="3"><input type="checkbox" class="checkbox" name="video"<?php echo isset($slider['properties']['video']) && $slider['properties']['video'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print print t('If using video in the slider, will prevent CSS3 3D Transforms to avoid graphical glitches')?>"></td>
         </tr>
          
					<thead>
						<tr>
							<td colspan="7">
                <span id="ac-icon-basic"></span>
								<h4><?php print t('Primary Controls') ?></h4>
							</td>
						</tr>
					</thead>
 					<tr>
            <td class="right"></td>
            <td class="right"><?php print t('Control Nav?') ?></td>
						<td><input type="checkbox" class="checkbox" name="controlNav"<?php echo isset($slider['properties']['controlNav']) && $slider['properties']['controlNav'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print print t('Create navigation for paging control of each clide? Note: Leave true for manualControls usage')?>"></td>
            
            <td class="right"><?php print t('Thumbnail Nav?') ?></td>
						<td><input type="checkbox" class="checkbox" name="thumbNav"<?php echo isset($slider['properties']['thumbNav']) && $slider['properties']['thumbNav'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print print t('Turned it on to enable Thumbnail navigation')?>"></td>

            <td class="right"><?php print t('Direction Nav?') ?></td>
						<td><input type="checkbox" class="checkbox" name="directionNav"<?php echo isset($slider['properties']['directionNav']) && $slider['properties']['directionNav'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print print t('Create navigation for previous/next navigation? (true/false)')?>"></td>
					</tr>
          <thead>
						<tr>
							<td colspan="7">
                <span id="ac-icon-basic"></span>
								<h4><?php print t('Carousel Options') ?></h4>
							</td>
						</tr>
					</thead>
 					<tr>
            <td class="right"></td>
            <td class="right"><?php print t('item Width') ?></td>
						<td><input type="text" name="itemWidth" value="<?php echo $slider['properties']['itemWidth']?>" data-help="<?php print t('Box-model width of individual carousel items, including horizontal borders and padding.')?>"> (px)</td>
            
            <td class="right"><?php print t('item Margin') ?></td>
						<td><input type="text" name="itemMargin" value="<?php echo $slider['properties']['itemMargin']?>" data-help="<?php print t('Margin between carousel items.')?>"> (px)</td>
            
            <td class="right"><?php print t('min Items') ?></td>
						<td><input type="text" name="minItems" value="<?php echo $slider['properties']['minItems']?>" data-help="<?php print t('Minimum number of carousel items that should be visible. Items will resize fluidly when below this.')?>"></td>
					</tr>
          <tr>
            <td class="right"></td>
            <td class="right"><?php print t('max Items') ?></td>
						<td><input type="text" name="maxItems" value="<?php echo $slider['properties']['maxItems']?>" data-help="<?php print t('Maxmimum number of carousel items that should be visible. Items will resize fluidly when above this limit.')?>"></td>
            
            <td class="right"><?php print t('move') ?></td>
						<td colspan="3"><input type="text" name="move" value="<?php echo $slider['properties']['move']?>" data-help="<?php print t('Number of carousel items that should move on animation. If 0, slider will move all visible items.')?>"></td>
					</tr>
          
				</table>            
			</div>
		</div>

		<!-- [Layers - Rendering Saved Layers] -->
		<div class="ac-page active">
      
			<div id="ac-layer-tabs">
       <?php if( isset($slider['layers']) && count($slider['layers']) > 0): ?>
          <?php foreach($slider['layers'] as $key => $layer) : ?>
            <?php $active = empty($key) ? 'active' : '' ?>
            <a href="#" class="<?php echo $active ?>">Slide #<?php echo ($key+1) ?><span>x</span></a>
            <?php endforeach; ?>
        	<?php else: ?>
            <a href="#" class="active">Slide #1<span>x</span></a>
        	<?php endif; ?>
				<a href="#" class="unsortable" id="ac-add-layer"><?php print t('Add new slide') ?></a>
				<div class="unsortable clear"></div>
			</div>
      
			<div id="ac-layers">
       <?php if( isset($slider['layers']) && count($slider['layers']) > 0): ?>
				<?php foreach($slider['layers'] as $key => $layer) : ?>
				<?php $active = empty($key) ? 'active' : '' ?>
				<div class="ac-box ac-layer-box <?php echo $active ?>">
					<table>
						<thead class="ac-layer-options-thead">
							<tr>
								<td colspan="7">
									<span id="ac-icon-layer-options"></span>
									<h4>
										<?php print t('Slide Options') ?>
									</h4>
									<button class="button duplicate ac-layer-duplicate"><?php print t('Duplicate this slide') ?></button>
								</td>
							</tr>
						</thead>
						<tbody class="ac-slide-options">
							<tr>
								<td class="right"><?php print t('Slide options') ?></td>
								<td class="right"><?php print t('Image') ?></td>
								<td>
									<div class="reset-parent">
										<input type="hidden" name="background_fid" class="fid" value="<?php echo $layer['properties']['background_fid']?>">
										<input type="text" name="background" class="<?php print $uploadClass?>" value="<?php echo $layer['properties']['background']?>" data-help="<?php print t('The slide image/background. Click into the field to open the Drupal Media Library to choose or upload an image.') ?>">
										<span class="ac-reset">x</span>
									</div>
								</td>
								
								<td class="right"><?php print t('background color') ?></td>
								<td>
									<div class="reset-parent">
										<input type="text" name="bgColor" class="auto ac-colorpicker" value="<?php echo $layer['properties']['bgColor']?>" data-help="<?php print t("The background color of slide. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF") ?>">
										<span class="ac-reset">x</span>
									</div>
								</td>
								
								<td class="right"><?php print t('Thumbnail') ?></td>
								<td>
									<div class="reset-parent">
										<input type="hidden" name="thumbnail_fid" class="fid" value="<?php echo $layer['properties']['thumbnail_fid']?>">
										<input type="text" name="thumbnail" class="<?php print $uploadClass?>" value="<?php echo $layer['properties']['thumbnail']?>" data-help="<?php print t('The thumbnail image of this slide. Click into the field to open the Drupal Media Library to choose or upload an image. If you leave this field empty, the slide image will be used.') ?>">
										<span class="ac-reset">x</span>
									</div>
								</td>
							</tr>
              
              <tr>
                <td class="right"></td>
                <td class="right"><?php print t('Video') ?></td>
                <td colspan="5">
                  <div class="reset-parent">
                    <input type="hidden" name="video_fid" class="fid" value="<?php print isset($layer['properties']['video_fid']) ? $layer['properties']['video_fid'] : ''?>">
                    <input type="text" name="video" class="<?php print $uploadClass?>" value="<?php print isset($layer['properties']['video']) ? $layer['properties']['video'] : ''?>" data-help="<?php print t('The slide Video. Click into the field to open the Drupal Media Library to choose or upload an video.') ?>">
                    <span class="ac-reset">x</span>
                  </div>
                </td>
              </tr>
              <tr>
                <td class="right"><?php print t('Link options') ?></td>
                <td class="right"><?php print t('Enable Link') ?></td>
                <td><input type="checkbox" data-help="<?php print t('Turn it on to enable link on image') ?>" name="enable_link"<?php print isset($layer['properties']['enable_link']) ? ' checked="checked" ' : ' ' ?>class="checkbox"></td>
                <td class="right" data-controller="enable_link"><?php print t('Link') ?></td>			
                <td data-controller="enable_link"><input type="text" name="link" value="<?php print isset($layer['properties']['link']) ? $layer['properties']['link'] : ''?>" data-help="<?php print t('A link to a url or a slide (you can use \'prev\' and \'next\' or slider number.)') ?>"></td>
                
                <td class="right notfirst" data-controller="enable_link"><?php print t('Link target') ?></td>
                <td data-controller="enable_link">
                  <select name="link_open_in" data-help="<?php _e('You can control here the link behaviour: _self means the linked page will open in the current tab/window, _blank will create a new tab/window.', REVSLIDER_TEXTDOMAIN) ?>">
                    <option<?php print (isset($layer['properties']['link_open_in']) && $layer['properties']['link_open_in'] == '_self') ? ' selected="selected"' : ''?>>_self</option>
                    <option<?php print (isset($layer['properties']['link_open_in']) && $layer['properties']['link_open_in'] == '_blank') ? ' selected="selected"' : ''?>>_blank</option>
                    <option<?php print (isset($layer['properties']['link_open_in']) && $layer['properties']['link_open_in'] == '_parent') ? ' selected="selected"' : ''?>>_parent</option>
                    <option<?php print (isset($layer['properties']['link_open_in']) && $layer['properties']['link_open_in'] == '_top') ? ' selected="selected"' : ''?>>_top</option>
                  </select>
                </td>
              </tr>
              <tr>
                <td class="right"><?php print t('Misc') ?></td>
                <td class="right"><?php print t('Slide caption') ?></td>
                <td colspan="5">
                  <textarea name="caption" cols="100" rows="5" data-help="<?php print t('Type here the caption of your slide. You can use any HTML codes in this field to insert other contents then text. This field is also shortcode-aware, so you can insert content from other plugins as well as video embed codes.') ?>"><?php print isset($layer['properties']['caption']) ? $layer['properties']['caption'] : ''?></textarea>
                </td>
              </tr>
						</tbody>
						
					</table>
					<table>
						<thead>
							<tr>
								<td>
									<span id="ac-icon-preview"></span>
									<h4><?php print t('Preview') ?></h4>
                  <button class="button ac-preview-button"><?php print t('Enter Preview') ?></button>
								</td>
							</tr>
						</thead>
						<tbody>
							<tr>
								<td class="ac-preview-td">
									<div class="ac-preview-wrapper">
										<div class="ac-preview">
											<div class="draggable resizable ac-layer"></div>
										</div>
										<div class="ac-real-time-preview"></div>
									</div>
								</td>
							</tr>
						</tbody>
					</table>
				</div>
				<?php endforeach; ?>
			<?php else: ?>
      <div class="ac-box ac-layer-box active">
      <table>
        <thead class="ac-layer-options-thead">
          <tr>
            <td colspan="7">
              <span id="ac-icon-layer-options"></span>
              <h4>
                <?php print t('Slide Options') ?>
              </h4>
              <button class="button duplicate ac-layer-duplicate"><?php print t('Duplicate this slide') ?></button>
            </td>
          </tr>
        </thead>
				
        <tbody class="ac-slide-options">
          <tr>
            <td class="right"><?php print t('Slide options') ?></td>
            <td class="right"><?php print t('Image') ?></td>
            <td>
              <div class="reset-parent">
								<input type="hidden" name="background_fid" class="fid" value="">
                <input type="text" name="background" class="<?php print $uploadClass?>" value="" data-help="<?php print t('The slide image/background. Click into the field to open the Drupal Media Library to choose or upload an image.') ?>">
                <span class="ac-reset">x</span>
              </div>
            </td>
						
            <td class="right"><?php print t('background color') ?></td>
            <td>
              <div class="reset-parent">
								<input type="text" name="bgColor" class="auto ac-colorpicker" value="" data-help="<?php print t("The background color of slide. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF") ?>">
                <span class="ac-reset">x</span>
              </div>
            </td>
						
            <td class="right"><?php print t('Thumbnail') ?></td>
            <td>
              <div class="reset-parent">
								<input type="hidden" name="thumbnail_fid" class="fid" value="">
                <input type="text" name="thumbnail" class="<?php print $uploadClass?>" value="" data-help="<?php print t('The thumbnail image of this slide. Click into the field to open the Drupal Media Library to choose or upload an image. If you leave this field empty, the slide image will be used.') ?>">
                <span class="ac-reset">x</span>
              </div>
            </td>
          </tr>

          <tr>
            <td class="right"></td>
            <td class="right"><?php print t('Video') ?></td>
            <td colspan="5">
              <div class="reset-parent">
								<input type="hidden" name="video_fid" class="fid" value="">
                <input type="text" name="video" class="<?php print $uploadClass?>" value="" data-help="<?php print t('The slide Video. Click into the field to open the Drupal Media Library to choose or upload an video.') ?>">
                <span class="ac-reset">x</span>
              </div>
            </td>
          </tr>
          
          <tr>
            <td class="right"><?php print t('Link options') ?></td>
            <td class="right"><?php print t('Enable Link') ?></td>
            <td><input type="checkbox" name="enable_link" class="checkbox" data-help="<?php print t('Turn it on to enable link on image') ?>"></td>
            <td class="right" data-controller="enable_link"><?php print t('Link') ?></td>			
            <td data-controller="enable_link"><input type="text" name="link" value="" data-help="<?php print t('A link to a url or a slide (you can use \'prev\' and \'next\' or slider number.)') ?>"></td>
            <td class="right notfirst" data-controller="enable_link"><?php print t('Link target') ?></td>
            <td data-controller="enable_link">
              <select name="link_open_in" data-help="<?php print t('You can control here the link behaviour: _self means the linked page will open in the current tab/window, _blank will create a new tab/window.') ?>">
                <option>_self</option>
                <option>_blank</option>
                <option>_parent</option>
                <option>_top</option>
              </select>
            </td>
          </tr>
          <tr>
            <td class="right"><?php print t('Misc') ?></td>
            <td class="right"><?php print t('Slide caption') ?></td>
            <td colspan="5">
              <textarea name="caption" cols="100" rows="5" data-help="<?php print t('Type here the caption of your slide. You can use any HTML codes in this field to insert other contents then text. This field is also shortcode-aware, so you can insert content from other plugins as well as video embed codes.') ?>"></textarea>
            </td>
          </tr>
        </tbody>
      </table>
      
      <table>
        <thead>
          <tr>
            <td>
              <span id="ac-icon-preview"></span>
              <h4><?php print t('Preview') ?></h4>
              <button class="button ac-preview-button"><?php print t('Enter Preview') ?></button>
            </td>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td class="ac-preview-td">
              <div class="ac-preview-wrapper">
                <div class="ac-preview">
                  <div class="draggable resizable ac-layer"></div>
                </div>
                <div class="ac-real-time-preview"></div>
              </div>
            </td>
          </tr>
        </tbody>
      </table>
    </div>
			<?php endif; ?>
			</div>
		</div>

	</div>

	<div class="ac-box ac-publish">
		<h3 class="header"><?php print t('Publish') ?></h3>
		<div class="inner">
			<button id="button-save" class="button-primary"><?php print t('Save changes') ?></button>
			<p class="ac-saving-warning"></p>
			<div class="clear"></div>
		</div>
	</div>
</form>

<!-- [/Slider form] -->
<script type="text/javascript">
  var pluginPath = '<?php print $plugins_url; ?>/';
  
	// Transition images
	var lsTrImgPath = '<?php print $plugins_url; ?>/img/';
</script>