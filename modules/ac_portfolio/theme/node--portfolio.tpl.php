<?php if ($node_top): ?>
  <div class="l-region l-node-top">
    <?php print render($node_top);?>
  </div>
<?php endif; ?>

<section class="block">
  <div class='s-i'>
   
   <div<?php print drupal_attributes($container_attributes); ?>>
     <div class="portfolio-options-bar ac-page-section-container clearfix">
      <div class="col-inner">
        <div class="ac-col ac-one-half"><?php print $portfolio_nav ?></div>
        <div class="ac-col ac-one-half"><?php print $share_links ?></div>
        <?php print theme('acquia_sep') ?>
      </div>
     </div>
     
     <div<?php print drupal_attributes($wrap_attributes); ?>>
     
     <?php if ($layout == 'left' || $layout == 'before'):?>
       <div class="<?php print $media_classes?>">
        <div class="col-inner">
          <?php print $media; ?>
        </div>
       </div>
     <?php endif;?>
     
     <div class="<?php print $desc_classes?>">
      <div class="col-inner">
       <?php
         // We hide the comments and links now so that we can render them later.
         if (isset($content[AC_PORTFOLIO_FIELD])) {
           hide($content[AC_PORTFOLIO_FIELD]);
         }
         hide($content['comments']);
         hide($content['links']);
         print render($content);
        ?>
        
         <div class="project-meta">
           <?php if ($display_submitted): ?>
             <div class="meta date">
               <h6><?php print t('date:')?></h6>
               <div class='meta-d'><?php print $date; ?></div>
             </div>
           <?php endif; ?>
           <?php if (isset($content[AC_PORTFOLIO_FIELD])): ?>
             <div class="meta">
               <h6><?php print t('category:')?></h6>
               <div class='meta-d'><?php print render($content[AC_PORTFOLIO_FIELD]) ?></div>
             </div>
           <?php endif; ?>
            <?php print theme('acquia_sep') ?>
            <div class="links">
              <?php print $link; ?>
              <?php if (trim($link) !=''):?>
                <span class="sep"></span>
              <?php endif?>
              <?php print $like_btn; ?>
            </div>
         </div>
         
       </div>
     </div>
       
     <?php if ($layout != 'left' && $layout != 'before'):?>
       <div class="<?php print $media_classes?>">
        <div class="col-inner">
          <?php print $media; ?>
        </div>
       </div>
     <?php endif;?>
     
    </div>
  </div>
</section>

<?php if ($node_bottom): ?>
  <div class="l-region l-node-bottom">
    <?php print render($node_bottom);?>
  </div>
<?php endif; ?>
</div>