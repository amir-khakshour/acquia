<?php if (!empty($media)): ?>
<li<?php print drupal_attributes($attrs)?>>
  <figure><?php print $media?></figure>
  <div class="o-content">
    <div class="bg-blur"></div>
    <div class="o-info">
      <?php if (isset($title)):?>
        <h4 class='title'><?php print $title?></h4>
      <?php endif?>
      <div class="mobile-hidden">
       <?php if (isset($tags) || isset($date)):?>
         <div class='meta<?php if (isset($date) && isset($tags)):?> date-tags<?php endif?>'>
           <?php print isset($date) ? $date : ''?>
           <?php if (isset($date) && isset($tags)):?>
            <span class='sep'></span>
           <?php endif?>
            <?php print isset($tags) ? $tags : ''; ?>
         </div>
       <!--data and tags-->
       <?php endif?>
       <?php if (isset($excerpt)):?>
        <div class='excerpt'><?php print $excerpt ?></div>
       <?php endif;?>
       <!--excerpt-->
       <?php if (isset($link) || isset($details)):?>
         <div class='meta'>
          <?php print isset($link) ? $link : ''?>
          <?php print isset($details) ? $details : ''?>
         </div>
       <?php endif;?>
       <!--Links-->
      </div>
    </div>
    <!--o-info-->
  </div>
</li>
<?php endif?>