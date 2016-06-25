<li<?php print drupal_attributes($attrs)?>><article class='item-i'>
<?php if (!empty($media)): ?>
  <div class="overlaid-portfolio ac-effect-container">
    <figure class='clearfix'>
      <?php print $media?>
      <?php if (!empty($features)):?>
      <span class="ac-f">
          <div class="o-info">
            <?php if (isset($title)):?>
              <h4 class='title'><?php print $title?></h4>
            <?php endif?>
            <?php if (isset($excerpt)):?>
              <div class='excerpt'><?php print $excerpt ?></div>
            <?php endif;?>
            <!--excerpt-->
            <?php if (isset($date)):?>
              <strong class='date'>
                <?php print isset($date) ? $date : ''?>
              </strong>
            <?php endif?>
            <!--data-->
          </div>
          <!--o-info-->
      </span>
      <?php endif?>
    </figure>
  </div>
  <?php endif?>
  <!--overlaid-portfolio-->
  <footer class='meta'>
    <?php print $features?>
    <?php print isset($counter) ? $counter : ''?>
    <!--Links-->
  </footer>
</article></li>