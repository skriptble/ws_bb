<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>WebServices Blueprint Tool</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="">
    <meta name="author" content="">
    <link href="css/bootstrap.css" rel="stylesheet">
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
      .label.download a{
        color: white;
      }
      
      .alert .download-text {
        text-align: right;
      }

    </style>
    <link href="css/bootstrap-responsive.css" rel="stylesheet">
  </head>
  <body>
<div class="container">

      <div class="form-blueprint">
        <h2 class="form-blueprint-heading">Web Services Blueprint Tool</h2>
        <p>This tool can be used to convert a sitemap created by Web Services into an XML Blueprint file.
            This blueprint file can then be used to create a Drupal empty site strucuture.</p>
        <p>Follow the steps below to ensure that your sitemap is correctly formatted. <em>Incorrectly formatted
            sitemaps may cause the program to crash or your xml to be malformed.</em></p>
        <br>
        <?php include 'blueprint.library.php'; ?>
        <?php create_blueprint(); ?>
      </div>

    </div> <!-- /container -->
  </body>
</html>
