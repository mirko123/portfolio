<?php 
require_once("DB-time-controller.php");
session_start();
$username = $_SESSION["username"];
$id_id = $_POST["idid"];
$room = $_POST["room"];
$day = $_POST["day"];
$start = $_POST["start"];
$finish = $_POST["finish"];
$type = $_POST["type"];
$discription = "Няма описание";
if(isset($_POST["discription"]) && count($_POST["discription"])) $discription = $_POST["discription"];
// $discription = $_POST["discription"];
// echo $id_id;

$dbTimeController = new DBTimeController($username);
$dbTimeController->add($room, $id_id, $day, $start, $finish, $type, $discription);

header('Location: ../profile.php?type=lecture&username='.$username);

 ?>