<?php 
require_once("DB-time-controller.php");
session_start();
$username = $_SESSION["username"];
$timeid = $_POST["timeid"];

$dbTimeController = new DBTimeController();
$dbTimeController->remove($timeid, $username);

header('Location: ../profile.php?type='.$_SESSION["type"].'&username='.$username);

 ?>