<?php

session_start();

// Define autoloader.

function __autoload($classname)
{
   include 'includes/class.' . $classname . '.inc';
}

$token = '';

// class instances
$session = new Session();

// Page title
$textitle = 'Publish';
$page = 'Publish Results';

$result = new Results();

if ($_SESSION['lock'] != 'Open') {

    // redirect if login was successful
    header('Location: ./login.php');
}

//Token salt
const SALT1 = '!Wr#$sjLaE17779';

if (
    isset($_POST) &&
    isset($_POST['submit']) &&
    isset($_POST['token']) &&
    null !== $session->check_token() &&
    !empty($_POST['token']) &&
    $session->check_token() == $_POST['token']
) {

    //0 Dispose form submission token
    $session->dispose_token();

    $ticket_keys = array();

    //
    $count = 1;

    $ticket_keys['`contestant`'] = '100';
    $ticket_keys['`result`'] = '100';

    $ticket_values = array();

    while ($count <= 3) {
        //add tickets
        $ticket_values[$count] = isset($_POST['Contestant' . $count]) ? $_POST['Contestant' . $count] : null;
        $ticket_values[$count . 'r'] = isset($_POST['result' . $count]) ? $_POST['Contestant' . $count] : null;

        //increment count
        $count++;
    }

    // save resuts
    if ($result->save($ticket_keys, array_filter($ticket_values))) {

        // redirect if login was successful
        Header('Location: publish_results.php?m=Added');
    }

} else {
    /*
     *Generate token hash
     *1. CSRF attack counter meature
     *2. Duplicate form submission counter meature
     */
    $token = hash_hmac('sha512', mt_rand(1, 1000000) . '9a7fd98asf' . time(), SALT1);

    // Assign hash to
    $session->sessionToken($token);
}

include 'includes/layouts/header.php';

if (isset($_REQUEST['m'])) {

    echo '<div id="note" class="notification has-text-grey-lighter">
    <button id="dtbtn" class="delete"></button>' . urldecode($_REQUEST['m']) . '</div>';
    unset($_REQUEST['m']);
}
?>

	<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>"  accept-charset="utf-8">
		      <div class="field">
		  <div class="control">
		    <input class="input is-medium has-text-centered" type="text" name="Contestant1" placeholder="1st Fullname" required>
		  </div>
		</div>

         <div class="field">
      <div class="control">
        <input class="input is-medium has-text-centered" type="text" name="result1" placeholder="%" required>
      </div>
    </div>
<hr>
          <div class="field">
      <div class="control">
        <input class="input is-medium has-text-centered" type="text" name="Contestant2" placeholder="2nd Fullname" required>
      </div>
    </div>

         <div class="field">
      <div class="control">
        <input class="input is-medium has-text-centered" type="text" name="result2" placeholder="% " required>
      </div>
    </div>
<hr>
          <div class="field">
      <div class="control">
        <input class="input is-medium has-text-centered" type="text" name="Contestant3" placeholder="3rd's Fullname" required>
      </div>
    </div>

         <div class="field">
      <div class="control">
        <input class="input is-medium has-text-centered" type="text" name="result3" placeholder="%" required>
         <input type="hidden" name="token" value="<?php echo $token; ?>">
      </div>
    </div>

		<div class="field">
		  <div class="control ">
		    <input class="button is-success is-medium is-fullwidth" type="submit" name="submit" value="Submit">
		  </div>
		</div>
		    </div>
	</form>


  </div>
   <div class="field">
        <div class="control ">
            <a id="results" href="./index.php" class="button is-success has-background-dark has-text-grey-light is-large is-fullwidth is-radiusless" ">Home</a>
        </div>
    </div>

<?php include "../includes/layouts/footer.php";?>