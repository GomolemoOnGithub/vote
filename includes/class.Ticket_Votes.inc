<?php 
	class Ticket_Votes extends Sql {

	 	// attributes.
		protected const TABLENAME = '`vote`.`ticket_votes`'; 

		public  $ticket_code;
		public  $id;
		public  $candidate_name;
		public  $ip_address;
		public  $vote_date;

		//Methods 

		public function save($values){

			$this->create($values);

		}

}
