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
					<td class="right"><?php print t('Slide background Image') ?></td>
					<td>
						<div class="reset-parent">
							<input type="hidden" name="background_fid" class="fid" value="">
							<input type="text" name="background" class="<?php print $uploadClass?>" value="" data-help="<?php print t('The slide image/background. Click into the field to open the Drupal Media Library to choose or upload an image.') ?>">
							<span class="ac-reset">x</span>
						</div>
					</td>
					
					<td class="right"><?php print t('Slide background color') ?></td>
					<td>
						<div class="reset-parent">
							<input type="text" name="bgColor" class="auto ac-colorpicker" value="" data-help="<?php print t("The background color of slide. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF") ?>">
							<span class="ac-reset">x</span>
						</div>
					</td>
          <td></td>
          <td></td>
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
		<table>
			<thead>
				<tr>
					<td>
						<span id="ac-icon-sublayers"></span>
						<h4><?php print t('Layers') ?></h4>
					</td>
				</tr>
			</thead>
			<tbody class="ac-sublayers ac-sublayer-sortable">
				<tr>
					<td>
						<div class="ac-sublayer-wrapper">
							<span class="ac-sublayer-number">1</span>
							<span class="ac-highlight"><input type="checkbox" class="noreplace"></span>
							<span class="ac-icon-eye"></span>
							<span class="ac-icon-lock"></span>
							<span class="ac-icon-duplicate"><button class="button duplicate" data-help="<?php print t('If you will use similar settings for other layers or you want to experiment on a copy, you can duplicate this layer.') ?>"><?php print t('Duplicate this layer') ?></button></span>
							<input type="text" name="subtitle" class="ac-sublayer-title" value="Layer #1">
							<div class="clear"></div>
							<div class="ac-sublayer-nav">
								<a href="#" class="active"><?php print t('Basic') ?></a>
								<a href="#"><?php print t('Style') ?></a>
								<a href="#"><?php print t('Attributes') ?></a>
								<a href="#" title="<?php print t('Remove this layer') ?>" class="remove">x</a>
							</div>
							<div class="ac-sublayer-pages">
								<div class="ac-sublayer-page ac-sublayer-basic active">
									<select name="type" class='no-fancy-select'>
										<option selected="selected">img</option>
										<option>div</option>
										<option>p</option>
										<option>span</option>
										<option>h1</option>
										<option>h2</option>
										<option>h3</option>
										<option>h4</option>
										<option>h5</option>
										<option>h6</option>
									</select>
	
									<div class="ac-sublayer-types">
										<span class="ac-type">
											<span class="ac-icon-img"></span><br>
											<?php print t('Image') ?>
										</span>
	
								
										<span class="ac-type">
											<span class="ac-icon-div"></span><br>
											<?php print t('Div') ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-p"></span><br>
											<?php print t('Paragraph') ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-span"></span><br>
											<?php print t('Span') ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-h1"></span><br>
											<?php print t('H1') ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-h2"></span><br>
											<?php print t('H2') ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-h3"></span><br>
											<?php print t('H3') ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-h4"></span><br>
											<?php print t('H4') ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-h5"></span><br>
											<?php print t('H5') ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-h6"></span><br>
											<?php print t('H6') ?>
										</span>
									</div>
									
									<div class="layer-content-items clearfix">
										<div class="ac-item ac-image-uploader">
											<img src="<?php echo file_create_url($plugins_url . '/img/transparent.png') ?>" alt="sublayer image">
											<input type="hidden" name="image_fid" class="fid" value="">
											<input type="text" name="image" class="<?php echo $uploadClass ?>" value="">
											<p>
												<?php print t('Click into this text field to open Drupal Media Library where you can upload new images or select previously used ones.') ?>
											</p>
										</div>
										
										<div class="ac-item ac-html-code">
											<h5><?php print t('Custom HTML content') ?></h5>
											<textarea name="html" cols="50" rows="5" data-help="<?php print t('Type here the contents of your layer. You can use any HTML codes in this field to insert other contents then text. This field is also shortcode-aware, so you can insert content from other plugins as well as video embed codes.') ?>"></textarea>
										</div>
									</div>
									
								</div>

								<div class="ac-sublayer-page ac-sublayer-style">
									<input type="hidden" name="styles">
									<table>
										<tbody>
											<tr>
												<td><?php print t('Layout & Positions') ?></td>
												<td class="right"><?php print t('Width') ?></td>
												<td><input type="text" name="width" class="auto" value="" data-help="<?php print t("You can set the width of your layer. You can use pixels, percents, or the default value 'auto'. Examples: 100px, 50% or auto") ?>"></td>
												<td class="right"><?php print t('Height') ?></td>
												<td><input type="text" name="height" class="auto" value="" data-help="<?php print t("You can set the height of your layer. You can use pixels, percents, or the default value 'auto'. Examples: 100px, 50% or auto") ?>"></td>
												<td class="right"><?php print t('Top') ?></td>
												<td><input type="text" name="top" value="20px" data-help="<?php print t("The layer position from the top of the slide. You can use pixels and percents. Examples: 100px or 50%. You can move your layers in the preview above with a drag n' drop, or set the exact values here.") ?>"></td>
												<td class="right"><?php print t('Left') ?></td>
												<td><input type="text" name="left" value="20px" data-help="<?php print t("The layer position from the left side of the slide. You can use pixels and percents. Examples: 100px or 50%. You can move your layers in the preview above with a drag n' drop, or set the exact values here.") ?>"></td>
											</tr>
											<tr>
												<td><?php print t('Padding') ?></td>
												<td class="right"><?php print t('Top') ?></td>
												<td><input type="text" name="padding-top" class="auto" value="" data-help="<?php print t('Padding on the top of the layer. Example: 10px') ?>"></td>
												<td class="right"><?php print t('Right') ?></td>
												<td><input type="text" name="padding-right" class="auto" value="" data-help="<?php print t('Padding on the right side of the layer. Example: 10px') ?>"></td>
												<td class="right"><?php print t('Bottom') ?></td>
												<td><input type="text" name="padding-bottom" class="auto" value="" data-help="<?php print t('Padding on the bottom of the layer. Example: 10px') ?>"></td>
												<td class="right"><?php print t('Left') ?></td>
												<td><input type="text" name="padding-left" class="auto" value="" data-help="<?php print t('Padding on the left side of the layer. Example: 10px') ?>"></td>
											</tr>
											<tr>
												<td><?php print t('Border') ?></td>
												<td class="right"><?php print t('Top') ?></td>
												<td><input type="text" name="border-top" class="auto" value="" data-help="<?php print t('Border on the top of the layer. Example: 5px solid #000') ?>"></td>
												<td class="right"><?php print t('Right') ?></td>
												<td><input type="text" name="border-right" class="auto" value="" data-help="<?php print t('Border on the right side of the layer. Example: 5px solid #000') ?>"></td>
												<td class="right"><?php print t('Bottom') ?></td>
												<td><input type="text" name="border-bottom" class="auto" value="" data-help="<?php print t('Border on the bottom of the layer. Example: 5px solid #000') ?>"></td>
												<td class="right"><?php print t('Left') ?></td>
												<td><input type="text" name="border-left" class="auto" value="" data-help="<?php print t('Border on the left side of the layer. Example: 5px solid #000') ?>"></td>
											</tr>
											<tr>
												<td><?php print t('Font') ?></td>
												<td class="right"><?php print t('Family') ?></td>
												<td><input type="text" name="font-family" class="auto" value="" data-help="<?php print t('List of your chosen fonts separated with a comma. Please use apostrophes if your font names contains white spaces. Example: Helvetica, Arial, sans-serif') ?>"></td>
												<td class="right"><?php print t('Size') ?></td>
												<td><input type="text" name="font-size" class="auto" value="" data-help="<?php print t('The font size in pixels. Example: 16px.') ?>"></td>
												<td class="right"><?php print t('Line-height') ?></td>
												<td><input type="text" name="line-height" class="auto" value="" data-help="<?php print t("The line height of your text. The default setting is 'normal'. Example: 22px") ?>"></td>
												<td class="right"><?php print t('Color') ?></td>
												<td><input type="text" name="color" class="auto ac-colorpicker" value="" data-help="<?php print t('The color of your text. You can use color names, hexadecimal, RGB or RGBA values. Example: #333') ?>"></td>
											</tr>
											<tr>
												<td><?php print t('Misc') ?></td>
												<td class="right"><?php print t('Background') ?></td>
												<td><input type="text" name="background" class="auto ac-colorpicker" value="" data-help="<?php print t("The background color of your layer. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF") ?>"></td>
												<td class="right"><?php print t('Rounded corners') ?></td>
												<td><input type="text" name="border-radius" class="auto" value="" data-help="<?php print t('If you want rounded corners, you can set here its radius. Example: 5px') ?>"></td>
												<td class="right"><?php print t('Word-wrap') ?></td>
												<td colspan="3"><input type="checkbox" name="wordwrap" class="checkbox" data-help="<?php print t('If you use custom sized layers, you have to enable this setting to wrap your text.') ?>"></td>
											</tr>
											<tr>
												<td><?php print t('Custom style settings') ?></td>
												<td class="right"><?php print t('Custom styles') ?></td>
												<td colspan="7"><textarea rows="5" cols="50" name="style" class="style" data-help="<?php print t('If you want to set style settings other then above, you can use here any CSS codes. Please make sure to write valid markup.') ?>"></textarea></td>
											</tr>
										</tbody>
									</table>
								</div>
								<div class="ac-sublayer-page ac-sublayer-attributes">
									<table>
										<tbody>
											<tr>
												<td class="right" rowspan="2"><?php print t('Attributes') ?></td>
												<td class="right"><?php print t('ID') ?></td>
												<td><input type="text" name="id" value="" data-help="<?php print t('You can apply an ID attribute on the HTML element of this layer to work with it in your custom CSS or Javascript code.') ?>"></td>
												<td class="right"><?php print t('Classes') ?></td>
												<td><input type="text" name="class" value="" data-help="<?php print t('You can apply classes on the HTML element of this layer to work with it in your custom CSS or Javascript code.') ?>"></td>
												<td class="right"><?php print t('Title') ?></td>
												<td colspan="3"><input type="text" name="title" value="" data-help="<?php print t('You can add a title to this layer which will display as a tooltip if someone holds his mouse cursor over the layer.') ?>"></td>
											</tr>
											<tr>
												<td class="right notfirst"><?php print t('Alt') ?></td>
												<td><input type="text" name="alt" value="" data-help="<?php print t('You can add an alternative text to your layer which is indexed by search engine robots and it helps people with certain disabilities.') ?>"></td>
												<td class="right"><?php print t('Rel') ?></td>
												<td colspan="5"><input type="text" name="rel" value="" data-help="<?php print t('Some plugin may use the rel attribute of a linked content, here you can specify it to make interaction with these plugins.') ?>"></td>
											</tr>
										</tbody>
									</table>
								</div>
							</div>
						
						</div>
					</td>
          </tr>
			</tbody>
		</table>
		<!-- [/Slide Sublayers] -->
		<a href="#" class="ac-add-sublayer"><?php print t('Add new layer') ?></a>
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
		<?php print t('Edit this Content Slider') ?>
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
							<td class="right" colspan="1"><?php print t('Slider height') ?></td>
							<td colspan="5"><input type="text" name="height" value="<?php echo $slider['properties']['height'] ?>"> The slider height in pixel</td>
						</tr>

            <tr>
						  <td class="right"></td>
              <td class="right"><?php print t('Global Background image') ?></td>
              <td>
               <div class="reset-parent">
                 <input type="hidden" name="bg_fid" class="fid" value="<?php echo isset($slider['properties']['bg_fid']) ? $slider['properties']['bg_fid'] : '' ?>">
                 <input type="text" name="bg" class="<?php print $uploadClass?>" value="<?php echo isset($slider['properties']['bg']) ? $slider['properties']['bg'] : ''?>" data-help="<?php print t('The default slider background image.') ?>">
                 <span class="ac-reset">x</span>
               </div>
              </td>
            </tr>
            <tr>
						  <td class="right"></td>
              <td class="right"><?php print t('Global Background image style') ?></td>
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
             <td class="right"><?php print t('Global background color') ?></td>
             <td>
               <div class="reset-parent">
                 <input type="text" name="bgColor" class="auto ac-colorpicker" value="<?php echo $slider['properties']['bgColor']?>" data-help="<?php print t("The background color of slide. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF") ?>">
                 <span class="ac-reset">x</span>
               </div>
             </td>
            </tr>
            
						<tr>
							<td class="right"></td>
							<td class="right"><?php print t('Full-width slider?') ?></td>
							<td colspan="5"><input type="checkbox" name="fullwidth" <?php echo ( isset($slider['properties']['fullwidth']) && $slider['properties']['fullwidth'] != 'false') ? 'checked="checked"' : '' ?>></td>
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
						<td class="right"><?php print t('Auto') ?></td>
						<td><input type="checkbox" class="checkbox" name="auto"<?php echo isset($slider['properties']['auto']) && $slider['properties']['auto'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print t('Animate automatically?')?>"></td>
						
						<td class="right"><?php print t('Speed') ?></td>
						<td><input type="text" name="speed" value="<?php echo $slider['properties']['speed']?>" data-help="<?php print t('Speed of the transition, in milliseconds')?>"></td>

						<td class="right"><?php print t('Timeout') ?></td>
						<td><input type="text" name="timeout" value="<?php echo $slider['properties']['timeout']?>" data-help="<?php print t('Time between slide transitions, in milliseconds')?>"></td>
          </tr>
					<tr>
						<td class="right"></td>
            <td class="right"><?php print t('Pager') ?></td>
						<td><input type="checkbox" class="checkbox" name="pager"<?php echo isset($slider['properties']['pager']) && $slider['properties']['pager'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print t('Show pager?')?>"></td>
           
            <td class="right"><?php print t('prev/next Navigation?') ?></td>
						<td><input type="checkbox" class="checkbox" name="nav"<?php echo isset($slider['properties']['nav']) && $slider['properties']['nav'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print t('Show navigation?')?>"></td>
           
            <td class="right"><?php print t('Random?') ?></td>
						<td><input type="checkbox" class="checkbox" name="random"<?php echo isset($slider['properties']['random']) && $slider['properties']['random'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print t('Randomize the order of the slides, true or false?')?>"></td>
          </tr>
					<tr>
						<td class="right"></td>
            <td class="right"><?php print t('Pause?') ?></td>
						<td><input type="checkbox" class="checkbox" name="pause"<?php echo isset($slider['properties']['pause']) && $slider['properties']['pause'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print t('Pause on hover?')?>"></td>
           
            <td class="right"><?php print t('pause controls?') ?></td>
						<td colspan="3"><input type="checkbox" class="checkbox" name="nav"<?php echo isset($slider['properties']['pauseControls']) && $slider['properties']['pauseControls'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print t('Pause when hovering controls?')?>"></td>
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
								<td class="right"><?php print t('Slide Background Image') ?></td>
								<td>
									<div class="reset-parent">
										<input type="hidden" name="background_fid" class="fid" value="<?php echo $layer['properties']['background_fid']?>">
										<input type="text" name="background" class="<?php print $uploadClass?>" value="<?php echo $layer['properties']['background']?>" data-help="<?php print t('The slide image/background. Click into the field to open the Drupal Media Library to choose or upload an image.') ?>">
										<span class="ac-reset">x</span>
									</div>
								</td>
								
								<td class="right"><?php print t('Slide background color') ?></td>
								<td>
									<div class="reset-parent">
										<input type="text" name="bgColor" class="auto ac-colorpicker" value="<?php echo $layer['properties']['bgColor']?>" data-help="<?php print t("The background color of slide. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF") ?>">
										<span class="ac-reset">x</span>
									</div>
								</td>
                <td></td>
                <td></td>
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
					<table>
						<thead>
							<tr>
								<td>
									<span id="ac-icon-sublayers"></span>
									<h4><?php print t('Layers') ?></h4>
								</td>
							</tr>
						</thead>
						<tbody class="ac-sublayers ac-sublayer-sortable">
							<?php if(!empty($layer['sublayers'])) : ?>
							<?php foreach($layer['sublayers'] as $key => $sublayer) : ?>
							<?php $active = (count($layer['sublayers']) == ($key+1)) ? ' class="active"' : '' ?>
							<?php $title = empty($sublayer['subtitle']) ? 'Layer #'.($key+1).'' : htmlspecialchars(stripslashes($sublayer['subtitle'])); ?>
							<tr<?php echo $active ?>>
								<td>
									<div class="ac-sublayer-wrapper">
										<span class="ac-sublayer-number"><?php print $key+1?></span>
										<span class="ac-highlight"><input type="checkbox" class="noreplace"></span>
										<span class="ac-icon-eye"></span>
										<span class="ac-icon-lock"></span>
										<span class="ac-icon-duplicate"><button class="button duplicate" data-help="<?php print t('If you will use similar settings for other layers or you want to experiment on a copy, you can duplicate this layer.') ?>"><?php print t('Duplicate this layer') ?></button></span>
										<input type="text" name="subtitle" class="ac-sublayer-title" value="<?php echo $sublayer['subtitle'] ?>">
										<div class="clear"></div>
										<div class="ac-sublayer-nav">
											<a href="#" class="active"><?php print t('Basic') ?></a>
											<a href="#"><?php print t('Style') ?></a>
											<a href="#"><?php print t('Attributes') ?></a>
											<a href="#" title="<?php print t('Remove this layer') ?>" class="remove">x</a>
										</div>
										<div class="ac-sublayer-pages">
											<div class="ac-sublayer-page ac-sublayer-basic active">
												<select name="type" class='no-fancy-select'>
													<option <?php echo ($sublayer['type'] == 'img') ? 'selected="selected"' : '' ?>>img</option>
													<option <?php echo ($sublayer['type'] == 'div') ? 'selected="selected"' : '' ?>>div</option>
													<option <?php echo ($sublayer['type'] == 'p') ? 'selected="selected"' : '' ?>>p</option>
													<option <?php echo ($sublayer['type'] == 'span') ? 'selected="selected"' : '' ?>>span</option>
													<option <?php echo ($sublayer['type'] == 'h1') ? 'selected="selected"' : '' ?>>h1</option>
													<option <?php echo ($sublayer['type'] == 'h2') ? 'selected="selected"' : '' ?>>h2</option>
													<option <?php echo ($sublayer['type'] == 'h3') ? 'selected="selected"' : '' ?>>h3</option>
													<option <?php echo ($sublayer['type'] == 'h4') ? 'selected="selected"' : '' ?>>h4</option>
													<option <?php echo ($sublayer['type'] == 'h5') ? 'selected="selected"' : '' ?>>h5</option>
													<option <?php echo ($sublayer['type'] == 'h6') ? 'selected="selected"' : '' ?>>h6</option>
												</select>
				
												<div class="ac-sublayer-types">
													<span class="ac-type">
														<span class="ac-icon-img"></span><br>
														<?php print t('Image') ?>
													</span>

													<span class="ac-type">
														<span class="ac-icon-div"></span><br>
														<?php print t('Div') ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-p"></span><br>
														<?php print t('Paragraph') ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-span"></span><br>
														<?php print t('Span') ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-h1"></span><br>
														<?php print t('H1') ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-h2"></span><br>
														<?php print t('H2') ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-h3"></span><br>
														<?php print t('H3') ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-h4"></span><br>
														<?php print t('H4') ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-h5"></span><br>
														<?php print t('H5') ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-h6"></span><br>
														<?php print t('H6') ?>
													</span>
												</div>
												
												<div class="layer-content-items clearfix">
													<div class="ac-item ac-image-uploader">
														<?php $imageSrc = !empty($sublayer['image']) ? $sublayer['image'] : file_create_url($plugins_url . '/img/transparent.png') ?>
														<img src="<?php echo $imageSrc ?>" alt="sublayer image">
														<input type="hidden" name="image_fid" class="fid" value="<?php echo $sublayer['image_fid']?>">
														<input type="text" name="image" class="<?php echo $uploadClass ?>" value="<?php echo $sublayer['image'] ?>">
														<p>
															<?php print t('Click into this text field to open Drupal Media Library where you can upload new images or select previously used ones.') ?>
														</p>
													</div>

													<div class="ac-item ac-html-code">
														<h5><?php print t('Custom HTML content') ?></h5>
														<textarea name="html" cols="50" rows="5" data-help="<?php print t('Type here the contents of your layer. You can use any HTML codes in this field to insert other contents then text. This field is also shortcode-aware, so you can insert content from other plugins as well as video embed codes.') ?>"><?php echo stripslashes($sublayer['html']) ?></textarea>
													</div>
												</div>
												
											</div>
											<div class="ac-sublayer-page ac-sublayer-style">
												<?php $sublayer['styles'] = !empty($sublayer['styles']) ? json_decode(stripslashes($sublayer['styles']), true) : array(); ?>
												<input type="hidden" name="styles">
												<table>
													<tbody>
														<tr>
															<td><?php print t('Layout & Positions') ?></td>
															<td class="right"><?php print t('Width') ?></td>
															<td><input type="text" name="width" class="auto" value="<?php echo isset($sublayer['styles']['width']) ? $sublayer['styles']['width'] : '' ?>" data-help="<?php print t("You can set the width of your layer. You can use pixels, percents, or the default value 'auto'. Examples: 100px, 50% or auto") ?>"></td>
															<td class="right"><?php print t('Height') ?></td>
															<td><input type="text" name="height" class="auto" value="<?php echo isset($sublayer['styles']['height']) ? $sublayer['styles']['height'] : '' ?>" data-help="<?php print t("You can set the height of your layer. You can use pixels, percents, or the default value 'auto'. Examples: 100px, 50% or auto") ?>"></td>
															<td class="right"><?php print t('Top') ?></td>
															<td><input type="text" name="top" value="<?php echo $sublayer['top'] ?>" data-help="<?php print t("The layer position from the top of the slide. You can use pixels and percents. Examples: 100px or 50%. You can move your layers in the preview above with a drag n' drop, or set the exact values here.") ?>"></td>
															<td class="right"><?php print t('Left') ?></td>
															<td><input type="text" name="left" value="<?php echo $sublayer['left'] ?>" data-help="<?php print t("The layer position from the left side of the slide. You can use pixels and percents. Examples: 100px or 50%. You can move your layers in the preview above with a drag n' drop, or set the exact values here.") ?>"></td>
														</tr>
														<tr>
															<td><?php print t('Padding') ?></td>
															<td class="right"><?php print t('Top') ?></td>
															<td><input type="text" name="padding-top" class="auto" value="<?php echo isset($sublayer['styles']['padding-top']) ? $sublayer['styles']['padding-top'] : '' ?>" data-help="<?php print t('Padding on the top of the layer. Example: 10px') ?>"></td>
															<td class="right"><?php print t('Right') ?></td>
															<td><input type="text" name="padding-right" class="auto" value="<?php echo isset($sublayer['styles']['padding-right']) ? $sublayer['styles']['padding-right'] : '' ?>" data-help="<?php print t('Padding on the right side of the layer. Example: 10px') ?>"></td>
															<td class="right"><?php print t('Bottom') ?></td>
															<td><input type="text" name="padding-bottom" class="auto" value="<?php echo isset($sublayer['styles']['padding-bottom']) ? $sublayer['styles']['padding-bottom'] : '' ?>" data-help="<?php print t('Padding on the bottom of the layer. Example: 10px') ?>"></td>
															<td class="right"><?php print t('Left') ?></td>
															<td><input type="text" name="padding-left" class="auto" value="<?php echo isset($sublayer['styles']['padding-left']) ? $sublayer['styles']['padding-left'] : '' ?>" data-help="<?php print t('Padding on the left side of the layer. Example: 10px') ?>"></td>
														</tr>
														<tr>
															<td><?php print t('Border') ?></td>
															<td class="right"><?php print t('Top') ?></td>
															<td><input type="text" name="border-top" class="auto" value="<?php echo isset($sublayer['styles']['border-top']) ? $sublayer['styles']['border-top'] : '' ?>" data-help="<?php print t('Border on the top of the layer. Example: 5px solid #000') ?>"></td>
															<td class="right"><?php print t('Right') ?></td>
															<td><input type="text" name="border-right" class="auto" value="<?php echo isset($sublayer['styles']['border-right']) ? $sublayer['styles']['border-right'] : '' ?>" data-help="<?php print t('Border on the right side of the layer. Example: 5px solid #000') ?>"></td>
															<td class="right"><?php print t('Bottom') ?></td>
															<td><input type="text" name="border-bottom" class="auto" value="<?php echo isset($sublayer['styles']['border-bottom']) ? $sublayer['styles']['border-bottom'] : '' ?>" data-help="<?php print t('Border on the bottom of the layer. Example: 5px solid #000') ?>"></td>
															<td class="right"><?php print t('Left') ?></td>
															<td><input type="text" name="border-left" class="auto" value="<?php echo isset($sublayer['styles']['border-left']) ? $sublayer['styles']['border-left'] : '' ?>" data-help="<?php print t('Border on the left side of the layer. Example: 5px solid #000') ?>"></td>
														</tr>
														<tr>
															<td><?php print t('Font') ?></td>
															<td class="right"><?php print t('Family') ?></td>
															<td><input type="text" name="font-family" class="auto" value="<?php echo isset($sublayer['styles']['font-family']) ? stripslashes($sublayer['styles']['font-family']) : '' ?>" data-help="<?php print t('List of your chosen fonts separated with a comma. Please use apostrophes if your font names contains white spaces. Example: Helvetica, Arial, sans-serif') ?>"></td>
															<td class="right"><?php print t('Size') ?></td>
															<td><input type="text" name="font-size" class="auto" value="<?php echo isset($sublayer['styles']['font-size']) ? $sublayer['styles']['font-size'] : '' ?>" data-help="<?php print t('The font size in pixels. Example: 16px.') ?>"></td>
															<td class="right"><?php print t('Line-height') ?></td>
															<td><input type="text" name="line-height" class="auto" value="<?php echo isset($sublayer['styles']['line-height']) ? $sublayer['styles']['line-height'] : '' ?>" data-help="<?php print t("The line height of your text. The default setting is 'normal'. Example: 22px") ?>"></td>
															<td class="right"><?php print t('Color') ?></td>
															<td><input type="text" name="color" class="auto ac-colorpicker" value="<?php echo isset($sublayer['styles']['color']) ? $sublayer['styles']['color'] : '' ?>" data-help="<?php print t('The color of your text. You can use color names, hexadecimal, RGB or RGBA values. Example: #333') ?>"></td>
														</tr>
														<tr>
															<td><?php print t('Misc') ?></td>
															<td class="right"><?php print t('Background') ?></td>
															<td><input type="text" name="background" class="auto ac-colorpicker" value="<?php echo isset($sublayer['styles']['background']) ? $sublayer['styles']['background'] : '' ?>" data-help="<?php print t("The background color of your layer. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF") ?>"></td>
															<td class="right"><?php print t('Rounded corners') ?></td>
															<td><input type="text" name="border-radius" class="auto" value="<?php echo isset($sublayer['styles']['border-radius']) ? $sublayer['styles']['border-radius'] : '' ?>" data-help="<?php print t('If you want rounded corners, you can set here its radius. Example: 5px') ?>"></td>
															<td class="right"><?php print t('Word-wrap') ?></td>
															<td colspan="3"><input type="checkbox" name="wordwrap" data-help="<?php print t('If you use custom sized layers, you have to enable this setting to wrap your text.') ?>" class="checkbox"<?php echo isset($sublayer['wordwrap']) ? ' checked="checked"' : '' ?>></td>
														</tr>
														<tr>
															<td><?php print t('Custom style settings') ?></td>
															<td class="right"><?php print t('Custom styles') ?></td>
															<td colspan="7"><textarea rows="5" cols="50" name="style" class="style" data-help="<?php print t('If you want to set style settings other then above, you can use here any CSS codes. Please make sure to write valid markup.') ?>"><?php echo stripslashes($sublayer['style']) ?></textarea></td>
														</tr>
													</tbody>
												</table>
											</div>
											<div class="ac-sublayer-page ac-sublayer-attributes">
												<table>
													<tbody>
														<tr>
															<td class="right" rowspan="2"><?php print t('Attributes') ?></td>
															<td class="right"><?php print t('ID') ?></td>
															<td><input type="text" name="id" value="<?php echo $sublayer['id']?>" data-help="<?php print t('You can apply an ID attribute on the HTML element of this layer to work with it in your custom CSS or Javascript code.') ?>"></td>
															<td class="right"><?php print t('Classes') ?></td>
															<td><input type="text" name="class" value="<?php echo $sublayer['class']?>" data-help="<?php print t('You can apply classes on the HTML element of this layer to work with it in your custom CSS or Javascript code.') ?>"></td>
															<td class="right"><?php print t('Title') ?></td>
															<td colspan="3"><input type="text" name="title" value="<?php echo $sublayer['title']?>" data-help="<?php print t('You can add a title to this layer which will display as a tooltip if someone holds his mouse cursor over the layer.') ?>"></td>
														</tr>
														<tr>
															<td class="right notfirst"><?php print t('Alt') ?></td>
															<td><input type="text" name="alt" value="<?php echo $sublayer['alt']?>" data-help="<?php print t('You can add an alternative text to your layer which is indexed by search engine robots and it helps people with certain disabilities.') ?>"></td>
															<td class="right"><?php print t('Rel') ?></td>
															<td colspan="5"><input type="text" name="rel" value="<?php echo $sublayer['rel']?>" data-help="<?php print t('Some plugin may use the rel attribute of a linked content, here you can specify it to make interaction with these plugins.') ?>"></td>
														</tr>
													</tbody>
												</table>
											</div>
										</div>
									</div>
								</td>
							</tr>
							<?php endforeach; ?>
							<?php endif; ?>
						</tbody>
					</table>
					<a href="#" class="ac-add-sublayer"><?php print t('Add new layer') ?></a>
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
            <td class="right"><?php print t('Slide background Image') ?></td>
            <td>
              <div class="reset-parent">
								<input type="hidden" name="background_fid" class="fid" value="">
                <input type="text" name="background" class="<?php print $uploadClass?>" value="" data-help="<?php print t('The slide image/background. Click into the field to open the Drupal Media Library to choose or upload an image.') ?>">
                <span class="ac-reset">x</span>
              </div>
            </td>
            <td class="right"><?php print t('Slide Background color') ?></td>
            <td colspan="3">
              <div class="reset-parent">
								<input type="text" name="bgColor" class="auto ac-colorpicker" value="" data-help="<?php print t("The background color of slide. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF") ?>">
                <span class="ac-reset">x</span>
              </div>
            </td>
          </tr>
          <tr>
            <td class="right"></td>
            <td><?php print t('Enable Link  on Media?') ?></td>
            <td><input type="checkbox" name="enable_link" class="checkbox"></td>
            <td class="right notfirst" data-controller="enable_link"><?php print t('Link target') ?></td>
            <td data-controller="enable_link">
              <select name="link_open_in" data-help="<?php print t('You can control here the link behaviour: _self means the linked page will open in the current tab/window, _blank will create a new tab/window.') ?>">
                <option>_self</option>
                <option>_blank</option>
                <option>_parent</option>
                <option>_top</option>
              </select>
            </td>
            <td class="right" data-controller="enable_link"><?php print t('Link') ?></td>			
            <td data-controller="enable_link"><input type="text" name="link" value="" data-help="<?php print t('A link to a url or a slide (you can use \'prev\' and \'next\' or slider number.)') ?>"></td>
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
      <table>
        <thead>
          <tr>
            <td>
              <span id="ac-icon-sublayers"></span>
              <h4><?php print t('Layers') ?></h4>
            </td>
          </tr>
        </thead>
        <tbody class="ac-sublayers ac-sublayer-sortable">
          <tr>
            <td>
              <div class="ac-sublayer-wrapper">
                <span class="ac-sublayer-number">1</span>
                <span class="ac-highlight"><input type="checkbox" class="noreplace"></span>
                <span class="ac-icon-eye"></span>
                <span class="ac-icon-lock"></span>
								<span class="ac-icon-duplicate"><button class="button duplicate" data-help="<?php print t('If you will use similar settings for other layers or you want to experiment on a copy, you can duplicate this layer.') ?>"><?php print t('Duplicate this layer') ?></button></span>
                <input type="text" name="subtitle" class="ac-sublayer-title" value="Layer #1">
                <div class="clear"></div>
                <div class="ac-sublayer-nav">
                  <a href="#" class="active"><?php print t('Basic') ?></a>
                  <a href="#"><?php print t('Style') ?></a>
                  <a href="#"><?php print t('Attributes') ?></a>
                  <a href="#" title="<?php print t('Remove this layer') ?>" class="remove">x</a>
                </div>
                <div class="ac-sublayer-pages">
                  <div class="ac-sublayer-page ac-sublayer-basic active">
                    <select name="type" class='no-fancy-select'>
                      <option selected="selected">img</option>
                      <option>div</option>
                      <option>p</option>
                      <option>span</option>
                      <option>h1</option>
                      <option>h2</option>
                      <option>h3</option>
                      <option>h4</option>
                      <option>h5</option>
                      <option>h6</option>
                    </select>
    
                    <div class="ac-sublayer-types">
                      <span class="ac-type">
                        <span class="ac-icon-img"></span><br>
                        <?php print t('Image') ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-div"></span><br>
                        <?php print t('Div') ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-p"></span><br>
                        <?php print t('Paragraph') ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-span"></span><br>
                        <?php print t('Span') ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-h1"></span><br>
                        <?php print t('H1') ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-h2"></span><br>
                        <?php print t('H2') ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-h3"></span><br>
                        <?php print t('H3') ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-h4"></span><br>
                        <?php print t('H4') ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-h5"></span><br>
                        <?php print t('H5') ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-h6"></span><br>
                        <?php print t('H6') ?>
                      </span>
                    </div>
										
										<div class="layer-content-items clearfix">
											<div class="ac-item ac-image-uploader">
												<img src="<?php echo file_create_url($plugins_url . '/img/transparent.png') ?>" alt="sublayer image">
												<input type="hidden" name="image_fid" class="fid" value="">
												<input type="text" name="image" class="<?php echo $uploadClass ?>" value="">
												<p>
													<?php print t('Click into this text field to open Drupal Media Library where you can upload new images or select previously used ones.') ?>
												</p>
											</div>
											<div class="ac-item ac-html-code">
												<h5><?php print t('Custom HTML content') ?></h5>
												<textarea name="html" cols="50" rows="5" data-help="<?php print t('Type here the contents of your layer. You can use any HTML codes in this field to insert other contents then text. This field is also shortcode-aware, so you can insert content from other plugins as well as video embed codes.') ?>"></textarea>
											</div>
										</div>
                  </div>
									<div class="ac-sublayer-page ac-sublayer-style">
                    <input type="hidden" name="styles">
                    <table>
                      <tbody>
                        <tr>
                          <td><?php print t('Layout & Positions') ?></td>
                          <td class="right"><?php print t('Width') ?></td>
                          <td><input type="text" name="width" class="auto" value="" data-help="<?php print t("You can set the width of your layer. You can use pixels, percents, or the default value 'auto'. Examples: 100px, 50% or auto") ?>"></td>
                          <td class="right"><?php print t('Height') ?></td>
                          <td><input type="text" name="height" class="auto" value="" data-help="<?php print t("You can set the height of your layer. You can use pixels, percents, or the default value 'auto'. Examples: 100px, 50% or auto") ?>"></td>
                          <td class="right"><?php print t('Top') ?></td>
                          <td><input type="text" name="top" value="20px" data-help="<?php print t("The layer position from the top of the slide. You can use pixels and percents. Examples: 100px or 50%. You can move your layers in the preview above with a drag n' drop, or set the exact values here.") ?>"></td>
                          <td class="right"><?php print t('Left') ?></td>
                          <td><input type="text" name="left" value="20px" data-help="<?php print t("The layer position from the left side of the slide. You can use pixels and percents. Examples: 100px or 50%. You can move your layers in the preview above with a drag n' drop, or set the exact values here.") ?>"></td>
                        </tr>
                        <tr>
                          <td><?php print t('Padding') ?></td>
                          <td class="right"><?php print t('Top') ?></td>
                          <td><input type="text" name="padding-top" class="auto" value="" data-help="<?php print t('Padding on the top of the layer. Example: 10px') ?>"></td>
                          <td class="right"><?php print t('Right') ?></td>
                          <td><input type="text" name="padding-right" class="auto" value="" data-help="<?php print t('Padding on the right side of the layer. Example: 10px') ?>"></td>
                          <td class="right"><?php print t('Bottom') ?></td>
                          <td><input type="text" name="padding-bottom" class="auto" value="" data-help="<?php print t('Padding on the bottom of the layer. Example: 10px') ?>"></td>
                          <td class="right"><?php print t('Left') ?></td>
                          <td><input type="text" name="padding-left" class="auto" value="" data-help="<?php print t('Padding on the left side of the layer. Example: 10px') ?>"></td>
                        </tr>
                        <tr>
                          <td><?php print t('Border') ?></td>
                          <td class="right"><?php print t('Top') ?></td>
                          <td><input type="text" name="border-top" class="auto" value="" data-help="<?php print t('Border on the top of the layer. Example: 5px solid #000') ?>"></td>
                          <td class="right"><?php print t('Right') ?></td>
                          <td><input type="text" name="border-right" class="auto" value="" data-help="<?php print t('Border on the right side of the layer. Example: 5px solid #000') ?>"></td>
                          <td class="right"><?php print t('Bottom') ?></td>
                          <td><input type="text" name="border-bottom" class="auto" value="" data-help="<?php print t('Border on the bottom of the layer. Example: 5px solid #000') ?>"></td>
                          <td class="right"><?php print t('Left') ?></td>
                          <td><input type="text" name="border-left" class="auto" value="" data-help="<?php print t('Border on the left side of the layer. Example: 5px solid #000') ?>"></td>
                        </tr>
                        <tr>
                          <td><?php print t('Font') ?></td>
                          <td class="right"><?php print t('Family') ?></td>
                          <td><input type="text" name="font-family" class="auto" value="" data-help="<?php print t('List of your chosen fonts separated with a comma. Please use apostrophes if your font names contains white spaces. Example: Helvetica, Arial, sans-serif') ?>"></td>
                          <td class="right"><?php print t('Size') ?></td>
                          <td><input type="text" name="font-size" class="auto" value="" data-help="<?php print t('The font size in pixels. Example: 16px.') ?>"></td>
                          <td class="right"><?php print t('Line-height') ?></td>
                          <td><input type="text" name="line-height" class="auto" value="" data-help="<?php print t("The line height of your text. The default setting is 'normal'. Example: 22px") ?>"></td>
                          <td class="right"><?php print t('Color') ?></td>
                          <td><input type="text" name="color" class="auto ac-colorpicker" value="" data-help="<?php print t('The color of your text. You can use color names, hexadecimal, RGB or RGBA values. Example: #333') ?>"></td>
                        </tr>
                        <tr>
                          <td><?php print t('Misc') ?></td>
                          <td class="right"><?php print t('Background') ?></td>
                          <td><input type="text" name="background" class="auto ac-colorpicker" value="" data-help="<?php print t("The background color of your layer. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF") ?>"></td>
                          <td class="right"><?php print t('Rounded corners') ?></td>
                          <td><input type="text" name="border-radius" class="auto" value="" data-help="<?php print t('If you want rounded corners, you can set here its radius. Example: 5px') ?>"></td>
                          <td class="right"><?php print t('Word-wrap') ?></td>
                          <td colspan="3"><input type="checkbox" name="wordwrap" class="checkbox" data-help="<?php print t('If you use custom sized layers, you have to enable this setting to wrap your text.') ?>"></td>
                        </tr>
                        <tr>
                          <td><?php print t('Custom style settings') ?></td>
                          <td class="right"><?php print t('Custom styles') ?></td>
                          <td colspan="7"><textarea rows="5" cols="50" name="style" class="style" data-help="<?php print t('If you want to set style settings other then above, you can use here any CSS codes. Please make sure to write valid markup.') ?>"></textarea></td>
                        </tr>
                      </tbody>
                    </table>
                  </div>
                  <div class="ac-sublayer-page ac-sublayer-attributes">
                    <table>
                      <tbody>
                        <tr>
                          <td class="right" rowspan="2"><?php print t('Attributes') ?></td>
                          <td class="right"><?php print t('ID') ?></td>
                          <td><input type="text" name="id" value="" data-help="<?php print t('You can apply an ID attribute on the HTML element of this layer to work with it in your custom CSS or Javascript code.') ?>"></td>
                          <td class="right"><?php print t('Classes') ?></td>
                          <td><input type="text" name="class" value="" data-help="<?php print t('You can apply classes on the HTML element of this layer to work with it in your custom CSS or Javascript code.') ?>"></td>
                          <td class="right"><?php print t('Title') ?></td>
                          <td colspan="3"><input type="text" name="title" value="" data-help="<?php print t('You can add a title to this layer which will display as a tooltip if someone holds his mouse cursor over the layer.') ?>"></td>
                        </tr>
												<tr>
                          <td class="right notfirst"><?php print t('Alt') ?></td>
                          <td><input type="text" name="alt" value="" data-help="<?php print t('You can add an alternative text to your layer which is indexed by search engine robots and it helps people with certain disabilities.') ?>"></td>
                          <td class="right"><?php print t('Rel') ?></td>
                          <td colspan="5"><input type="text" name="rel" value="" data-help="<?php print t('Some plugin may use the rel attribute of a linked content, here you can specify it to make interaction with these plugins.') ?>"></td>
                        </tr>
                      </tbody>
                    </table>
                  </div>
                </div>
              </div>
            </td>
          </tr>
        </tbody>
      </table>
      <a href="#" class="ac-add-sublayer"><?php print t('Add new layer') ?></a>
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