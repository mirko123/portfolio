<?php 
	// abstract class Validate
	// {
	// 	protected $data;
	// 	protected $requirements;
	// 	protected $errors;
	// 	protected $invalidFields;
	// 	function __construct($data, $requirements)
	// 	{
	// 		$this->data = $data;
	// 		$this->requirements = $requirements;
	// 		$this->errors = array();
	// 		$this->invalidFields = array();
	// 	}

	// 	abstract public function isValid();
	// 	abstract public function getInvalidFields();
	// 	abstract public function printErrors();
	// }
	abstract class Validate
	{
		protected $data;
		protected $requirements;
		protected $errors;
		protected $invalidFields;
		function __construct($data,  $requirements)
		{
			$this->data = $data;
			$this->requirements = $requirements;
			$this->errors = array();
			$this->invalidFields = array();
		}

		public function isValid()
		{
			foreach ($this->data as $fieldName => $fieldValue) 
			{
				$fieldRequirements = $this->requirements[$fieldName];
				if(!isset($fieldRequirements["max"]))
				{
					if(!in_array($fieldValue, $fieldRequirements))
					{
						array_push($this->errors, $fieldName." must be from ".implode(",", $fieldRequirements));
						array_push($this->invalidFields, $fieldName);
					}
				}
				else if($fieldRequirements["max"] < strlen($fieldValue))
				{
					array_push($this->errors, $fieldName." must be less ".$fieldRequirements["max"]);
					array_push($this->invalidFields, $fieldName);
				}
				else if($fieldRequirements["min"] > strlen($fieldValue))
				{
					array_push($this->errors, $fieldName." must be more of ".$fieldRequirements["min"]);
					array_push($this->invalidFields, $fieldName);
				}
			}
			if(count($this->errors) != 0) return false;
			return true;
		}

		public function getInvalidFields()
		{
			return $this->invalidFields;
		}

		public function getErrors()
		{
			return $this->errors;
		}

		abstract public function printErrors();
	}





	class ValidateLogin extends Validate
	{
		
		function __construct($data,  $requirements = null)
		{
			if(!$requirements)
			{
				$requirements = [
				 	"username" => [
					 	"max" => 100,
					 	"min" => 2
					 ],
				 	"password" => [
					 	"max" => 100,
					 	"min" => 2
					 ]
				];
			}
			parent::__construct($data, $requirements);
		}

		public function printErrors()
		{
			echo "<ul>";
			foreach ($this->errors as $error) {
				echo "<li>";
				echo $error;
				echo "</li>";
			}
			echo "</ul>";
		}
	}
	class ValidateRegister extends Validate
	{
		
		function __construct($data,  $requirements = null)
		{
			if(!$requirements)
			{
				$requirements = [
				 	"username" => [
					 	"max" => 100,
					 	"min" => 2
					 ],
				 	"password" => [
					 	"max" => 100,
					 	"min" => 1
					 ],
				 	"email" => [
					 	"max" => 100,
					 	"min" => 2
					 ],
					 "type" => ["student", "lecture"]
				];
			}
			parent::__construct($data, $requirements);
		}


		public function printErrors()
		{
			echo "<ul>";
			foreach ($this->errors as $error) {
				echo "<li>";
				echo $error;
				echo "</li>";
			}
			echo "</ul>";
		}
	}

 ?>











