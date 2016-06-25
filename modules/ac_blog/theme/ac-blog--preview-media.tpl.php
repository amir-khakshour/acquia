<?php
 if (isset($view) && $view == 'slideshow'){
   print '<div class="ac-slider" data-itemWidth="100%"><ul class="slides">';
   $tag = 'li';
 }else{
  $tag = 'div';
 }
?>
<?php foreach($items as $item):?>
 <<?php print $tag?> class="item"><div class='item-i'><?php print $item['file']?></div></<?php print $tag?>>
<?php endforeach?>

<?php if (isset($view) && $view == 'slideshow'):?>
 </ul>
 </div>
<?php endif?>
