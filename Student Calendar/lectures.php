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
	      <th>Катедра</th>
	      <th>Поща</th>
	    </tr>
	  </thead>
	  <tbody>
	    <?php 
			require_once("php/DB-lecture-controller.php");
			$dbLectureController = new DBLectureController();
			$lectures = $dbLectureController->getAllLectures();
			
			foreach ($lectures as $key=>$lecture) {
				echo "<tr>";
				echo "<td>$key</td>";
				$arc = "<a href='profile.php?type=lecture&username=".$lecture["username"]."'>".$lecture["username"]."</a>";
				echo "<td>".$arc."</td>";
				echo "<td>".$lecture["department"]."</td>";
				echo "<td>".$lecture["email"]."</td>";
				echo "</tr>";
			}		
			
	     ?>
	  </tbody>
	</table>


    </section>

</body>

</html>