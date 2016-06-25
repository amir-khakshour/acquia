<li<?php print drupal_attributes($attrs)?>><article class='item-i'>
<?php if (!empty($media)): ?>
  <div class="overlaid-portfolio ac-effect-container">
    <figure class='clearfix'>
      <?php print $media?>
      <?php if (!empty($features)):?>
      <i class="ac-f features">
        <span class="ac-t"><span class="ac-c"><?php print $features?></span></span>
      </i>
      <?php endif?>
    </figure>
  </div>
  <?php endif?>
  
  <?php if (isset($title) || isset($date) || isset($tags) || isset($excerpt) || isset($details) || isset($link)):?> 
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
  <?php endif;?>
</article></li>