<?php 
	class Candidate extends Sql{

	/*
	 *URL of display
	 */	
	protected const TABLENAME = 'candidates';
	public $id;
	public $name;
	public $surname;
	public $url;
	public $added_on;

	public static function getCandidates(){
	    $all = static::select_all();
		//1. Priming variable
		$output = "";
		$count = 1;
		//2. get prepare all events 
		try {
			
			foreach($all as $event) {

				$output .= '<div>
								<a  id="'. $event->id .'" class="vote" style="de" >
									<div class="card">
										<div class="card-image">
											<figure class="image"><img src="'.$event->url.'" >
											</figure>
										</div>
									
	
									<div class="card-content has-background-dark">
										<div class="media-content has-text-centered ">
											<p class="title is-4 has-text-warning">'. $event->name . ' ' . $event->surname . '</p>
										</div>
									</div>
									</div>	
								</a>
	
								
							</div><br>';	
	
			}
		} catch(Exception $e) {
			echo 'Message: ' .$e->getMessage();
		  }
		


	    //unset($result);

	    return $output;
	}

}