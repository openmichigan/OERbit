// $Id: views-accordion.js,v 1.1.2.15 2010/01/18 19:39:28 manuelgarcia Exp $
Drupal.behaviors.views_accordion = function(context) {

  if(Drupal.settings.views_accordion){
    $.each(Drupal.settings.views_accordion, function(id) {
      var activeClass = 'accordion-header-active'; // the CSS class that the active header will recieve when it's open
      var hoverClass = 'accordion-header-hover'; // the CSS class that the headers will recieve when the mouse goes over
      var contentClass = 'accordion-content'; // the CSS class that the content in the accordions will have
      /*
       * Our view settings
       */
      var usegroupheader = this.usegroupheader;
      var grouped = this.grouping;  // wether or not field grouping is enabled
      var keeponeopen = this.keeponeopen; // wether or not we'll be allowing the user to close opened items
      var speed = this.speed;  // how fast the sliding will be
      var startopen = this.startopen;  // wether or not an item will start opened
      var cycleOn = this.autocycle; // wether or not we'll be using auto cycling of items
      var cycleSpeed = this.autocyclespeed; // time between each cycle (added to speed below to avoid weird behaviour)
      var togglelinks = this.togglelinks;  // wether or not to show Open All / Close All links
      var disablecloseothers = this.disablecloseothers;  // wether or not when clicking a closed item we should close all others.
      var rowstartopen = this.rowstartopen; // The row that we have to open on load, if any.

      // the selectors we have to play with
      var contentSelector = 'div.' + contentClass; // used for selecting all accordion content to show/hide
      var displaySelector = this.display;  // Used to grab anything under our view.
      var headerSelector = usegroupheader ? (this.header) : ('.' + this.header); // this.header is the class of our first field

      // we have to use different selectors if using field grouping because we have several divs with #id
      var idSelector = grouped ? ('.' + id) : ('#' + id);
      var $viewcontent = $('#' + displaySelector);
      if (usegroupheader) $viewcontent = $viewcontent.parent().parent();
      if (grouped && !usegroupheader) $viewcontent = $viewcontent.parent();  // views renders html as if you had several views...

      /*
       * Fixing ajax views bug (was wrapping the div everytime), we need to check hasRan
       * It seems to work fine even with grouping enabled, though further testing couldn't hurt
       */
      var hasRan = $(idSelector + ' ' + contentSelector).length;
      //console.log(hasRan ? idSelector + ' already ran' : idSelector + ' had not ran already');  // for debugging

      if (!hasRan) {
        var $triggers = usegroupheader ? $(headerSelector, $viewcontent) : $(idSelector + ' ' + headerSelector);
        $triggers.addClass('accordion-header');

        $triggers.parent().each(function(){
          $(this).children().slice(1).wrapAll('<div class="' + contentClass + '">') // we wrap all but the header in a div so we can target the content later
        }).parent().addClass('accordion-active');

        var $content =  usegroupheader ? $(contentSelector, $viewcontent) : $(idSelector + ' ' + contentSelector);
        $content.hide();

        // Hide all - show all action & buttons
        if (!cycleOn && togglelinks) {
            var links = '<span class="toggleAccordion"><a class="open-all-accordion" href="#">' + Drupal.t('Open All') + '</a> | <a class="close-all-accordion" href="#">' + Drupal.t('Close All') + '</a></span>';
            $viewcontent.before(links);
            var $toggleContainer = $viewcontent.prev();
            $('a.close-all-accordion', $toggleContainer).click(function(){
                $content.hide();
                $triggers.removeClass(activeClass);
                return false;
              });
            $('a.open-all-accordion', $toggleContainer).click(function(){
                $content.show();
                $triggers.addClass(activeClass);
                return false;
              });
          }

        /*
         *  Accordion action
         */
        $triggers.click(function(ev) {
          if (ev.detail === 1 || !ev.detail) { // so we prevent double clicking madness (for not so savy web users) !ev.detail is for when its triggered by code
            // so we keep accordions for each field group are independent (if using field groups)
            var $ourTrigger = $(this);
            var $contentToHandle = (grouped && (!usegroupheader)) ? $ourTrigger.parents(idSelector).children().children().children(contentSelector) : $content;

            var $ourContent = $(this).next();
            var $ourContentVisible = $ourContent.is(":visible");

            // if the one we clicked is open
            if ($ourContentVisible) {
              if(keeponeopen === 0) {
                $ourContent.slideUp(speed);
                $ourTrigger.removeClass(activeClass);
              }
            }
            // otherwise
            else if (!$ourContentVisible) {
              if (!disablecloseothers) {
                // if we have one open, close it
                var $visibleContent = $contentToHandle.filter(':visible');
                if($visibleContent.length) {
                  $triggers.removeClass(activeClass);
                  $visibleContent.slideUp(speed);
                }
              }
              // and open our section
              $ourContent.slideToggle(speed);
              $ourTrigger.addClass(activeClass);
            }
          }
          return false;
        });

        $triggers.hover(function(){
          // on mouse over
          $(this).addClass(hoverClass);
          },function(){
            // on mouse out
            $(this).removeClass(hoverClass);
        });

        // Open a row on load if so configured
        if (startopen) {
          $triggers.filter(':eq('+rowstartopen+')').addClass(activeClass).next().show();
        }

        /*
         * Auto-Cycling through the accordion
         */
        if (cycleOn) {
          var running = true;
          var interval = speed + cycleSpeed;  // (animation time + cycle time)
          var hardstop = false;
          // creating buttons stop/start/ paused status
          $viewcontent.before('<span class="stop-accordion"><a class="stop-accordion" href="#">' + Drupal.t('Stop') + '</a></span>');
          var $stoplink = $viewcontent.prev().children();

          // main cycle action
          function cycleAccordion() {
            if (running) {
              var $activeHeader = $triggers.filter('.' + activeClass);
              var $firstHeader = $triggers.filter(':first');
              var $nextHeader = $activeHeader.parent().next().children().filter(':first');
              var $triggerToClick = ($nextHeader.length) ? $nextHeader : $firstHeader;
              $triggerToClick.trigger("click");
            }
            setTimeout(cycleAccordion, interval);
          }
          setTimeout(cycleAccordion, interval);

          /*
           * BUTTONS to stop/start cycling action
           */
          $stoplink.click(function() {
            var $this = $(this);
            if (hardstop === true) {
              $triggers.filter(':first').trigger('start');
              $this.html(Drupal.t('Stop'));
            }
            else if (hardstop === false) {
                $triggers.filter(':first').trigger('stop');
                $this.html(Drupal.t('Start'));
            }
            hardstop = (hardstop === true) ? false : true;
            return false;
          });

          /*
           * Stop cycling on mouse over the whole thing
           */
          $triggers.parent().parent().hover(function () {
              // on mouse over
              if (!hardstop) {
                $triggers.filter(':first').trigger('stop');
                $stoplink.html(Drupal.t('Paused'));
              }
            }, function () {
              // on mouse out
              if (!hardstop){
                $triggers.filter(':first').trigger('start');
                $stoplink.html(Drupal.t('Stop'));
              }
            });

          $triggers.bind('stop', function () {
              running = false;
            }).bind('start', function () {
                running = true;
              });
        } // end autocycle
      }
    });
  }
};
