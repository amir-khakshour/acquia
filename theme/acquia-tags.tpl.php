<ul class="category ac-s-li">
  <?php foreach ($tags as $delta => $tag): ?>
    <li class="<?php print $delta % 2 ? 'odd' : 'even'; ?>">
      <?php print t($tag); ?><?php if ($delta != count($tags)-1):?><span>,&nbsp;</span><?php endif;?>
    </li>
  <?php endforeach; ?>
</ul>