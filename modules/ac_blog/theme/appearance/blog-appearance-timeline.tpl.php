<?php
$post_count = 1;
$prev_post_timestamp = null;
$prev_post_month = null;
$first_timeline_loop = false;
?>

<?php if (!empty($items)): ?>
<div<?php print drupal_attributes($outter_attrs)?>>
  <div<?php print drupal_attributes($wrapper_attrs)?>>
    <?php foreach($items as $item):?>
      <?php
          $post_timestamp = $item['date'];
          $post_month = date('n', $post_timestamp);
          $post_year = date('o', $post_timestamp);
          $current_date = date('o-n');
      ?>
 			<?php if($prev_post_month != $post_month): ?>
				<div class="ac-timeline-date"><h3 class="ac-timeline-title"><?php echo format_date($post_timestamp, 'custom', 'F Y'); ?></h3></div>
			<?php endif; ?>
     <div class="<?php print $item['class']?>"><?php print $item['content']?></div>
      <?php
        $prev_post_timestamp = $post_timestamp;
        $prev_post_month = $post_month;
        $post_count++;
      ?>
    <?php endforeach?>
  </div>
  <?php if (count($items) > 1):?>
  <?php endif ?>
</div>
<?php print $pager?>
<?php endif ?>