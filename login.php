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
$page = 'Login';

$textitle = 'Login';

$s = new Sql();

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

    $password = $s->find_by_username();

    // 7. Fetch the results
    if (password_verify($_POST['password'], $password)) {

        $_SESSION['lock'] = 'Open';

        // redirect if login was successful
        header('Location: ./index.php');

        return true;
    } else {
        return false;

        echo "not inside";
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

?>
	<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>"  accept-charset="utf-8">
		      <div class="field">
		  <div class="control">
		    <input class="input is-medium has-text-centered" type="text" name="username" placeholder="username" required>
        <input type="hidden" name="token" value="<?php echo $token; ?>">
		  </div>
		</div>


		<div class="field">
		  <p class="control ">
		    <input class="input is-medium has-text-centered" type="password" name="password" placeholder="password" required>
		  </p>
		</div>

		<div class="field">
		  <div class="control ">
		    <input class="button is-success is-medium is-fullwidth" type="submit" name="submit" value="Login">
		  </div>
		</div>
		    </div>

	</form>



  </section>




	</div>
<?php include "includes/layouts/footer.php";?>