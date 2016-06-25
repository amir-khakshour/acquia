<section<?php print drupal_attributes($attributes_array); ?>>
  <div class='s-i'>
    <div class="<?php print $media_classes?>">
      <?php print isset($media) ? $media : ''; ?>
    </div>
    <!--Media-->
    <div class="<?php print $desc_classes?>">
      <div class="item-i">
        <?php if (!empty($title_prefix) || !empty($title_suffix) || !$page): ?>
          <header>
            <?php print render($title_prefix); ?>
            <?php if (!$page): ?>
              <h4<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>" rel="bookmark"><?php print $title; ?></a></h4>
            <?php endif; ?>
            <?php print render($title_suffix); ?>
          </header>
        <?php endif; ?>
        <!--Header-->
        <div class="node-meta">
          <div class='meta'>
            <?php if ($display_submitted): ?>
             <?php print t('by ') . $author?>
             <span class='sep'></span>
             <?php if ($date): ?>
               <?php print $date?>
               <span class='sep'></span>
             <?php endif; ?>
            <?php endif; ?>
            <?php if (isset($content[AC_BLOG_CAT_FIELD])): ?>
              <?php print render($content[AC_BLOG_CAT_FIELD]) ?>
              <span class='sep'></span>
            <?php endif; ?>
            <?php print $comment_count_formatted?>
          </div>
        </div>
        <!--Meta-->
        <div class="blog-excerpt"><?php print strip_tags(render($content['body']));?></div>
        
      </div>
    </div>
    <!--desc_classes-->
    <?php if (isset($read_more)):?>
      <div class='meta read_more'>
       <?php print $read_more?>
      </div>
    <?php endif;?>
    <!--Links-->
  </div>
</section>