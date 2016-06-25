<?php
 if ($view == 'slideshow'){
   print '<div class="ac-slider ac-init-hidden" data-itemWidth="100%"><ul class="slides">';
   $tag = 'li';
 }else{
  $tag = 'div';
 }
?>
<?php foreach($items as $item):?>
 <<?php print $tag?> class="item"><div class='item-i'><?php print $item['file']?></div></<?php print $tag?>>
<?php endforeach?>

<?php if ($view == 'slideshow'):?>
 </ul>
 </div>
<?php endif?>
