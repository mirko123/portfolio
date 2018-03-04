<!DOCTYPE html>
<html lang="en">
<?php require_once("php/templates.php");
    mainTemplate::head();
 ?>
<body id="page">
    <?php mainTemplate::header(); ?>

    <section id="container" class="container text-center">
    <table class="table">
	  <thead>
	    <tr>
	      <th>#</th>
	      <th>Име</th>
	      <th>Специалност</th>
	      <th>Курс</th>
	    </tr>
	  </thead>
	  <tbody>
	    <?php 
			require_once("php/DB-user-controller.php");
			require_once("php/converter.php");
			$dbUserController = new DBUserController();
			$users = $dbUserController->getAllUsers();
			
			foreach ($users as $key=>$user) {
				echo "<tr>";
				echo "<td>$key</td>";
				$arc = "<a href='profile.php?type=student&username=".$user["username"]."'>".$user["username"]."</a>";
				echo "<td>".$arc."</td>";
				echo "<td>".Converter::abvToSpec($user["speciality"])."</td>";
				echo "<td>".$user["course"]."</td>";
				echo "</tr>";
			}		
			
	     ?>
	  </tbody>
	</table>


    </section>

</body>

</html>