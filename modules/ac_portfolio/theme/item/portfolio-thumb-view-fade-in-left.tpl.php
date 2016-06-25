<?php if (!empty($media)): ?>
<li<?php print drupal_attributes($attrs)?>><article class='item-i'>
<div class="overlaid-portfolio ac-effect-container">
  <figure><?php print $media?></figure>
  <div class="o-content">
    <div class="ac-f ac-mf">
      <span class="ac-t"><span class="ac-c">
        <span class="ac-c o-links features"><?php print $features?></span>
        <div class="o-info">
          <?php if (isset($title)):?>
            <h4 class='title'><?php print $title?></h4>
          <?php endif?>
          <?php if (isset($tags) || isset($date)):?>
            <div class='meta<?php if (isset($date) && isset($tags)):?> date-tags<?php endif?>'>
            <?php print isset($date) ? $date : ''?>
            <?php if (isset($date) && isset($tags)):?>
             <span class='sep'></span>
            <?php endif?>
            <?php print isset($tags) ? $tags : ''; ?>
            </div>
          <?php endif?>
          <!--data and tags-->
          <?php if (isset($excerpt)):?>
           <div class='excerpt'><?php print $excerpt ?></div>
          <?php endif;?>
          <!--excerpt-->
          <?php if (isset($link) || isset($details)):?>
            <div class='meta link-details'>
             <?php print isset($link) ? $link : ''?>
             <?php print isset($details) ? $details : ''?>
            </div>
          <?php endif;?>
          <!--Links-->
        </div>
        <!--o-info-->
     </span></span>
     </div>
  </div>
</div>
</article></li>
<?php endif?>