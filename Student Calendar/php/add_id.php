<?php 
require_once("DB-ids-controller.php");
session_start();
$username = $_SESSION["username"];
$idname = $_POST["idname"];
$credits = $_POST["credits"];

$dbIdsController = new DBIDsController($username);
$dbIdsController->add($idname, $username, $credits);

header('Location: ../profile.php?type=lecture&username='.$username);

 ?>