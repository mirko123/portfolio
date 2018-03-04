<?php 
/**
* 
*/
require_once("DB.php");
abstract class IDBUserController 
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
	abstract public function getCurrentUser($username);
	abstract public function getAllUsers();
}

class DBUserController extends IDBUserController
{
	
	function __construct()
	{
		require_once("DB.php");
		$db = DB::getInstance();
		parent::__construct($db);
	}
	public function create($username, $email, $password)
	{
		$query = "INSERT INTO `users` (username, email, password) VALUES (:username, :email, :password)";
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

		$query = "SELECT * FROM `users` WHERE username = :username AND authKey = :authKey";
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

		$query = "SELECT * FROM `users` WHERE username = :username AND password = :password";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":username",$username);
		$statement->bindParam(":password",$password);
		$statement->execute();
		$count = $statement->rowCount();

		if($count != 0) return TRUE;
		return FALSE;
	}
	public function updateInfo($username, $speciality, $course)
	{
		$uptate_authkey_query = "UPDATE users SET course = :course , speciality = :speciality WHERE username = :username";
		$statement = $this->db->connection->prepare($uptate_authkey_query);
		$statement->bindParam(":username",$username);
		$statement->bindParam(":speciality",$speciality);
		$statement->bindParam(":course",$course);
		$statement->execute();
	}
	public function exist($username)
	{
		$check_user_exist_query = "SELECT * FROM `users` WHERE username = :username";
		$statement = $this->db->connection->prepare($check_user_exist_query);
		$statement->bindParam(":username",$username);
		$statement->execute();
		$count = $statement->rowCount();
		if($count != 0) return TRUE;
		else return FALSE;
	}
	public function getCurrentUser($username)
	{
		$check_user_exist_query = "SELECT username, id, speciality, course FROM `users` WHERE username = :username";
		$statement = $this->db->connection->prepare($check_user_exist_query);
		$statement->bindParam(":username",$username);
		$statement->execute();
		$count = $statement->rowCount();
		if($count == 0) return FALSE;

		$user = $statement->fetch(PDO::FETCH_ASSOC);
		return $user;
	}

	public function getAllUsers()
	{	
		$query = "SELECT username, id, speciality, course  FROM `users`";
		$statement = $this->db->connection->prepare($query);
		$statement->bindParam(":username",$username);
		$statement->execute();
		$count = $statement->rowCount();

		if($count != 0) return $statement->fetchAll(PDO::FETCH_ASSOC);
		return array();
	}
}

 ?>






