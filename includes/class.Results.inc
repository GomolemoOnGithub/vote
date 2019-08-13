<?php 
	class Results extends Sql{

	/*
	 *URL of display
	 */	
	protected const TABLENAME = '`vote`.`results`';
	public $id;
	public $contestant;
	public $result;
	public $added_on;


	//Methods 
	public function save($keys, $values ){

		$this->createMultiple2($keys,$values);

	}

	public static function checkResults(){

		$db = MySQLDatabase::PDOInstance();

		//1. Define sql
		$sql =" SELECT * ";
		$sql .="FROM `vote`.`results` order by result desc";
	
	    // prepare
		$stmt = $db->prepare($sql);

		//execute
		$stmt->execute();

		if( $stmt->rowCount() > 0 )

		{

		    return true;
		    
		}

		else

		{	
		    return false;
		    
		}
	}

	public function getResults(){

		$db = MySQLDatabase::PDOInstance();

		//1. Define sql
		$sql = " SELECT * from `vote`.`results` order by `result`";

	
	    $all = static::select($sql);

		//1. Priming variable
		$output = "";

	    //2. get prepare all events 
	    foreach($all as $result) {

			$output .= '
						<div class="card">
							<div class="card-content ">
								<div class="media">

									<div class="media-content has-text-centered">
										<p class="title is-fullwidth is-radiusless is-4 has-text-dark">'. $result->contestant. '</p>
										<p class="title button is-fullwidth is-radiusless is-4 has-text-warning has-background-dark">'. $result->result . '</p>
									</div>

								</div>
							</div>
								
						</div>	
					<br>'; 
	    }

	    return $output;
	}

}