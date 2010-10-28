// $Id: README.txt,v 1.4 2010/03/25 18:43:43 johnalbin Exp $

ABOUT
-----

On 404 Not Found pages, Drupal will skip rendering of several pieces of your
website for performance reasons. These include:

1. The "Left" and "Right" regions of your theme.
2. The "Primary links" block and any other menu links block.*
3. The Primary links and Secondary links of your theme.*

* Unless you have configured a "Default 404 (not found) page" on
  admin/settings/error-reporting.

But many websites find those items invaluable. Especially on 404 pages, when
they want to show users how to get to real pages.

So this module simply revives those features on 404 pages.


INSTALLATION
------------

Simply install and enable the module. No configuration needed.
