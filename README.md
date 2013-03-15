# CUMC Web Services Blueprint & Build Tool

The Blueprint & Build (B&B) tool will assist you in creating a Drupal 7 website from a sitemap.

## Dependencies
* [ctools][]
* [entity][]
* [features][]
* [feeds][] - Requires a patch
    * [Patch Issue][]
    * [Patch File][]
* [feeds_xpathparser][]
* php - [currently in core][]
* [rules][]

## Installation
Follow these instructions to install the module:

1. Download all dependencies and this repository
2. Place these files in your Drupal site
3. Enable all the modules
4. Under the "navigation" menu, go to "Extract new blueprint"
5. Choose a menu name and upload the Blueprint Archive
6. Click "Extract Blueprint" and your site will be built
    * The B&B tool will make a new node of Site Blueprint type that can be used to reimport the site


[ctools]: http://drupal.org/project/ctools
[entity]: http://drupal.org/project/entity
[features]: http://drupal.org/project/features
[feeds]: http://drupal.org/project/feeds
[Patch Issue]: http://drupal.org/node/1633014
[Patch File]: http://drupal.org/files/feeds-add_menu_item_map-1633014-8.patch
[feeds_xpathparser]: http://drupal.org/project/feeds_xpathparser
[currently in core]: http://drupal.org/node/1203886
[rules]: http://drupal.org/project/rules