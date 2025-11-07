<?php
session_start();
include('includes/db_connect.php');
$ligaBD = conectarBD();

$errorMessage = ''; // Variável para armazenar mensagens de erro

if (isset($_SESSION["registoId"])) {
    header("Location: index.php");
    exit();
}

if (isset($_POST['enviar'])) {
    $input = trim($_POST["registoNome"]);
    $ps = trim($_POST["palavraPasse"]);

    $existe = "SELECT * FROM registos WHERE nomeUtilizador = ? OR email = ? LIMIT 1";
    $stmt = mysqli_prepare($ligaBD, $existe);
    if ($stmt === false) {
        $errorMessage = "Erro na query: " . mysqli_error($ligaBD);
    } else {
        mysqli_stmt_bind_param($stmt, "ss", $input, $input);
        mysqli_stmt_execute($stmt);
        $result = mysqli_stmt_get_result($stmt);

        if (!$result || mysqli_num_rows($result) == 0) {
            $errorMessage = "Utilizador não registado.";
            mysqli_stmt_close($stmt);
        } else {
            $user = mysqli_fetch_assoc($result);
            mysqli_stmt_close($stmt);


            if (isset($user['palavraPasse']) && password_verify($ps, $user['palavraPasse'])) {
                session_regenerate_id(true);

                $_SESSION['registoId'] = (int)$user['registoId'];
                $_SESSION['registoNome'] = $user['registoNome'];
                $_SESSION['display_name'] = $user['registoEquipa'] ?? $user['registoNome'];
                $_SESSION['permitirAdmin'] = $user['permitirAdmin'] ?? 'user';

                header('Location: index.php');
                exit();
            } else {
                $errorMessage = "Erro de autenticação. Tente novamente";
            }
        }
    }
}
?>

<!DOCTYPE html>
<html lang="pt">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login</title>
    <link href="css/bootstrap.min.css" rel="stylesheet">
    <link rel="stylesheet" href="css/styles.css">

</head>

<body>
<form class="form" action="" method="POST">
    <img src="assets/logo.png" alt="Logo" class="logo">

    <h2 class="heading">LOGIN</h2>

    <input class="input" required placeholder="Nome de Utilizador ou E-mail" type="text" name="registoNome" />

    <input class="input" required placeholder="Palavra-Passe" type="password" name="palavraPasse" />

    <?php if (!empty($errorMessage)): ?>
        <div class="alert alert-danger" role="alert">
            <p><?php echo htmlspecialchars($errorMessage); ?></p>
        </div>
    <?php endif; ?>

    <button class="btn" name="enviar" type="submit">ENTRAR</button>

    <div class="register-link">
        <p>Não tem uma conta? <a href="registo.php">Registar-se</a></p>
    </div>
</form>
</body>
<script src="js/bootstrap.bundle.min.js"></script>
</html>