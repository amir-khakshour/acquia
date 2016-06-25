<li <?php print drupal_attributes($container_attrs) ?>>
    <div class="g-i">
        <div class="g-i-i clearfix">
            <div class="testimonial-inner ac-frame-on ac-table">
                 <div class="dev-details ac-cell">
                    <span class="headshot">
                        <?php print $avatar?>
                    </span>
                </div>
                <div class="text ac-cell">
                  <p><i class="s-q">“</i><?php print $testimonial?><i class="e-q">”</i></p>
                  <h5 class='s-title'><?php print $name?><span class="pos"><?php print $position?></span></h5>
                </div>
            </div>
        </div>
    </div>
</li>