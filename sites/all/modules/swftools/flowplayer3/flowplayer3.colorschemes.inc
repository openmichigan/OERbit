<?php
// $Id: flowplayer3.colorschemes.inc,v 1.1.2.1 2009/03/17 21:21:16 stuartgreenfield Exp $

$info = array(

  /**
   * Use color schemes in sequence
   * backgroundColor  #000000
   *   Canvas color.
   * controlbarbackgroundColor #000000
   *   Background color for the control bar
   * timeColor        #01daff
   *   Font color in the time field. This is the running time. 
   * durationColor    #ffffff
   *   Value for the font color in the time field that specifies the total duration of the clip or "total time". 
   * progressColor    #015b7a
   *   Color of the progress bar. This is the bar in the timeline from zero time to the point where playback is at a given time. 
   * bufferColor      #6c9cbc
   *   Color of the buffer. The buffer is the bar that indicates how much video data has been read into the player's memory. 
   * sliderColor      #000000
   *   Background color for the timeline before the buffer bar fills it. The same background color is also used in the volume slider. 
   * buttonColor      #889aa4
   *   Color of the player buttons: stop, play, pause and fullscreen.
   * buttonOverColor  #92b2bd
   *   Button color when the mouse is positioned over them
   */

  // Pre-defined color schemes.
  'schemes' => array(

    '#000000,#000000,#01daff,#ffffff,#015b7a,#6c9cbc,#000000,#889aa4,#92b2bd' => t('FlowPlayer3 (Default)'),
    '#0072b9,#0072b9,#5ab5ee,#5ab5ee,#5ab5ee,#027ac6,#494949,#2385c2,#5ab5ee' => t('Blue Lagoon'),
    '#464849,#464849,#5d6779,#5d6779,#5d6779,#2f416f,#494949,#2a2b2d,#5d6779' => t('Ash'),
    '#55c0e2,#55c0e2,#007e94,#007e94,#007e94,#000000,#696969,#085360,#007e94' => t('Aquamarine'),
    '#d5b048,#d5b048,#d5b048,#d5b048,#971702,#6c420e,#494949,#331900,#971702' => t('Belgian Chocolate'),
    '#3f3f3f,#3f3f3f,#6598cb,#6598cb,#6598cb,#336699,#000000,#336699,#6598cb' => t('Blue Marine'),
    '#d0cb9a,#d0cb9a,#e6fb2d,#e6fb2d,#e6fb2d,#917803,#494949,#efde01,#e6fb2d' => t('Citrus Blast'),
    '#0f005c,#0f005c,#1a1575,#1a1575,#1a1575,#434f8c,#000000,#4d91ff,#1a1575' => t('Cold Day'),
    '#c9c497,#c9c497,#7be000,#7be000,#7be000,#0c7a00,#494949,#03961e,#7be000' => t('Greenbeam'),
    '#ffe23d,#ffe23d,#a30f42,#a30f42,#a30f42,#a9290a,#494949,#fc6d1d,#a30f42' => t('Mediterrano'),
    '#788597,#788597,#d4d4d4,#d4d4d4,#d4d4d4,#3f728d,#707070,#a9adbc,#d4d4d4' => t('Mercury'),
    '#5b5fa9,#5b5fa9,#9fa8d5,#9fa8d5,#9fa8d5,#5b5faa,#494949,#0a2352,#9fa8d5' => t('Nocturnal'),
    '#7db323,#7db323,#7db323,#7db323,#7db323,#6a9915,#191a19,#b5d52a,#7db323' => t('Olivia'),
    '#12020b,#12020b,#f41063,#f41063,#f41063,#1b1a13,#898080,#f391c6,#f41063' => t('Pink Plastic'),
    '#b7a0ba,#b7a0ba,#f21107,#f21107,#f21107,#c70000,#515d52,#a1443a,#f21107' => t('Shiny Tomato'),
    '#18583d,#18583d,#52bf90,#52bf90,#52bf90,#1b5f42,#2d2d2d,#34775a,#52bf90' => t('Teal Top'), 
  ),

);
