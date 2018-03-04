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
        $password = $_POST["password"];
        $type = $_POST["type"];

        require_once("php/validation.php");
        $obj = array("username"=>$username, "password"=>$password);
        $validator = new ValidateLogin($obj);

        if($validator->isValid())
        {   
            $res;
            $passHesh = sha1($password);
            if($type=="student")
            {
                require_once("php/DB-user-controller.php");
                $dbUserController = new DBUserController();
                $res = $dbUserController->canLogin($username, $passHesh);
            }
            else {
                require_once("php/DB-lecture-controller.php");
                $dbLectureController = new DBLectureController();
                $res = $dbLectureController->canLogin($username, $passHesh);
            }
            
            if($res == 1) {
                session_start();
                $_SESSION["type"] = $type;
                $_SESSION['logged_in'] = 1; 
                $_SESSION['username'] = $username; 
                header('Location: profile.php?type='.$type.'&username='.$username);
            }
            else {
                echo '<div class="alert alert-danger">
  <strong></strong>Bad username or password</div>';
            }
        }
        else {
            echo '<div class="alert alert-danger">';
            $validator->printErrors();
            echo '</div>';
        }

    }
    ?>
        <form action="login.php" method="POST">
            <label>
                Username
                <input name="username" id="tb-username" class="form-control" type="text">
            </label>
            <br />
            <label>
                Password
                <input name="password" id="tb-password" class="form-control" type="password">
            </label>
            <br />
            <label>
                Влез като
                <select name="type" class="form-control col-sm-9">
                    <option value="student">студент</option>
                    <option value="lecture">лектор</option>
                </select>
            </label>
            <br />
            <input type="submit" id="btn-login" class="btn btn-success" value="Влез" />
        </form>
    </section>

</body>

</html>