<?php
/**
 * @file
 * ws_bb.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ws_bb_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ws_bb_node_info() {
  $items = array(
    'site_blueprint' => array(
      'name' => t('Site Blueprint'),
      'base' => 'node_content',
      'description' => t('A <em>Site Blueprint</em> XML file to be imported. Create one of those if you have an XML URL for a blueprint xml file.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
