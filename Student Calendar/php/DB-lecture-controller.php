<?php 
/**
* 
*/
require_once("DB.php");
abstract class IDBLectureController 
{
	protected $db;
	function __construct($db)
	{
		$this->db = $db;
	}
	abstract public function create($username, $email, $password);
	abstract public function isLogin($username, $authKey);
	abstract public function canLogin($username, $password);
	abstract public function exist($username);
	abstract public function getCurrentLecture($username);
	abstract public function getAllLectures();
}

class DBLectureController extends IDBLectureController
{
	
	function __construct()
	{
		require_once("DB.php");
		$db = DB::getInstance();
		parent::__construct($db);
	}
	public function create($username, $email, $password)
	{
		$query = "INSERT INTO `lectures` (username, email, password) VALUES (:username, :email, :password)";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":username",$username);
		$statement->bindParam(":email",$email);
		$statement->bindParam(":password", $password);
		$res = $statement->execute();
		return $res;
	}
	public function isLogin($username, $authKey)
	{

		$db = DB::getInstance();

		$query = "SELECT * FROM `lectures` WHERE username = :username AND authKey = :authKey";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":username",$username);
		$statement->bindParam(":authKey",$authKey);
		$statement->execute();

		$count = $statement->rowCount();
		if($count != 0) return TRUE;
		return FALSE;
	}
	public function canLogin($username, $password)
	{

		$db = DB::getInstance();

		$query = "SELECT * FROM `lectures` WHERE username = :username AND password = :password";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":username",$username);
		$statement->bindParam(":password",$password);
		$statement->execute();
		$count = $statement->rowCount();

		if($count != 0) return TRUE;
		return FALSE;
	}
	public function updateInfo($username, $department)
	{
		$uptate_authkey_query = "UPDATE lectures SET department = :department WHERE username = :username";
		$statement = $this->db->connection->prepare($uptate_authkey_query);
		$statement->bindParam(":username",$username);
		$statement->bindParam(":department",$department);
		$statement->execute();
	}
	public function exist($username)
	{
		$check_user_exist_query = "SELECT * FROM `lectures` WHERE username = :username";
		$statement = $this->db->connection->prepare($check_user_exist_query);
		$statement->bindParam(":username",$username);
		$statement->execute();
		$count = $statement->rowCount();
		if($count != 0) return TRUE;
		else return FALSE;
	}
	public function getCurrentLecture($username)
	{
		$check_user_exist_query = "SELECT * FROM `lectures` WHERE username = :username";
		$statement = $this->db->connection->prepare($check_user_exist_query);
		$statement->bindParam(":username",$username);
		$statement->execute();
		$count = $statement->rowCount();
		if($count == 0) return FALSE;

		$user = $statement->fetch(PDO::FETCH_ASSOC);
		return $user;
	}

	public function getAllLectures()
	{	
		$query = "SELECT * FROM `lectures`";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":username",$username);
		$statement->execute();
		$count = $statement->rowCount();

		if($count != 0) return $statement->fetchAll(PDO::FETCH_ASSOC);
		return array();
	}
}

 ?>






