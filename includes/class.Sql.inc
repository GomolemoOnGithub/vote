<?php 

class Sql
{
	// Common Database Methods
	public static function select_all(){
		try{
		    $db = MySQLDatabase::PDOInstance();		
			//SQL query
			$sql = "SELECT * FROM ". static::TABLENAME ;	
			// prepare
			$result = $db->query($sql);
			// Fetch Object instance
			$object = $result->fetchAll(PDO::FETCH_OBJ);

			// Return Instance
			return $object;
		} catch (Exception $e){
			$error = $e->getMessage();
		}
	}

	public static function select($sql=''){

		try{
			//instanciate PDO
		    $db = MySQLDatabase::PDOInstance();			
			// prepare
			$stmt = $db->prepare($sql);

			//execute
			$stmt->execute();

			// Fetch Object instance
			$result = $stmt->fetchAll(PDO::FETCH_OBJ);

			// Return Instance
			return $result;
		} catch (Exception $e){
			$error = $e->getMessage();
		}
	}

	public static function selectAssoc($sql=''){
		try{
		    $db = MySQLDatabase::PDOInstance();			
			// prepare
			$result = $db->query($sql);

			// Fetch Object instance
			$assoc = $result->fetchAll(PDO::FETCH_ASSOC);

			// Return Instance
			return $assoc;
		} catch (Exception $e){
			$error = $e->getMessage();
		}
	}

	public function findColumn($sql=''){
		try{	
			$db = MySQLDatabase::PDOInstance();

			$result = $db->query($sql)->fetchAll(PDO::FETCH_COLUMN,0);

			return $result;
		}catch (Exception $e){
			$error = $e->getMessage();
		}
	}

		public function find_by_username() {
		try{	
			$db = MySQLDatabase::PDOInstance();

			// 2. Query
			$sql = 'SELECT `password` FROM `vote`.`users` WHERE `user` = ? LIMIT 1';


			// 2. Preprare and validate the SQL with placeholders

			$stmt = $db->prepare($sql);

			// 3. Bind values to the placeholder

			// username must be a string, and to keep it clear it came from a user, and we don't trust it, leave it in POST.

			$stmt->bindValue(1, $_POST['username'], PDO::PARAM_STR); //bindParam only takes

			// 4. Execute the statement
			$stmt->execute();

			// 6. Where to put the results.
			$stmt->bindColumn('password', $hash);

			// 5. Fetch the results
			$stmt->fetch(PDO::FETCH_BOUND);
			// 7
			$stmt->closeCursor();

			// Return Instance
			return $hash;
		} catch (Exception $e){
			$error = $e->getMessage();
		}
	}

	public function instanciate($stmt) {
		try{

			 // 4. Instanciate the class
			$_instance = new self();
			
			// Execute
			$stmt->execute();

			// 4. Instanciate the object
			$stmt->setFetchMode(PDO::FETCH_INTO,$_instance);

			// Fetch Object instance
			$stmt->fetch();

			// 6. close Cursor
			$stmt->closeCursor();

		}catch (Exception $e){
			$error = $e->getMessage();
		}
	}	

	public function selectOne($sql) {
		try{	
			$db = MySQLDatabase::PDOInstance();

			// prepare
			$stmt = $db->prepare($sql);

			// Execute
			$stmt->execute() or die('...');

			// Fetch Object instance
			$object = $stmt->fetch(PDO::FETCH_OBJ);

			// Return Instance
			return $object;
		} catch (Exception $e){
			$error = $e->getMessage();
		}
	}

	public static function countAll(): int{
		try{
			// Database Instance
			$db = MySQLDatabase::PDOInstance();

			// Query sql statement
			$result = $db->query("SELECT COUNT(*)FROM " . static::TABLENAME);

			// Get number of rows
			$rows   = $result->fetchColumn();

			return $rows;
		} catch (Exception $e){
			$error = $e->getMessage();
		}
	}

	protected function create($values){

		try{
			$db = MySQLDatabase::PDOInstance();

			/*1. Query*/
			$sql = "INSERT INTO ". static::TABLENAME ." (";
			$sql .= join(", ",array_keys($values));
			$sql .= ") VALUES ("; 
			$sql .= join(",", $this->generatePlaceholders($values));
			$sql .= ")";

			/*2. Preprare*/
			$stmt = $db->prepare($sql);

			// print_r($values);
			// echo $sql;

			/*3. Execute the statement*/
			

			if($stmt->execute(array_values($values)))
			{

			    echo 1;
			    
			}
			else
			{	
			    echo 0;
			    
			}

		} catch (Exception $e){
			$error = $e->getMessage();
		}
	}

	protected function createMultiple($keys,$values){

		try{
			$db = MySQLDatabase::PDOInstance();

			/*1. Query*/
			$sql = "INSERT INTO ". static::TABLENAME ." (";
			$sql .= join(", ",array_keys($keys));
			$sql .= ") VALUES ("; 
			$sql .= join(",(", $this->generateMultiPlaceholders($values));
			// $sql .= ")";

			/*2. Preprare*/
			$stmt = $db->prepare($sql);

			// echo $sql;

			/*3. Execute the statement*/
			$stmt->execute(array_values($values)); 
			
			// 4. Check affected rows
			if( $stmt->rowCount() > 0 )

			{

			    return true;
			    
			}

			else

			{	
			    return false;
			    
			}

		} catch (Exception $e){
			$error = $e->getMessage();
		}
	}

	protected function createMultiple2($keys,$values){

		try{
			$db = MySQLDatabase::PDOInstance();

			/*1. Query*/
			$sql = "INSERT INTO ". static::TABLENAME ." (";
			$sql .= join(", ",array_keys($keys));
			$sql .= ") VALUES ("; 
			$sql .= join(",(", $this->generateMultiPlaceholders2($values));
			// $sql .= ")";

			/*2. Preprare*/
			$stmt = $db->prepare($sql);

			// echo $sql;

			// print_r(array_values($values));

			/*3. Execute the statement*/
			$stmt->execute(array_values($values)); 
			
			// 4. Check affected rows
			if( $stmt->rowCount() > 0 )

			{

			    return true;
			    
			}

			else

			{	
			    return false;
			    
			}

		} catch (Exception $e){
			$error = $e->getMessage();
		}
	}

	private function generatePlaceholders($array){
		// For statement 
		for ($i = 0; $i < count($array) ; $i++) {
			$output[] = '?';
		}
		return $output;
	}


	private function generateMultiPlaceholders($array){
		// For statement 
		for ($i = 0; $i < count($array) ; $i++) {
			$output[] = '?)';
		}
		return $output;
	}


	private function generateMultiPlaceholders2($array){
		// For statement 
		for ($i = 0; $i < count($array)/2 ; $i++) {
			$output[] = '?,?)';
		}
		return $output;
	}
	
	protected function update($values){

		$db = MySQLDatabase::PDOInstance();	

		foreach($values as $key => $value){
			$attribute_keys_pair[] = "{$key} =  ? ";
		}

		$sql = "UPDATE ". static::TABLENAME ." SET ";
		$sql .= join(", ", $attribute_keys_pair);
		
		// add id 
		if (isset($this->id)) {
			$values['id'] = $this->id ;
			$sql .= " WHERE id = ?";
			
		}
		
		if(isset($this->abv)){
			$values['id'] = $this->abv ;
			$sql .= " WHERE abv = ?";
		}

		echo $sql;
		$stmt = $db->prepare($sql) or die('..1..');	

		print_r($values);	

		$stmt->execute(array_values($values)) or die('..3..');
		//confirm query
		// return ($affected === 1) ? true : false;
	}

	public function delete(){
		$db = MySQLDatabase::PDOInstance();
		//DELETE from table
		$sql = "DELETE FROM " . static::TABLENAME ;
		$sql.= " WHERE id=" . $this->id ;
		$sql.= " LIMIT 1";

		// Delete all rows from the FRUIT table 
		$affected = $db->exec($sql);

		return $affected == 1 ? true : false;	
	}
}