<section class="ac-about-author">
  <div class="s-i">
    <div class='item-o'>
     <div class='content ac-table'>
       <div class='ac-author-pic ac-cell'><?php print $picture?></div>
       <div class='ac-author-bio ac-bordered ac-cell'>
         <h5 class='ac-header'><?php print t('about the author: !name', array('!name'=> $name))?></h5>
         <?php print render($biography)?>
       </div>
     </div>
    </div>
  </div>
</section>