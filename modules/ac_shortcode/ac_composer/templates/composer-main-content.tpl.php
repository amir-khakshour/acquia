<div class="db-content">
    <div class="db-loading" style="display: none;">
        <div class="inner">
            <div class="sk-folding-cube">
              <div class="sk-cube1 sk-cube"></div>
              <div class="sk-cube2 sk-cube"></div>
              <div class="sk-cube4 sk-cube"></div>
              <div class="sk-cube3 sk-cube"></div>
            </div>
            <h1 class="loading-text"><?php print t("Loading, please wait...")?></h1>
        </div>
    </div>

    <div id="db-visual" class="db-visual"></div>
    <div id="db-intro" class="db-intro">
        <h2><?php print t("No content yet! You should add some..")?></h2>
        <div class="db-buttons">
            <a id="db-not-empty-add-element" class="db-not-empty-add-element" title="Add Element"></a>
            <a href='#' class='button add-element-to-layout'>
                <i class="admin-icon icon-admin-plus"></i><span>Add element</span>
            </a>
            <a href='#' class='button add-text-block-to-content' parent-container='#db-visual'>
                <i class='admin-icon admin-icon-text'></i><span>Add Text block</span>
            </a>
        </div>

    </div>
</div>