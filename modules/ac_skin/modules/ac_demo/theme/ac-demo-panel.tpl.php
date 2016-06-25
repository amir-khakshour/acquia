<div id="ac-demo-panel" class="ac-demo-panel">
	<div class="ac-demo-panel-i">
		<div id="ac-demo-skins" class="ac-demo-skins clearfix">
			<strong><span>Skins</span></strong>
			<?php foreach($skins as $skin => $info):?>
			 <div id="skin-<?php print $skin?>" class="ac-skin-preview<?php print  !isset($_COOKIE['acUserSkin']) && $skin == variable_get('ac_default_skin', 'dark-turquoise') ? ' on' : ''?>">
				<a href="#" data-skin="<?php print $skin?>" data-accent="<?php print $info['accent-color']?>" title="<?php print t($info['name'])?>">
				 <img src="<?php print $info['scr']?>" title="<?php print $skin?>" alt="<?php print $skin?>"/>
				</a>
			 </div>
			<?php endforeach?>
		</div>
		<div id="ac-demo-layout-sel" class="clearfix">
			<strong><span>Layouts</span></strong>
			<div class="form-item">
				<input id="ac-wide-layout" type="radio" name="ac-demo-layout" value="wide" checked="checked" /><label for="ac-wide-layout">Wide</label>
			</div>
			<div class="form-item">
				<input id="ac-boxed-layout" type="radio" name="ac-demo-layout" value="boxed" /><label for="ac-boxed-layout">Boxed</label>
			</div>
		</div>
		<div class="ac-demo-close-btn">
			<a title="<?php print t('Theme Settings')?>" class="btn toggle" href="#"><span class="font-icon icon-cog-2"></span></a>
			<a title="<?php print t('Purchase Theme')?>" class="btn purchase" href="http://themeforest.net/item/aura-responsive-multipurpose-theme/8065072"><span class="font-icon icon-bag-2"></span></a>
		</div>
	</div>
</div>
