<?php

function ws_bb_extract_page() {
  return drupal_get_form('ws_bb_extraction');
}

function ws_bb_extraction($form, &$form_state) {
  // Text field
  $form['menu_name'] = array(
    '#title' => t('Menu Name'),
    '#type' => 'textfield',
    '#default_value' => 'main-menu',
    '#required' => TRUE,
  );
  // Use the #managed_file FAPI element to upload an image file.
  $form['blueprint_archive'] = array(
    '#title' => t('Blueprint Archive'),
    '#type' => 'file',
    '#description' => t('The Blueprint to use for site construction.'),   
  );
  
  // Submit
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Extract Blueprint',
  );

  return $form;
}

function ws_bb_extraction_validate($form, &$form_state) {
  if (!($form_state['values']['blueprint_archive'] XOR !empty($_FILES['files']['name']['blueprint_archive']))) {
    form_set_error('blueprint_archive', t('You must provide an archive file.'));
  }
}

function ws_bb_extraction_submit($form, &$form_state) {
      $validators = array('file_validate_extensions' => array(archiver_get_extensions()));
    $field = 'blueprint_archive';
    if (!($finfo = file_save_upload($field, $validators, NULL, FILE_EXISTS_REPLACE))) {
      // Failed to upload the file. file_save_upload() calls form_set_error() on
      // failure.
      return;
    }
    $local_cache = $finfo->uri;

   
    $directory = 'temporary://build-blueprint-extraction';
    try {
      $archive = ws_bb_archive_extract($local_cache, $directory);
    }
    catch (Exception $e) {

      form_set_error($field, $e->getMessage());
      return;
    }
    $files = $archive->listContents();
    if (!$files) {
      form_set_error($field, t('Provided archive contains no files.'));
      return;
    }    
    
    // Unfortunately, we can only use the directory name to determine the project
    // name. Some archivers list the first file as the directory (i.e., MODULE/)
    // and others list an actual file (i.e., MODULE/README.TXT).
    $blueprint = strtok($files[1], '/\\');

    $blueprint_location = $directory . '/' . $blueprint;

    $blueprint_real_location = drupal_realpath($blueprint_location);
    $arguments = array(
      'blueprint' => $blueprint,
      'local_url' => $blueprint_real_location,
    );
    module_load_include('inc', 'update', 'update.authorize');
    $filetransfer = new FileTransferLocal(DRUPAL_ROOT);
    $source = $blueprint_location;
    $destination = DRUPAL_ROOT . '/sites/default/files/blueprints/';

    $destination_root = "public://blueprints";
    file_prepare_directory($destination_root, FILE_CREATE_DIRECTORY);
    $filetransfer->copyDirectory($source, $destination);
     $dir = "public://blueprints/$blueprint";
    $files = file_scan_directory($dir, '/.*\.blueprint$/', array('key' => 'name'));
    $blueprint_file = current($files);

    $base_directory = $destination . $blueprint;
    $site_name = $blueprint;
    $menu_name = $form_state['values']['menu_name'];
    ws_bb_blueprint_processor($blueprint_file, $base_directory, $site_name, $menu_name);
}

function ws_bb_archive_extract($file, $directory) {
  $archiver = archiver_get_archiver($file);
  if (!$archiver) {
    throw new Exception(t('Cannot extract %file, not a valid archive.', array ('%file' => $file)));
  }

  // Remove the directory if it exists, otherwise it might contain a mixture of
  // old files mixed with the new files (e.g. in cases where files were removed
  // from a later release).
  $files = $archiver->listContents();

  // Unfortunately, we can only use the directory name to determine the project
  // name. Some archivers list the first file as the directory (i.e., MODULE/)
  // and others list an actual file (i.e., MODULE/README.TXT).
  $project = strtok($files[1], '/\\');

  $extract_location = $directory . '/' . $project;
  if (file_exists($extract_location)) {
    file_unmanaged_delete_recursive($extract_location);
  }

  $archiver->extract($directory);
  return $archiver;
}