$Id: README.txt,v 1.3 2010/07/10 00:17:34 rdeboer Exp $

DESCRIPTION
=========== 
Workflow-post-install is a utility to put content that is in the workflow state
of 'No state' into a valid state making it usable in workflows. This refers in
particular to content that existed before you installed the Workflow module.
Therefore you typically use this module only once, namely immediately after
enabling the Workflow module.
There's deliberately no menu created to use this utility. You invoke it by
typing the following URI in your browser:
    
    .../content/set_workflow_state/<state>
   
where <state> is the name of an existing state you want to put all content in 
e.g. "public". The module makes sure that only content that is of a type that
participates in workflows is affected, i.e, as set on the Administer >> 

INSTALLATION
============
1. Place the workflow_post_install folder in "sites/all/modules".
2. Enable the module under Administer >> Site building >> Modules.

USAGE
=====
Type a URI of the following form in your browser:
    
    .../content/set_workflow_state/<state>
   
where <state> is the name of an existing state you want to put all content in 
e.g. "live" or "published". If you mistype the state name, nothing will happen.
WARNING: this action cannot be undone.

Note, the logged-in user must have the "administer nodes" permission (e.g. be
an administrator) to be authorised to use the above link.

AUTHOR
======
Rik de Boer, Melbourne, Australia
