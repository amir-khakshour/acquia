<?php if (!empty($media)): ?>
<li<?php print drupal_attributes($attrs)?>><article class='item-i'>
<div class="overlaid-portfolio ac-effect-container">
  <figure><?php print $media?></figure>
  <div class="o-content">
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
      <!--data and tags-->
      <?php endif?>
      <?php if (isset($excerpt)):?>
        <div class='excerpt'><?php print $excerpt ?></div>
      <?php endif;?>
      <!--excerpt-->
      <?php if (isset($link) || isset($details) || isset($features)):?>
        <div class='meta link-details'>
         <?php print isset($link) ? $link : ''?>
         <?php print isset($details) ? $details : ''?>
         <?php print $features?>
        </div>
      <!--Links-->
      <?php endif;?>
    </div>
    <!--o-info-->
  </div>
</div>
</article></li>
<?php endif?>