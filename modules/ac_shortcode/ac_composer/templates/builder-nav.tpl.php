<ul id="builder-main-nav" class="builder-main-nav clearfix">
    <li>
        <a href="http://support.diamondlayers.com/" class="nav-btn" title="<?php print t('DiamondLayers') ?>">
            <i class="admin-icon icon-admin-diamond-down"></i>
        </a>
    </li>
    <li>
        <a href="#" class="nav-btn db-add-new-element" id="db-add-new-element" title="<?php print t('Add element') ?>">
            <i class="admin-icon icon-admin-plus-x"></i>
        </a>
    </li>
    <li class="db-templates-toggle">
        <a href="#" class="nav-btn show-templates" title="<?php print t('Add Templates') ?>">
            <i class="admin-icon icon-admin-layout"></i>
        </a>
        <ul class="db-templates-menu">
            <?php print $submenu_links ?>
        </ul>
    </li>
</ul>