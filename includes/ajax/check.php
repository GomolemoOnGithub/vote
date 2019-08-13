<?php
// START SESSION
session_start();

// 1. Define autoloader.
function __autoload($classname)
{
    include '../class.' . $classname . '.inc';
}

$checker = new Ticket();

$ticket_code = $_POST['ticket_code'];

//assign values

if (filter_var($ticket_code, FILTER_VALIDATE_INT) !== false) {

    // Add Module
    $checker->check($ticket_code);

}
