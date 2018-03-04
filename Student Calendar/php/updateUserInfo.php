<?php 
	session_start();
	$username = $_SESSION['username'];

	$dbUserController;
	if($_SESSION["type"] == "student") {
		$course = $_POST["course"];
		$speciality = $_POST["speciality"];
    	require_once("DB-user-controller.php");
    	$dbUserController = new DBUserController();
		$dbUserController->updateInfo($username, $speciality, $course);
	}
	else {
		$department = $_POST["department"];
    	require_once("DB-lecture-controller.php");
    	$dbUserController = new DBLectureController();
		$dbUserController->updateInfo($username, $department);
	}

	header('Location: ../profile.php?type='.$_SESSION["type"].'&username='.$username);


 ?>