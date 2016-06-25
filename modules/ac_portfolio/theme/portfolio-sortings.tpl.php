<div <?php print drupal_attributes($attributes_array)?>>
  <div <?php print drupal_attributes($tags_attrs)?>>
    <?php print $tags?>
  </div>
  
  <?php if ($extra_sortings):?>
  <div <?php print drupal_attributes($extra_attrs)?>>
    <?php print $extra_sortings?>
  </div>
  <?php endif?>
  
</div>