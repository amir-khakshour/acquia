<div class='item-i'>
  <?php if (!empty($media)): ?>
  <figure class='clearfix'>
    <?php print isset($media) ? $media : ''; ?>
  </figure>
  <?php endif?>
  <!--Picture-->
  <div class="o-info">
    <div class="ac-timeline-circle"></div>
    <div class="ac-timeline-arrow"></div>
    <?php print isset($picture) ? $picture : ''?>
  <?php if (isset($title)):?>
    <h4 class='title'><?php print $title?></h4>
  <?php endif?>
  <?php if (isset($author)):?>
    <div class='meta<?php if (isset($author) && isset($date)):?> author-date<?php endif?>'>
        <?php print isset($author) ? t('by') .' '.$author : ''?>
        <?php if (isset($author) && isset($date)):?>
         <span class='sep'></span>
        <?php endif?>
        <?php if (isset($date)):?>
          <?php print $date; ?>
        <?php unset($date)?>
        <?php endif?>
    </div>
  <?php endif?>
  <?php if (isset($tags) || isset($date)):?>
    <div class='meta<?php if (isset($date) && isset($tags)):?> date-tags<?php endif?>'>
    <?php print isset($date) ? $date : ''?>
    <?php if (isset($date) && isset($tags)):?>
     <span class='sep'></span>
    <?php endif?>
    <?php print $tags; ?>
    </div>
  <?php endif?>
  <?php if (isset($excerpt)):?>
    <div class='excerpt'><?php print strip_tags(trim(render($excerpt)))?></div>
  <?php endif?>
  <!--data and tags-->
  <div class='meta details'>
    <?php print $comment_count_formatted?>
    <?php print $read_more?>
  </div>
  </div>
</div>