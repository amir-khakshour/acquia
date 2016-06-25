<?php if ($section != 'frontend'):?>
<div <?php print $attributes;?> class="<?php print $classes;?>">
  <?php print $columns;?>
</div>
<?php else:?>
<ul <?php print $attributes;?> class="<?php print $classes;?>">
  <?php print $columns;?>
</ul>
<?php endif;?>