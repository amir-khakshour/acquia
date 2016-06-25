<?php if ($section != 'frontend'):?>
<div <?php print $attributes;?> class="<?php print $classes;?>">
  <div class="ac-megamenu-column-inner mega-inner clearfix">
    <?php if($close_button): ?>
      <?php print $close_button;?>
    <?php endif;?>
    <?php print $ac_items;?>
  </div>
</div>
<?php else:?>
<li <?php print $attributes;?> class="<?php print $classes;?>">
  <div class="nav-column-links">
    <?php print $ac_items;?>
  </div>
</li>
<?php endif;?>
