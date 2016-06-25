
(function ($) {

    $(document).ready(function(){
        var content_target = findPagerTargetSelector();
        if (content_target == '') return;
        var options = {
            content: content_target + ' > *',
            link: Drupal.settings.infscr.pagerNext,
            pager: Drupal.settings.infscr.pager,
            appendTo: content_target,
            pagerNav: $(Drupal.settings.infscr.pager).closest('.pager-o').siblings('.ac-ajax-paginator').find('a'),
            doneText: Drupal.settings.infscr.doneText,
        };

        var status = {
            content: $(options.content).filter(':last'),
            currentUrl: null,
            nextUrl: null,
            active: false,
            page: 1
        };

        // Run the first time (if more results are needed)
        setUrl();
        $(Drupal.settings.infscr.pager).closest('.pager-o').hide();
        if ($(content_target).attr('data-ajax_type') == 'click'){
            loadOnClick();
        }else{
            $(window).scroll(loadOnScroll);
        }

        // Using the pager find it's content target
        function findPagerTargetSelector() {
            $target = $(Drupal.settings.infscr.pager).closest('.pager-o').parent();

            if ($target.length == 0 || $target.attr('id') == '') return '';
            var target = '#' + $target.attr('id') + ' .pager-target';
            return target;
        }

        // Set the new url to be loaded
        function setUrl(nextAnchor) {
            status.currentUrl = status.nextUrl || window.location.href;
            status.nextUrl = nextAnchor ? nextAnchor.attr('href') : $(options.link).attr('href');
        }

        // Show/hide content loader
        function toogleLoader() {
            if (status.active) {
                $('#infinitescroll-loader').remove();
            }
            else {
                $(options.pager).before('<div id="infinitescroll-loader"><div></div></div>');
            }
        }

        // Load new content
        function loadOnScroll() {
            if (status.content.offset().top + status.content.height() < $(document).scrollTop() + $(window).height()) {
                if (status.active || !status.nextUrl || options.disabled) return;
                $(options.pagerNav).addClass('ac-in-progress');
                toogleLoader();
                status.active = true;
                $.get(status.nextUrl, insertContent);
            }
        }

        // Load new content
        function loadOnClick() {
            $(options.pagerNav).click(function(e){
                e.preventDefault();
                $(this).addClass('ac-in-progress');
                if (status.active || !status.nextUrl || options.disabled) return;
                toogleLoader();
                status.active = true;
                $.get(status.nextUrl, insertContent);
            });
        }

        function extractCurrentTags($tags){
            var tags = new Array();
            $.each($tags, function(){
                tags.push($(this).attr('data-filter'));
            });
            return tags;
        }

        // Insert the new content into the current page
        function insertContent(res) {
            $(options.pagerNav).removeClass('ac-in-progress');
            toogleLoader();
            status.page++;
            setUrl($(options.link, res));

            var nextContent = $(options.content, res);
            if (nextContent.length) {
                var tags = $(options.appendTo, res).closest('.ac-pager-ajax').find('.tag-sortings a');
                if (tags.length) {

                    var filter = $(options.appendTo).closest('.ac-pager-ajax').find('.tag-sortings li'),
                        tagsArr = extractCurrentTags($('a', filter)),
                        prepend = filter.last();

                    $.each(tags, function(){
                        if ($.inArray($(this).attr('data-filter') + "", tagsArr) ==-1) {
                            $(this).insertBefore(prepend).wrap('<li />');
                        }
                    });
                }
                nextContent.hide().appendTo(options.appendTo);
                Drupal.attachBehaviors(nextContent);
                Drupal.attachBehaviors($(nextContent).closest('.ac-portfolio').find('.filter'));
                var container = $(nextContent).closest('.p-items');
                if (container.is('.ac-appearance-multigrid')){
                    imagesLoaded(nextContent, function() {
                        $(nextContent).fadeIn();
                        var elH = parseInt(container.attr("data-gplus_height")) ? parseInt(container.attr("data-gplus_height")) : 350;
                        //$(nextContent).css('height', elH);
                        container.collage();
                    });
                }else if (jQuery().isotope) {
                    imagesLoaded(nextContent, function() {
                        $(nextContent).fadeIn();
                        $(nextContent).closest('.ac-appearance-masonry').isotope('appended', $(nextContent));
                        $(nextContent).find('.ac-fluid-video').fitVids();
                        $(nextContent).closest('.ac-appearance-masonry').isotope('reLayout');
                    });
                };

                status.content = nextContent.filter(':last');
            }

            // No more data
            if (!status.nextUrl && options.pager) {
                $(options.pagerNav).text(Drupal.t(options.doneText));
            }

            status.active = false;
        }
    });

})(jQuery);