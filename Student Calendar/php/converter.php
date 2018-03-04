<?php 
class Converter 
{
	
	public static function abvToSpec($speciality)
	{
		$speciality;
		switch ($speciality) {
			case 'SI':
				$speciality = "Софтуерно Инженерство";
				break;
			case 'KN':
				$speciality = "Компютърни Науки";
				break;
			case 'IS':
				$speciality = "Информационни Системи";
				break;
			case 'I':
				$speciality = "Информатика";
				break;
			case 'PM':
				$speciality = "Приложна Математика";
				break;
		}
		return $speciality;
	}
	public static function numberToDay($number)
	{
		$day;
		switch ($number) {
			case 1:
				$day = "Понеделник";
				break;
			case 2:
				$day = "Вторник";
				break;
			case 3:
				$day = "Сряда";
				break;
			case 4:
				$day = "Четвъртак";
				break;
			case 5:
				$day = "Петък";
				break;
			case 6:
				$day = "Събота";
				break;
			case 7:
				$day = "Неделя";
				break;
		}
		return $day;
	}
}
	 ?>