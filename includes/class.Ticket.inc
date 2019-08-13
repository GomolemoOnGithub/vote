<?php 
	class Ticket extends Sql {


	 	// attributes.
		protected const TABLENAME = '`vote`.`ticket`'; 

		public  $ticket_code;
		public  $ticket_event;
		public  $added_on;

		//Methods 

		public function save($keys, $values ){

			$this->createMultiple($keys,$values);

			return true;

		}

		public function check($id){

			$db = MySQLDatabase::PDOInstance();
			// SQL query
			$sql = 'SELECT * FROM `vote`.`ticket` WHERE ticket_code= ?;';

			// prepare
			$stmt = $db->prepare($sql);

			$stmt->bindParam(1,$id,PDO::PARAM_INT);

			//execute
			$stmt->execute();

			if( $stmt->rowCount() > 0 )

			{

			    echo 1;
			    
			}

			else

			{	
			    echo 0;
			    
			}

		}
}
