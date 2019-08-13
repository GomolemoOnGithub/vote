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
$textitle = 'Add';
$page = 'Add Tickets';

$ticket = new Ticket();

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

    $ticket_keys['`ticket_code`'] = '100';

    $ticket_values = array();

    while ($count <= 5) {
        //add tickets
        $ticket_values['ticket_code' . $count] = (isset($_POST['ticket_code' . $count])) ? $_POST['ticket_code' . $count] : null;

        //increment count
        $count++;
    }

    // var_dump($ticket_keys);
    // echo '<pre>';
    // print_r($ticket_values);
    // // echo '</pre>';

    // die('stop');

    if ($ticket->save($ticket_keys, array_filter($ticket_values))) {

        // redirect if login was successful
        Header("Location: add.php?m=Added");
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
		    <input class="input is-medium has-text-centered" type="text" name="ticket_code1" placeholder="Ticket Code 1" required>
		  </div>
		</div>

         <div class="field">
      <div class="control">
        <input class="input is-medium has-text-centered" type="text" name="ticket_code2" placeholder="Ticket Code 2 " >
      </div>
    </div>

         <div class="field">
      <div class="control">
        <input class="input is-medium has-text-centered" type="text" name="ticket_code3" placeholder="Ticket Code 3" >
        <input type="hidden" name="token" value="<?php echo $token; ?>">
      </div>
    </div>

         <div class="field">
      <div class="control">
        <input class="input is-medium has-text-centered" type="text" name="ticket_code4" placeholder="Ticket Code 4 " >
      </div>
    </div>

         <div class="field">
      <div class="control">
        <input class="input is-medium has-text-centered" type="text" name="ticket_code5" placeholder="Ticket Code 5" >
      </div>
    </div>

		<div class="field">
		  <div class="control ">
		    <input class="button is-success is-medium is-fullwidth" type="submit" name="submit" value="Login">
		  </div>
		</div>
		    </div>
	</form>

  </div>

   <div class="field">
        <div class="control ">
            <a id="results" href="./index.php" class="button is-success has-background-dark has-text-grey-light is-large is-fullwidth is-radiusless">Home</a>
        </div>
    </div>

  <script>

<?php include "includes/layouts/footer.php";?>