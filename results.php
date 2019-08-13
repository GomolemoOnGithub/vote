<?php
// START SESSION
session_start();

// Define autoloader.
function __autoload($classname)
{
    include 'includes/class.' . $classname . '.inc';
}

// Class Objects
$vote = new Results();

$textitle = 'MissBW | Results';

$page = 'Results';

$header = 'Welcame';

include 'includes/layouts/header.php';

?>

      <div >
                      <?php
if ($vote->checkResults()) {

    echo $vote->getResults();
} else {
    echo '<br><div class="container has-text-centered"></p><p class="title is-6 ">Results being varified <br>...</p><center><div class="is-large loader"></div><br></div></center><div class="container has-text-centered"><p class="subtitle is-6">Voting process audited by<br>MSD Mesotlo & Associates</p></div><br><br>';
}

?>
      </div>

      <div>
         <p class="title"></p>
          <p class="subtitle">

          </p>
      </div>

    <div class="field">
        <div class="control ">
            <a id="results" href="./index.php" class="button is-success has-background-dark has-text-grey-light is-large is-fullwidth is-radiusless" ">Home</a>
        </div>
    </div>

    </div>

<?php include "includes/layouts/footer.php";?>