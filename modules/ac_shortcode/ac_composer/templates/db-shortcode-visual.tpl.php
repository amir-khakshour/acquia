<section <?php print drupal_attributes($shortcode_attrs) ?>">
    <?php if (isset($controls)): ?>
        <?php print $controls ?>
    <?php endif;?>
    <div <?php print drupal_attributes($shortcode_inner_attrs) ?>>
        <?php print $shortcode_inner ?>
    </div>
</section>