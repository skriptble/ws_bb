<?php
/**
 * @file
 * ws_bb.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ws_bb_default_rules_configuration() {
  $items = array();
  $items['rules_blueprint_mapper'] = entity_import('rules_config', '{ "rules_blueprint_mapper" : {
      "LABEL" : "Blueprint Mapper",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Blueprint", "XML" ],
      "REQUIRES" : [ "rules", "php", "feeds" ],
      "ON" : [ "feeds_import_xml_site_creator" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "page" : "page" } } } }
      ],
      "DO" : [
        { "php_eval" : { "code" : "\\u003C?php\\r\\n$mlids = variable_get(\\u0027sitemap_blueprint_previous_mlids\\u0027,NULL);\\r\\nif($mlids) {\\r\\n  $curr_path = $node-\\u003Epath[\\u0027alias\\u0027];\\r\\n  $curr_path_arr = explode(\\u0027\\/\\u0027, $curr_path);\\r\\n  array_pop($curr_path_arr);\\r\\n  $parent_path = implode(\\u0027\\/\\u0027, $curr_path_arr);\\r\\n  if (array_key_exists($parent_path, $mlids)) {\\r\\n      $node-\\u003Emenu[\\u0027plid\\u0027] = $mlids[$parent_path];\\r\\n  }\\r\\n}\\r\\n\\r\\n?\\u003E" } }
      ]
    }
  }');
  $items['rules_create_menu_items'] = entity_import('rules_config', '{ "rules_create_menu_items" : {
      "LABEL" : "Create Menu Items",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Blueprint", "XML" ],
      "REQUIRES" : [ "rules", "php" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "page" : "page" } } } }
      ],
      "DO" : [
        { "php_eval" : { "code" : "\\u003C?php\\r\\n$mlids = variable_get(\\u0027sitemap_blueprint_previous_mlids\\u0027, array());\\r\\n$mlids[$node-\\u003Epath[\\u0027alias\\u0027]] = $node-\\u003Emenu[\\u0027mlid\\u0027];\\r\\nvariable_set(\\u0027sitemap_blueprint_previous_mlids\\u0027, $mlids);\\r\\n?\\u003E" } }
      ]
    }
  }');
  return $items;
}
