<?php
// START SESSION
session_start();

// 1. Define autoloader.
function __autoload($classname)
{
    include '../class.' . $classname . '.inc';
}

$vote = new Ticket_Votes();
$values = array();

$ticket_code = $_POST['ticket_code'];

//assign values

if (filter_var($ticket_code, FILTER_VALIDATE_INT) !== false) {

    $values['`ticket_code`'] = $ticket_code;
    $values['`candidate_id`'] = $_POST['candidate_id'];
    $values['`candidate_name`'] = trim($_POST['candidate_name']);
    // $values['`ip_address`'] = trim($_POST['ip_address']);

}

// Add Module
$vote->save($values);

// echo password_hash('@VoteApp2018',
//     PASSWORD_BCRYPT,
//     ['cost' => 10])
