<?php if (!empty($items)):?>
<div<?php print drupal_attributes($wrap_attrs)?>>
  <ul class='m-slides clearfix ac-s-li'>
    <?php foreach($items as $item):?>
    <li class="item"><div class='item-i'><?php print $item['file']?></div></li>
    <?php endforeach?>
  </ul>
</div>
<?php endif?>