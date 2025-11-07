<?php
session_start();
if (!isset($_SESSION["registoId"])) {
    header("Location: login.php");
    exit();
}

include("includes/db_connect.php");
$ligaBD = conectarBD();
include 'includes/button_dropdown.php';

$query = "SELECT * FROM registos WHERE registoId = ?";
$stmt = mysqli_prepare($ligaBD, $query);
mysqli_stmt_bind_param($stmt, "i", $_SESSION["registoId"]);
mysqli_stmt_execute($stmt);
$result = mysqli_stmt_get_result($stmt);
$user_data = mysqli_fetch_assoc($result);

$mensagem = "";
$tipo_mensagem = "danger";

if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST["atualizar"])) {

    $username = trim($_POST["registoNome"]);
    $email = trim($_POST["email"]);
    $teamname = trim($_POST["registoEquipa"]);
    $password_atual = $_POST["password_atual"];
    $nova_password = $_POST["nova_password"];
    $confirmar_password = $_POST["confirmar_password"];
    $userId = $_SESSION["registoId"];


    if (password_verify($password_atual, $user_data["palavraPasse"])) {

        $erros_validacao = [];

        if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
            $erros_validacao[] = "O formato do e-mail é inválido.";
        }
        if (!empty($nova_password)) {
            if (strlen($nova_password) < 8) {
                $erros_validacao[] = "A nova palavra-passe deve ter no mínimo 8 caracteres.";
            }
            if (!preg_match('/[A-Z]/', $nova_password)) {
                $erros_validacao[] = "A nova palavra-passe deve conter pelo menos uma letra maiúscula.";
            }
            if ($nova_password !== $confirmar_password) {
                $erros_validacao[] = "A nova palavra-passe e a sua confirmação não coincidem.";
            }
        }
        if (empty($erros_validacao)) {
            $checkUserQuery = "SELECT registoId FROM registos WHERE nomeUtilizador = ? AND registoId != ?";
            $checkUserStmt = mysqli_prepare($ligaBD, $checkUserQuery);
            mysqli_stmt_bind_param($checkUserStmt, "si", $username, $userId);
            mysqli_stmt_execute($checkUserStmt);
            $userResult = mysqli_stmt_get_result($checkUserStmt);

            $checkEmailQuery = "SELECT registoId FROM registos WHERE email = ? AND registoId != ?";
            $checkEmailStmt = mysqli_prepare($ligaBD, $checkEmailQuery);
            mysqli_stmt_bind_param($checkEmailStmt, "si", $email, $userId);
            mysqli_stmt_execute($checkEmailStmt);
            $emailResult = mysqli_stmt_get_result($checkEmailStmt);

            if (mysqli_num_rows($userResult) > 0) {
                $mensagem = "O nome de utilizador escolhido já se encontra registado.";
            } elseif (mysqli_num_rows($emailResult) > 0) {
                $mensagem = "O endereço de e-mail escolhido já se encontra registado.";
            } else {
                if (!empty($nova_password)) {
                    $nova_password_hash = password_hash($nova_password, PASSWORD_DEFAULT);
                    $update_query = "UPDATE registos SET nomeUtilizador = ?, email = ?, nomeEquipa = ?, palavraPasse = ? WHERE registoId = ?";
                    $update_stmt = mysqli_prepare($ligaBD, $update_query);
                    mysqli_stmt_bind_param($update_stmt, "ssssi", $username, $email, $teamname, $nova_password_hash, $userId);
                } else {
                    $update_query = "UPDATE registos SET nomeUtilizador = ?, email = ?, nomeEquipa = ? WHERE registoId = ?";
                    $update_stmt = mysqli_prepare($ligaBD, $update_query);
                    mysqli_stmt_bind_param($update_stmt, "sssi", $username, $email, $teamname, $userId);
                }

                if (mysqli_stmt_execute($update_stmt)) {
                    $_SESSION["registoNome"] = $username;
                    $stmt_reload = mysqli_prepare($ligaBD, "SELECT * FROM registos WHERE registoId = ?");
                    mysqli_stmt_bind_param($stmt_reload, "i", $userId);
                    mysqli_stmt_execute($stmt_reload);
                    $result_reload = mysqli_stmt_get_result($stmt_reload);
                    $user_data = mysqli_fetch_assoc($result_reload);

                    $mensagem = "Alterações guardadas com sucesso!";
                    $tipo_mensagem = "success";
                } else {
                    $mensagem = "Erro ao guardar alterações.";
                }
            }
        } else {
            $mensagem = implode("<br>", $erros_validacao);
        }
    } else {
        $mensagem = "A palavra-passe atual está incorreta.";
        session_destroy();
        header('Location: login.php?');
        exit();
    }
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Definições</title>
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <style>
        body {
            margin: 0;
            padding: 0;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background-image: url('assets/background1.jpg');
            background-size: cover;
            background-position: center;
            background-attachment: fixed;
            min-height: 100vh;
            display: flex;
            justify-content: center;
            align-items: center;
            position: relative;
        }

        body > div {
            width: 100%;
            max-width: 500px;
            margin: 20px;
        }

        .form {
            display: flex;
            flex-direction: column;
            gap: 10px;
            padding-top: 3em;
            padding-left: 3.5em;
            padding-right: 3.5em;
            padding-bottom: 2.1em;
            border: 2px dashed #ffb7d5;
            border-radius: 15px;
            background-color: #7d2a19;
            background-image: url("assets/formw1.png");
            background-size: cover;
            background-position: center;
            background-repeat: no-repeat;
            background-attachment: fixed;
            box-shadow: 0 0 0 4px #7d2a19, 2px 2px 4px 2px rgba(0, 0, 0, 0.5);
            transition: .4s ease-in-out;
            position: relative;
            min-width: 600px;
            min-height: 800px;
        }

        ::placeholder {
            color: #975a4e;
            text-align: center;
        }

        .form .heading {
            padding-left: 0.8em;
            color: #ffb7d5;
            background-color: transparent;
            letter-spacing: .5em;
            text-align: center;
            padding-top: 0.5em;
            padding-bottom: 2em;
            text-shadow: inset -1px -1px 1px #DAA06D;
            margin: 0;
            font-family: blippo, fantasy;
        }

        .form .input {
            outline: none;
            padding: 0.5em;
            border: 1px solid #3c0001;
            color: #ffb7d5;
            width: 100%;
            height: 3em;
            border-radius: 10px;
            background-color: #2c0602;
            text-align: center;
            box-sizing: border-box;
        }

        .form .btn {
            align-self: center;
            margin-top: 1em;
            border-radius: 10px;
            outline: none;
            border: none;
            color: #ffffff;
            background-color: #fd92be;
            font-weight: bold;
            letter-spacing: 0.1em;
            transition: .4s ease-in-out opacity, .1s ease-in-out active;
            padding: 1em;
            box-shadow: 0.5px 0.5px 0.5px 0.5px rgb(172, 45, 79);
            width: 100%;
            cursor: pointer;
        }

        .form .btn:hover {
            opacity: 0.8;
        }

        .form .btn:active {
            transform: translateX(0.1em) translateY(0.1em);
            box-shadow: none;
        }

        .form label {
            display: block;
            margin-bottom: 3px;
            color: #ededed;
            font-weight: 500;
            text-align: center;
            font-size: 13px;
        }

        .form > div {
            margin-bottom: 5px;
        }

        .form > div:last-child {
            display: flex;
            flex-direction: column;
            gap: 10px;
            margin-top: 1em;
            margin-bottom: 0;
        }

        .form > div:last-child > a {
            align-self: center;
            border-radius: 10px;
            outline: none;
            border: none;
            color: #ffffff;
            background-color: #fd92be;
            font-weight: bold;
            letter-spacing: 0.1em;
            transition: .4s ease-in-out opacity, .1s ease-in-out active;
            padding: 1em;
            box-shadow: 0.5px 0.5px 0.5px 0.5px rgb(172, 45, 79);
            width: 100%;
            text-decoration: none;
            text-align: center;
            cursor: pointer;
        }

        .form > div:last-child > a:hover {
            opacity: 0.8;
        }

        .form > div:last-child > a:active {
            transform: translateX(0.1em) translateY(0.1em);
            box-shadow: none;
        }

        .alert {
            padding: 0.6em 1em;
            margin-top: 1em;
            margin-bottom: 0.5em;
            border-radius: 10px;
            text-align: center;
            width: 100%;
            font-size: 0.9em;
            animation: fadeOut 10s forwards;
            box-sizing: border-box;
        }

        .alert-success {
            background-color: rgba(193, 244, 148, 0.9);
            border: 1px solid #619356;
            color: white;
        }

        .alert-danger {
            background-color: rgb(209, 0, 21);
            border: 1px solid #c63241;
            color: white;
        }

        .btn-close {
            background: transparent;
            border: none;
            color: inherit;
            opacity: 0.7;
            cursor: pointer;
            font-size: 20px;
            position: absolute;
            right: 10px;
            top: 50%;
            transform: translateY(-50%);
        }

        .btn-close:hover {
            opacity: 1;
        }

        #mensagemErroJS {
            padding: 12px 20px;
            border-radius: 10px;
            background-color: rgb(209, 0, 21);
            border: 1px solid #6e0510;
            color: white;
            text-align: center;
        }
    </style>

</head>
<body>
<div>
    <div>
        <?php if (!empty($mensagem)): ?>
            <div class="alert alert-<?php echo $tipo_mensagem; ?> alert-dismissible fade show" role="alert">
                <?php echo $mensagem; ?>
                <button type="button" class="btn-close" data-bs-dismiss="alert" aria-label="Fechar">×</button>
            </div>
        <?php endif; ?>
        <form method="POST" action="" id="settingsForm" class="form">
            <h2 class="heading">Definições</h2>
            <div>
                <label for="registoNome" class="form-label">Nome de Utilizador</label>
                <input type="text" class="input" id="registoNome" name="registoNome" value="<?php echo htmlspecialchars($user_data['registoNome']); ?>">
            </div>
            <div>
                <label for="email">E-mail</label>
                <input type="email" class="input" id="email" name="email" value="<?php echo htmlspecialchars($user_data['email']); ?>">
            </div>
            <div>
                <label for="registoEquipa">Nome da Equipa</label>
                <input type="text" class="input" id="registoEquipa" name="registoEquipa" value="<?php echo htmlspecialchars($user_data['registoEquipa']); ?>">
            </div>
            <div class="mb-3">
                <label for="password_atual">Palavra-passe Atual (Obrigatória para guardar)</label>
                <input type="password" class="input" id="password_atual" name="password_atual" required>
            </div>
            <div>
                <label for="nova_password">Nova Palavra-passe</label>
                <input type="password" class="input" id="nova_password" name="nova_password">
            </div>
            <div>
                <label for="confirmar_password">Confirmar Nova Palavra-passe</label>
                <input type="password" class="input" id="confirmar_password" name="confirmar_password">
            </div>
            <div id="mensagemErroJS" style="display: none; margin-top: 10px;"></div>
            <div>
                <button type="submit" class="btn" name="atualizar">Guardar</button>
                <a href="login.php">Cancelar</a>
            </div>
        </form>
    </div>
</div>
<script src="js/bootstrap.bundle.min.js"></script>

<script>
    const form = document.getElementById('settingsForm');

    form.addEventListener('submit', function(event) {

        const emailValue = document.getElementById('email').value;
        const newPasswordValue = document.getElementById('nova_password').value;
        const confirmPasswordValue = document.getElementById('confirmar_password').value;
        const mensagemErroDiv = document.getElementById('mensagemErroJS');

        function validarEmail(email) {
            const re = /^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
            return re.test(String(email).toLowerCase());
        }

        function validarRequisitosPassword(password) {
            const re = /^(?=.*[A-Z]).{8,}$/;
            return re.test(password);
        }

        if (!validarEmail(emailValue)) {
            mensagemErroDiv.textContent = 'Por favor, insira um endereço de e-mail com formato válido.';
            mensagemErroDiv.style.display = 'block';
            event.preventDefault();
            return;
        }

        if (newPasswordValue !== "") {
            if (!validarRequisitosPassword(newPasswordValue)) {
                mensagemErroDiv.textContent = 'A nova palavra-passe deve ter no mínimo 8 caracteres e conter pelo menos uma letra maiúscula.';
                mensagemErroDiv.style.display = 'block';
                event.preventDefault();
                return;
            }
            if (newPasswordValue !== confirmPasswordValue) {
                mensagemErroDiv.textContent = 'As novas palavras-passe não coincidem. Tente novamente!';
                mensagemErroDiv.style.display = 'block';
                event.preventDefault();
                return;
            }
        }

        mensagemErroDiv.style.display = 'none';
    });
</script>
</body>
</html>