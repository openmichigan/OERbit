$Id: README.txt,v 1.1.2.1 2010/03/26 16:05:47 jdanthinne Exp $

Custom search 6.x-1.x
--------------------------

Install
-------
* Enable the module
* Go to Administer > Settings > Custom search to change settings
* Don't forget to set permissions, otherwise nobody will see the changes

Description
-----------
This module alters the default search box in many ways. If you need to have options available like in advanced search, but directly in the search box, this module is for you.

The module adds options to select:

- which content type(s) to search,
- which specific module search to use (node, help, user or any module that implements search),
- which taxonomy term to search in the results (by vocabulary).
- For all these choices, there are options to switch between a select box, checkboxes or radio buttons, and also customize the selector label and the default - Any - text.

There are also options to:

- change the default search box label,
- adds a default text in the search box,
- change the default submit button text,
- use an image instead of the submit button,
- via a "tabledrag", the ordering of all the added options can be changed.

Finally, there's some javascript to:

- check if the search box is not empty on submit,
- clear the default text on focus, and put it back on blur (if search box is empty),
- handle checkboxes (deselect some checkbox if -Any-, or a special module search, is checked),
- reselect options in the advanced search options (in results page).


The module integrates well with Internationalization (i18nstrings).

This module is inspired by some modules that implements some of these options (search_config, search_type, custom_seach_box).

Author
------
jdanthinne
