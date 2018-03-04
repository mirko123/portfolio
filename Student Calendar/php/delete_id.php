<?php 
session_start();
$username = $_SESSION["username"];

$dbIdController;
if($_SESSION["type"]=="student") 
{
	require_once("DB-users-id-controller.php");
	$dbUserIdController= new DBUsersIDController($username);
	$idName = $_POST["idname"];
	$dbUserIdController->remove($idName, $_SESSION['username']);
} 
else {
	require_once("DB-ids-controller.php");
	$dbIdsController= new DBIDsController();
	$id_id = $_POST["id"];
	$dbIdsController->remove($id_id, $username);
}

header('Location: ../profile.php?type='.$_SESSION["type"].'&username='.$username);

 ?>