<?php 
/**
* 
*/
require_once("DB.php");
abstract class IDBUsersIDController 
{
	protected $db;
	public $username;
	function __construct($db, $username)
	{
		$this->db = $db;
		$this->username = $username;
	}
	abstract public function add($idName, $priority);
	abstract public function remove($idName);
	abstract public function get($idName);
	abstract public function getAll();

}

class DBUsersIDController extends IDBUsersIDController
{
	
	function __construct($username)
	{
		require_once("DB.php");
		$db = DB::getInstance();
		parent::__construct($db,$username);
	}
	public function add($id_id, $priority)
	{
		$query = "INSERT INTO `user_ids` (id_id, username, priority) VALUES (:id_id, :username, :priority)";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":username",$this->username);
		$statement->bindParam(":id_id",$id_id);
		$statement->bindParam(":priority",$priority);
		$res = $statement->execute();
		return $res;
	}
	public function remove($idName)
	{
		$query = "DELETE uids FROM user_ids uids INNER JOIN ids idss ON idss.name = :name AND idss.id=uids.id_id WHERE uids.username=:username";
		
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":name",$idName);
		$statement->bindParam(":username", $this->username);
		$res = $statement->execute();
	}
	public function get($idName)
	{
		$query = "SELECT name, ids.id, ids.lecture, ids.credits, user_ids.priority FROM `user_ids` 
		INNER JOIN ids ON user_ids.id_id = ids.id
		WHERE username = :username AND name=:name";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":name",$idName);
		$statement->bindParam(":username",$this->username);
		$statement->execute();
		$count = $statement->rowCount();
		if($count == 0) return FALSE;

		$id = $statement->fetch(PDO::FETCH_ASSOC);
		return $id;
	}
	public function getAll()
	{	
		$query = "SELECT name, ids.id, ids.lecture, ids.credits, user_ids.priority FROM `user_ids` 
		INNER JOIN ids ON user_ids.id_id = ids.id
		WHERE user_ids.username=:username";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":username",$this->username);
		$statement->execute();
		$count = $statement->rowCount();

		if($count != 0) return $statement->fetchAll(PDO::FETCH_ASSOC);
		return array();
	}
}
 ?>






