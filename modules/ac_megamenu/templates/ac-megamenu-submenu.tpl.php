<?php if ($section != 'frontend'):?>
  <div <?php print $attributes;?> class="<?php print $classes;?>">
    <div class="mega-dropdown-inner">
      <?php print $rows;?>
    </div>
  </div>
<?php else:?>
  <div <?php print $attributes;?>>
    <div <?php print drupal_attributes($sub_attributes)?>>
      <?php print $rows;?>
    </div>
  </div>
<?php endif;?>