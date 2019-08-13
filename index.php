<?php
// START SESSION
session_start();

// Define autoloader.

function __autoload($classname)
{
    include 'includes/class.' . $classname . '.inc';
}

// Class Objects

$candidate = new Candidate();

$textitle = 'Vote';
$page = 'Audience vote';
?>
<!DOCTYPE html>
<html lang="e-us">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <meta name="description" content="">
    <meta http-equiv="imagetoolbar" content="no" />
    <meta name="Moses Ditlhong" content="Miss Botswana 2019">
    <link rel="icon" type="image/x-icon" href="images/favicon.ico">

    <title><?php echo $textitle ?></title>

    <script src="https://code.jquery.com/jquery-2.2.4.js"
  integrity="sha256-iT6Q9iMJYuQiMWNd9lDyBUStIq/8PuOW33aOqmvFpqI="
  crossorigin="anonymous"></script>


    <!-- bulma -->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/bulma/0.7.1/css/bulma.min.css">

    <!-- Custome Style Sheet   -->
    <link rel="stylesheet" href="css/app.css">

    <script defer src="https://use.fontawesome.com/releases/v5.1.0/js/all.js"></script>

    <script src="js/app.js"></script>

    <!-- Sweet Alert -->
    <script src="https://unpkg.com/sweetalert2@7.8.2/dist/sweetalert2.all.js"></script>
</head>

  <body>
    <div style="font-family: https://fonts.google.com/specimen/Nunito?selection.family=Nunito"   class="section is-paddingless">
            <div class="section" >
              <div class="section has-background-warning">
                <p class="title ">
                  Miss Botswana 2019
                </p>
                <p class="subtitle"><?php echo $page; ?></p>
                 <div class="field">
                    <div class="control">
                      <input id="ticket_code" class="input is-medium is-fullwidth has-text-centered" type="text" placeholder="Enter ticket code.">
                    </div>
                </div>
      </div>
        <br>


    <?php echo $candidate->getCandidates(); ?>

    <div class="field">
    <div class="control ">
    <a id="results" href="./results.php" class="button is-success has-background-dark has-text-grey-light is-large is-fullwidth is-radiusless" ">Results</a>
    </div>
    </div>

</div>
<?php include "includes/layouts/footer.php";?>