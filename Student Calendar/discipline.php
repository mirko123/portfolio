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
				<th>Лектор</th>
				<th>Катедра</th>
				<th>Кредити</th>
			</tr>
		</thead>
		<tbody>
		<?php 
			require_once("php/DB-ids-controller.php");
			$dbIDsController = new DBIDsController();
			$ids = $dbIDsController->getAll();
			foreach ($ids as $key => $id) {
				echo "<tr>";
				echo "<td>".$id["id"]."</td>";
				echo "<td>".$id["name"]."</td>";
				echo "<td><a href='profile.php?type=lecture&username=".$id["lecture"]."'>".$id["lecture"]."</a></td>";
				echo "<td>".$id["department"]."</td>";
				echo "<td>".$id["credits"]."</td>";
				echo "</tr>";
			}
	    ?>
		</tbody>
	</table>


    </section>

</body>

</html>