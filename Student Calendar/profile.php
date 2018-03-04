<!DOCTYPE html>
<html lang="en">
<?php 
require_once("php/templates.php");
require_once("php/profile_template.php");
require_once("php/lecture_profile_template.php");
require_once("php/DB-users-id-controller.php");
require_once("php/DB-user-controller.php");

    mainTemplate::head();
 ?>
<body id="page">
    <?php mainTemplate::header(); ?>

    <section id="container" class="container text-center">
    <?php 

    $profileTemplate;
    if($_GET["type"] == "student") {
        $profileTemplate = new ProfilePage();
    }
    else $profileTemplate = new LectureProfilePage();
    $profileTemplate->printUserInfo();
    $profileTemplate->printSettings();
    $profileTemplate->printIDs();
    $profileTemplate->addID();
    ?>





    </section>

</body>

</html>