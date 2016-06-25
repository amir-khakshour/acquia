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
                            <button class="button duplicate ac-layer-duplicate">
                                <?php print t('Duplicate this slide') ?>
                            </button>
                        </td>
                    </tr>
                </thead>
                <tbody class="ac-slide-options">
                    <tr>
                        <td class="right">
                            <?php print t('Slide options') ?>
                        </td>
                        <td class="right">
                            <?php print t('Background Image') ?>
                        </td>
                        <td>
                            <div class="reset-parent">
                                <input type="hidden" name="background_fid" class="fid" value="">
                                <input type="text" name="background" class="<?php print $uploadClass?>" value="" data-help="<?php print t('The slide image/background. Click into the field to open the Drupal Media Library to choose or upload an image.') ?>">
                                <span class="ac-reset">x</span>
                            </div>
                        </td>

                        <td class="right">
                            <?php print t('Background color') ?>
                        </td>
                        <td>
                            <div class="reset-parent">
                                <input type="text" name="bgColor" class="auto ac-colorpicker" value="" data-help="<?php print t(" The background color of slide. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF ") ?>">
                                <span class="ac-reset">x</span>
                            </div>
                        </td>
                        <td class="right"></td>
                        <td>

                        </td>
                    </tr>
					<tr>
						<td class="right"></td>
						<td>
							<?php print t('Title') ?>
						</td>
						<td colspan="5">
						<input size="100" name="title" class="title" data-help="<?php print t('Enter the Slide title here.') ?>" value="" />
					</tr>
					<tr>
						<td class="right"></td>
						<td>
							<?php print t('Price') ?>
						</td>
						<td colspan="5">
							<input size="20" name="price" class="title" data-help="<?php print t('Enter the Slide title here.') ?>" value="" />
						</td>

					</tr>

					<tr>
						<td class="right"></td>
						<td>
							<?php print t('Subtitle') ?>
						</td>
						<td colspan="5">
							<textarea cols="100" rows="2" name="subtitle" class="subtitle" data-help="<?php print t('Enter the Slide subtitle text.') ?>"></textarea>
						</td>
					</tr>

					<tr>
						<td class="right"></td>
						<td>
							<?php print t('Buy link address:') ?>
						</td>
						<td colspan="5">
							<input size="100" name="buy_link" class="title" data-help="<?php print t('Enter the buy button link here.') ?>" value="" />
						</td>

					</tr>

                </tbody>


            </table>
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
		<?php print t('Edit this Showcase Slider') ?>
		<a href="<?php print url(SLIDER_LIST_PATH)?>" class="add-new-h2"><?php print t('Back to the list') ?></a>
	</h2>

        <!-- [Main menu bar] -->
        <div id="ac-main-nav-bar">
            <a href="#" class="settings">
                <?php print t('Global Settings') ?>
            </a>
            <a href="#" class="layers active">
                <?php print t('Slides') ?>
            </a>
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
                                <td class="right" colspan="1">
                                    <?php print t('Slider Width') ?>
                                </td>
                                <td colspan="5">
                                    <input type="text" name="width" value="<?php echo $slider['properties']['width'] ?>"> The slider width in pixel or percentage.</td>
                            </tr>
                            <tr>
                                <td class="right"></td>
                                <td class="right" colspan="1">
                                    <?php print t('Slider height') ?>
                                </td>
                                <td colspan="5">
                                    <input type="text" name="height" value="<?php echo $slider['properties']['height'] ?>"> The slider height in pixel</td>
                            </tr>

                            <tr>
                                <td class="right"></td>
                                <td class="right">
                                    <?php print t('Slides background image style') ?>
                                </td>
                                <td colspan="5">
                                    <select name="bg_style">
                                        <?php foreach(image_style_options() as $mn => $type):?>
                                            <option value="<?php print $mn?>" <?php echo ($slider[ 'properties'][ 'bg_style']==$mn) ? 'selected="selected"' : '' ?>>
                                                <?php print $type ?>
                                            </option>
                                            <?php endforeach?>
                                    </select>
                                </td>
                            </tr>


                            <tr>
                                <td class="right"></td>
                                <td class="right">
                                    <?php print t('Full width slider?') ?>
                                </td>
                                <td colspan="5">
                                    <input type="checkbox" name="fullwidth" <?php echo ( isset($slider[ 'properties'][ 'fullwidth']) && $slider[ 'properties'][ 'fullwidth'] !='false' ) ? 'checked="checked"' : '' ?>></td>
                            </tr>

                            <tr>
                                <td class="right"></td>
                                <td class="right">
                                    <?php print t('full height?') ?>
                                </td>
                                <td colspan="5">
                                    <input type="checkbox" ame="fullheight" <?php echo ( isset($slider[ 'properties'][ 'fullheight']) && $slider[ 'properties'][ 'fullheight']=='true' ) ? ' checked="checked"' : '' ?>>
                                </td>
                            </tr>

                        </tbody>
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
                                            <a href="#" class="unsortable" id="ac-add-layer">
                                                <?php print t('Add new slide') ?>
                                            </a>
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
                                                    <button class="button duplicate ac-layer-duplicate">
                                                        <?php print t('Duplicate this slide') ?>
                                                    </button>
                                                </td>
                                            </tr>
                                        </thead>
                                        <tbody class="ac-slide-options">
                                            <tr>
                                                <td class="right">
                                                    <?php print t('Slide options') ?>
                                                </td>
                                                <td class="right">
                                                    <?php print t('Background Image') ?>
                                                </td>
                                                <td>
                                                    <div class="reset-parent">
                                                        <input type="hidden" name="background_fid" class="fid" value="<?php echo $layer['properties']['background_fid']?>">
                                                        <input type="text" name="background" class="<?php print $uploadClass?>" value="<?php echo $layer['properties']['background']?>" data-help="<?php print t('The slide image/background. Click into the field to open the Drupal Media Library to choose or upload an image.') ?>">
                                                        <span class="ac-reset">x</span>
                                                    </div>
                                                </td>

                                                <td class="right">
                                                    <?php print t('Background color') ?>
                                                </td>
                                                <td>
                                                    <div class="reset-parent">
                                                        <input type="text" name="bgColor" class="auto ac-colorpicker" value="<?php echo $layer['properties']['bgColor']?>" data-help="<?php print t(" The background color of slide. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF ") ?>">
                                                        <span class="ac-reset">x</span>
                                                    </div>
                                                </td>
                                                <td class="right"></td>
                                                <td>
                                                </td>
                                            </tr>

											<tr>
												<td class="right"></td>
												<td>
													<?php print t('Title') ?>
												</td>
												<td colspan="5">
												<input size="100" name="title" class="title" data-help="<?php print t('Enter the Slide title here.') ?>" value="<?php echo $layer['properties']['title']?>" />
											</tr>
											<tr>
												<td class="right"></td>
												<td>
													<?php print t('Price') ?>
												</td>
												<td colspan="5">
													<input size="20" name="price" class="title" data-help="<?php print t('Enter the Slide title here.') ?>" value="<?php echo $layer['properties']['price']?>" />
												</td>

											</tr>

											<tr>
												<td class="right"></td>
												<td>
													<?php print t('Subtitle') ?>
												</td>
												<td colspan="5">
													<textarea cols="100" rows="2" name="subtitle" class="subtitle" data-help="<?php print t('Enter the Slide subtitle text.') ?>"><?php echo $layer['properties']['subtitle']?></textarea>
												</td>
											</tr>

											<tr>
												<td class="right"></td>
												<td>
													<?php print t('Buy link address:') ?>
												</td>
												<td colspan="5">
													<input size="100" name="buy_link" class="title" data-help="<?php print t('Enter the buy button link here.') ?>" value="<?php echo $layer['properties']['buy_link']?>" />
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
                                                            <button class="button duplicate ac-layer-duplicate">
                                                                <?php print t('Duplicate this slide') ?>
                                                            </button>
                                                        </td>
                                                    </tr>
                                                </thead>

                                                <tbody class="ac-slide-options">
                                                    <tr>
                                                        <td class="right">
                                                            <?php print t('Slide options') ?>
                                                        </td>
                                                        <td class="right">
                                                            <?php print t('Background Image') ?>
                                                        </td>
                                                        <td>
                                                            <div class="reset-parent">
                                                                <input type="hidden" name="background_fid" class="fid" value="">
                                                                <input type="text" name="background" class="<?php print $uploadClass?>" value="" data-help="<?php print t('The slide image/background. Click into the field to open the Drupal Media Library to choose or upload an image.') ?>">
                                                                <span class="ac-reset">x</span>
                                                            </div>
                                                        </td>
                                                        <td class="right">
                                                            <?php print t('Background color') ?>
                                                        </td>
                                                        <td>
                                                            <div class="reset-parent">
                                                                <input type="text" name="bgColor" class="auto ac-colorpicker" value="" data-help="<?php print t(" The background color of slide. You can use color names, hexadecimal, RGB or RGBA values as well as the 'transparent' keyword. Example: #FFF ") ?>">
                                                                <span class="ac-reset">x</span>
                                                            </div>
                                                        </td>
                                                        <td class="right"></td>
                                                        <td>

                                                        </td>
                                                    </tr>
                                                    <tr>
                                                        <td class="right"></td>
                                                        <td>
                                                            <?php print t('Title') ?>
                                                        </td>
                                                        <td colspan="5">
                                                		<input size="100" name="title" class="title" data-help="<?php print t('Enter the Slide title here.') ?>" value="" />
                                                    </tr>
                                                    <tr>
                                                        <td class="right"></td>
                                                        <td>
                                                            <?php print t('Price') ?>
                                                        </td>
                                                        <td colspan="5">
                                                        	<input size="20" name="price" class="title" data-help="<?php print t('Enter the Slide title here.') ?>" value="" />
                                                        </td>

                                                    </tr>

                                                    <tr>
                                                        <td class="right"></td>
                                                        <td>
                                                            <?php print t('Subtitle') ?>
                                                        </td>
                                                        <td colspan="5">
															<textarea cols="100" rows="2" name="subtitle" class="subtitle" data-help="<?php print t('Enter the Slide subtitle text.') ?>"></textarea>
                                                        </td>
                                                    </tr>

                                                    <tr>
                                                        <td class="right"></td>
                                                        <td>
                                                            <?php print t('Buy link address:') ?>
                                                        </td>
                                                        <td colspan="5">
                                                        	<input size="100" name="buy_link" class="title" data-help="<?php print t('Enter the buy button link here.') ?>" value="" />
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
                <button id="button-save" class="button-primary">
                    <?php print t('Save changes') ?>
                </button>
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