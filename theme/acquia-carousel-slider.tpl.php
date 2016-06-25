<?php if (!empty($items)):?>
<div<?php print drupal_attributes($wrap_attrs)?>>

  <div class="preview-container">
    <ul<?php print drupal_attributes($preview_attrs)?>>
        <?php foreach($preview_slides as $slide):?>
        <div class='item-i'><?php print $slide?></div>
        <?php endforeach?>
    </ul>
  </div>

  <div class="thumb-container">
    <?php print $thumbs_slider?>
  </div>

</div>
<?php endif?>