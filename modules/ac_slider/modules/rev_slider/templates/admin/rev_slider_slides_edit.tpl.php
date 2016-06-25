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
              <?php _e('Slide Options', REVSLIDER_TEXTDOMAIN) ?>
            </h4>
            <button class="button duplicate ac-layer-duplicate"><?php _e('Duplicate this slide', REVSLIDER_TEXTDOMAIN) ?></button>
          </td>
				</tr>
			</thead>
			<tbody class="ac-slide-options">
				<tr>
					<td class="right"><?php _e('Slide options', REVSLIDER_TEXTDOMAIN) ?></td>
					<td class="right"><?php _e('Image', REVSLIDER_TEXTDOMAIN) ?></td>
					<td>
						<div class="reset-parent">
							<input type="hidden" name="background_fid" class="fid" value="">
							<input type="text" name="background" class="<?php print $uploadClass?>" value="" data-help="<?php _e('The slide image/background. Click into the field to open the WordPress Media Library to choose or upload an image.', REVSLIDER_TEXTDOMAIN) ?>">
							<span class="ac-reset">x</span>
						</div>
					</td>
					
					<td class="right"><?php _e('background color', REVSLIDER_TEXTDOMAIN) ?></td>
					<td>
						<div class="reset-parent">
							<input type="text" name="bgColor" class="auto ac-colorpicker" value="" data-help="<?php _e("The background color of slide. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF", "revSlider") ?>">
							<span class="ac-reset">x</span>
						</div>
					</td>
					
					<td class="right"><?php _e('Thumbnail', REVSLIDER_TEXTDOMAIN) ?></td>
					<td>
						<div class="reset-parent">
							<input type="hidden" name="thumbnail_fid" class="fid" value="">
							<input type="text" name="thumbnail" class="<?php print $uploadClass?>" value="" data-help="<?php _e('The thumbnail image of this slide. Click into the field to open the WordPress Media Library to choose or upload an image. If you leave this field empty, the slide image will be used.', REVSLIDER_TEXTDOMAIN) ?>">
							<span class="ac-reset">x</span>
						</div>
					</td>
				 
				</tr>
				<tr>
					<td class="right" rowspan="2"><?php _e('Slide transition', REVSLIDER_TEXTDOMAIN) ?></td>
					<td class="right"><?php _e('Transitions', REVSLIDER_TEXTDOMAIN) ?></td>
					<td>
						<input type='hidden' name="slide_transitions" value="" >
						<select name="slide_transition" class="input_checklist no-fancy-select" multiple="" data-minwidth="280px" size="1">
						<?php foreach (rev_slider_transitions() as $k => $v):?>
							<option value="<?php print $k?>"><?php _e($v, REVSLIDER_TEXTDOMAIN) ?></option>
						<?php endforeach?>
						</select>
					</td>
					<td class="right"><?php _e('Slot Amount', REVSLIDER_TEXTDOMAIN) ?></td>
					<td><input type="text" name="slot_amount" value="7" data-help="<?php _e('The number of slots or boxes the slide is divided into. If you use boxfade, over 7 slots can be juggy.', REVSLIDER_TEXTDOMAIN) ?>"> </td>
					<td class="right"><?php _e('Rotation', REVSLIDER_TEXTDOMAIN) ?></td>
					<td><input type="text" name="transition_rotation" class="layerprop" value="0" data-help="<?php _e('Rotation (-720 -> 720, 999 = random) Only for Simple Transitions.', REVSLIDER_TEXTDOMAIN) ?>"></td>
				</tr>
				<tr>
					<td class="right notfirst"><?php _e('Transition Duration', REVSLIDER_TEXTDOMAIN) ?></td>
					<td><input type="text" name="transition_duration" class="layerprop" value="300" data-help="<?php _e('The duration of the transition (Default:300, min: 100 max 2000).', REVSLIDER_TEXTDOMAIN) ?>"> (ms)</td>
					<td class="right"><?php _e('Delay', REVSLIDER_TEXTDOMAIN) ?></td>
					<td colspan="3"><input type="text" name="delay" class="layerprop" data-help="<?php _e('A new delay value for the Slide. If no delay defined per slide, the delay defined via Options (9000ms) will be used.', REVSLIDER_TEXTDOMAIN) ?>"> (ms)</td>
				</tr>
				<tr>
					<td class="right" rowspan="2"><?php _e('Link this slide', REVSLIDER_TEXTDOMAIN); ?></td>
					<td class="right"><?php _e('Enable Link', REVSLIDER_TEXTDOMAIN) ?></td>
					<td><input type="checkbox" name="enable_link" class="checkbox"></td>
					<td class="right" data-controller="enable_link"><?php _e('Link type', REVSLIDER_TEXTDOMAIN) ?></td>
					<td data-controller="enable_link">
						<select name="link_type">
							<option value="regular"><?php _e('Regular', REVSLIDER_TEXTDOMAIN) ?></option>
							<option value="slide"><?php _e('Slide', REVSLIDER_TEXTDOMAIN) ?></option>
						</select>
					</td>
					<td class="right" data-controller="enable_link"><?php _e('Link', REVSLIDER_TEXTDOMAIN) ?></td>			
					<td data-controller="enable_link"><input type="text" name="link" value="" data-help="<?php _e('A link to a url or a slide (you can use \'prev\' and \'next\' or slider number.)', REVSLIDER_TEXTDOMAIN) ?>"></td>
				</tr>
				<tr>
					<td class="right notfirst" data-controller="enable_link"><?php _e('Link target', REVSLIDER_TEXTDOMAIN) ?></td>
					<td data-controller="enable_link">
						<select name="link_open_in" data-help="<?php _e('You can control here the link behaviour: _self means the linked page will open in the current tab/window, _blank will create a new tab/window.', REVSLIDER_TEXTDOMAIN) ?>">
							<option>_self</option>
							<option>_blank</option>
							<option>_parent</option>
							<option>_top</option>
						</select>
					</td>
					<td class="right" data-controller="enable_link"><?php _e('Link Position', REVSLIDER_TEXTDOMAIN) ?></td>
					<td data-controller="enable_link" colspan="3">
						<select name="link_pos" data-help="<?php _e('The position of the link related to layers.', REVSLIDER_TEXTDOMAIN) ?>">
							<option value="front"><?php _e('Front', REVSLIDER_TEXTDOMAIN) ?></option>
							<option value="back"><?php _e('Back', REVSLIDER_TEXTDOMAIN) ?></option>
						</select>
					</td>
				</tr>
				
				<tr>
					<td class="right"><?php _e('Misc', REVSLIDER_TEXTDOMAIN) ?></td>
					<td class="right"><?php _e('Full Width Centering', REVSLIDER_TEXTDOMAIN) ?></td>
					<td><input type="checkbox" name="fullwidth_centering" class="checkbox" checked="checked" data-help="<?php _e('Apply to full width mode only. Centering vertically slide images.', REVSLIDER_TEXTDOMAIN)?>"></td>
					
					<td class="right"><?php _e('Ken Burns / Pan Zoom Settings:', REVSLIDER_TEXTDOMAIN) ?></td>
					<td colspan="3"><input type="checkbox" name="kenburn_effect" class="checkbox"></td>
					
				</tr>
				
				<tr>
					<td class="right"><?php _e('Ken Burns Background', REVSLIDER_TEXTDOMAIN) ?></td>
					<td class="right"><?php _e('Start Position', REVSLIDER_TEXTDOMAIN) ?></td>
					<td>
						<select name="bg_position" id="slide_bg_position">
							<option value="center top">center top</option>
							<option value="center right">center right</option>
							<option value="center bottom">center bottom</option>
							<option value="center center">center center</option>
							<option value="left top">left top</option>
							<option value="left center">left center</option>
							<option value="left bottom" selected="selected">left bottom</option>
							<option value="right top">right top</option>
							<option value="right center">right center</option>
							<option value="right bottom">right bottom</option>
							<option value="percentage">(x%, y%)</option>
						</select>
						<div style="display: none;" class="bg_position bg_position_x">
							<label for="bg_position_x">position x</label>&nbsp;&nbsp;&nbsp;<input type="text" name="bg_position_x"  value="" />
						</div>
						<div style="display: none;" class="bg_position bg_position_y">
							<label for="bg_position_y">position y</label>&nbsp;&nbsp;&nbsp;<input type="text" name="bg_position_y" value="" />
						</div>
					</td>
					
					<td class="right"><?php _e('Start Fit: (in %)', REVSLIDER_TEXTDOMAIN) ?></td>
					<td><input type="text" name="kb_start_fit" value="120"></td>
					
					<td class="right"><?php _e('Easing', REVSLIDER_TEXTDOMAIN) ?></td>
					<td>
						<select name="kb_easing">
							<?php foreach ($easing as $key => $title):?>
								<option value="<?php print $key?>"<?php echo ($key == 'easeInOutQuint') ? 'selected="selected"' : '' ?>><?php print t($title) ?></option>
							<?php endforeach?>
						</select>
					</td>
				</tr>
				
				<tr>
					<td class="right"></td>
					<td class="right"><?php _e('End Position', REVSLIDER_TEXTDOMAIN) ?></td>
					<td>
						<select name="bg_end_position" id="slide_bg_end_position">
							<option value="center top">center top</option>
							<option value="center right">center right</option>
							<option value="center bottom">center bottom</option>
							<option value="center center">center center</option>
							<option value="left top">left top</option>
							<option value="left center">left center</option>
							<option value="left bottom">left bottom</option>
							<option value="right top" selected="selected">right top</option>
							<option value="right center">right center</option>
							<option value="right bottom">right bottom</option>
							<option value="percentage">(x%, y%)</option>
						</select>
						<div style="display: none;" class="bg_position bg_position_x">
							<label for="bg_end_position_x">position x</label>&nbsp;&nbsp;&nbsp;<input type="text" name="bg_end_position_x"  value="" />
						</div>
						<div style="display: none;" class="bg_position bg_position_y">
							<label for="bg_end_position_y">position y</label>&nbsp;&nbsp;&nbsp;<input type="text" name="bg_end_position_y" value="" />
						</div>
					</td>
					
					<td class="right"><?php _e('End Fit: (in %)', REVSLIDER_TEXTDOMAIN) ?></td>
					<td><input type="text" name="kb_end_fit" value="100"></td>
					
					<td class="right"><?php _e('Duration (in ms):	', REVSLIDER_TEXTDOMAIN) ?></td>
					<td>
						<input type="text" name="kb_duration" value="10000" />
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
						<h4><?php _e('Preview', REVSLIDER_TEXTDOMAIN) ?></h4>
						<button class="button ac-preview-button"><?php _e('Enter Preview', REVSLIDER_TEXTDOMAIN) ?></button>
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
						<h4><?php _e('Layers', REVSLIDER_TEXTDOMAIN) ?></h4>
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
							<span class="ac-icon-duplicate"><button class="button duplicate" data-help="<?php _e('If you will use similar settings for other layers or you want to experiment on a copy, you can duplicate this layer.', REVSLIDER_TEXTDOMAIN) ?>"><?php _e('Duplicate this layer', REVSLIDER_TEXTDOMAIN) ?></button></span>
							<input type="text" name="subtitle" class="ac-sublayer-title" value="Layer #1">
							<div class="clear"></div>
							<div class="ac-sublayer-nav">
								<a href="#" class="active"><?php _e('Basic', REVSLIDER_TEXTDOMAIN) ?></a>
								<a href="#"><?php _e('Options', REVSLIDER_TEXTDOMAIN) ?></a>
								<a href="#"><?php _e('Link', REVSLIDER_TEXTDOMAIN) ?></a>
								<a href="#"><?php _e('Style', REVSLIDER_TEXTDOMAIN) ?></a>
								<a href="#"><?php _e('Attributes', REVSLIDER_TEXTDOMAIN) ?></a>
								<a href="#" title="<?php _e('Remove this layer', REVSLIDER_TEXTDOMAIN) ?>" class="remove">x</a>
							</div>
							<div class="ac-sublayer-pages">
								<div class="ac-sublayer-page ac-sublayer-basic active">
									<select name="type" class="no-fancy-select">
										<option selected="selected">img</option>
										<option>video</option>
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
											<?php _e('Image', REVSLIDER_TEXTDOMAIN) ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-video"></span><br>
											<?php _e('Video', REVSLIDER_TEXTDOMAIN) ?>
										</span> 
										
										<span class="ac-type">
											<span class="ac-icon-div"></span><br>
											<?php _e('Div', REVSLIDER_TEXTDOMAIN) ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-p"></span><br>
											<?php _e('Paragraph', REVSLIDER_TEXTDOMAIN) ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-span"></span><br>
											<?php _e('Span', REVSLIDER_TEXTDOMAIN) ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-h1"></span><br>
											<?php _e('H1', REVSLIDER_TEXTDOMAIN) ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-h2"></span><br>
											<?php _e('H2', REVSLIDER_TEXTDOMAIN) ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-h3"></span><br>
											<?php _e('H3', REVSLIDER_TEXTDOMAIN) ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-h4"></span><br>
											<?php _e('H4', REVSLIDER_TEXTDOMAIN) ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-h5"></span><br>
											<?php _e('H5', REVSLIDER_TEXTDOMAIN) ?>
										</span>
	
										<span class="ac-type">
											<span class="ac-icon-h6"></span><br>
											<?php _e('H6', REVSLIDER_TEXTDOMAIN) ?>
										</span>
									</div>
									
									<div class="layer-content-items clearfix">
										<div class="ac-item ac-image-uploader">
											<img src="<?php echo file_create_url($plugins_url . '/img/transparent.png') ?>" alt="sublayer image">
											<input type="hidden" name="image_fid" class="fid" value="">
											<input type="text" name="image" class="<?php echo $uploadClass ?>" value="">
											<p>
												<?php _e('Click into this text field to open WordPress Media Library where you can upload new images or select previously used ones.', REVSLIDER_TEXTDOMAIN) ?>
											</p>
										</div>
										
										<div class="ac-item ac-video-data">
											<img src="<?php echo file_create_url($plugins_url . '/img/transparent.png') ?>" data-src="<?php echo file_create_url($plugins_url . '/img/transparent.png') ?>" alt="image of video sublayer">
											<button class="button_add_layer_video button" value="add"><?php _e('Add Video', REVSLIDER_TEXTDOMAIN) ?></button>								
											<p>Add video as a sublayer.</p>

											<button class="button_edit_layer_video button" style="display:none" value="edit"><?php _e('Edit Video', REVSLIDER_TEXTDOMAIN) ?></button>								
											<button class="button_del_layer_video button" style="display:none" value="delete"><?php _e('Delete Video', REVSLIDER_TEXTDOMAIN) ?></button>								
											<p style="display:none">click on "Edit video" to change video setting or click on 'delete video' to remove the vide.</p>

											<textarea style="display: none" name="video_data" class="video_data"></textarea>
										</div>
										
										<div class="ac-item ac-html-code">
											<h5><?php _e('Custom HTML content', REVSLIDER_TEXTDOMAIN) ?></h5>
											<textarea name="html" cols="50" rows="5" data-help="<?php _e('Type here the contents of your layer. You can use any HTML codes in this field to insert other contents then text. This field is also shortcode-aware, so you can insert content from other plugins as well as video embed codes.', REVSLIDER_TEXTDOMAIN) ?>"></textarea>
										</div>
									</div>
									
								</div>
								<div class="ac-sublayer-page ac-sublayer-options">
									<table>
										<tbody>
											<tr>
												<td><?php _e('Start Transition', REVSLIDER_TEXTDOMAIN) ?></td>
												<td class="right"><?php _e('Animation', REVSLIDER_TEXTDOMAIN) ?></td>
												<td>
													<select name="animation">
														<?php foreach ($start_anim as $key => $title):?>
															<option value="<?php print $key?>"><?php print t($title) ?></option>
														<?php endforeach?>
													</select>
												</td>
												<td class="right"><?php _e('Speed', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="speed" class="sublayerprop" value="300"> (ms)</td>
												<td class="right"><a href="http://easings.net/" target="_blank"><?php _e('Easing', REVSLIDER_TEXTDOMAIN) ?></a></td>
												<td>
													<select name="easing" class="sublayerprop" data-help="<?php _e('The timing function of the animation, with it you can manipualte the layer movement. Please click on the link next to this select field to open easings.net for more information and real-time examples.', REVSLIDER_TEXTDOMAIN) ?>">
														<?php foreach ($easing as $key => $title):?>
															<option value="<?php print $key?>"<?php echo ($key == 'easeInOutQuint') ? 'selected="selected"' : '' ?>><?php print t($title) ?></option>
														<?php endforeach?>
													</select>
												</td>
												<td class="right"><?php _e('Start Time', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="start" class="sublayerprop" value="500"> (ms)</td>
											</tr>
											
											<tr>
												<td class="right"><?php _e('End Transition (optional)', REVSLIDER_TEXTDOMAIN) ?></td>
												<td class="right"><?php _e('Animation', REVSLIDER_TEXTDOMAIN) ?></td>
												<td>
													<select name="endanimation">
														<?php foreach ($end_anim as $key => $title):?>
															<option value="<?php print $key?>"<?php echo ($key == 'auto') ? ' selected="selected" ' : ' ' ?>><?php print t($title) ?></option>
														<?php endforeach?>
													</select>
												</td>
												<td class="right"><?php _e('End Speed', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="endspeed" class="sublayerprop" value="300"> (ms)</td>
												<td class="right"><a href="http://easings.net/" target="_blank"><?php _e('Easing', REVSLIDER_TEXTDOMAIN) ?></a></td>
												<td>
													<select name="endeasing" class="sublayerprop" data-help="<?php _e('The timing function of the animation, with it you can manipualte the layer movement. Please click on the link next to this select field to open easings.net for more information and real-time examples.', REVSLIDER_TEXTDOMAIN) ?>">
														<?php foreach ($end_easing as $key => $title):?>
															<option value="<?php print $key?>" <?php print $key == 'nothing' ? ' selected="selected"' : ''?>><?php print t($title) ?></option>
														<?php endforeach?>
													</select>
												</td>
												<td class="right"><?php _e('End Time', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="endtime" class="sublayerprop" value="0"> (ms)</td>
											</tr>
											<tr>
												<td><?php _e('Other options', REVSLIDER_TEXTDOMAIN) ?></td>
												<td class="right"><?php _e('Hidden', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="checkbox" name="skip" class="checkbox" data-help="<?php _e("If you don't want to use this layer, but you want to keep it, you can hide it with this switch.", "revSlider") ?>"></td>
												<td class="right"><?php _e('Responsive Through All Levels', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="checkbox" name="resizeme" class="sublayerprop" class="checkbox"></td>
												<td colspan="4"></td>
											</tr>
									</table>
								</div>
								<div class="ac-sublayer-page ac-sublayer-link">
									<table>
										<tbody>
											<tr>
												<td><?php _e('URL', REVSLIDER_TEXTDOMAIN) ?></td>
												<td class="url"><input type="text" name="url" value="" data-help="<?php _e('A link to a url or a slide (you can use \'prev\' and \'next\' or slider number fot linking to a slide)', REVSLIDER_TEXTDOMAIN) ?>"></td>
												<td>
													<select name="target" data-help="<?php _e('You can control here the link behaviour: _self means the linked page will open in the current tab/window, _blank will open it in a new tab/window.', REVSLIDER_TEXTDOMAIN) ?>">
														<option>_self</option>
														<option>_blank</option>
														<option>_parent</option>
														<option>_top</option>
													</select>
												</td>
											</tr>
										</tbody>
									</table>
								</div>
								<div class="ac-sublayer-page ac-sublayer-style">
									<input type="hidden" name="styles">
									<table>
										<tbody>
											<tr>
												<td><?php _e('Layout & Positions', REVSLIDER_TEXTDOMAIN) ?></td>
												<td class="right"><?php _e('Width', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="width" class="auto" value="" data-help="<?php _e("You can set the width of your layer. You can use pixels, percents, or the default value 'auto'. Examples: 100px, 50% or auto", "revSlider") ?>"></td>
												<td class="right"><?php _e('Height', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="height" class="auto" value="" data-help="<?php _e("You can set the height of your layer. You can use pixels, percents, or the default value 'auto'. Examples: 100px, 50% or auto", "revSlider") ?>"></td>
												<td class="right"><?php _e('Top', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="top" value="20px" data-help="<?php _e("The layer position from the top of the slide. You can use pixels and percents. Examples: 100px or 50%. You can move your layers in the preview above with a drag n' drop, or set the exact values here.", "revSlider") ?>"></td>
												<td class="right"><?php _e('Left', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="left" value="20px" data-help="<?php _e("The layer position from the left side of the slide. You can use pixels and percents. Examples: 100px or 50%. You can move your layers in the preview above with a drag n' drop, or set the exact values here.", "revSlider") ?>"></td>
											</tr>
											<tr>
												<td><?php _e('Padding', REVSLIDER_TEXTDOMAIN) ?></td>
												<td class="right"><?php _e('Top', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="padding-top" class="auto" value="" data-help="<?php _e('Padding on the top of the layer. Example: 10px', REVSLIDER_TEXTDOMAIN) ?>"></td>
												<td class="right"><?php _e('Right', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="padding-right" class="auto" value="" data-help="<?php _e('Padding on the right side of the layer. Example: 10px', REVSLIDER_TEXTDOMAIN) ?>"></td>
												<td class="right"><?php _e('Bottom', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="padding-bottom" class="auto" value="" data-help="<?php _e('Padding on the bottom of the layer. Example: 10px', REVSLIDER_TEXTDOMAIN) ?>"></td>
												<td class="right"><?php _e('Left', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="padding-left" class="auto" value="" data-help="<?php _e('Padding on the left side of the layer. Example: 10px', REVSLIDER_TEXTDOMAIN) ?>"></td>
											</tr>
											<tr>
												<td><?php _e('Border', REVSLIDER_TEXTDOMAIN) ?></td>
												<td class="right"><?php _e('Top', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="border-top" class="auto" value="" data-help="<?php _e('Border on the top of the layer. Example: 5px solid #000', REVSLIDER_TEXTDOMAIN) ?>"></td>
												<td class="right"><?php _e('Right', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="border-right" class="auto" value="" data-help="<?php _e('Border on the right side of the layer. Example: 5px solid #000', REVSLIDER_TEXTDOMAIN) ?>"></td>
												<td class="right"><?php _e('Bottom', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="border-bottom" class="auto" value="" data-help="<?php _e('Border on the bottom of the layer. Example: 5px solid #000', REVSLIDER_TEXTDOMAIN) ?>"></td>
												<td class="right"><?php _e('Left', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="border-left" class="auto" value="" data-help="<?php _e('Border on the left side of the layer. Example: 5px solid #000', REVSLIDER_TEXTDOMAIN) ?>"></td>
											</tr>
											<tr>
												<td><?php _e('Font', REVSLIDER_TEXTDOMAIN) ?></td>
												<td class="right"><?php _e('Family', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="font-family" class="auto" value="" data-help="<?php _e('List of your chosen fonts separated with a comma. Please use apostrophes if your font names contains white spaces. Example: Helvetica, Arial, sans-serif', REVSLIDER_TEXTDOMAIN) ?>"></td>
												<td class="right"><?php _e('Size', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="font-size" class="auto" value="" data-help="<?php _e('The font size in pixels. Example: 16px.', REVSLIDER_TEXTDOMAIN) ?>"></td>
												<td class="right"><?php _e('Line-height', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="line-height" class="auto" value="" data-help="<?php _e("The line height of your text. The default setting is 'normal'. Example: 22px", "revSlider") ?>"></td>
												<td class="right"><?php _e('Color', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="color" class="auto ac-colorpicker" value="" data-help="<?php _e('The color of your text. You can use color names, hexadecimal, RGB or RGBA values. Example: #333', REVSLIDER_TEXTDOMAIN) ?>"></td>
											</tr>
											<tr>
												<td><?php _e('Misc', REVSLIDER_TEXTDOMAIN) ?></td>
												<td class="right"><?php _e('Background', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="background" class="auto ac-colorpicker" value="" data-help="<?php _e("The background color of your layer. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF", "revSlider") ?>"></td>
												<td class="right"><?php _e('Rounded corners', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="border-radius" class="auto" value="" data-help="<?php _e('If you want rounded corners, you can set here its radius. Example: 5px', REVSLIDER_TEXTDOMAIN) ?>"></td>
												<td class="right"><?php _e('Word-wrap', REVSLIDER_TEXTDOMAIN) ?></td>
												<td colspan="3"><input type="checkbox" name="wordwrap" class="checkbox" data-help="<?php _e('If you use custom sized layers, you have to enable this setting to wrap your text.', REVSLIDER_TEXTDOMAIN) ?>"></td>
											</tr>
											<tr>
												<td><?php _e('Custom style settings', REVSLIDER_TEXTDOMAIN) ?></td>
												<td class="right"><?php _e('Custom styles', REVSLIDER_TEXTDOMAIN) ?></td>
												<td colspan="7"><textarea rows="5" cols="50" name="style" class="style" data-help="<?php _e('If you want to set style settings other then above, you can use here any CSS codes. Please make sure to write valid markup.', REVSLIDER_TEXTDOMAIN) ?>"></textarea></td>
											</tr>
										</tbody>
									</table>
								</div>
								<div class="ac-sublayer-page ac-sublayer-attributes">
									<table>
										<tbody>
											<tr>
												<td class="right" rowspan="2"><?php _e('Attributes', REVSLIDER_TEXTDOMAIN) ?></td>
												<td class="right"><?php _e('ID', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="id" value="" data-help="<?php _e('You can apply an ID attribute on the HTML element of this layer to work with it in your custom CSS or Javascript code.', REVSLIDER_TEXTDOMAIN) ?>"></td>
												<td class="right"><?php _e('Classes', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="class" value="" data-help="<?php _e('You can apply classes on the HTML element of this layer to work with it in your custom CSS or Javascript code.', REVSLIDER_TEXTDOMAIN) ?>"></td>
												<td class="right"><?php _e('Title', REVSLIDER_TEXTDOMAIN) ?></td>
												<td colspan="3"><input type="text" name="title" value="" data-help="<?php _e('You can add a title to this layer which will display as a tooltip if someone holds his mouse cursor over the layer.', REVSLIDER_TEXTDOMAIN) ?>"></td>
											</tr>
											<tr>
												<td class="right notfirst"><?php _e('Alt', REVSLIDER_TEXTDOMAIN) ?></td>
												<td><input type="text" name="alt" value="" data-help="<?php _e('You can add an alternative text to your layer which is indexed by search engine robots and it helps people with certain disabilities.', REVSLIDER_TEXTDOMAIN) ?>"></td>
												<td class="right"><?php _e('Rel', REVSLIDER_TEXTDOMAIN) ?></td>
												<td colspan="5"><input type="text" name="rel" value="" data-help="<?php _e('Some plugin may use the rel attribute of a linked content, here you can specify it to make interaction with these plugins.', REVSLIDER_TEXTDOMAIN) ?>"></td>
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
		<a href="#" class="ac-add-sublayer"><?php _e('Add new layer', REVSLIDER_TEXTDOMAIN) ?></a>
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
		<?php _e('Edit this Revolution Slider', REVSLIDER_TEXTDOMAIN) ?>
		<a href="<?php print url(SLIDER_LIST_PATH)?>" class="add-new-h2"><?php _e('Back to the list', REVSLIDER_TEXTDOMAIN) ?></a>
	</h2>

	<!-- [Main menu bar] -->
	<div id="ac-main-nav-bar">
		<a href="#" class="settings"><?php _e('Global Settings', REVSLIDER_TEXTDOMAIN) ?></a>
		<a href="#" class="layers active"><?php _e('Slides', REVSLIDER_TEXTDOMAIN) ?></a>
		<a href="#" class="clear unselectable"></a>
	</div>

	<!-- [Pages] -->
	<div id="ac-pages">

		<!-- [Global Settings] -->
		<div class="ac-page ac-settings">

			<div id="post-body-content">
				<div id="titlediv">
					<div id="titlewrap">
						<input type="text" name="title" value="<?php echo $slider['properties']['title'] ?>" id="title" autocomplete="off" placeholder="<?php _e('Type your slider name here', REVSLIDER_TEXTDOMAIN) ?>">
					</div>
				</div>
			</div>

			<div class="ac-box" id="global-settings">
				<h3 class="header"><?php _e('Global Settings', REVSLIDER_TEXTDOMAIN) ?></h3>
				<table>
					<thead>
						<tr>
							<td colspan="7">
								<span id="ac-icon-basic"></span>
								<h4><?php _e('Slider Layout', REVSLIDER_TEXTDOMAIN) ?></h4>
							</td>
						</tr>
					</thead>
					<tbody>
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('type', REVSLIDER_TEXTDOMAIN) ?></td>
						<td>
							<select name="slider_type">
									<option value="fixed"<?php echo ($slider['properties']['slider_type'] == 'fixed') ? 'selected="selected"' : '' ?>><?php _e('Fixed', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="responsitive"<?php echo ($slider['properties']['slider_type'] == 'responsitive') ? 'selected="selected"' : '' ?>><?php _e('Custom', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="fullwidth"<?php echo ($slider['properties']['slider_type'] == 'fullwidth') ? 'selected="selected"' : '' ?>><?php _e('Auto Responsive', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="fullscreen"<?php echo ($slider['properties']['slider_type'] == 'fullscreen') ? 'selected="selected"' : '' ?>><?php _e('Full Screen   ', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
						
						<td class="right"><?php _e('Grid Width', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="width" value="<?php echo $slider['properties']['width'] ?>"> (px)</td>
						<td class="right"><?php _e('Grid Height', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="height" value="<?php echo $slider['properties']['height'] ?>"> (px)</td>
					</tr>
					
					<tr class="fullscreen_tr">
						<td class="right"></td>
						<td class="right"><?php _e('Fullscreen Offset Container:', REVSLIDER_TEXTDOMAIN) ?></td>
						<td colspan="5"><input type="text" name="fullscreen_offset_container" value="<?php echo isset($slider['properties']['fullscreen_offset_container']) ? $slider['properties']['fullscreen_offset_container'] : '' ?>" data-help="<?php print _e('Example: #header | The height of fullscreen slider will be decreased with the height of the #header to fit perfect in the screen.', REVSLIDER_TEXTDOMAIN)?>"></td>
					</tr>
					
					<?php for ($i =1; $i<= 6; $i++):?>
					<tr class='responsitive-row'>
						<td class="right"><?php _e('Responsive Sizes ' . $i, REVSLIDER_TEXTDOMAIN) ?></td>
						<td class="right"><?php _e('Screen Width' . $i, REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="responsitive_w<?php print $i?>" value="<?php echo isset($slider['properties']['responsitive_w'. $i]) ? $slider['properties']['responsitive_w'. $i] : '' ?>"> (px)</td>
						<td class="right"><?php _e('Slider Width' . $i, REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="responsitive_sw<?php print $i?>" value="<?php echo $slider['properties']['responsitive_sw'. $i] ?>"> (px)</td>
						<td></td>
						<td></td>
					</tr>
					<?php endfor;?>
					</tbody>
					
					<thead>
						<tr>
							<td colspan="7">
								<span id="ac-icon-general"></span>
								<h4><?php _e('General Settings', REVSLIDER_TEXTDOMAIN) ?></h4>
							</td>
						</tr>
					</thead>
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Delay', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="delay" value="<?php echo $slider['properties']['delay'] ?>" data-help="<?php print _e('Turn Shuffle Mode on and off! Will be randomized only once at the start.', REVSLIDER_TEXTDOMAIN)?>"> (ms)</td>
						
						<td class="right"><?php _e('Shuffle Mode', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="checkbox" class="checkbox" name="shuffle"<?php echo $slider['properties']['shuffle'] == 'true' ? ' checked="checked" '  : '' ?>data-help="<?php print _e('Turn Shuffle Mode on and off! Will be randomized only once at the start.', REVSLIDER_TEXTDOMAIN)?>"></td>
						
						<td class="right"><?php _e('Lazy Load', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="checkbox" class="checkbox" name="lazy_load"<?php echo $slider['properties']['lazy_load'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print _e('The lazy load means that the images will be loaded by demand, it speeds the loading of the slider.', REVSLIDER_TEXTDOMAIN)?>"></td>
					</tr>

					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Load Google Font', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="checkbox" class="checkbox" name="load_googlefont"<?php echo $slider['properties']['load_googlefont'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print _e('yes / no to load google font', REVSLIDER_TEXTDOMAIN)?>"></td>
						<td data-controller="load_googlefont" class="right"><?php _e('Google Font', REVSLIDER_TEXTDOMAIN) ?></td>
						<td data-controller="load_googlefont"><input data-controller="stop_slider" type="text" name="google_font" value="<?php echo $slider['properties']['google_font']?>" data-help="<?php print _e('The google font family to load', REVSLIDER_TEXTDOMAIN)?>"></td>
						<td colspan="2">To add more google fonts please read <a target="_blank" href="http://codecanyon.net/item/slider-revolution-responsive-wordpress-plugin/2751380/faqs/15268"> this tutorial </a></td>
					</tr>	

					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Stop Slider', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="checkbox" class="checkbox" name="stop_slider"<?php echo $slider['properties']['stop_slider'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print _e('On / Off to stop slider after some amount of loops / slides', REVSLIDER_TEXTDOMAIN)?>"></td>
						<td class="right" data-controller="stop_slider"><?php _e('Stop After Loops', REVSLIDER_TEXTDOMAIN) ?></td>
						<td data-controller="stop_slider"><input type="text" name="stop_after_loops" value="<?php echo $slider['properties']['stop_after_loops']?>" data-help="<?php print _e('Stop the slider after certain amount of loops. 0 related to the first loop.', REVSLIDER_TEXTDOMAIN)?>"></td>
						<td class="right" data-controller="stop_slider"><?php _e('Stop At Slide', REVSLIDER_TEXTDOMAIN) ?></td>
						<td data-controller="stop_slider"><input type="text" name="stop_at_slide" value="<?php echo $slider['properties']['stop_at_slide']?>" data-help="<?php print _e('Stop the slider at the given slide.', REVSLIDER_TEXTDOMAIN)?>"></td>
					</tr>
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Disable Title?', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="checkbox" class="checkbox" name="disable_title"<?php echo $slider['properties']['disable_title'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print _e('You can disable title by turning on this option.', REVSLIDER_TEXTDOMAIN)?>"></td>
					</tr>
					<thead>
						<tr>
							<td colspan="7">
								<span id="ac-icon-position"></span>
								<h4><?php _e('Position', REVSLIDER_TEXTDOMAIN) ?></h4>
							</td>
						</tr>
					</thead>
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Position on the page', REVSLIDER_TEXTDOMAIN) ?></td>
						<td>
						<select name="position">
									<option value="left"<?php echo ($slider['properties']['position'] == 'left') ? 'selected="selected"' : '' ?>><?php _e('Left', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="center"<?php echo ($slider['properties']['position'] == 'center') ? 'selected="selected"' : '' ?>><?php _e('Center', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="right"<?php echo ($slider['properties']['position'] == 'right') ? 'selected="selected"' : '' ?>><?php _e('Right', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
						<td class="right"><?php _e('Margin Top', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="margin_top" value="<?php echo $slider['properties']['margin_top']?>" data-help="<?php print _e('The top margin of the slider wrapper div', REVSLIDER_TEXTDOMAIN)?>"> (px)</td>
						<td class="right"><?php _e('Margin Bottom', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="margin_bottom" value="<?php echo $slider['properties']['margin_bottom']?>" data-help="<?php print _e('The Bottom margin of the slider wrapper div', REVSLIDER_TEXTDOMAIN)?>"> (px)</td>
					</tr>	
					<tr id="hor-margin">
						<td colspan="3"></td>
						<td class="right"><?php _e('Margin Left', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="margin_left" value="<?php echo $slider['properties']['margin_left']?>" data-help="<?php print _e('The left margin of the slider wrapper div', REVSLIDER_TEXTDOMAIN)?>"> (px)</td>
						<td class="right"><?php _e('Margin Right', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="margin_right" value="<?php echo $slider['properties']['margin_right']?>" data-help="<?php print _e('The right margin of the slider wrapper div', REVSLIDER_TEXTDOMAIN)?>"> (px)</td>
					</tr>
					
					<thead>
						<tr>
							<td colspan="7">
								<span id="ac-icon-appearance"></span>
								<h4><?php _e('Appearance', REVSLIDER_TEXTDOMAIN) ?></h4>
							</td>
						</tr>
					</thead>
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Shadow Type', REVSLIDER_TEXTDOMAIN) ?></td>
						<td>
						<select name="shadow_type" data-help="<?php _e('The Shadow display underneath the banner. The shadow apply to fixed and responsive modes only, the full width slider don\'t have a shadow.', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="0"<?php echo ($slider['properties']['shadow_type'] == '0') ? 'selected="selected"' : '' ?>><?php _e('No Shadow', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="1"<?php echo ($slider['properties']['shadow_type'] == '1') ? 'selected="selected"' : '' ?>><?php _e('0', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="2"<?php echo ($slider['properties']['shadow_type'] == '2') ? 'selected="selected"' : '' ?>><?php _e('1', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="3"<?php echo ($slider['properties']['shadow_type'] == '3') ? 'selected="selected"' : '' ?>><?php _e('2', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>	
						<td class="right"><?php _e('Show Timer Line', REVSLIDER_TEXTDOMAIN) ?></td>
						<td>
						<select name="show_timerbar" data-help="<?php _e('Show the top running timer line.', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="top"<?php echo ($slider['properties']['show_timerbar'] == 'top') ? 'selected="selected"' : '' ?>><?php _e('Top', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="bottom"<?php echo ($slider['properties']['show_timerbar'] == 'bottom') ? 'selected="selected"' : '' ?>><?php _e('Bottom', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="hide"<?php echo ($slider['properties']['show_timerbar'] == 'hide') ? 'selected="selected"' : '' ?>><?php _e('Hide', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>

							<td class="right"><?php _e('Background color', REVSLIDER_TEXTDOMAIN) ?></td>
							<td>
								<div class="reset-parent">
									<input type="text" name="background_color" class="auto ac-colorpicker" value="<?php echo $slider['properties']['background_color']?>" data-help="<?php _e('Slider wrapper div background color, for transparent slider, leave empty.', REVSLIDER_TEXTDOMAIN) ?>">
								</div>
							</td>
					</tr>
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Padding (border)', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="padding" value="<?php echo $slider['properties']['padding']?>" data-help="<?php _e('The wrapper div padding, if it has value, then together with background color it it will make border around the slider.', REVSLIDER_TEXTDOMAIN) ?>"></td>
						<td class="right"><?php _e('Dotted Overlay Size', REVSLIDER_TEXTDOMAIN) ?></td>
						<td>
							<select name="background_dotted_overlay" data-help="<?php _e('Show a dotted overlay on the whole slider, choose width of dots.', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="none"<?php echo ($slider['properties']['background_dotted_overlay'] == 'none') ? 'selected="selected"' : '' ?>><?php _e('none', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="darkoverlay"<?php echo ($slider['properties']['background_dotted_overlay'] == 'darkoverlay') ? 'selected="selected"' : '' ?>><?php _e('Dark Overlay', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="twoxtwo"<?php echo ($slider['properties']['background_dotted_overlay'] == 'twoxtwo') ? 'selected="selected"' : '' ?>><?php _e('2 x 2 Black', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="twoxtwowhite"<?php echo ($slider['properties']['background_dotted_overlay'] == 'twoxtwowhite') ? 'selected="selected"' : '' ?>><?php _e('2 x 2 White', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="threexthree"<?php echo ($slider['properties']['background_dotted_overlay'] == 'threexthree') ? 'selected="selected"' : '' ?>><?php _e('3 x 3 Black', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="threexthreewhite"<?php echo ($slider['properties']['background_dotted_overlay'] == 'threexthreewhite') ? 'selected="selected"' : '' ?>><?php _e('3 x 3 White', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
						<td class="right"><?php _e('Show Background Image', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="checkbox" class="checkbox" name="show_background_image"<?php echo $slider['properties']['show_background_image'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print _e('yes / no to put background image to the main slider wrapper.', REVSLIDER_TEXTDOMAIN)?>"></td>
					</tr>
					
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Background Image', REVSLIDER_TEXTDOMAIN) ?></td>
						<td data-controller="show_background_image">
							<div class="reset-parent">
								<input type="hidden" name="background_image_fid" class="fid" value="<?php echo $slider['properties']['background_image_fid']?>">
								<input type="text" name="background_image" class="<?php print $uploadClass?>" value="<?php echo $slider['properties']['background_image']?>" data-help="<?php _e('The background image that will be on the slider wrapper. Will be shown at slider preloading.', REVSLIDER_TEXTDOMAIN) ?>">
								<span class="ac-reset">x</span>
							</div>
						</td>
							
						<td class="right"><?php _e('Background Fit', REVSLIDER_TEXTDOMAIN) ?></td>
						<td data-controller="show_background_image"><select name="bg_fit" data-help="<?php _e('How the background will be fitted into the Slider.', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="cover"<?php echo ($slider['properties']['bg_fit'] == 'cover') ? 'selected="selected"' : '' ?>><?php _e('cover', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="contain"<?php echo ($slider['properties']['bg_fit'] == 'contain') ? 'selected="selected"' : '' ?>><?php _e('contain', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="normal"<?php echo ($slider['properties']['bg_fit'] == 'normal') ? 'selected="selected"' : '' ?>><?php _e('normal', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
		
						<td class="right"><?php _e('Background Repeat', REVSLIDER_TEXTDOMAIN) ?></td>
						<td data-controller="show_background_image"><select name="bg_repeat" data-help="<?php _e('How the background will be repeated into the Slider.', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="no-repeat"<?php echo ($slider['properties']['bg_repeat'] == 'no-repeat') ? 'selected="selected"' : '' ?>><?php _e('no-repeat', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="repeat"<?php echo ($slider['properties']['bg_repeat'] == 'repeat') ? 'selected="selected"' : '' ?>><?php _e('repeat', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="repeat-x"<?php echo ($slider['properties']['bg_repeat'] == 'repeat-x') ? 'selected="selected"' : '' ?>><?php _e('repeat-x', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="repeat-y"<?php echo ($slider['properties']['bg_repeat'] == 'repeat-y') ? 'selected="selected"' : '' ?>><?php _e('repeat-y', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
					</tr>	
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Background Position', REVSLIDER_TEXTDOMAIN) ?></td>
						<td data-controller="show_background_image">
							<select name="bg_position" data-help="<?php _e('How the background will be positioned into the Slider', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="center top"<?php echo ($slider['properties']['bg_position'] == 'center top') ? 'selected="selected"' : '' ?>><?php _e('center top', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="center right"<?php echo ($slider['properties']['bg_position'] == 'center right') ? 'selected="selected"' : '' ?>><?php _e('center right', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="center bottom"<?php echo ($slider['properties']['bg_position'] == 'center bottom') ? 'selected="selected"' : '' ?>><?php _e('center bottom', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="left top"<?php echo ($slider['properties']['bg_position'] == 'left top') ? 'selected="selected"' : '' ?>><?php _e('left top', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="left center"<?php echo ($slider['properties']['bg_position'] == 'left center') ? 'selected="selected"' : '' ?>><?php _e('left center', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="left bottom"<?php echo ($slider['properties']['bg_position'] == 'left bottom') ? 'selected="selected"' : '' ?>><?php _e('left bottom', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="right top"<?php echo ($slider['properties']['bg_position'] == 'right top') ? 'selected="selected"' : '' ?>><?php _e('right top', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="right center"<?php echo ($slider['properties']['bg_position'] == 'right center') ? 'selected="selected"' : '' ?>><?php _e('right center', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="right bottom"<?php echo ($slider['properties']['bg_position'] == 'right bottom') ? 'selected="selected"' : '' ?>><?php _e('right bottom', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
					</tr>	
		
					<thead>
						<tr>
							<td colspan="7">
								<span id="ac-icon-nav"></span>
								<h4><?php _e('Navigation', REVSLIDER_TEXTDOMAIN) ?></h4>
							</td>
						</tr>
					</thead>
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Touch Enabled', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="checkbox" class="checkbox" name="touchenabled"<?php echo $slider['properties']['touchenabled'] === 'true' ? ' checked="checked" ' : '' ?>data-help="<?php _e('Enable Swipe Function on touch devices', REVSLIDER_TEXTDOMAIN) ?>"></td>
						<td class="right"><?php _e('Stop On Hover', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="checkbox" class="checkbox" name="stop_on_hover"<?php echo $slider['properties']['stop_on_hover'] === 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print _e('Stop the Timer when hovering the slider.', REVSLIDER_TEXTDOMAIN)?>"></td>
						
						<td class="right"><?php _e('Navigation Type', REVSLIDER_TEXTDOMAIN) ?></td>
						<td>
						<select name="navigaion_type" data-help="<?php _e('Display type of the navigation bar (Default:none).', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="none"<?php echo ($slider['properties']['navigaion_type'] == 'none') ? 'selected="selected"' : '' ?>><?php _e('None', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="bullet"<?php echo ($slider['properties']['navigaion_type'] == 'bullet') ? 'selected="selected"' : '' ?>><?php _e('Bullet', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="thumb"<?php echo ($slider['properties']['navigaion_type'] == 'thumb') ? 'selected="selected"' : '' ?>><?php _e('Thumb', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="both"<?php echo ($slider['properties']['navigaion_type'] == 'both') ? 'selected="selected"' : '' ?>><?php _e('Both', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
					</tr>	
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Navigation Arrows', REVSLIDER_TEXTDOMAIN) ?></td>
						<td>
						<select name="navigation_arrows" data-help="<?php _e('Display position of the Navigation Arrows (** By navigation Type Thumb arrows always centered or none visible).', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="nexttobullets"<?php echo ($slider['properties']['navigation_arrows'] == 'nexttobullets') ? 'selected="selected"' : '' ?>><?php _e('With Bullets', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="solo"<?php echo ($slider['properties']['navigation_arrows'] == 'solo') ? 'selected="selected"' : '' ?>><?php _e('Solo', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="none"<?php echo ($slider['properties']['navigation_arrows'] == 'None') ? 'selected="selected"' : '' ?>><?php _e('None', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
						<td class="right"><?php _e('Navigation Style', REVSLIDER_TEXTDOMAIN) ?></td>
						<td>
						<select name="navigation_style" data-help="<?php _e('Look of the navigation bullets  ** If you choose navbar, we recommend to choose Navigation Arrows to nexttobullets.', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="round"<?php echo ($slider['properties']['navigation_style'] == 'round') ? 'selected="selected"' : '' ?>><?php _e('round', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="navbar"<?php echo ($slider['properties']['navigation_style'] == 'navbar') ? 'selected="selected"' : '' ?>><?php _e('navbar', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="round-old"<?php echo ($slider['properties']['navigation_style'] == 'round-old') ? 'selected="selected"' : '' ?>><?php _e('Old Round', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="square-old"<?php echo ($slider['properties']['navigation_style'] == 'square-old') ? 'selected="selected"' : '' ?>><?php _e('Old Square', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="navbar-old"<?php echo ($slider['properties']['navigation_style'] == 'navbar-old') ? 'selected="selected"' : '' ?>><?php _e('Old Navbar', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
						<td class="right"><?php _e('Always Show Navigation', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="checkbox" class="checkbox" name="navigaion_always_on"<?php echo $slider['properties']['navigaion_always_on'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php print _e('Always show the navigation and the thumbnails.', REVSLIDER_TEXTDOMAIN)?>"></td>
					</tr>
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Hide Navitagion After', REVSLIDER_TEXTDOMAIN) ?></td>
						<td colspan="5"><input type="text" name="hide_thumbs" value="<?php echo $slider['properties']['hide_thumbs']?>" data-help="<?php _e('Time after that the Navigation and the Thumbs will be hidden(Default: 200 ms).', REVSLIDER_TEXTDOMAIN) ?>"> (ms)</td>
					</tr>	
					
					<tr>
						<td class="right"><?php _e('Navigation:', REVSLIDER_TEXTDOMAIN) ?></td>
						<td class="right"><?php _e('Horizontal Align', REVSLIDER_TEXTDOMAIN) ?></td>
						<td>
						<select name="navigaion_align_hor" data-help="<?php _e('Horizontal Align of Bullets / Thumbnails.', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="left"<?php echo ($slider['properties']['navigaion_align_hor'] == 'left') ? 'selected="selected"' : '' ?>><?php _e('Left', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="center"<?php echo ($slider['properties']['navigaion_align_hor'] == 'center') ? 'selected="selected"' : '' ?>><?php _e('Center', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="right"<?php echo ($slider['properties']['navigaion_align_hor'] == 'right') ? 'selected="selected"' : '' ?>><?php _e('Right', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
						<td class="right"><?php _e('Vertical Align', REVSLIDER_TEXTDOMAIN) ?></td>
						<td>
						<select name="navigaion_align_vert" data-help="<?php _e('Vertical Align of Bullets / Thumbnails.', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="top"<?php echo ($slider['properties']['navigaion_align_vert'] == 'top') ? 'selected="selected"' : '' ?>><?php _e('Top', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="center"<?php echo ($slider['properties']['navigaion_align_vert'] == 'center') ? 'selected="selected"' : '' ?>><?php _e('Center', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="bottom"<?php echo ($slider['properties']['navigaion_align_vert'] == 'bottom') ? 'selected="selected"' : '' ?>><?php _e('Bottom', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
						<td class="right"><?php _e('Horizontal Offset', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="navigaion_offset_hor" value="<?php echo $slider['properties']['navigaion_offset_hor']?>" data-help="<?php _e('Offset from current Horizontal position of Bullets / Thumbnails negative and positive direction.', REVSLIDER_TEXTDOMAIN) ?>"> (px)</td>
					</tr>
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Vertical Offset', REVSLIDER_TEXTDOMAIN) ?></td>
						<td colspan="5"><input type="text" name="navigaion_offset_vert" value="<?php echo $slider['properties']['navigaion_offset_vert']?>" data-help="<?php _e('Offset from current Vertical  position of Bullets / Thumbnails negative and positive direction.', REVSLIDER_TEXTDOMAIN) ?>"> (px)</td>
					</tr>
					
					<tr>
						<td class="right"><?php _e('Left Arrow:') ?></td>
						<td class="right"><?php _e('Horizontal Align', REVSLIDER_TEXTDOMAIN) ?></td>
						<td>
						<select name="leftarrow_align_hor" data-help="<?php _e('Horizontal Align of left Arrow (only if arrow is not next to bullets).', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="left"<?php echo ($slider['properties']['leftarrow_align_hor'] == 'left') ? 'selected="selected"' : '' ?>><?php _e('Left', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="center"<?php echo ($slider['properties']['leftarrow_align_hor'] == 'center') ? 'selected="selected"' : '' ?>><?php _e('Center', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="right"<?php echo ($slider['properties']['leftarrow_align_hor'] == 'right') ? 'selected="selected"' : '' ?>><?php _e('Right', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
						<td class="right"><?php _e('Vertical Align', REVSLIDER_TEXTDOMAIN) ?></td>
						<td>
						<select name="leftarrow_align_vert" data-help="<?php _e('Vertical Align of left Arrow (only if arrow is not next to bullets)', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="top"<?php echo ($slider['properties']['leftarrow_align_vert'] == 'top') ? 'selected="selected"' : '' ?>><?php _e('Top', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="center"<?php echo ($slider['properties']['leftarrow_align_vert'] == 'center') ? 'selected="selected"' : '' ?>><?php _e('Center', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="bottom"<?php echo ($slider['properties']['leftarrow_align_vert'] == 'bottom') ? 'selected="selected"' : '' ?>><?php _e('Bottom', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
						<td class="right"><?php _e('Horizontal Offset', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="leftarrow_offset_hor" value="<?php echo $slider['properties']['leftarrow_offset_hor']?>" data-help="<?php _e('Offset from current Horizontal position of of left Arrow  negative and positive direction.', REVSLIDER_TEXTDOMAIN) ?>"> (px)</td>
					</tr>
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Vertical Offset') ?></td>
						<td colspan="5"><input type="text" name="leftarrow_offset_vert" value="<?php echo $slider['properties']['leftarrow_offset_vert']?>" data-help="<?php _e('Offset from current Vertical position of of left Arrow negative and positive direction.', REVSLIDER_TEXTDOMAIN) ?>"> (px)</td>
					</tr>		
					
					<tr>
						<td class="right"><?php _e('Right Arrow:') ?></td>
						<td class="right"><?php _e('Horizontal Align', REVSLIDER_TEXTDOMAIN) ?></td>
						<td>
						<select name="rightarrow_align_hor" data-help="<?php _e('Horizontal Align of right Arrow (only if arrow is not next to bullets).', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="left"<?php echo ($slider['properties']['rightarrow_align_hor'] == 'left') ? 'selected="selected"' : '' ?>><?php _e('Left', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="center"<?php echo ($slider['properties']['rightarrow_align_hor'] == 'center') ? 'selected="selected"' : '' ?>><?php _e('Center', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="right"<?php echo ($slider['properties']['rightarrow_align_hor'] == 'right') ? 'selected="selected"' : '' ?>><?php _e('Right', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
						<td class="right"><?php _e('Vertical Align', REVSLIDER_TEXTDOMAIN) ?></td>
						<td>
						<select name="rightarrow_align_vert" data-help="<?php _e('Vertical Align of right Arrow (only if arrow is not next to bullets).', REVSLIDER_TEXTDOMAIN) ?>">
									<option value="top"<?php echo ($slider['properties']['rightarrow_align_vert'] == 'top') ? 'selected="selected"' : '' ?>><?php _e('Top', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="center"<?php echo ($slider['properties']['rightarrow_align_vert'] == 'center') ? 'selected="selected"' : '' ?>><?php _e('Center', REVSLIDER_TEXTDOMAIN) ?></option>
									<option value="bottom"<?php echo ($slider['properties']['rightarrow_align_vert'] == 'bottom') ? 'selected="selected"' : '' ?>><?php _e('Bottom', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
						<td class="right"><?php _e('Horizontal Offset', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="rightarrow_offset_hor" value="<?php echo $slider['properties']['rightarrow_offset_hor']?>" data-help="<?php _e('Offset from current Horizontal position of of right Arrow negative and positive direction.', REVSLIDER_TEXTDOMAIN) ?>"> (px)</td>
					</tr>
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Vertical Offset', REVSLIDER_TEXTDOMAIN) ?></td>
						<td colspan="5"><input type="text" name="rightarrow_offset_vert" value="<?php echo $slider['properties']['rightarrow_offset_vert']?>" data-help="<?php _e('Offset from current Vertical position of of right Arrow negative and positive direction.', REVSLIDER_TEXTDOMAIN) ?>"> (px)</td>
					</tr>
					
					<thead>
						<tr>
							<td colspan="7">
								<span id="ac-icon-thumb"></span>
								<h4><?php _e('Thumbnails', REVSLIDER_TEXTDOMAIN) ?></h4>
							</td>
						</tr>
					</thead>		
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Thumb Width', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="thumb_width" value="<?php echo $slider['properties']['thumb_width']?>" data-help="<?php _e('The basic Width of one Thumbnail (only if thumb is selected).', REVSLIDER_TEXTDOMAIN) ?>"> (px)</td>
						<td class="right"><?php _e('Thumb Height', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="thumb_height" value="<?php echo $slider['properties']['thumb_height']?>" data-help="<?php _e('The basic height of one Thumbnail (only if thumb is selected).', REVSLIDER_TEXTDOMAIN) ?>"> (px)</td>
						<td class="right"><?php _e('Thumb Amount', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="thumb_amount" value="<?php echo $slider['properties']['thumb_amount']?>" data-help="<?php _e('the amount of the Thumbs visible same time (only if thumb is selected).', REVSLIDER_TEXTDOMAIN) ?>"></td>
					</tr>
					
					<thead>
						<tr>
							<td colspan="7">
								<span id="ac-icon-mobile"></span>
								<h4><?php _e('Mobile Visibility', REVSLIDER_TEXTDOMAIN) ?></h4>
							</td>
						</tr>
					</thead>		
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Hide Slider Under Width', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="hide_slider_under" value="<?php echo $slider['properties']['hide_slider_under']?>" data-help="<?php _e('Hide the slider under some slider width. Works only in Responsive Style. Not available for Fullwidth.', REVSLIDER_TEXTDOMAIN) ?>"> (px)</td>
						<td class="right"><?php _e('Hide Defined Layers Under Width', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="hide_defined_layers_under" value="<?php echo $slider['properties']['hide_defined_layers_under']?>" data-help="<?php _e('Hide some defined layers in the layer properties under some slider width.', REVSLIDER_TEXTDOMAIN) ?>"> (px)</td>
						<td class="right"><?php _e('Hide All Layers Under Width', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="hide_all_layers_under" value="<?php echo $slider['properties']['hide_all_layers_under']?>" data-help="<?php _e('Hide all layers under some slider width.', REVSLIDER_TEXTDOMAIN) ?>"></td>
					</tr>
					
					<thead>
						<tr>
							<td colspan="7">
								<span id="ac-icon-alternate"></span>
								<h4><?php _e('Alternative First Slide', REVSLIDER_TEXTDOMAIN) ?></h4>
							</td>
						</tr>
					</thead>		
					<tr>
						<td class="right"></td>
						<td class="right"><?php _e('Start With Slide', REVSLIDER_TEXTDOMAIN) ?></td>
						<td><input type="text" name="start_with_slide" value="<?php echo $slider['properties']['start_with_slide']?>" data-help="<?php _e('Change it if you want to start from a different slide then 1.', REVSLIDER_TEXTDOMAIN) ?>"></td>
						<td class="right"><?php _e('First Transition Active', REVSLIDER_TEXTDOMAIN) ?></td>
						<td colspan="3"><input type="checkbox" class="checkbox" name="first_transition_active"<?php echo $slider['properties']['first_transition_active'] == 'true' ? ' checked="checked" ' : '' ?>data-help="<?php _e('If active, it will overwrite the first slide transition. Use it when you want a special transition for the first slide only.', REVSLIDER_TEXTDOMAIN) ?>"></td>
					</tr>
					<tr>
						<td class="right"></td>
						<td class="right" data-controller="first_transition_active"><?php _e('First Transition Type', REVSLIDER_TEXTDOMAIN) ?></td>
						<td data-controller="first_transition_active">
							<select name="first_transition_type" data-help="<?php _e('First slide transition type', REVSLIDER_TEXTDOMAIN) ?>">
							<?php foreach (rev_slider_transitions() as $k => $v):?>
								<option value="<?php print $k?>"<?php echo ($slider['properties']['first_transition_type'] == $k) ? 'selected="selected"' : '' ?>><?php _e($v, REVSLIDER_TEXTDOMAIN) ?></option>
							<?php endforeach?>
							</select>
						</td>
						<td class="right" data-controller="first_transition_active"><?php _e('First Transition Duration', REVSLIDER_TEXTDOMAIN) ?></td>
						<td data-controller="first_transition_active"><input type="text" name="first_transition_duration" value="<?php echo $slider['properties']['first_transition_duration']?>" data-help="<?php _e('First slide transition duration (Default:300, min: 100 max 2000)', REVSLIDER_TEXTDOMAIN) ?>"> (ms)</td>
						<td class="right" data-controller="first_transition_active"><?php _e('First Transition Slot Amount', REVSLIDER_TEXTDOMAIN) ?></td>
						<td data-controller="first_transition_active"><input type="text" name="first_transition_slot_amount" value="<?php echo $slider['properties']['first_transition_slot_amount']?>" data-help="<?php _e('The number of slots or boxes the slide is divided into. If you use boxfade, over 7 slots can be juggy', REVSLIDER_TEXTDOMAIN) ?>"></td>

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
				<a href="#" class="unsortable" id="ac-add-layer"><?php _e('Add new slide', REVSLIDER_TEXTDOMAIN) ?></a>
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
										<?php _e('Slide Options', REVSLIDER_TEXTDOMAIN) ?>
									</h4>
									<button class="button duplicate ac-layer-duplicate"><?php _e('Duplicate this slide', REVSLIDER_TEXTDOMAIN) ?></button>
								</td>
							</tr>
						</thead>
						<tbody class="ac-slide-options">
							<tr>
								<td class="right"><?php _e('Slide options', REVSLIDER_TEXTDOMAIN) ?></td>
								<td class="right"><?php _e('Image', REVSLIDER_TEXTDOMAIN) ?></td>
								<td>
									<div class="reset-parent">
										<input type="hidden" name="background_fid" class="fid" value="<?php echo $layer['properties']['background_fid']?>">
										<input type="text" name="background" class="<?php print $uploadClass?>" value="<?php echo $layer['properties']['background']?>" data-help="<?php _e('The slide image/background. Click into the field to open the WordPress Media Library to choose or upload an image.', REVSLIDER_TEXTDOMAIN) ?>">
										<span class="ac-reset">x</span>
									</div>
								</td>
								
								<td class="right"><?php _e('background color', REVSLIDER_TEXTDOMAIN) ?></td>
								<td>
									<div class="reset-parent">
										<input type="text" name="bgColor" class="auto ac-colorpicker" value="<?php echo $layer['properties']['bgColor']?>" data-help="<?php _e("The background color of slide. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF", "revSlider") ?>">
										<span class="ac-reset">x</span>
									</div>
								</td>
								
								<td class="right"><?php _e('Thumbnail', REVSLIDER_TEXTDOMAIN) ?></td>
								<td>
									<div class="reset-parent">
										<input type="hidden" name="thumbnail_fid" class="fid" value="<?php echo $layer['properties']['thumbnail_fid']?>">
										<input type="text" name="thumbnail" class="<?php print $uploadClass?>" value="<?php echo $layer['properties']['thumbnail']?>" data-help="<?php _e('The thumbnail image of this slide. Click into the field to open the WordPress Media Library to choose or upload an image. If you leave this field empty, the slide image will be used.', REVSLIDER_TEXTDOMAIN) ?>">
										<span class="ac-reset">x</span>
									</div>
								</td>
							 
							</tr>
							<tr>
								<td class="right" rowspan="2"><?php _e('Slide transition', REVSLIDER_TEXTDOMAIN) ?></td>
								<td class="right"><?php _e('Transitions', REVSLIDER_TEXTDOMAIN) ?></td>
								<td class="">
									<input type='hidden' name="slide_transitions" value="<?php print $layer['properties']['slide_transitions']?>" >
									<select name="slide_transition" class="input_checklist no-fancy-select" multiple="" data-minwidth="280px" size="1">
										<?php foreach (rev_slider_transitions() as $k => $v):?>
											<option<?php echo in_array($k, $layer['properties']['slide_transition']) ? ' selected="selected" ' : ' '?>value="<?php print $k?>"><?php _e($v, REVSLIDER_TEXTDOMAIN) ?></option>
										<?php endforeach?>
									</select>
								</td>
								<td class="right"><?php _e('Slot Amount', REVSLIDER_TEXTDOMAIN) ?></td>
								<td><input type="text" name="slot_amount" value="<?php print $layer['properties']['slot_amount']?>" data-help="<?php _e('The number of slots or boxes the slide is divided into. If you use boxfade, over 7 slots can be juggy.', REVSLIDER_TEXTDOMAIN) ?>"> </td>
								<td class="right"><?php _e('Rotation', REVSLIDER_TEXTDOMAIN) ?></td>
								<td><input type="text" name="transition_rotation" class="layerprop" value="<?php print $layer['properties']['transition_rotation']?>" data-help="<?php _e('Rotation (-720 -> 720, 999 = random) Only for Simple Transitions.', REVSLIDER_TEXTDOMAIN) ?>"></td>
							</tr>
							<tr>
								<td class="right notfirst"><?php _e('Transition Duration', REVSLIDER_TEXTDOMAIN) ?></td>
								<td><input type="text" name="transition_duration" class="layerprop" value="<?php print $layer['properties']['transition_duration']?>" data-help="<?php _e('The duration of the transition (Default:300, min: 100 max 2000).', REVSLIDER_TEXTDOMAIN) ?>"> (ms)</td>
								<td class="right"><?php _e('Delay', REVSLIDER_TEXTDOMAIN) ?></td>
								<td colspan="3"><input type="text" name="delay" class="layerprop" value="<?php print $layer['properties']['delay']?>" data-help="<?php _e('A new delay value for the Slide. If no delay defined per slide, the delay defined via Options (9000ms) will be used.', REVSLIDER_TEXTDOMAIN) ?>"> (ms)</td>
							</tr>
							<tr>
								<td class="right" rowspan="2"><?php _e('Link this slide', REVSLIDER_TEXTDOMAIN); ?></td>
								<td class="right"><?php _e('Enable Link', REVSLIDER_TEXTDOMAIN) ?></td>
								<td><input type="checkbox" name="enable_link"<?php print isset($layer['properties']['enable_link']) ? ' checked="checked" ' : ' ' ?>class="checkbox"></td>
								<td class="right" data-controller="enable_link"><?php _e('Link type', REVSLIDER_TEXTDOMAIN) ?></td>
								<td data-controller="enable_link">
									<select name="link_type">
										<option<?php print isset($layer['properties']['link_type']) && $layer['properties']['link_type'] == 'regular' ? ' selected="selected" ' : ' '?>value="regular"><?php _e('Regular', REVSLIDER_TEXTDOMAIN) ?></option>
										<option<?php print isset($layer['properties']['link_type']) && $layer['properties']['link_type'] == 'slide' ? ' selected="selected" ' : ' '?>value="slide"><?php _e('Slide', REVSLIDER_TEXTDOMAIN) ?></option>
									</select>
								</td>
								<td class="right" data-controller="enable_link"><?php _e('Link', REVSLIDER_TEXTDOMAIN) ?></td>			
								<td data-controller="enable_link"><input type="text" name="link" value="<?php print isset($layer['properties']['link']) ? $layer['properties']['link'] : ''?>" data-help="<?php _e('A link to a url or a slide (you can use \'prev\' and \'next\' or slider number.)', REVSLIDER_TEXTDOMAIN) ?>"></td>
							</tr>
							<tr>
								<td class="right notfirst" data-controller="enable_link"><?php _e('Link target', REVSLIDER_TEXTDOMAIN) ?></td>
								<td data-controller="enable_link">
									<select name="link_open_in" data-help="<?php _e('You can control here the link behaviour: _self means the linked page will open in the current tab/window, _blank will create a new tab/window.', REVSLIDER_TEXTDOMAIN) ?>">
										<option<?php print (isset($layer['properties']['link_open_in']) && $layer['properties']['link_open_in'] == '_self') ? ' selected="selected"' : ''?>>_self</option>
										<option<?php print (isset($layer['properties']['link_open_in']) && $layer['properties']['link_open_in'] == '_blank') ? ' selected="selected"' : ''?>>_blank</option>
										<option<?php print (isset($layer['properties']['link_open_in']) && $layer['properties']['link_open_in'] == '_parent') ? ' selected="selected"' : ''?>>_parent</option>
										<option<?php print (isset($layer['properties']['link_open_in']) && $layer['properties']['link_open_in'] == '_top') ? ' selected="selected"' : ''?>>_top</option>
									</select>
								</td>
								<td class="right" data-controller="enable_link"><?php _e('Link Position', REVSLIDER_TEXTDOMAIN) ?></td>
								<td data-controller="enable_link" colspan="3">
									<select name="link_pos" data-help="<?php _e('The position of the link related to layers.', REVSLIDER_TEXTDOMAIN) ?>">
										<option<?php print (isset($layer['properties']['link_pos']) && $layer['properties']['link_pos'] == 'front') ? ' selected="selected" ' : ' '?>value="front"><?php _e('Front', REVSLIDER_TEXTDOMAIN) ?></option>
										<option<?php print (isset($layer['properties']['link_pos']) && $layer['properties']['link_pos'] == 'back') ? ' selected="selected" ' : ' '?>value="back"><?php _e('Back', REVSLIDER_TEXTDOMAIN) ?></option>
									</select>
								</td>
							</tr>
							
							<tr>
								<td class="right"><?php _e('Misc', REVSLIDER_TEXTDOMAIN) ?></td>
								<td class="right"><?php _e('Full Width Centering', REVSLIDER_TEXTDOMAIN) ?></td>
								<td><input type="checkbox" name="fullwidth_centering" class="checkbox"<?php print isset($layer['properties']['fullwidth_centering']) ? ' checked="checked" ' : ' ' ?>data-help="<?php _e('Apply to full width mode only. Centering vertically slide images.', REVSLIDER_TEXTDOMAIN)?>"></td>
								<td class="right"><?php _e('Ken Burns / Pan Zoom Settings:', REVSLIDER_TEXTDOMAIN) ?></td>
								<td colspan="3"><input type="checkbox" name="kenburn_effect" class="checkbox"<?php print isset($layer['properties']['kenburn_effect']) ? ' checked="checked" ' : ' '?>></td>
							</tr>
							
							<tr>
								<td class="right"><?php _e('Ken Burns Background', REVSLIDER_TEXTDOMAIN) ?></td>
								<td class="right"><?php _e('Start Position', REVSLIDER_TEXTDOMAIN) ?></td>
								<td>
									<select name="bg_position" id="slide_bg_position">
										<option value="center top"<?php if($layer['properties']['bg_position'] == 'center top') echo ' selected="selected"'; ?>>center top</option>
										<option value="center right"<?php if($layer['properties']['bg_position'] == 'center right') echo ' selected="selected"'; ?>>center right</option>
										<option value="center bottom"<?php if($layer['properties']['bg_position'] == 'center bottom') echo ' selected="selected"'; ?>>center bottom</option>
										<option value="center center"<?php if($layer['properties']['bg_position'] == 'center center') echo ' selected="selected"'; ?>>center center</option>
										<option value="left top"<?php if($layer['properties']['bg_position'] == 'left top') echo ' selected="selected"'; ?>>left top</option>
										<option value="left center"<?php if($layer['properties']['bg_position'] == 'left center') echo ' selected="selected"'; ?>>left center</option>
										<option value="left bottom"<?php if($layer['properties']['bg_position'] == 'left bottom') echo ' selected="selected"'; ?>>left bottom</option>
										<option value="right top"<?php if($layer['properties']['bg_position'] == 'right top') echo ' selected="selected"'; ?>>right top</option>
										<option value="right center"<?php if($layer['properties']['bg_position'] == 'right center') echo ' selected="selected"'; ?>>right center</option>
										<option value="right bottom"<?php if($layer['properties']['bg_position'] == 'right bottom') echo ' selected="selected"'; ?>>right bottom</option>
										<option value="percentage"<?php if($layer['properties']['bg_position'] == 'percentage') echo ' selected="selected"'; ?>>(x%, y%)</option>
									</select>
									<div style="display: none;" class="bg_position bg_position_x">
										<label for="bg_position_x">position x</label>&nbsp;&nbsp;&nbsp;<input type="text" name="bg_position_x" value="<?php print $layer['properties']['bg_position_x']?>" />
									</div>
									<div style="display: none;" class="bg_position bg_position_y">
										<label for="bg_position_y">position y</label>&nbsp;&nbsp;&nbsp;<input type="text" name="bg_position_y" value="<?php print $layer['properties']['bg_position_y']?>" />
									</div>
								</td>
								
								<td class="right"><?php _e('Start Fit: (in %)', REVSLIDER_TEXTDOMAIN) ?></td>
								<td><input type="text" name="kb_start_fit" value="<?php print $layer['properties']['kb_start_fit']?>"></td>
								
								<td class="right"><?php _e('Easing', REVSLIDER_TEXTDOMAIN) ?></td>
								<td>
									<select name="kb_easing">
										<?php foreach ($easing as $key => $title):?>
											<option value="<?php print $key?>"<?php echo ($layer['properties']['kb_easing'] == $key) ? 'selected="selected"' : '' ?>><?php print t($title) ?></option>
										<?php endforeach?>
									</select>
								</td>
							</tr>
							
							<tr>
								<td class="right"></td>
								<td class="right"><?php _e('End Position', REVSLIDER_TEXTDOMAIN) ?></td>
								<td>
									<select name="bg_end_position" id="slide_bg_end_position">
										<option value="center top"<?php if($layer['properties']['bg_end_position'] == 'center top') echo ' selected="selected"'; ?>>center top</option>
										<option value="center right"<?php if($layer['properties']['bg_end_position'] == 'center right') echo ' selected="selected"'; ?>>center right</option>
										<option value="center bottom"<?php if($layer['properties']['bg_end_position'] == 'center bottom') echo ' selected="selected"'; ?>>center bottom</option>
										<option value="center center"<?php if($layer['properties']['bg_end_position'] == 'center center') echo ' selected="selected"'; ?>>center center</option>
										<option value="left top"<?php if($layer['properties']['bg_end_position'] == 'left top') echo ' selected="selected"'; ?>>left top</option>
										<option value="left center"<?php if($layer['properties']['bg_end_position'] == 'left center') echo ' selected="selected"'; ?>>left center</option>
										<option value="left bottom"<?php if($layer['properties']['bg_end_position'] == 'left bottom') echo ' selected="selected"'; ?>>left bottom</option>
										<option value="right top"<?php if($layer['properties']['bg_end_position'] == 'right top') echo ' selected="selected"'; ?>>right top</option>
										<option value="right center"<?php if($layer['properties']['bg_end_position'] == 'right center') echo ' selected="selected"'; ?>>right center</option>
										<option value="right bottom"<?php if($layer['properties']['bg_end_position'] == 'right bottom') echo ' selected="selected"'; ?>>right bottom</option>
										<option value="percentage"<?php if($layer['properties']['bg_end_position'] == 'percentage') echo ' selected="selected"'; ?>>(x%, y%)</option>
									</select>
									<div style="display: none;" class="bg_position bg_position_x">
										<label for="bg_end_position_x">position x</label>&nbsp;&nbsp;&nbsp;<input type="text" name="bg_end_position_x"  value="<?php print $layer['properties']['bg_end_position_x']?>" />
									</div>
									<div style="display: none;" class="bg_position bg_position_y">
										<label for="bg_end_position_y">position y</label>&nbsp;&nbsp;&nbsp;<input type="text" name="bg_end_position_y" value="<?php print $layer['properties']['bg_end_position_y']?>" />
									</div>
								</td>
								
								<td class="right"><?php _e('End Fit: (in %)', REVSLIDER_TEXTDOMAIN) ?></td>
								<td><input type="text" name="kb_end_fit" value="<?php print $layer['properties']['kb_end_fit']?>"></td>
								
								<td class="right"><?php _e('Duration (in ms):	', REVSLIDER_TEXTDOMAIN) ?></td>
								<td>
									<input type="text" name="kb_duration" value="<?php print $layer['properties']['kb_duration']?>" />
								</td>
						</tr>
					</tbody>
						
					</table>
					<table>
						<thead>
							<tr>
								<td>
									<span id="ac-icon-preview"></span>
									<h4><?php _e('Preview', REVSLIDER_TEXTDOMAIN) ?></h4>
                  <button class="button ac-preview-button"><?php _e('Enter Preview', REVSLIDER_TEXTDOMAIN) ?></button>
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
									<h4><?php _e('Layers', REVSLIDER_TEXTDOMAIN) ?></h4>
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
										<span class="ac-icon-duplicate"><button class="button duplicate" data-help="<?php _e('If you will use similar settings for other layers or you want to experiment on a copy, you can duplicate this layer.', REVSLIDER_TEXTDOMAIN) ?>"><?php _e('Duplicate this layer', REVSLIDER_TEXTDOMAIN) ?></button></span>
										<input type="text" name="subtitle" class="ac-sublayer-title" value="<?php echo $sublayer['subtitle'] ?>">
										<div class="clear"></div>
										<div class="ac-sublayer-nav">
											<a href="#" class="active"><?php _e('Basic', REVSLIDER_TEXTDOMAIN) ?></a>
											<a href="#"><?php _e('Options', REVSLIDER_TEXTDOMAIN) ?></a>
											<a href="#"><?php _e('Link', REVSLIDER_TEXTDOMAIN) ?></a>
											<a href="#"><?php _e('Style', REVSLIDER_TEXTDOMAIN) ?></a>
											<a href="#"><?php _e('Attributes', REVSLIDER_TEXTDOMAIN) ?></a>
											<a href="#" title="<?php _e('Remove this layer', REVSLIDER_TEXTDOMAIN) ?>" class="remove">x</a>
										</div>
										<div class="ac-sublayer-pages">
											<div class="ac-sublayer-page ac-sublayer-basic active">
												<select name="type" class="no-fancy-select">
													<option <?php echo ($sublayer['type'] == 'img') ? 'selected="selected"' : '' ?>>img</option>
													<option <?php echo ($sublayer['type'] == 'video') ? 'selected="selected"' : '' ?>>video</option>
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
														<?php _e('Image', REVSLIDER_TEXTDOMAIN) ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-video"></span><br>
														<?php _e('Video', REVSLIDER_TEXTDOMAIN) ?>
													</span> 
													
													<span class="ac-type">
														<span class="ac-icon-div"></span><br>
														<?php _e('Div', REVSLIDER_TEXTDOMAIN) ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-p"></span><br>
														<?php _e('Paragraph', REVSLIDER_TEXTDOMAIN) ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-span"></span><br>
														<?php _e('Span', REVSLIDER_TEXTDOMAIN) ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-h1"></span><br>
														<?php _e('H1', REVSLIDER_TEXTDOMAIN) ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-h2"></span><br>
														<?php _e('H2', REVSLIDER_TEXTDOMAIN) ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-h3"></span><br>
														<?php _e('H3', REVSLIDER_TEXTDOMAIN) ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-h4"></span><br>
														<?php _e('H4', REVSLIDER_TEXTDOMAIN) ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-h5"></span><br>
														<?php _e('H5', REVSLIDER_TEXTDOMAIN) ?>
													</span>
				
													<span class="ac-type">
														<span class="ac-icon-h6"></span><br>
														<?php _e('H6', REVSLIDER_TEXTDOMAIN) ?>
													</span>
												</div>
												
												<div class="layer-content-items clearfix">
													<div class="ac-item ac-image-uploader">
														<?php $imageSrc = !empty($sublayer['image']) ? $sublayer['image'] : $plugins_url . '/images/transparent.png' ?>
														<img src="<?php echo $imageSrc ?>" alt="sublayer image">
														<input type="hidden" name="image_fid" class="fid" value="<?php echo $sublayer['image_fid']?>">
														<input type="text" name="image" class="<?php echo $uploadClass ?>" value="<?php echo $sublayer['image'] ?>">
														<p>
															<?php _e('Click into this text field to open WordPress Media Library where you can upload new images or select previously used ones.', REVSLIDER_TEXTDOMAIN) ?>
														</p>
													</div>
													
													<div class="ac-item ac-video-data">
														<img src="<?php echo file_create_url($plugins_url . '/img/transparent.png') ?>" data-src="<?php echo file_create_url($plugins_url . '/img/transparent.png') ?>" alt="image of video sublayer">
														<button class="button_add_layer_video button" value="add"><?php _e('Add Video', REVSLIDER_TEXTDOMAIN) ?></button>								
														<p>Add video as a sublayer.</p>

														<button class="button_edit_layer_video button" style="display:none" value="edit"><?php _e('Edit Video', REVSLIDER_TEXTDOMAIN) ?></button>								
														<button class="button_del_layer_video button" style="display:none" value="delete"><?php _e('Delete Video', REVSLIDER_TEXTDOMAIN) ?></button>								
														<p style="display:none">click on "Edit video" to change video setting or click on 'delete video' to remove the vide.</p>

														<textarea style="display: none" name="video_data" class="video_data"><?php print !empty($sublayer['video_data']) ? $sublayer['video_data'] : '' ?></textarea>
													</div>
													
													<div class="ac-item ac-html-code">
														<h5><?php _e('Custom HTML content', REVSLIDER_TEXTDOMAIN) ?></h5>
														<textarea name="html" cols="50" rows="5" data-help="<?php _e('Type here the contents of your layer. You can use any HTML codes in this field to insert other contents then text. This field is also shortcode-aware, so you can insert content from other plugins as well as video embed codes.', REVSLIDER_TEXTDOMAIN) ?>"><?php echo stripslashes($sublayer['html']) ?></textarea>
													</div>
												</div>
												
											</div>
											<div class="ac-sublayer-page ac-sublayer-options">
												<table>
													<tbody>
														<tr>
															<td><?php _e('Start Transition', REVSLIDER_TEXTDOMAIN) ?></td>
															<td class="right"><?php _e('Animation', REVSLIDER_TEXTDOMAIN) ?></td>
															<td>
																<select name="animation">
																	<?php foreach ($start_anim as $key => $title):?>
																		<option value="<?php print $key?>"<?php echo ($sublayer['animation'] == $key) ? ' selected="selected" ' : ' ' ?>><?php print t($title) ?></option>
																	<?php endforeach?>
																</select>
															</td>
															<td class="right"><?php _e('Speed', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="speed" class="sublayerprop" value="<?php echo $sublayer['speed'] ?>"> (ms)</td>
															<td class="right"><a href="http://easings.net/" target="_blank"><?php _e('Easing', REVSLIDER_TEXTDOMAIN) ?></a></td>
															<td>
																<select name="easing" class="sublayerprop" data-help="<?php _e('The timing function of the animation, with it you can manipualte the layer movement. Please click on the link next to this select field to open easings.net for more information and real-time examples.', REVSLIDER_TEXTDOMAIN) ?>">
																	<?php foreach ($easing as $key => $title):?>
																		<option value="<?php print $key?>"<?php echo ($sublayer['easing'] == $key) ? 'selected="selected"' : '' ?>><?php print t($title) ?></option>
																	<?php endforeach?>
																</select>
															</td>
															<td class="right"><?php _e('Start Time', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="start" class="sublayerprop" value="<?php echo $sublayer['start'] ?>"> (ms)</td>
														</tr>
														
														<tr>
															<td class="right"><?php _e('End Transition (optional)', REVSLIDER_TEXTDOMAIN) ?></td>
															<td class="right"><?php _e('Animation', REVSLIDER_TEXTDOMAIN) ?></td>
															<td>
																<select name="endanimation">
																	<?php foreach ($end_anim as $key => $title):?>
																		<option value="<?php print $key?>"<?php echo ($sublayer['endanimation'] == $key) ? ' selected="selected" ' : ' ' ?>><?php print t($title) ?></option>
																	<?php endforeach?>
																</select>
															</td>
															<td class="right"><?php _e('End Speed', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="endspeed" class="sublayerprop" value="<?php echo $sublayer['endspeed'] ?>"> (ms)</td>
															<td class="right"><a href="http://easings.net/" target="_blank"><?php _e('Easing', REVSLIDER_TEXTDOMAIN) ?></a></td>
															<td>
																<select name="endeasing" class="sublayerprop" data-help="<?php _e('The timing function of the animation, with it you can manipualte the layer movement. Please click on the link next to this select field to open easings.net for more information and real-time examples.', REVSLIDER_TEXTDOMAIN) ?>">
																	<?php foreach ($end_easing as $key => $title):?>
																		<option value="<?php print $key?>"<?php echo ($sublayer['endeasing'] == $key) ? 'selected="selected"' : '' ?>><?php print t($title) ?></option>
																	<?php endforeach?>
																</select>
															</td>
															<td class="right"><?php _e('End Time', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="endtime" class="sublayerprop" value="<?php echo $sublayer['endtime'] ?>"> (ms)</td>
														</tr>
														<tr>
															<td><?php _e('Other options', REVSLIDER_TEXTDOMAIN) ?></td>
															<td class="right"><?php _e('Hidden', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="checkbox" name="skip" class="checkbox"<?php print isset($sublayer['skip']) ? ' checked="checked" ' : ' ' ?>data-help="<?php _e("If you don't want to use this layer, but you want to keep it, you can hide it with this switch.", "revSlider") ?>"></td>
															<td class="right"><?php _e('Responsive Through All Levels', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="checkbox" name="resizeme" class="sublayerprop"<?php print isset($sublayer['resizeme']) ? ' checked="checked" ' : ' ' ?>class="checkbox"></td>
															<td colspan="4"></td>
														</tr>
												</table>
											</div>
											<div class="ac-sublayer-page ac-sublayer-link">
												<table>
													<tbody>
														<tr>
															<td><?php _e('URL', REVSLIDER_TEXTDOMAIN) ?></td>
															<td class="url"><input type="text" name="url" value="<?php echo $sublayer['url'] ?>" data-help="<?php _e('A link to a url or a slide (you can use \'prev\' and \'next\' or slider number fot linking to a slide)', REVSLIDER_TEXTDOMAIN) ?>"></td>
															<td>
																<select name="target" data-help="<?php _e('You can control here the link behaviour: _self means the linked page will open in the current tab/window, _blank will open it in a new tab/window.', REVSLIDER_TEXTDOMAIN) ?>">
																	<option <?php echo ($sublayer['target'] == '_self') ? 'selected="selected"' : '' ?>>_self</option>
																	<option <?php echo ($sublayer['target'] == '_blank') ? 'selected="selected"' : '' ?>>_blank</option>
																	<option <?php echo ($sublayer['target'] == '_parent') ? 'selected="selected"' : '' ?>>_parent</option>
																	<option <?php echo ($sublayer['target'] == '_top') ? 'selected="selected"' : '' ?>>_top</option>
																</select>
															</td>
														</tr>
													</tbody>
												</table>
											</div>
											<div class="ac-sublayer-page ac-sublayer-style">
												<?php $sublayer['styles'] = !empty($sublayer['styles']) ? json_decode(stripslashes($sublayer['styles']), true) : array(); ?>
												<input type="hidden" name="styles">
												<table>
													<tbody>
														<tr>
															<td><?php _e('Layout & Positions', REVSLIDER_TEXTDOMAIN) ?></td>
															<td class="right"><?php _e('Width', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="width" class="auto" value="<?php echo isset($sublayer['styles']['width']) ? $sublayer['styles']['width'] : '' ?>" data-help="<?php _e("You can set the width of your layer. You can use pixels, percents, or the default value 'auto'. Examples: 100px, 50% or auto", "revSlider") ?>"></td>
															<td class="right"><?php _e('Height', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="height" class="auto" value="<?php echo isset($sublayer['styles']['height']) ? $sublayer['styles']['height'] : '' ?>" data-help="<?php _e("You can set the height of your layer. You can use pixels, percents, or the default value 'auto'. Examples: 100px, 50% or auto", "revSlider") ?>"></td>
															<td class="right"><?php _e('Top', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="top" value="<?php echo $sublayer['top'] ?>" data-help="<?php _e("The layer position from the top of the slide. You can use pixels and percents. Examples: 100px or 50%. You can move your layers in the preview above with a drag n' drop, or set the exact values here.", "revSlider") ?>"></td>
															<td class="right"><?php _e('Left', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="left" value="<?php echo $sublayer['left'] ?>" data-help="<?php _e("The layer position from the left side of the slide. You can use pixels and percents. Examples: 100px or 50%. You can move your layers in the preview above with a drag n' drop, or set the exact values here.", "revSlider") ?>"></td>
														</tr>
														<tr>
															<td><?php _e('Padding', REVSLIDER_TEXTDOMAIN) ?></td>
															<td class="right"><?php _e('Top', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="padding-top" class="auto" value="<?php echo isset($sublayer['styles']['padding-top']) ? $sublayer['styles']['padding-top'] : '' ?>" data-help="<?php _e('Padding on the top of the layer. Example: 10px', REVSLIDER_TEXTDOMAIN) ?>"></td>
															<td class="right"><?php _e('Right', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="padding-right" class="auto" value="<?php echo isset($sublayer['styles']['padding-right']) ? $sublayer['styles']['padding-right'] : '' ?>" data-help="<?php _e('Padding on the right side of the layer. Example: 10px', REVSLIDER_TEXTDOMAIN) ?>"></td>
															<td class="right"><?php _e('Bottom', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="padding-bottom" class="auto" value="<?php echo isset($sublayer['styles']['padding-bottom']) ? $sublayer['styles']['padding-bottom'] : '' ?>" data-help="<?php _e('Padding on the bottom of the layer. Example: 10px', REVSLIDER_TEXTDOMAIN) ?>"></td>
															<td class="right"><?php _e('Left', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="padding-left" class="auto" value="<?php echo isset($sublayer['styles']['padding-left']) ? $sublayer['styles']['padding-left'] : '' ?>" data-help="<?php _e('Padding on the left side of the layer. Example: 10px', REVSLIDER_TEXTDOMAIN) ?>"></td>
														</tr>
														<tr>
															<td><?php _e('Border', REVSLIDER_TEXTDOMAIN) ?></td>
															<td class="right"><?php _e('Top', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="border-top" class="auto" value="<?php echo isset($sublayer['styles']['border-top']) ? $sublayer['styles']['border-top'] : '' ?>" data-help="<?php _e('Border on the top of the layer. Example: 5px solid #000', REVSLIDER_TEXTDOMAIN) ?>"></td>
															<td class="right"><?php _e('Right', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="border-right" class="auto" value="<?php echo isset($sublayer['styles']['border-right']) ? $sublayer['styles']['border-right'] : '' ?>" data-help="<?php _e('Border on the right side of the layer. Example: 5px solid #000', REVSLIDER_TEXTDOMAIN) ?>"></td>
															<td class="right"><?php _e('Bottom', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="border-bottom" class="auto" value="<?php echo isset($sublayer['styles']['border-bottom']) ? $sublayer['styles']['border-bottom'] : '' ?>" data-help="<?php _e('Border on the bottom of the layer. Example: 5px solid #000', REVSLIDER_TEXTDOMAIN) ?>"></td>
															<td class="right"><?php _e('Left', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="border-left" class="auto" value="<?php echo isset($sublayer['styles']['border-left']) ? $sublayer['styles']['border-left'] : '' ?>" data-help="<?php _e('Border on the left side of the layer. Example: 5px solid #000', REVSLIDER_TEXTDOMAIN) ?>"></td>
														</tr>
														<tr>
															<td><?php _e('Font', REVSLIDER_TEXTDOMAIN) ?></td>
															<td class="right"><?php _e('Family', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="font-family" class="auto" value="<?php echo isset($sublayer['styles']['font-family']) ? stripslashes($sublayer['styles']['font-family']) : '' ?>" data-help="<?php _e('List of your chosen fonts separated with a comma. Please use apostrophes if your font names contains white spaces. Example: Helvetica, Arial, sans-serif', REVSLIDER_TEXTDOMAIN) ?>"></td>
															<td class="right"><?php _e('Size', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="font-size" class="auto" value="<?php echo isset($sublayer['styles']['font-size']) ? $sublayer['styles']['font-size'] : '' ?>" data-help="<?php _e('The font size in pixels. Example: 16px.', REVSLIDER_TEXTDOMAIN) ?>"></td>
															<td class="right"><?php _e('Line-height', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="line-height" class="auto" value="<?php echo isset($sublayer['styles']['line-height']) ? $sublayer['styles']['line-height'] : '' ?>" data-help="<?php _e("The line height of your text. The default setting is 'normal'. Example: 22px", "revSlider") ?>"></td>
															<td class="right"><?php _e('Color', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="color" class="auto ac-colorpicker" value="<?php echo isset($sublayer['styles']['color']) ? $sublayer['styles']['color'] : '' ?>" data-help="<?php _e('The color of your text. You can use color names, hexadecimal, RGB or RGBA values. Example: #333', REVSLIDER_TEXTDOMAIN) ?>"></td>
														</tr>
														<tr>
															<td><?php _e('Misc', REVSLIDER_TEXTDOMAIN) ?></td>
															<td class="right"><?php _e('Background', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="background" class="auto ac-colorpicker" value="<?php echo isset($sublayer['styles']['background']) ? $sublayer['styles']['background'] : '' ?>" data-help="<?php _e("The background color of your layer. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF", "revSlider") ?>"></td>
															<td class="right"><?php _e('Rounded corners', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="border-radius" class="auto" value="<?php echo isset($sublayer['styles']['border-radius']) ? $sublayer['styles']['border-radius'] : '' ?>" data-help="<?php _e('If you want rounded corners, you can set here its radius. Example: 5px', REVSLIDER_TEXTDOMAIN) ?>"></td>
															<td class="right"><?php _e('Word-wrap', REVSLIDER_TEXTDOMAIN) ?></td>
															<td colspan="3"><input type="checkbox" name="wordwrap" data-help="<?php _e('If you use custom sized layers, you have to enable this setting to wrap your text.', REVSLIDER_TEXTDOMAIN) ?>" class="checkbox"<?php echo isset($sublayer['wordwrap']) ? ' checked="checked"' : '' ?>></td>
														</tr>
														<tr>
															<td><?php _e('Custom style settings', REVSLIDER_TEXTDOMAIN) ?></td>
															<td class="right"><?php _e('Custom styles', REVSLIDER_TEXTDOMAIN) ?></td>
															<td colspan="7"><textarea rows="5" cols="50" name="style" class="style" data-help="<?php _e('If you want to set style settings other then above, you can use here any CSS codes. Please make sure to write valid markup.', REVSLIDER_TEXTDOMAIN) ?>"><?php echo stripslashes($sublayer['style']) ?></textarea></td>
														</tr>
													</tbody>
												</table>
											</div>
											<div class="ac-sublayer-page ac-sublayer-attributes">
												<table>
													<tbody>
														<tr>
															<td class="right" rowspan="2"><?php _e('Attributes', REVSLIDER_TEXTDOMAIN) ?></td>
															<td class="right"><?php _e('ID', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="id" value="<?php echo $sublayer['id']?>" data-help="<?php _e('You can apply an ID attribute on the HTML element of this layer to work with it in your custom CSS or Javascript code.', REVSLIDER_TEXTDOMAIN) ?>"></td>
															<td class="right"><?php _e('Classes', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="class" value="<?php echo $sublayer['class']?>" data-help="<?php _e('You can apply classes on the HTML element of this layer to work with it in your custom CSS or Javascript code.', REVSLIDER_TEXTDOMAIN) ?>"></td>
															<td class="right"><?php _e('Title', REVSLIDER_TEXTDOMAIN) ?></td>
															<td colspan="3"><input type="text" name="title" value="<?php echo $sublayer['title']?>" data-help="<?php _e('You can add a title to this layer which will display as a tooltip if someone holds his mouse cursor over the layer.', REVSLIDER_TEXTDOMAIN) ?>"></td>
														</tr>
														<tr>
															<td class="right notfirst"><?php _e('Alt', REVSLIDER_TEXTDOMAIN) ?></td>
															<td><input type="text" name="alt" value="<?php echo $sublayer['alt']?>" data-help="<?php _e('You can add an alternative text to your layer which is indexed by search engine robots and it helps people with certain disabilities.', REVSLIDER_TEXTDOMAIN) ?>"></td>
															<td class="right"><?php _e('Rel', REVSLIDER_TEXTDOMAIN) ?></td>
															<td colspan="5"><input type="text" name="rel" value="<?php echo $sublayer['rel']?>" data-help="<?php _e('Some plugin may use the rel attribute of a linked content, here you can specify it to make interaction with these plugins.', REVSLIDER_TEXTDOMAIN) ?>"></td>
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
					<a href="#" class="ac-add-sublayer"><?php _e('Add new layer', REVSLIDER_TEXTDOMAIN) ?></a>
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
                <?php _e('Slide Options', REVSLIDER_TEXTDOMAIN) ?>
              </h4>
              <button class="button duplicate ac-layer-duplicate"><?php _e('Duplicate this slide', REVSLIDER_TEXTDOMAIN) ?></button>
            </td>
          </tr>
        </thead>
				
        <tbody class="ac-slide-options">
          <tr>
            <td class="right"><?php _e('Slide options', REVSLIDER_TEXTDOMAIN) ?></td>
            <td class="right"><?php _e('Image', REVSLIDER_TEXTDOMAIN) ?></td>
            <td>
              <div class="reset-parent">
								<input type="hidden" name="background_fid" class="fid" value="">
                <input type="text" name="background" class="<?php print $uploadClass?>" value="" data-help="<?php _e('The slide image/background. Click into the field to open the WordPress Media Library to choose or upload an image.', REVSLIDER_TEXTDOMAIN) ?>">
                <span class="ac-reset">x</span>
              </div>
            </td>
						
            <td class="right"><?php _e('background color', REVSLIDER_TEXTDOMAIN) ?></td>
            <td>
              <div class="reset-parent">
								<input type="text" name="bgColor" class="auto ac-colorpicker" value="" data-help="<?php _e("The background color of slide. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF", "revSlider") ?>">
                <span class="ac-reset">x</span>
              </div>
            </td>
						
            <td class="right"><?php _e('Thumbnail', REVSLIDER_TEXTDOMAIN) ?></td>
            <td>
              <div class="reset-parent">
								<input type="hidden" name="thumbnail_fid" class="fid" value="">
                <input type="text" name="thumbnail" class="<?php print $uploadClass?>" value="" data-help="<?php _e('The thumbnail image of this slide. Click into the field to open the WordPress Media Library to choose or upload an image. If you leave this field empty, the slide image will be used.', REVSLIDER_TEXTDOMAIN) ?>">
                <span class="ac-reset">x</span>
              </div>
            </td>
           
          </tr>
          <tr>
            <td class="right" rowspan="2"><?php _e('Slide transition', REVSLIDER_TEXTDOMAIN) ?></td>
            <td class="right"><?php _e('Transitions', REVSLIDER_TEXTDOMAIN) ?></td>
            <td>
							<input type='hidden' name="slide_transitions" value="" >
							<select name="slide_transition" class="input_checklist no-fancy-select" multiple="" data-minwidth="280px" size="1">
							<?php foreach (rev_slider_transitions() as $k => $v):?>
								<option value="<?php print $k?>"><?php _e($v, REVSLIDER_TEXTDOMAIN) ?></option>
							<?php endforeach?>
							</select>
            </td>
            <td class="right"><?php _e('Slot Amount', REVSLIDER_TEXTDOMAIN) ?></td>
            <td><input type="text" name="slot_amount" value="7" data-help="<?php _e('The number of slots or boxes the slide is divided into. If you use boxfade, over 7 slots can be juggy.', REVSLIDER_TEXTDOMAIN) ?>"> </td>
            <td class="right"><?php _e('Rotation', REVSLIDER_TEXTDOMAIN) ?></td>
            <td><input type="text" name="transition_rotation" class="layerprop" value="0" data-help="<?php _e('Rotation (-720 -> 720, 999 = random) Only for Simple Transitions.', REVSLIDER_TEXTDOMAIN) ?>"></td>
          </tr>
          <tr>
            <td class="right notfirst"><?php _e('Transition Duration', REVSLIDER_TEXTDOMAIN) ?></td>
            <td><input type="text" name="transition_duration" class="layerprop" value="300" data-help="<?php _e('The duration of the transition (Default:300, min: 100 max 2000).', REVSLIDER_TEXTDOMAIN) ?>"> (ms)</td>
            <td class="right"><?php _e('Delay', REVSLIDER_TEXTDOMAIN) ?></td>
            <td colspan="3"><input type="text" name="delay" class="layerprop" data-help="<?php _e('A new delay value for the Slide. If no delay defined per slide, the delay defined via Options (9000ms) will be used.', REVSLIDER_TEXTDOMAIN) ?>"> (ms)</td>
          </tr>
          <tr>
            <td class="right" rowspan="2"><?php _e('Link this slide', REVSLIDER_TEXTDOMAIN); ?></td>
            <td class="right"><?php _e('Enable Link', REVSLIDER_TEXTDOMAIN) ?></td>
            <td><input type="checkbox" name="enable_link" class="checkbox"></td>
						<td class="right" data-controller="enable_link"><?php _e('Link type', REVSLIDER_TEXTDOMAIN) ?></td>
            <td data-controller="enable_link">
							<select name="link_type">
								<option value="regular"><?php _e('Regular', REVSLIDER_TEXTDOMAIN) ?></option>
								<option value="slide"><?php _e('Slide', REVSLIDER_TEXTDOMAIN) ?></option>
							</select>
						</td>
            <td class="right" data-controller="enable_link"><?php _e('Link', REVSLIDER_TEXTDOMAIN) ?></td>			
            <td data-controller="enable_link"><input type="text" name="link" value="" data-help="<?php _e('A link to a url or a slide (you can use \'prev\' and \'next\' or slider number.)', REVSLIDER_TEXTDOMAIN) ?>"></td>
          </tr>
					<tr>
            <td class="right notfirst" data-controller="enable_link"><?php _e('Link target', REVSLIDER_TEXTDOMAIN) ?></td>
            <td data-controller="enable_link">
              <select name="link_open_in" data-help="<?php _e('You can control here the link behaviour: _self means the linked page will open in the current tab/window, _blank will create a new tab/window.', REVSLIDER_TEXTDOMAIN) ?>">
                <option>_self</option>
                <option>_blank</option>
                <option>_parent</option>
                <option>_top</option>
              </select>
            </td>
						<td class="right" data-controller="enable_link"><?php _e('Link Position', REVSLIDER_TEXTDOMAIN) ?></td>
            <td data-controller="enable_link" colspan="3">
              <select name="link_pos" data-help="<?php _e('The position of the link related to layers.', REVSLIDER_TEXTDOMAIN) ?>">
                <option value="front"><?php _e('Front', REVSLIDER_TEXTDOMAIN) ?></option>
                <option value="back"><?php _e('Back', REVSLIDER_TEXTDOMAIN) ?></option>
              </select>
            </td>
          </tr>
					
		<tr>
					<td class="right"><?php _e('Misc', REVSLIDER_TEXTDOMAIN) ?></td>
					<td class="right"><?php _e('Full Width Centering', REVSLIDER_TEXTDOMAIN) ?></td>
					<td><input type="checkbox" name="fullwidth_centering" class="checkbox" checked="checked" data-help="<?php _e('Apply to full width mode only. Centering vertically slide images.', REVSLIDER_TEXTDOMAIN)?>"></td>
					
					<td class="right"><?php _e('Ken Burns / Pan Zoom Settings:', REVSLIDER_TEXTDOMAIN) ?></td>
					<td colspan="3"><input type="checkbox" name="kenburn_effect" class="checkbox"></td>
					
				</tr>
				
				<tr>
					<td class="right"><?php _e('Ken Burns Background', REVSLIDER_TEXTDOMAIN) ?></td>
					<td class="right"><?php _e('Start Position', REVSLIDER_TEXTDOMAIN) ?></td>
					<td>
						<select name="bg_position" id="slide_bg_position">
							<option value="center top">center top</option>
							<option value="center right">center right</option>
							<option value="center bottom">center bottom</option>
							<option value="center center">center center</option>
							<option value="left top">left top</option>
							<option value="left center">left center</option>
							<option value="left bottom" selected="selected">left bottom</option>
							<option value="right top">right top</option>
							<option value="right center">right center</option>
							<option value="right bottom">right bottom</option>
							<option value="percentage">(x%, y%)</option>
						</select>
						<div style="display: none;" class="bg_position bg_position_x">
							<label for="bg_position_x">position x</label>&nbsp;&nbsp;&nbsp;<input type="text" name="bg_position_x"  value="" />
						</div>
						<div style="display: none;" class="bg_position bg_position_y">
							<label for="bg_position_y">position y</label>&nbsp;&nbsp;&nbsp;<input type="text" name="bg_position_y" value="" />
						</div>
					</td>
					
					<td class="right"><?php _e('Start Fit: (in %)', REVSLIDER_TEXTDOMAIN) ?></td>
					<td><input type="text" name="kb_start_fit" value="120"></td>
					
					<td class="right"><?php _e('Easing', REVSLIDER_TEXTDOMAIN) ?></td>
					<td>
						<select name="kb_easing">
							<?php foreach ($easing as $key => $title):?>
								<option value="<?php print $key?>"<?php echo ($key == 'easeInOutQuint') ? 'selected="selected"' : '' ?>><?php print t($title) ?></option>
							<?php endforeach?>
						</select>
					</td>
				</tr>
				
				<tr>
					<td class="right"></td>
					<td class="right"><?php _e('End Position', REVSLIDER_TEXTDOMAIN) ?></td>
					<td>
						<select name="bg_end_position" id="slide_bg_end_position">
							<option value="center top">center top</option>
							<option value="center right">center right</option>
							<option value="center bottom">center bottom</option>
							<option value="center center">center center</option>
							<option value="left top">left top</option>
							<option value="left center">left center</option>
							<option value="left bottom">left bottom</option>
							<option value="right top" selected="selected">right top</option>
							<option value="right center">right center</option>
							<option value="right bottom">right bottom</option>
							<option value="percentage">(x%, y%)</option>
						</select>
						<div style="display: none;" class="bg_position bg_position_x">
							<label for="bg_end_position_x">position x</label>&nbsp;&nbsp;&nbsp;<input type="text" name="bg_end_position_x"  value="" />
						</div>
						<div style="display: none;" class="bg_position bg_position_y">
							<label for="bg_end_position_y">position y</label>&nbsp;&nbsp;&nbsp;<input type="text" name="bg_end_position_y" value="" />
						</div>
					</td>
					
					<td class="right"><?php _e('End Fit: (in %)', REVSLIDER_TEXTDOMAIN) ?></td>
					<td><input type="text" name="kb_end_fit" value="100"></td>
					
					<td class="right"><?php _e('Duration (in ms):	', REVSLIDER_TEXTDOMAIN) ?></td>
					<td>
						<input type="text" name="kb_duration" value="10000" />
					</td>
				</tr>
				
			</tbody>
				
				
      </table>
      <table>
        <thead>
          <tr>
            <td>
              <span id="ac-icon-preview"></span>
              <h4><?php _e('Preview', REVSLIDER_TEXTDOMAIN) ?></h4>
              <button class="button ac-preview-button"><?php _e('Enter Preview', REVSLIDER_TEXTDOMAIN) ?></button>
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
              <h4><?php _e('Layers', REVSLIDER_TEXTDOMAIN) ?></h4>
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
								<span class="ac-icon-duplicate"><button class="button duplicate" data-help="<?php _e('If you will use similar settings for other layers or you want to experiment on a copy, you can duplicate this layer.', REVSLIDER_TEXTDOMAIN) ?>"><?php _e('Duplicate this layer', REVSLIDER_TEXTDOMAIN) ?></button></span>
                <input type="text" name="subtitle" class="ac-sublayer-title" value="Layer #1">
                <div class="clear"></div>
                <div class="ac-sublayer-nav">
                  <a href="#" class="active"><?php _e('Basic', REVSLIDER_TEXTDOMAIN) ?></a>
                  <a href="#"><?php _e('Options', REVSLIDER_TEXTDOMAIN) ?></a>
                  <a href="#"><?php _e('Link', REVSLIDER_TEXTDOMAIN) ?></a>
                  <a href="#"><?php _e('Style', REVSLIDER_TEXTDOMAIN) ?></a>
                  <a href="#"><?php _e('Attributes', REVSLIDER_TEXTDOMAIN) ?></a>
                  <a href="#" title="<?php _e('Remove this layer', REVSLIDER_TEXTDOMAIN) ?>" class="remove">x</a>
                </div>
                <div class="ac-sublayer-pages">
                  <div class="ac-sublayer-page ac-sublayer-basic active">
                    <select name="type" class="no-fancy-select">
                      <option selected="selected">img</option>
                      <option>video</option>
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
                        <?php _e('Image', REVSLIDER_TEXTDOMAIN) ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-video"></span><br>
                        <?php _e('Video', REVSLIDER_TEXTDOMAIN) ?>
                      </span> 
											
                      <span class="ac-type">
                        <span class="ac-icon-div"></span><br>
                        <?php _e('Div', REVSLIDER_TEXTDOMAIN) ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-p"></span><br>
                        <?php _e('Paragraph', REVSLIDER_TEXTDOMAIN) ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-span"></span><br>
                        <?php _e('Span', REVSLIDER_TEXTDOMAIN) ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-h1"></span><br>
                        <?php _e('H1', REVSLIDER_TEXTDOMAIN) ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-h2"></span><br>
                        <?php _e('H2', REVSLIDER_TEXTDOMAIN) ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-h3"></span><br>
                        <?php _e('H3', REVSLIDER_TEXTDOMAIN) ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-h4"></span><br>
                        <?php _e('H4', REVSLIDER_TEXTDOMAIN) ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-h5"></span><br>
                        <?php _e('H5', REVSLIDER_TEXTDOMAIN) ?>
                      </span>
    
                      <span class="ac-type">
                        <span class="ac-icon-h6"></span><br>
                        <?php _e('H6', REVSLIDER_TEXTDOMAIN) ?>
                      </span>
                    </div>
										
										<div class="layer-content-items clearfix">
											<div class="ac-item ac-image-uploader">
												<img src="<?php echo file_create_url($plugins_url . '/img/transparent.png') ?>" alt="sublayer image">
												<input type="hidden" name="image_fid" class="fid" value="">
												<input type="text" name="image" class="<?php echo $uploadClass ?>" value="">
												<p>
													<?php _e('Click into this text field to open WordPress Media Library where you can upload new images or select previously used ones.', REVSLIDER_TEXTDOMAIN) ?>
												</p>
											</div>
											
											<div class="ac-item ac-video-data">
												<img src="<?php echo file_create_url($plugins_url . '/img/transparent.png') ?>" data-src="<?php echo file_create_url($plugins_url . '/img/transparent.png') ?>" alt="image of video sublayer">
												<button class="button_add_layer_video button" value="add"><?php _e('Add Video', REVSLIDER_TEXTDOMAIN) ?></button>								
												<p>Add video as a sublayer.</p>

												<button class="button_edit_layer_video button" style="display:none" value="edit"><?php _e('Edit Video', REVSLIDER_TEXTDOMAIN) ?></button>								
												<button class="button_del_layer_video button" style="display:none" value="delete"><?php _e('Delete Video', REVSLIDER_TEXTDOMAIN) ?></button>								
												<p style="display:none">click on "Edit video" to change video setting or click on 'delete video' to remove the vide.</p>
												<textarea style="display: none" name="video_data" class="video_data"></textarea>
											</div>
											
											<div class="ac-item ac-html-code">
												<h5><?php _e('Custom HTML content', REVSLIDER_TEXTDOMAIN) ?></h5>
												<textarea name="html" cols="50" rows="5" data-help="<?php _e('Type here the contents of your layer. You can use any HTML codes in this field to insert other contents then text. This field is also shortcode-aware, so you can insert content from other plugins as well as video embed codes.', REVSLIDER_TEXTDOMAIN) ?>"></textarea>
											</div>
										</div>
                  </div>
                  <div class="ac-sublayer-page ac-sublayer-options">
                    <table>
                      <tbody>
                        <tr>
                          <td><?php _e('Start Transition', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td class="right"><?php _e('Animation', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td>
														<select name="animation">
															<?php foreach ($start_anim as $key => $title):?>
																<option value="<?php print $key?>"><?php print t($title) ?></option>
															<?php endforeach?>
														</select>
                          </td>
                          <td class="right"><?php _e('Speed', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="speed" class="sublayerprop" value="300"> (ms)</td>
                          <td class="right"><a href="http://easings.net/" target="_blank"><?php _e('Easing', REVSLIDER_TEXTDOMAIN) ?></a></td>
                          <td>
                            <select name="easing" class="sublayerprop" data-help="<?php _e('The timing function of the animation, with it you can manipualte the layer movement. Please click on the link next to this select field to open easings.net for more information and real-time examples.', REVSLIDER_TEXTDOMAIN) ?>">
															<?php foreach ($easing as $key => $title):?>
																<option value="<?php print $key?>" <?php print $key == 'easeInOutQuint' ? ' selected="selected"' : ''?>><option>><?php print t($title) ?></option>
															<?php endforeach?>
                            </select>
                          </td>
                          <td class="right"><?php _e('Start Time', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="start" class="sublayerprop" value="500"> (ms)</td>
                        </tr>
												
                        <tr>
                          <td class="right"><?php _e('End Transition (optional)', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td class="right"><?php _e('Animation', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td>
														<select name="endanimation">
															<?php foreach ($end_anim as $key => $title):?>
																<option value="<?php print $key?>" <?php print $key == 'auto' ? ' selected="selected"' : ''?>><?php print t($title) ?></option>
															<?php endforeach?>
														</select>
                          </td>
                          <td class="right"><?php _e('End Speed', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="endspeed" class="sublayerprop" value="300"> (ms)</td>
                          <td class="right"><a href="http://easings.net/" target="_blank"><?php _e('Easing', REVSLIDER_TEXTDOMAIN) ?></a></td>
                          <td>
                            <select name="endeasing" class="sublayerprop" data-help="<?php _e('The timing function of the animation, with it you can manipualte the layer movement. Please click on the link next to this select field to open easings.net for more information and real-time examples.', REVSLIDER_TEXTDOMAIN) ?>">
															<?php foreach ($end_easing as $key => $title):?>
																<option value="<?php print $key?>"<?php echo ($key == 'nothing') ? 'selected="selected"' : '' ?>><?php print t($title) ?></option>
															<?php endforeach?>
                            </select>
                          </td>
                          <td class="right"><?php _e('End Time', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="endtime" class="sublayerprop" value="0"> (ms)</td>
                        </tr>
                        <tr>
                          <td><?php _e('Other options', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td class="right"><?php _e('Hidden', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="checkbox" name="skip" class="checkbox" data-help="<?php _e("If you don't want to use this layer, but you want to keep it, you can hide it with this switch.", "revSlider") ?>"></td>
                          <td class="right"><?php _e('Responsive Through All Levels', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="checkbox" name="resizeme" class="sublayerprop" class="checkbox"></td>
                          <td colspan="4"></td>
                        </tr>
										 </tbody>
                    </table>
                  </div>
                  <div class="ac-sublayer-page ac-sublayer-link">
                    <table>
                      <tbody>
                        <tr>
                          <td><?php _e('URL', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td class="url"><input type="text" name="url" value="" data-help="<?php _e('A link to a url or a slide (you can use \'prev\' and \'next\' or slider number fot linking to a slide)', REVSLIDER_TEXTDOMAIN) ?>"></td>
                          <td>
                            <select name="target" data-help="<?php _e('You can control here the link behaviour: _self means the linked page will open in the current tab/window, _blank will open it in a new tab/window.', REVSLIDER_TEXTDOMAIN) ?>">
                              <option>_self</option>
                              <option>_blank</option>
                              <option>_parent</option>
                              <option>_top</option>
                            </select>
                          </td>
                        </tr>
                      </tbody>
                    </table>
                  </div>
                  <div class="ac-sublayer-page ac-sublayer-style">
                    <input type="hidden" name="styles">
                    <table>
                      <tbody>
                        <tr>
                          <td><?php _e('Layout & Positions', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td class="right"><?php _e('Width', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="width" class="auto" value="" data-help="<?php _e("You can set the width of your layer. You can use pixels, percents, or the default value 'auto'. Examples: 100px, 50% or auto", "revSlider") ?>"></td>
                          <td class="right"><?php _e('Height', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="height" class="auto" value="" data-help="<?php _e("You can set the height of your layer. You can use pixels, percents, or the default value 'auto'. Examples: 100px, 50% or auto", "revSlider") ?>"></td>
                          <td class="right"><?php _e('Top', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="top" value="20px" data-help="<?php _e("The layer position from the top of the slide. You can use pixels and percents. Examples: 100px or 50%. You can move your layers in the preview above with a drag n' drop, or set the exact values here.", "revSlider") ?>"></td>
                          <td class="right"><?php _e('Left', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="left" value="20px" data-help="<?php _e("The layer position from the left side of the slide. You can use pixels and percents. Examples: 100px or 50%. You can move your layers in the preview above with a drag n' drop, or set the exact values here.", "revSlider") ?>"></td>
                        </tr>
                        <tr>
                          <td><?php _e('Padding', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td class="right"><?php _e('Top', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="padding-top" class="auto" value="" data-help="<?php _e('Padding on the top of the layer. Example: 10px', REVSLIDER_TEXTDOMAIN) ?>"></td>
                          <td class="right"><?php _e('Right', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="padding-right" class="auto" value="" data-help="<?php _e('Padding on the right side of the layer. Example: 10px', REVSLIDER_TEXTDOMAIN) ?>"></td>
                          <td class="right"><?php _e('Bottom', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="padding-bottom" class="auto" value="" data-help="<?php _e('Padding on the bottom of the layer. Example: 10px', REVSLIDER_TEXTDOMAIN) ?>"></td>
                          <td class="right"><?php _e('Left', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="padding-left" class="auto" value="" data-help="<?php _e('Padding on the left side of the layer. Example: 10px', REVSLIDER_TEXTDOMAIN) ?>"></td>
                        </tr>
                        <tr>
                          <td><?php _e('Border', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td class="right"><?php _e('Top', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="border-top" class="auto" value="" data-help="<?php _e('Border on the top of the layer. Example: 5px solid #000', REVSLIDER_TEXTDOMAIN) ?>"></td>
                          <td class="right"><?php _e('Right', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="border-right" class="auto" value="" data-help="<?php _e('Border on the right side of the layer. Example: 5px solid #000', REVSLIDER_TEXTDOMAIN) ?>"></td>
                          <td class="right"><?php _e('Bottom', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="border-bottom" class="auto" value="" data-help="<?php _e('Border on the bottom of the layer. Example: 5px solid #000', REVSLIDER_TEXTDOMAIN) ?>"></td>
                          <td class="right"><?php _e('Left', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="border-left" class="auto" value="" data-help="<?php _e('Border on the left side of the layer. Example: 5px solid #000', REVSLIDER_TEXTDOMAIN) ?>"></td>
                        </tr>
                        <tr>
                          <td><?php _e('Font', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td class="right"><?php _e('Family', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="font-family" class="auto" value="" data-help="<?php _e('List of your chosen fonts separated with a comma. Please use apostrophes if your font names contains white spaces. Example: Helvetica, Arial, sans-serif', REVSLIDER_TEXTDOMAIN) ?>"></td>
                          <td class="right"><?php _e('Size', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="font-size" class="auto" value="" data-help="<?php _e('The font size in pixels. Example: 16px.', REVSLIDER_TEXTDOMAIN) ?>"></td>
                          <td class="right"><?php _e('Line-height', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="line-height" class="auto" value="" data-help="<?php _e("The line height of your text. The default setting is 'normal'. Example: 22px", "revSlider") ?>"></td>
                          <td class="right"><?php _e('Color', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="color" class="auto ac-colorpicker" value="" data-help="<?php _e('The color of your text. You can use color names, hexadecimal, RGB or RGBA values. Example: #333', REVSLIDER_TEXTDOMAIN) ?>"></td>
                        </tr>
                        <tr>
                          <td><?php _e('Misc', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td class="right"><?php _e('Background', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="background" class="auto ac-colorpicker" value="" data-help="<?php _e("The background color of your layer. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF", "revSlider") ?>"></td>
                          <td class="right"><?php _e('Rounded corners', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="border-radius" class="auto" value="" data-help="<?php _e('If you want rounded corners, you can set here its radius. Example: 5px', REVSLIDER_TEXTDOMAIN) ?>"></td>
                          <td class="right"><?php _e('Word-wrap', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td colspan="3"><input type="checkbox" name="wordwrap" class="checkbox" data-help="<?php _e('If you use custom sized layers, you have to enable this setting to wrap your text.', REVSLIDER_TEXTDOMAIN) ?>"></td>
                        </tr>
                        <tr>
                          <td><?php _e('Custom style settings', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td class="right"><?php _e('Custom styles', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td colspan="7"><textarea rows="5" cols="50" name="style" class="style" data-help="<?php _e('If you want to set style settings other then above, you can use here any CSS codes. Please make sure to write valid markup.', REVSLIDER_TEXTDOMAIN) ?>"></textarea></td>
                        </tr>
                      </tbody>
                    </table>
                  </div>
                  <div class="ac-sublayer-page ac-sublayer-attributes">
                    <table>
                      <tbody>
                        <tr>
                          <td class="right" rowspan="2"><?php _e('Attributes', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td class="right"><?php _e('ID', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="id" value="" data-help="<?php _e('You can apply an ID attribute on the HTML element of this layer to work with it in your custom CSS or Javascript code.', REVSLIDER_TEXTDOMAIN) ?>"></td>
                          <td class="right"><?php _e('Classes', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="class" value="" data-help="<?php _e('You can apply classes on the HTML element of this layer to work with it in your custom CSS or Javascript code.', REVSLIDER_TEXTDOMAIN) ?>"></td>
                          <td class="right"><?php _e('Title', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td colspan="3"><input type="text" name="title" value="" data-help="<?php _e('You can add a title to this layer which will display as a tooltip if someone holds his mouse cursor over the layer.', REVSLIDER_TEXTDOMAIN) ?>"></td>
                        </tr>
												<tr>
                          <td class="right notfirst"><?php _e('Alt', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td><input type="text" name="alt" value="" data-help="<?php _e('You can add an alternative text to your layer which is indexed by search engine robots and it helps people with certain disabilities.', REVSLIDER_TEXTDOMAIN) ?>"></td>
                          <td class="right"><?php _e('Rel', REVSLIDER_TEXTDOMAIN) ?></td>
                          <td colspan="5"><input type="text" name="rel" value="" data-help="<?php _e('Some plugin may use the rel attribute of a linked content, here you can specify it to make interaction with these plugins.', REVSLIDER_TEXTDOMAIN) ?>"></td>
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
      <a href="#" class="ac-add-sublayer"><?php _e('Add new layer', REVSLIDER_TEXTDOMAIN) ?></a>
    </div>
			<?php endif; ?>
			</div>
		</div>

	</div>

	<div class="ac-box ac-publish">
		<h3 class="header"><?php _e('Publish', REVSLIDER_TEXTDOMAIN) ?></h3>
		<div class="inner">
			<button id="button-save" class="button-primary"><?php _e('Save changes', REVSLIDER_TEXTDOMAIN) ?></button>
			<p class="ac-saving-warning"></p>
			<div class="clear"></div>
		</div>
	</div>
</form>
<!-- [/Slider form] -->
<?php require_once dirname(__FILE__) . '/video_dialog.php' ?>
<script type="text/javascript">
  var pluginPath = '<?php print $plugins_url; ?>/';
</script>