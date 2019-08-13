<?php 
	/*
	 *MySQL database.
	 */
	class MySQLDatabase
	{
		//Database connection constants
		private $DB_SERVER = 'localhost';
		private $DB_USER = 'root';
		private $DB_PASS = '';
		private $DB_NAME = 'vote';

		/*connection instance*/
		private $_connection;
		//store the single instance.
		private static $_instance;
		private static $_instancePDO;

		/*
		*Constructor
		*/
		public function __construct(){	
			$this->_connection = new  mysqli($this->DB_SERVER,$this->DB_USER,$this->DB_PASS,$this->DB_NAME);
			//error handling
			if(mysqli_connect_error()){
				trigger_error('Database connection failed:' . mysqli_connect_error(), E_USER_ERROR);
			}
		}


		/*magic method to prevent clonning*/
		private function __clone(){} 

		/*
		*Get an Instance of the database
		*/
		public static function getInstance(){
			if(!self::$_instance){ 
				self::$_instance = new self();
				}
			
			return self::$_instance;
		}

		/*
		*Get a PDO Instance of the database
		*/
		public static function PDOInstance(){
			if(!self::$_instancePDO){ 
				$dsn = 'mysql:host=localhost;dbname=vote';
				self::$_instancePDO = new PDO($dsn,'root', '');
			}		
			//return PDO instance
			return self::$_instancePDO;
		}

		/*
		* Get connection
		*/
		public function getConnection(){
			return $this->_connection;
		}

		//2. Perforn database query
		public function query($sql){
			$result = mysqli_query($this->_connection, $sql);
			return $result;
		}

		//3. Performe database objrct query
		public function object_query($sql){	
			try
			{
				$result = mysqli_query($this->_connection, $sql);
				return mysqli_fetch_object($result);
			} catch (Exception $e){
				return null;
			}								
		}

		/*4. close connection*/
		public static function closeConnection(){
			if(isset($_connection)){
				mysqli_close($_connection);
				unset ($_connection);
				uset ($_instance);
			}
		}

		/*confirm sql query*/
		private function confirm_query($result_set){
		// Test if there was a query error
			if (!$result_set) {
				die("Database query failed");				
			}
		}
		
		public function prep($string){
			$prepared_string = mysqli_real_escape_string($this->_connection,trim($string));
			return $prepared_string;
		}

		/*database ignasting functions*/
		public function fetch_array($resultSet){
			//gets result
			return mysqli_fetch_array($resultSet);
		}

		public static function num_rows($resultSet){
			//how many rows were affected by the last ran
			return mysqli_num_rows($resultSet);
		}

		public static function count_all($table){
			
			$result = self::query("SELECT COUNT(*) FROM " . $table);
			$row = self::fetch_array($result);
			return array_shift($result);
		}

		public function insert_id(){
			//gets the last id insertes over the current db connection
			return mysqli_insert_id($this->_connection);
		}

		public function affected_rows(){
			//how many rows were affected by the last ran
			return mysqli_affected_rows($this->_connection);
		}
}
?>