<?php 
require_once("DB-time-controller.php");

function printCalendar($student)
{
	$day = date('w');
	$dbTimeController = new DBTimeController();
	$idsByDayAndStudent = $dbTimeController->getByDayAndStudent($day,$student);
	usort($idsByDayAndStudent, function($a, $b)
	{
	    if ($a["start"] == $b["start"]) {
	    	if($a["priority"] == $b["priority"])
	        	return 0;
	    	return ($a["priority"] < $b["priority"]) ? -1 : 1;
	    }
	    return ($a["start"] < $b["start"]) ? -1 : 1;
	});


	?>
		<div class="container">
		<div id="myTimeline">
		  <ul class="timeline-events">


		 <?php 
		$date = date("Y-m-d");
		foreach ($idsByDayAndStudent as $key => $id) {
			$start = $date." ".$id["start"].":00";
			$end = $date." ".$id["finish"].":00";
			$row;
			if($id["priority"] > 5) $row = 5;
			else if($id["priority"] < 1) $row = 1;
			else $row = $id["priority"];
		  	?>
		    <li data-timeline-node="{ start:'<?php echo $start; ?>',end:'<?php echo $end; ?>',row:<?php echo $row; ?>, content:'<p><?php echo $id["discription"] ?></p>' }"><?php echo $id["name"]." - ".$id["room"]." (".$id["type"].")"; ?></li>
		  	<?php 

		}
		   ?>
		  </ul>
		</div>
		<div class="timeline-event-view"></div>
		<script type="text/javascript">
			$("#myTimeline").timeline({
				range: 5,
				  minGridPer: 3,
				  minGridSize: 30
			});
		</script>
		</div>
	<?php 
}

 ?>