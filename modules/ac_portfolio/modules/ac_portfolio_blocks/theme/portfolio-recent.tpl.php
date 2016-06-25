<?php $wrap_attrs['class'] .= ' block'?>
<?php if (!empty($items)): ?>
<section<?php print drupal_attributes($wrap_attrs)?>>
<?php if (isset($sortings)):?>
  <?php if($fullwidth):?>
    <div class='container'><div class='col-inner'><?php print $sortings?></div></div>
  <?php else:?>
    <?php print $sortings?>
  <?php endif?>
<?php endif?>
<div<?php print drupal_attributes($outter_attrs);?>>
<ul<?php print drupal_attributes($wrapper_attrs)?>>
        <?php foreach($items as $item):?><?php print $item?>
        <?php endforeach?>
    </ul>
</div>
<?php print $pager?>
</section>
<?php endif ?>
<?php print isset($footer) ? $footer : ''?>