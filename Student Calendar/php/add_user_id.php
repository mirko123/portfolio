<?php 
require_once("DB-users-id-controller.php");
session_start();
$username = $_SESSION["username"];
$id_id = $_POST["id_id"];
$priority = $_POST["priority"];

$dbUserIdController = new DBUsersIDController($username);
$dbUserIdController->add($id_id, $priority);

header('Location: ../profile.php?type=student&username='.$username);

 ?>