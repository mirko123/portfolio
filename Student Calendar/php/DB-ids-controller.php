<?php 

require_once("DB.php");
abstract class IDBIDsController 
{
	protected $db;
	function __construct($db)
	{
		$this->db = $db;
	}
	abstract public function add($name, $lecture, $credits);
	abstract public function remove($id, $lecture);
	abstract public function getByLecture($lecture);
	abstract public function getAll();

}

class DBIDsController extends IDBIDsController
{
	
	function __construct()
	{
		require_once("DB.php");
		$db = DB::getInstance();
		parent::__construct($db);
	}

	public function add($name, $lecture, $credits)
	{	
		$query = "INSERT INTO `ids` (name, lecture, credits) VALUES (:name, :lecture, :credits)";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":name",$name);
		$statement->bindParam(":lecture",$lecture);
		$statement->bindParam(":credits", $credits);
		$res = $statement->execute();
		return $res;
	}

	public function remove($id, $lectureName)
	{
		$query = "DELETE FROM ids WHERE id=:id AND lecture=:lecture";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":id",$id);
		$statement->bindParam(":lecture",$lectureName);
		$res = $statement->execute();
	}

	public function getByLecture($lectureName)
	{	
		$query = "SELECT ids.id, ids.name, ids.lecture, ids.credits, lectures.department FROM ids INNER JOIN lectures ON lectures.username = ids.lecture  WHERE ids.lecture = :lecture";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":lecture",$lectureName);
		$statement->execute();
		$count = $statement->rowCount();

		if($count != 0) return $statement->fetchAll(PDO::FETCH_ASSOC);
		return array();
	}

	public function getAll()
	{	
		$query = "SELECT ids.id, ids.name, ids.lecture, ids.credits, lectures.department 
		FROM ids INNER JOIN lectures ON lectures.username = ids.lecture ";
		$statement = $this->db->connection->prepare($query);
		$statement->execute();
		$count = $statement->rowCount();

		if($count != 0) return $statement->fetchAll(PDO::FETCH_ASSOC);
		return array();
	}
}

 ?>






