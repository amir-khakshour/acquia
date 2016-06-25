<section<?php print drupal_attributes($attributes_array); ?>>
  <div class='s-i'>
    <div class="<?php print $media_classes?>">
      <?php print isset($media) ? $media : ''; ?>
    </div>
     
    <div class="<?php print $desc_classes?>">
      <div class="item-i">
        <?php if (!empty($title_prefix) || !empty($title_suffix) || !$page): ?>
          <header>
            <?php print render($title_prefix); ?>
            <?php if (!$page): ?>
              <h3<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>" rel="bookmark"><?php print $title; ?></a></h3>
            <?php endif; ?>
            <?php print render($title_suffix); ?>
          </header>
        <?php endif; ?>
        <div class="node-meta">
          <div class='meta'>
            <?php if ($display_submitted && $date): ?>
              <?php print $date?>
              <span class='sep'></span>
            <?php endif; ?>
            <?php if (isset($content[AC_PORTFOLIO_FIELD])): ?>
              <?php print render($content[AC_PORTFOLIO_FIELD]) ?>
            <?php endif; ?>
          </div>
        </div>
        <!--Meta-->
        <div class="project-excerpt"><?php print render($excerpt);?></div>
      </div>
    </div>
    <?php if (isset($read_more)):?>
      <div class='meta read_more'>
       <?php print $read_more?>
      </div>
    <?php endif;?>
    <!--Links-->
  </div>
</section>