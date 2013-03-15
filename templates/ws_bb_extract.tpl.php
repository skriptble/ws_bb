<?php global $base_url; ?>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>WebServices Blueprint Tool</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="">
    <meta name="author" content="">
    <link href="<?php print $base_url . '/' . drupal_get_path('module', 'ws_bb'); ?>/css/bootstrap.css" rel="stylesheet">
    <style type="text/css">
      body {
        padding-top: 40px;
        padding-bottom: 40px;
        background-color: #f5f5f5;
      }

      .form-blueprint {
        max-width: 500px;
        padding: 19px 29px 29px;
        margin: 0 auto 20px;
        background-color: #fff;
        border: 1px solid #e5e5e5;
        -webkit-border-radius: 5px;
           -moz-border-radius: 5px;
                border-radius: 5px;
        -webkit-box-shadow: 0 1px 2px rgba(0,0,0,.05);
           -moz-box-shadow: 0 1px 2px rgba(0,0,0,.05);
                box-shadow: 0 1px 2px rgba(0,0,0,.05);
      }
      .form-blueprint .form-blueprint-heading,
      .form-blueprint .checkbox {
        margin-bottom: 10px;
      }

    </style>
    <link href="<?php print $base_url . '/' . drupal_get_path('module', 'ws_bb'); ?>/css/bootstrap-responsive.css" rel="stylesheet">
  </head>
  <body>
<div class="container">

      <form class="form-blueprint" action="../extraction.php" method="post" enctype="multipart/form-data">
        <h2 class="form-blueprint-heading">Web Services Blueprint Tool</h2>
        <h4 class="form-blueprint-heading">Extraction Tool</h4>
        <p>This tool can be used to extract an uploaded zip or tar file.</p>
        <br>
        <label for="text">Menu Name:</label>
        <input type="text" name="menu-name" id="menu-name-text"></input>
        <label for="file">File:</label>
        <input type="file" name="archive-file" id="file">        
        <button class="btn btn btn-primary" type="submit">Extract</button>
      </form>

    </div> <!-- /container -->
  </body>
</html>

