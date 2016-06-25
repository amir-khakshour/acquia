<?php if ($node_top): ?>
  <div class="l-region l-node-top">
    <?php print render($node_top);?>
  </div>
<?php endif; ?>

<section class="block">
  <div class='s-i'>
   <div<?php print drupal_attributes($container_attributes); ?>>
   
     <div class="portfolio-options-bar clearfix">
        <div class="ac-col ac-one-half"><?php print $portfolio_nav ?></div>
        <div class="ac-col ac-one-half"><?php print $share_links ?></div>
        <?php print theme('acquia_sep') ?>
     </div>
     
      <div<?php print drupal_attributes($wrap_attributes); ?>>
        <!--Desc-->
        <div class="<?php print $desc_classes?>">
          <div class="col-inner ac-page-section-container">
            <div class="ac-col ac-two-third first"><div class="col-inner">
              <?php
              // We hide the comments and links now so that we can render them later.
              if (isset($content[AC_PORTFOLIO_FIELD])) {
                 hide($content[AC_PORTFOLIO_FIELD]);
              }
              hide($content['comments']);
              hide($content['links']);
              print render($content);
             ?>
           </div></div>
           <!--project-meta-->
           <div class="project-meta ac-col ac-one-third last"><div class="col-inner">
            <?php if ($display_submitted): ?>
              <div class="meta date">
                <strong><?php print t('date:')?></strong>
                <div class='meta-d'><?php print $date; ?></div>
              </div>
            <?php endif; ?>
          
            <?php if (isset($content[AC_PORTFOLIO_FIELD])): ?>
              <?php if ($display_submitted):?>
                <div class="ac-divider ac-type-line ac-align-center clearfix"><div class="divider-inner"></div></div>
              <?php endif?>
                <div class="meta">
                  <strong><?php print t('category:')?></strong>
                  <div class='meta-d'><?php print render($content[AC_PORTFOLIO_FIELD]) ?></div>
                </div>
            <?php endif; ?>
            
            <?php if (isset($link) || isset($like_btn)):?>
              <div class="ac-divider ac-type-line ac-align-center clearfix"><div class="divider-inner"></div></div>
              <div class="links">
                <?php print $link; ?>
                <?php print $like_btn; ?>
              </div>
            <?php endif?>
          </div></div>
          <!--project-meta-->
       </div>
      </div>
      <!--Desc-->
      <!--Wrapper-->
     </div>

    </div>
  </div>
</section>

<?php if ($node_bottom): ?>
  <div class="l-region l-node-bottom">
    <?php print render($node_bottom);?>
  </div>
<?php endif; ?>
