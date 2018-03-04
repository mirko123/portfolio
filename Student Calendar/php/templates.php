<?php 
class mainTemplate 
{
	public static function head() {
		session_start();
		echo '<head>
    <meta charset="UTF-8">
    <title>Fortune Cookies</title>
    <link rel="stylesheet" href="bower_components/bootstrap/dist/css/bootstrap.css">
    <link rel="stylesheet" href="css/main.css">
    <script src="bower_components/jquery/dist/jquery.js"></script>
    <script src="bower_components/bootstrap/dist/js/bootstrap.js"></script>
    <link rel="stylesheet" href="js/jquery.timeline-master/dist/timeline.min.css">
    <script src="js/jquery.timeline-master/dist/timeline.min.js"></script>
    </head>';
	}

	public static function header(){
		echo '<header id="header">
			    <h1>Студентски календар</h1>
			    	<nav class="navbar navbar-default">
			    	<ul class="nav navbar-nav" id="main-nav">';

		echo '
                <li class="users">
                    <a href="users.php">Студенти</a>
                </li>
                <li class="users">
                    <a href="lectures.php">Преподаватели</a>
                </li>
                <li class="ids">
                    <a href="discipline.php">ИД</a>
                </li>';
        if(isset($_SESSION['logged_in']) && $_SESSION['logged_in'] == 1) 
	        echo '<li><a href="profile.php?type='.$_SESSION['type'].'&username='.$_SESSION['username'].'">Профил</a></li>
	              <li><a class="btn-nav-logout" href="logout.php">Изход</a></li>';

   		else {
   			echo '<li>
                    <a href="login.php">Вход</a>
                </li>
                <li>
                    <a href="register.php">Регистрация</a>
                </li>
            </ul>';
   		}
		echo "</nav></header>";
   	}
}
 ?>













