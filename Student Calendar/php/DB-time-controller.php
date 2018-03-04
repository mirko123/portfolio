<?php 

require_once("DB.php");
abstract class IDBTimeController
{
	protected $db;
	function __construct($db)
	{
		$this->db = $db;
	}
	abstract public function add($room, $id_id, $day, $start, $finish, $type, $discription);
	abstract public function get($id);

}

class DBTimeController extends IDBTimeController
{
	
	function __construct()
	{
		require_once("DB.php");
		$db = DB::getInstance();
		parent::__construct($db);
	}

	public function add($room, $id_id, $day, $start, $finish, $type, $discription)
	{	
		if($start > $finish) return false;
		$query = "INSERT INTO `time_distribution` (room, id_id, day, start, finish, type, discription) VALUES (:room, :id_id, :day, :start, :finish, :type, :discription)";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":room",$room);
		$statement->bindParam(":id_id",$id_id);
		$statement->bindParam(":day",$day);
		$statement->bindParam(":start", $start);
		$statement->bindParam(":finish", $finish);
		$statement->bindParam(":type", $type);
		$statement->bindParam(":discription", $discription);
		$res = $statement->execute();
		return $res;
	}

	public function remove($id, $lecture)
	{	
		$query = "DELETE time_distribution FROM time_distribution, ids WHERE time_distribution.id=:id AND ids.id = time_distribution.id_id AND ids.lecture=:lecture";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":id",$id);
		$statement->bindParam(":lecture",$lecture);
		$res = $statement->execute();
	}

	public function get($id_id)
	{	
		$query = "SELECT * FROM time_distribution WHERE id_id = :id_id";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":id_id",$id_id);
		$statement->execute();
		$count = $statement->rowCount();

		if($count != 0) return $statement->fetchAll(PDO::FETCH_ASSOC);
		return array();
	}
	public function getByDayAndStudent($day, $student)
	{
		$query = "SELECT  time_distribution.*, user_ids.priority, ids.name
		FROM ids, time_distribution
		INNER JOIN user_ids ON user_ids.username = :student
		AND user_ids.id_id = time_distribution.id_id 
		WHERE time_distribution.day=:day AND time_distribution.id_id = ids.id";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":day",$day);
		$statement->bindParam(":student",$student);
		$statement->execute();
		$count = $statement->rowCount();
		if($count != 0) return $statement->fetchAll(PDO::FETCH_ASSOC);
		return array();
	}

}

 ?>






