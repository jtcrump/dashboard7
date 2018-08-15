CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation

INTRODUCTION
------------

Vehicle is a module that borrows heavily from the storage style of Taxonomy. It 
allows any content on your site to be tagged with a Vehicle Make and Model 
entity. Potential uses are shopping carts with products tagged with Vehicle 
compatibility. Both Make and Model entities are fieldable and have a direct 
relationship with each other.

In addition to basic tagging, tools have been provided for easy searching and 
filtering of content based on the Vehicle Make and Model it has been tagged 
with.  This includes Views integration as well as a custom Y/M/M widget 
available in Block form as well as via a custom API call to 
vehicle_ymm_selector()

INSTALLATION
------------

Installation of the Vehicle module is simple and straightforward.  If you've 
used the Taxonomy module you are familiar with the basic setup and workings of 
this module.

 1. Copy this vehicle/ directory to your sites/SITENAME/modules directory.

 2. Enable the Vehicle, Vehicle Make and Vehicle Model modules and configure 
settings.  Note that the Vehicle module currently serves to display the 
administrative interface for the Make and Model modules as well as placeholder 
for future features.  You must enable one or both of these modules in order to 
use the module properly.

 3. Vehicle Makes and Vehicle Models can be added manually through the 
configuration interface.  Additionally, a premade list can be purchased from 
sites such as carqueryapi.com and the CSV file imported to the database.

 4. Once at least one Vehicle Make and Model has been added, you may proceed 
with adding a custom field type to your content type in order to tag.

COMMON ISSUES
------------

 Q. When I click on "Vehicle" I get a message saying "You have no 
administrative items."

 A. Make sure to enable the Vehicle Make and/or Vehicle Model modules.  Empty 
your cache and the administrative menus for these module should appear.
