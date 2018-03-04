<?php 
require_once("profile_template.php");
require_once("DB-lecture-controller.php");
require_once("DB-ids-controller.php");
require_once("DB-time-controller.php");
require_once("converter.php");

class LectureProfilePage extends IProfilePage
{
	function __construct()
	{
		$this->isCurrentUser = isset($_SESSION['logged_in']) && $_SESSION['logged_in'] == 1 && $_SESSION['username'] == $_GET["username"];
	}

	public function printUserInfo()
	{
		$dbLectureController = new DBLectureController();
		$lecture = $dbLectureController->getCurrentLecture($_GET["username"]);

		echo "<h3>Преподавател: ". $lecture["username"]. "</h3><p class='lead'>";
		if($lecture["department"]) echo "От катедра ".$lecture["department"]." и ";
		echo "с поща ".$lecture["email"]."</p>";
	}

	public function printSettings() 
	{
		if($this->isCurrentUser) {
		?>
		<button class="btn btn-danger btn-controll settings" data-toggle="modal" data-toggle="modal" data-target="#controlModal">Настройки</button>


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
				                Смени катедра 
							<select name="department">
							  <option value="Изчислителни системи">
							  	Изчислителни системи</option>
							  <option value="Информационни технологии">
							  	Информационни технологии</option>
							  <option value="Компютърна информатика">
							  	Компютърна информатика</option>
							  <option value="Софтуерни технологии">
							  	Софтуерни технологии</option>
							  <option value="Вероятности, операционни изследвания и статистика">
							  Вероятности,операционни изследвания и статистика</option>
								</select>
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
			      <?php if($this->isCurrentUser) echo "<th></th><th></th>";
			      else if(isset($_SESSION['logged_in']) && $_SESSION['logged_in'] == 1 && $_SESSION["type"]=="student")  echo "<th></th>";?>
			    </tr>
			  </thead>
			  <tbody>
			    <?php 
					
					$dbIdsController = new DBIDsController();
					$ids = $dbIdsController->getByLecture($_GET["username"]);
					$delBtn = "";
					foreach ($ids as $key=>$id) {
						echo "<tr class='active'>";
						echo "<td>$key</td>";
						echo "<td>".$id["name"]."</td>";
						echo "<td>".$id["lecture"]."</td>";
						echo "<td>".$id["credits"]."</td>";
						if($this->isCurrentUser) 
						{
							?>
							<td class="col-md-1">
							<button type="button" class="btn btn-info" data-toggle="modal" data-target="#timeModal<?php echo $key;?>">Време на провеждане</button>

							<div id="timeModal<?php echo $key;?>" class="modal fade" role="dialog">
							  <div class="modal-dialog">

							    <!-- Modal content-->
							    <div class="modal-content">
							      <div class="modal-header">
							        <button type="button" class="close" data-dismiss="modal">&times;</button>
							        <h4 class="modal-title">Добави време на провеждане <?php echo $id["name"]; ?></h4>
							      </div>
							      <div class="modal-body">

							      <form action="php/time_distribution_add.php" method="POST">
							      		<input type="hidden" name="idid" value="<?php echo $id["id"]?>">
							            <label>Кабинет
							            <input type="number" min="1" name="room"/>
							            </label>
							            <label>Ден 
							            <select name="day">
							            	<option value="1">Понеделник</option>
							            	<option value="2">Вторник</option>
							            	<option value="3">Сряда</option>
							            	<option value="4">Четвъртък</option>
							            	<option value="5">Петък</option>
							            	<option value="6">Събота</option>
							            	<option value="7">Неделя</option>
							            </select>
							            <!-- <input type="number" min="1" max="7" name="day"/> -->
							            </label></br>
							            <label>От час
							            <input type="number" min="1" max="24" name="start"/>
							            </label>
							            <label>До час
							            <input type="number" min="1" max="24" name="finish"/>
							            </label>
							            <label>Тип
							            <select name="type">
							            	<option value="Лекция">Лекция</option>
							            	<option value="Упражнение">Упражнение</option>
							            	<option value="Консултация">Консултация</option>
							            	<option value="Семинар">Семинар</option>
							            </select>
							            </label>
							            <br />
							            <label>Кратко Описание
							            <input type="text" class="form-control input-lg" name="discription"/>
							            </label>
							            <br />
							            <input type="submit" id="btn-login" class="btn btn-success" value="Добави" />
							        </form>	
							      </div>
							      <div class="modal-footer">
							        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
									      </div>
									    </div>
									  </div>
							</div>
							</td>
							<td class="col-md-1">
					        <form action="php/delete_id.php" method="POST" class="form-inline">
					            <input type="hidden" name="id" value="<?php  echo $id["id"];?>">
					            <input type="submit" class="btn btn-danger" data-title="Delete" value="Изтрий" >
					        </form>
					        </td>
							<?php  
						}
						if( isset($_SESSION['logged_in']) && $_SESSION['logged_in'] == 1 && $_SESSION["type"] == "student")
						{?>
							<td class="col-md-4">
							<form action="php/add_user_id.php" method="POST" class="form-inline">
					            <input type="hidden" name="id_id" value="<?php  echo $id["id"];?>">
					            Приоритет:
								<input type="number" min="1" name="priority"/>
					            <input type="submit" class="btn btn-success" data-title="Delete" value="Добави" >
					        </form>
							</td>
							<?php	
						}?>
						</tr>
						<tr><td  colspan='5'><ul class="list-unstyled">

						<?php 
						$dbTimeController = new DBTimeController();
						$IdsTime = $dbTimeController->get($id["id"]);
						foreach ($IdsTime as $key => $id) {
							echo "<li ><h4 >";
							echo $id["type"]." ще се проведе ".Converter::numberToDay($id["day"])."  от ".$id["start"]." до ".$id["finish"]." часа в кабинет ".$id["room"];
							echo "";
							if($this->isCurrentUser){
								echo "</h4><form action='php/delete_time.php' method='POST'>
								<input type='hidden' name='timeid' value='".$id["id"]."'/>";
								echo '<button class="pull-right btn btn-danger btn-xs btn-remove-id" data-title="Delete" data-toggle="modal" data-target="#delete"><span class="glyphicon glyphicon-trash"></span></button>';
								echo "</form></li>";
							}
						}
						echo "</ul><td></tr>";
					} ?>
			  </tbody>
			</table>
				
		<?php 
	}

	public function addID() 
	{
		if($this->isCurrentUser) {
		?>
		</br></br>
		<h2>Добави Избираема Дисциплина към записаните</h2>
		<form class="form-horizontal" action="php/add_id.php" method="POST">
		    <div class="form-group">
		      	<label class="control-label col-sm-2" for="email">Име на дисциплината:</label>
		      	<div class="col-sm-9">
		        <input name="idname" id="tb-idname" class="form-control" placeholder="Enter id name" type="text">
		      	</div>
		        </label>
		      	<label class="control-label col-sm-2" for="email">Брой кредити:</label>
		      	<div class="col-sm-9">
		        <input name="credits" id="tb-credits" class="form-control" type="number" placeholder="Enter credits">
		      	</div>
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