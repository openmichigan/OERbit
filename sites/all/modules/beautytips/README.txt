
  
                          IMPORTANT INSTALLATION INSTRUCTIONS
    ------------------------------------------------------------------------------------
    In order for this module to work properly with IE, you will need to download the 
    ExplorerCanvas library, which can be found here - http://excanvas.sourceforge.net/.
    Place the downloaded directory 'excanvas_r3' inside the 'beautytips/other_libs' directory.

    Other than that, you just need to turn the module on in the usual Drupal way.

    --------------------------------------------------------------------------------------
                                     ABOUT THE MODULE

    The Beautytips module provides ballon-help style tooltip for any page element. 
    It integrates BeautyTips jQuery plugin by Jeff Robbins with Drupal.  Currently, this 
    module allows tooltips to appear with textfields and textareas.  It also supplies hover
    tips for Drupal help links and advanced help links.  Most importantly, it allows developers
    to add their own beautytips popups to their site without having to delve into jQuery.

    For information about the Beauty Tips jQuery plugin:
      http://www.lullabot.com/articles/announcing-beautytips-jquery-tooltip-plugin
      http://www.lullabot.com/articles/beautytips-09-release

    To see a demonstration:
      http://www.lullabot.com/files/bt/bt-latest/DEMO/index.html
    --------------------------------------------------------------------------------------
                                           API
    --------------------------------------------------------------------------------------
      Beautytips has an API so that you can create your own beautytips and add them into 
    any place on your site.  To do this, you will need to set up an array of options and 
    then pass them along to the beautytips_add_beautytips function.  All of the options are 
    outlined below.  This array will need to have a couple of important pieces of 
    information, and can accept a plethora of other optional info.

      1.  Each beautytip will need a name - distinct from other beautytips added on the 
          web page.
        ex. options['bt_drupal_help_page'] = array( . . .

      2.  Each beautytip will need a css(or jQuery) selector.  This is how the bt plugin 
          knows where to place the tooltip.
        ex. 'area' => '.help-items li a'

      3.  Each beautytip will need some text to display.  You can define what to display 
          in 3 different ways.

        a.  Use 'text' to directly add supply the text.  It can accept html.
          ex 1.  'text' => t('Here's some beautytips text to display on this page.'),

        b.  Use 'contentSelector' to use jQuery to tell beautytips where to find the text 
            on a page.
          ex 2.  'contentSelector' => '$(this).next(".description").html()',
          This tells beautytips to find the next item after the css selector with class 
          'description' and use display it's html

        c.  Use 'ajaxPath' to provide a place on another webpage that should be displayed.

          ex 3. 'ajaxPath' => 'demo.html',
          This will display that particular webpage within the tooltip balloon.

          ex 4.  'ajaxPath' => '$(this).attr("href")',
          This uses jQuery to find the url associated with the link that was selected with 
          the css selector and displays it.

          ex 5. 'ajaxPath' => array(0 => '$(this).attr("href"), 1 => '#squeeze.clear-block p'),
          This does the same thing as ex. 4, except it only displays the css-selected section of 
          the page.

        d.  If none of the above 3 options are given, the beautytips plugin will by default set 
        'contentSelector' to be '$(this).attr('title')'.

      4.  All other options are optional.  See the list below.
        ex.  'fill' => "rgb(255, 155, 55)" - sets the background color of the balloon.

    ------------------------------------------------------------------------------------
      ex. Full options array and function call to add beautytips

      $options['bt_drupal_help_page'] = array(
        'area' => '.help-items li a',
        'ajaxPath' => array(0 => "$(this).attr('href')", 1 => '.clear-block p'),
        'trigger' => array(0 => 'mouseover', 1 => 'click'),
        'width' => 350,
      );
      beautytips_add_beautytips($options);
    ------------------------------------------------------------------------------------


  *******************************************************************************************
  Beautytips options and defaults (Copied from the jQuery.bt.js file.  See it for more info.)
  *******************************************************************************************
  /**
     * Defaults for the beauty tips
     *
     * Note this is a variable definition and not a function. So defaults can be
     * written for an entire page by simply redefining attributes like so:
     *
     *   jQuery.bt.defaults.width = 400;
     *
     * This would make all Beauty Tips boxes 400px wide.
     *
     * Each of these options may also be overridden during
     *
     * Can be overriden globally or at time of call.
     *
     */
    jQuery.bt.defaults = {
      trigger:         'hover',                // trigger to show/hide tip
                                               // use [on, off] to define separate on/off triggers
                                               // also use space character to allow multiple  to trigger
                                               // examples:
                                               //   ['focus', 'blur'] // focus displays, blur hides
                                               //   'dblclick'        // dblclick toggles on/off
                                               //   ['focus mouseover', 'blur mouseout'] // multiple triggers
                                               //   'now'             // shows/hides tip without event
                                               //   'none'            // use $('#selector').btOn(); and ...btOff();
                                               //   'hoverIntent'     // hover using hoverIntent plugin (settings below)
                                               // note:
                                               //   hoverIntent becomes default if available

      clickAnywhereToClose: true,              // clicking anywhere outside of the tip will close it 
      closeWhenOthersOpen: false,              // tip will be closed before another opens - stop >= 2 tips being on

      width:            '200px',               // width of tooltip box
                                               //   when combined with cssStyles: {width: 'auto'}, this becomes a max-width for the text
      padding:          '10px',                // padding for content (get more fine grained with cssStyles)
      spikeGirth:       10,                    // width of spike
      spikeLength:      15,                    // length of spike
      overlap:          0,                     // spike overlap (px) onto target (can cause problems with 'hover' trigger)
      overlay:          false,                 // display overlay on target (use CSS to style) -- BUGGY!
      killTitle:        true,                  // kill title tags to avoid double tooltips

      textzIndex:       9999,                  // z-index for the text
      boxzIndex:        9998,                  // z-index for the "talk" box (should always be less than textzIndex)
      wrapperzIndex:    9997,
      positions:        ['most'],              // preference of positions for tip (will use first with available space)
                                               // possible values 'top', 'bottom', 'left', 'right' as an array in order of
                                               // preference. Last value will be used if others don't have enough space.
                                               // or use 'most' to use the area with the most space
      fill:             "rgb(255, 255, 102)",  // fill color for the tooltip box, you can use any CSS-style color definition method
                                               // http://www.w3.org/TR/css3-color/#numerical - not all methods have been tested

      windowMargin:     10,                    // space (px) to leave between text box and browser edge

      strokeWidth:      1,                     // width of stroke around box, **set to 0 for no stroke**
      strokeStyle:      "#000",                // color/alpha of stroke

      cornerRadius:     5,                     // radius of corners (px), set to 0 for square corners

                        // following values are on a scale of 0 to 1 with .5 being centered

      centerPointX:     .5,                    // the spike extends from center of the target edge to this point
      centerPointY:     .5,                    // defined by percentage horizontal (x) and vertical (y)

      shadow:           false,                 // use drop shadow? (only displays in Safari and FF 3.1) - experimental
      shadowOffsetX:    2,                     // shadow offset x (px)
      shadowOffsetY:    2,                     // shadow offset y (px)
      shadowBlur:       3,                     // shadow blur (px)
      shadowColor:      "#000",                // shadow color/alpha
      shadowOverlap:   false,                  // when shadows overlap the target element it can cause problem with hovering
                                               // set this to true to overlap or set to a numeric value to define the amount of overlap
      noShadowOpts:     {strokeStyle: '#999'},  // use this to define 'fall-back' options for browsers which don't support drop shadows

      animate:          false,                 // animate show/hide of box - EXPERIMENTAL (buggy in IE)
      distance:         15,                    // distance of animation movement (px)
      easing:           'swing',               // animation easing
      speed:            200,                   // speed (ms) of animation

      cssClass:         '',                    // CSS class to add to the box wrapper div (of the TIP)
      cssStyles:        {},                    // styles to add the text box
                                               //   example: {fontFamily: 'Georgia, Times, serif', fontWeight: 'bold'}

      activeClass:      'bt-active',           // class added to TARGET element when its BeautyTip is active

      contentSelector:  "$(this).attr('title')", // if there is no content argument, use this selector to retrieve the title

      ajaxPath:         null,                  // if using ajax request for content, this contains url and (opt) selector
                                               // this will override content and contentSelector
                                               // examples (see jQuery load() function):
                                               //   '/demo.html'
                                               //   '/help/ajax/snip'
                                               //   '/help/existing/full div#content'

                                               // ajaxPath can also be defined as an array
                                               // in which case, the first value will be parsed as a jQuery selector
                                               // the result of which will be used as the ajaxPath
                                               // the second (optional) value is the content selector as above
                                               // examples:
                                               //    ["$(this).attr('href')", 'div#content']
                                               //    ["$(this).parents('.wrapper').find('.title').attr('href')"]
                                               //    ["$('#some-element').val()"]

      ajaxError:        '<strong>ERROR:</strong> <em>%error</em>',
                                               // error text, use "%error" to insert error from server
      ajaxLoading:     '<blink>Loading...</blink>',  // yes folks, it's the blink tag!
      ajaxData:         {},                    // key/value pairs
      ajaxType:         'GET',                 // 'GET' or 'POST'
      ajaxCache:        true,                  // cache ajax results and do not send request to same url multiple times
      ajaxOpts:         {},                    // any other ajax options - timeout, passwords, processing functions, etc...
                                               // see http://docs.jquery.com/Ajax/jQuery.ajax#options

      preShow:          function(){return;},       // function to run before popup is built and displayed
      postShow:         function(){return;},       // function to run after popup is built and displayed
      preHide:          function(){return;},       // function to run before popup is removed
      postHide:         function(){return;},       // function to run after popup is removed

      hoverIntentOpts:  {                          // options for hoverIntent (if installed)
                          interval: 300,           // http://cherne.net/brian/resources/jquery.hoverIntent.html
                          timeout: 500
                        }

    }; // </ jQuery.bt.defaults >