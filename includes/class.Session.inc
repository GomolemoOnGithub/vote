<?php

	/*Cookies
	Cookies are little fi les of data that the server puts on the user’s computer. They are often used to
	identify a user and retain data needed in multiple screens.
	setcookie()
	You create a cookie with the setcookie() command and retrieve it with the $_COOKIE function
	that works just like $_GET and $_POST. The syntax of the setcookie() looks like:
	setcookie(name, value, expire, path, domain);
	The following code creates two cookies called “username” and “password” and assigns the values
	“andyt” and “12345” to them. It expires in one day. The setcookie() function must be before any
	HTML including the <html> tag.
	<?php
	setcookie(“username”, “andy”, time()+(60*60*24));
	setcookie(“password”, “12345”, time()+(60*60*24));

*/


	/*
	* session logging users in and out
	* DB-objects not saved in session
	*/
	class Session
	{	

		public function sessionToken($t){
			$_SESSION['token'] = $t;
		}

		public static function check_token(){
			/*Is there a message stored in the session?*/
			if (isset($_SESSION['token'])) {
			/*Add it as an attribute and erease the stored version*/
				$t = $_SESSION['token'];
				return $t ;
			}
		}

		public static function dispose_token(){
			/*Is there a message stored in the session?*/
			if (isset($_SESSION['token'])) {
				unset($_SESSION['token']);
			}
		}


}
