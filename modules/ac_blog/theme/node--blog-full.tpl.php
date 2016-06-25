<?php if ($node_top): ?>
  <div class="l-region l-node-top">
    <?php print render($node_top);?>
  </div>
<?php endif; ?>

<section<?php print drupal_attributes($attributes_array); ?>>
  <div class='s-i'>
    
  <div class="ac-table ac-node-meta-wrap">
      
    <!--Node Meta - Start -->
    <div class="node-meta first ac-cell">
        <div class="meta">
          <?php if ($display_submitted): ?>
              <?php print t('by ') . $name?>
          <?php endif; ?>
          <?php if ($date): ?>
           <span class='sep'></span>
            <?php print $date?>
            <span class='sep'></span>
          <?php endif; ?>
           <?php if (isset($content[AC_BLOG_CAT_FIELD])): ?>
             <?php print render($content[AC_BLOG_CAT_FIELD]) ?>
             <span class='sep'></span>
          <?php endif; ?>
          <?php print $comment_count_formatted?>
        </div>
    </div>
    <!--Node Meta - End-->
    <div class="ac-cell">
      <?php print $share_links ?>
    </div>
  </div>

    <div class="<?php print $media_classes?>">
      <?php print $media; ?>
    </div>
    <!--Node Media-->
    <div class="<?php print $desc_classes?>">
      <?php
        // We hide the comments and links now so that we can render them later.
        if (isset($content[AC_BLOG_CAT_FIELD])) {
          hide($content[AC_BLOG_CAT_FIELD]);
        }
        if (isset($content[AC_BLOG_TAGS_FIELD])) {
          hide($content[AC_BLOG_TAGS_FIELD]);
        }
        hide($content['comments']);
        hide($content['links']);
        print render($content);
       ?>         
    </div>
    <!--Node Meta - Start -->
    <div class="node-meta last">
        <!--Meta-->
        <div class="meta">
          <?php if (isset($content[AC_BLOG_TAGS_FIELD])): ?>
              <span class="icon-tag"></span>
              <?php print render($content[AC_BLOG_TAGS_FIELD]) ?>
              <span class='sep'></span>
          <?php endif; ?>
          <?php print render($content['links']) ?>
        </div>
        <!--Meta-->
    </div>
    <!--Node Meta - End-->
  </div>
</section>

<div class="l-region l-node-bottom">
  <?php if ($about_author):?>
   <?php print $about_author?>
  <?php endif?>
  
  <?php if ($node_bottom): ?>
    <?php print render($node_bottom);?>
  <?php endif; ?>

  <?php if ($content['comments']): ?>
    <?php print render($content['comments'])?>
  <?php endif; ?>
</div>




