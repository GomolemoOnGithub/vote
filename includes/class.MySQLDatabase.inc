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
		private static mysqli $_instance;
		private static PDO $_instancePDO;

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

	
		/**
		 * __clone
		 *
		 * @return void
		 */
		private function __clone(){} 

	
		/**
		 * getInstance
		 *
		 * @return mysqli
		 */
		public static function getInstance(){
			if(!self::$_instance){ 
				self::$_instance = new self();
				}
			
			return self::$_instance;
		}
		
		/**
		 * PDOInstance
		 *
		 * @return PDO
		 */
		public function getPDO(){
			if(!self::$_instancePDO){ 
				$dsn = 'mysql:host=localhost;dbname=vote';
				self::$_instancePDO = new PDO($dsn,'root', '');
			}		
			return self::$_instancePDO;
		}
		
		/**
		 * getConnection
		 *
		 * @return string
		 */
		public function getConnection(){
			return $this->_connection;
		}
			
		/**
		 * query
		 *
		 * @param  mixed $sql
		 * @return array
		 */
		public function  query($sql){
			$result = mysqli_query($this->_connection, $sql);
			return (array) $result;
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
		public function closeConnection(){
			if(isset($_connection)){
				mysqli_close($_connection);
				unset ($_connection);
				unset ($_instance);
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

		public function num_rows($resultSet){
			//how many rows were affected by the last ran
			return mysqli_num_rows($resultSet);
		}

		public function count_all($table){
			
			$result = $this->query("SELECT COUNT(*) FROM " . $table);
			$row 	= $this->fetch_array($result);
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