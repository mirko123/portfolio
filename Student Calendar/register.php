<!DOCTYPE html>
<html lang="en">
<?php require_once("php/templates.php");
    mainTemplate::head();
 ?>

<body id="page">
    <?php mainTemplate::header(); ?>

    
    <section id="container" class="container text-center">
    <?php if($_SERVER['REQUEST_METHOD'] === 'POST') {
        $username = $_POST["username"];
        $email = $_POST["email"];
        $type = $_POST["type"];
        $password = $_POST["password"];
        $secondpassword = $_POST["secondpass"];

        require_once("php/validation.php");

        $obj = array("username"=>$username, "email"=>$email, "type"=>$type, "password"=>$password);
        $validator = new ValidateRegister($obj);

        $firstPassEqSecondPass =  $password == $secondpassword;
        if(!$firstPassEqSecondPass) 
            echo '<div class="alert alert-danger">First pass != second</div>';
        if($validator->isValid() && $firstPassEqSecondPass)
        {   
            $res;
            $passHesh = sha1($password);
            if($type=="student") {
                require_once("php/DB-user-controller.php");
                $dbUserController = new DBUserController();
                $res = $dbUserController->create($username, $email, $passHesh);
            }
            else {
                require_once("php/DB-lecture-controller.php");
                $dbLectureController = new DBLectureController();
                $res = $dbLectureController->create($username, $email, $passHesh);
            }

            if($res == 1) {
                session_start();
                $_SESSION['logged_in'] = 1; 
                $_SESSION['username'] = $username; 
                $_SESSION['type'] = $type; 
                header('Location: profile.php?type='.$type.'&username='.$username);
            }
            else {
                echo '<div class="alert alert-danger">
<strong></strong>Username exist</div>';
            }


        }
        else {
            echo '<div class="alert alert-danger">';
            $validator->printErrors();
            echo '</div>';
        }

    }
    ?>

    <form action="register.php" method="POST">
        <label>
            Потребителко име
            <input name="username" id="tb-username" class="form-control" type="text" placeholder="Enter Username" type="text">
        </label>
        <br />
        <label>
            Е-поща
            <input name="email" id="tb-email" class="form-control" type="text" placeholder="Enter email" type="text">
        </label>
        <br />
        <label>
            Тип на профила
            <select name="type" class="form-control col-sm-9">
                <option value="student">студент</option>
                <option value="lecture">лектор</option>
            </select>
        </label>
        <br />
        <label>
            Парола
            <input name="password" id="tb-password" class="form-control" type="password" placeholder="Enter password">
        </label>
        <br />
        <label>
            Отново парола
            <input name="secondpass" id="tb-password2" class="form-control" type="password" placeholder="Again password">
        </label>
        <br />
        <input type="submit" id="btn-register" class="btn btn-success" value="Регистър">
    </form>
    </section>

</body>

</html>