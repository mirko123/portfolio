<?php 
require_once("DB-user-controller.php");
require_once("DB-time-controller.php");
require_once("calendar_template.php");
// require_once("DB-id-controller.php");

abstract class IProfilePage 
{
	protected $isCurrentUser;
	protected $isStudent;
	function __construct()
	{
		$this->isCurrentUser = isset($_SESSION['logged_in']) && $_SESSION['logged_in'] == 1 && $_SESSION['username'] == $_GET["username"];
		$this->isStudent = isset($_SESSION['logged_in']) && $_SESSION['logged_in'] == 1 && $_SESSION['type']=="student"; // не работи, явно някъде не се инициализира $_sessions["type"]
	}
	abstract public function printUserInfo();
	abstract public function printSettings();
	abstract public function printIDs();
	abstract public function addID();

}


class ProfilePage extends IProfilePage
{
	public function PrintUserInfo()
	{
		$dbUserController = new DBUserController();
		$user = $dbUserController->getCurrentUser($_GET["username"]);

		echo "<h3>Потребител: ". $user["username"]. "</h3>";
		echo "<p class='lead'>Специалност ";
		require_once("php/converter.php");
		$speciality = Converter::abvToSpec($user["speciality"]);
		echo $speciality;
		echo " и е ".$user["course"]." курс </p>";
	}

	public function printSettings() 
	{
		if($this->isCurrentUser) {
		?>
		<button class="btn btn-danger btn-controll settings" data-toggle="modal" data-toggle="modal" data-target="#controlModal">Настройки</button><br>


		<div class="modal fade" id="controlModal" role="dialog">
                <div class="modal-dialog">
                  <div class="modal-content">
                    <div class="modal-header">
                      <button type="button" class="close" data-dismiss="modal">&times;</button>
                      <h4 class="modal-title">Настройки</h4>
                    </div>
                    <div class="modal-body">
                        <form action="php/updateUserInfo.php" method="POST">
				            <label>
				                Избери специалност 
								<select name="speciality">
								  <option value="SI">Софтуерно Инженерство</option>
								  <option value="KN">Компютърни Науки</option>
								  <option value="IS">Информационни Системи</option>
								  <option value="I">Информатика</option>
								  <option value="PM">Приложна Математика</option>
								</select>
				            </label><br>
				            <label>
				                Избери курс 
				                <input name="course" min="1" max="4" value="1" type="number">
				            </label>
				            <br />
				            <input type="submit" id="btn-login" class="btn btn-success" value="Промени" />
				        </form>	
                    </div>
                    <div class="modal-footer">
                      <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                    </div>
                  </div>
                </div>
              </div>
		<?php  
		}
	}

	public function printIDs()
	{
		?>
		    <table class="table">
			  <thead>
			    <tr class="info">
			      <th>#</th>
			      <th>Име</th>
			      <th>Лектор</th>
			      <th>Кредити</th>
			      <th>Приоритет</th>
			      <?php if($this->isCurrentUser) echo "<th>Изтриване</th>"; ?>
			    </tr>
			  </thead>
			  <tbody>
			    <?php 
					
					$dbUserIdController = new DBUsersIDController($_GET["username"]);
					$ids = $dbUserIdController->getAll();
					$delBtn = "";
					$dbTimeController = new DBTimeController();
					foreach ($ids as $key=>$id) {
						echo "<tr class='active'>";
						echo "<td>$key</td>";
						echo "<td>".$id["name"]."</td>";
						echo "<td>".$id["lecture"]."</td>";
						echo "<td>".$id["credits"]."</td>";
						echo "<td>".$id["priority"]."</td>";
						if($this->isCurrentUser) 
						{
							?>
							<td>
					        <form action="php/delete_id.php" method="POST">
					            <input type="hidden" name="idname" value="<?php  echo $id["name"];?>">
					            <input type="submit" class="btn btn-danger btn" data-title="Delete" value="Изтрий" >
					        </form>
					        </td>
							<?php  
						}
						echo "</tr>";
						echo "<tr><td  colspan='6'><ul class='list-unstyled'>";

						$IdsTime = $dbTimeController->get($id["id"]);
						foreach ($IdsTime as $key => $id) {
							echo "<li><h4>";
							echo $id["type"]." ще се проведе ".Converter::numberToDay($id["day"])."  от ".$id["start"]." до ".$id["finish"]." часа в кабинет ".$id["room"];
							echo "</h4></li>";
						}
					}	

			     ?>
			  </tbody>
			</table>
		<?php 
		printCalendar($_GET["username"]);
	}

	public function addID() 
	{
		if($this->isCurrentUser) {
		?>
		</br></br>
		<h2>Добави Избираема Дисциплина към записаните</h2>
		<form class="form-horizontal" action="php/add_user_id.php" method="POST">
		    <div class="form-group">
		      	<label class="control-label col-sm-2" for="id_id">Име:</label>
		      	<div class="col-sm-10">
		        <select class="form-control" id="sel" name="id_id">
				<?php 
					require_once("DB-ids-controller.php");
					$dbIDsController = new DBIDsController();
					$ids = $dbIDsController->getAll();
					foreach ($ids as $key => $id) {
						echo "<option value='".$id["id"]."'>";
						echo $id["name"]." с лектор ".$id["lecture"];
						echo "</option>";
					}
			    ?>
			    </select>
		      	</div>

		      	<label class="control-label col-sm-4" for="priority">Приоритет:

				<input type="number" min="1" name="priority"/>

		      	</label>
		    </div>
		    <div class="form-group">        
		      	<div class="col-sm-offset-2 col-sm-10">
		        	<input type="submit" class="btn btn-default" value="Добави"/>
		      	</div>
		    </div>
		</form>

		<?php 
		}
	}
}

 ?>