<script id="db-elements-list-modal-template" type="text/template">
    <div id="db-elements-list" class="db-elements-list">
        <div class="hedaer ac-table">
            <div class="db-categories-filter ac-cell" style="position: relative;">
                <?php print $categories ?>
            </div>
            <input class="ac-cell db-search-categories" id="db-search-categories" type="text" name="db_search_categories" placeholder="<?php print t('Search by element name')?>"/>
        </div>
        <div class="shortcode-list">
            <?php print $shortcodes ?>
        </div>
    </div>
</script>
