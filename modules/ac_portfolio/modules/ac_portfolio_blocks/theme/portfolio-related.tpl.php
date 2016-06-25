<?php if (!empty($items)): ?>
<section<?php print drupal_attributes($wrap_attrs)?>>
    <?php if(!acquia_variable_get('portfolio_related_fullwidth', TRUE)):?>
      <div class='container'>
    <?php endif;?>
    <div<?php print drupal_attributes($outter_attrs)?>>
      <ul<?php print drupal_attributes($wrapper_attrs)?>>
        <?php foreach($items as $item):?>
         <?php print $item?>
        <?php endforeach?>
      </ul>
    </div>
    <?php if(!acquia_variable_get('portfolio_related_fullwidth', TRUE)):?>
      </div>
    <?php endif;?>
</section>
<?php endif ?>
