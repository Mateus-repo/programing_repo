<?php
session_start();

if (isset($_SESSION["registoId"])){
    header("Location: index.php");
    exit();
}

include('includes/db_connect.php');
$ligaBD = conectarBD();
$errorMessage = "";

if (isset($_POST['enviar'])) {
    $user = trim($_POST["registoNome"]);
    $email = trim($_POST["email"]);
    $password = trim($_POST["palavraPasse"]);
    $equipa = trim($_POST["registoEquipa"]);

    if (empty($user) || empty($email) || empty($password) || empty($equipa)) {
        $errorMessage = "Todos os campos são de preenchimento obrigatório.";
    } elseif (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
        $errorMessage = "Por favor, introduza um endereço de e-mail válido.";
    } else {
        $checkUser = "SELECT * FROM registos WHERE nomeUtilizador = ? OR email = ?";
        $stmt = mysqli_prepare($ligaBD, $checkUser);
        mysqli_stmt_bind_param($stmt, "ss", $user, $email);
        mysqli_stmt_execute($stmt);
        $result = mysqli_stmt_get_result($stmt);

        if (mysqli_num_rows($result) > 0) {
            $errorMessage = "O nome de utilizador ou o e-mail já se encontra registado.";
        } else {
            $passwordHash = password_hash($password, PASSWORD_DEFAULT);

            $query = "INSERT INTO registos (nomeUtilizador, email, palavraPasse, nomeEquipa) VALUES (?, ?, ?, ?)";
            $stmt2 = mysqli_prepare($ligaBD, $query);
            mysqli_stmt_bind_param($stmt2, "ssss", $user, $email, $passwordHash, $equipa);

            if (mysqli_stmt_execute($stmt2)) {
                header("Location: login.php");
                exit();
            } else {
                $errorMessage = "Ocorreu um erro ao efetuar o registo. Tente novamente. Erro: ";
            }
            mysqli_stmt_close($stmt2);
        }
        mysqli_stmt_close($stmt);
    }
}
?>
<!DOCTYPE html>
<html lang="pt-pt">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Registo</title>
    <link href="css/bootstrap.min.css" rel="stylesheet">
    <link rel="stylesheet" href="css/styles.css">
</head>

<body>
<div>
    <form class="form" action="" method="POST" id="registoForm">
        <img src="assets/logo.png" alt="Logo" class="logo">
        <h2 class="heading">REGISTO</h2>

        <input class="input" required placeholder="Nome de Utilizador" type="text" name="registoNome" />
        <input class="input" required placeholder="E-mail" type="email" name="email" id="email" />

        <input class="input" required placeholder="Palavra-passe" type="password" name="palavraPasse" id="palavraPasse" />
        <input class="input" required placeholder="Confirmar palavra-passe" type="password" name="confirmaPalavraPasse" id="confirmaPalavraPasse" />

        <input class="input" required placeholder="Nome da Equipa" type="text" name="registoEquipa" />

        <?php if (!empty($errorMessage)): ?>
            <div class="alert alert-danger mt-3" role="alert">
                <?php echo htmlspecialchars($errorMessage); ?>
            </div>
        <?php endif; ?>

        <div id="mensagemErroJS" class="alert alert-danger" style="display: none; margin-top: 10px;"></div>

        <button name="enviar" class="btn btn d-block text-center" type="submit">Registar</button>

        <div class="register-link">
            <p>Já tem uma conta? <a href="login.php">Fazer login</a></p>
        </div>
    </form>
</div>
<script>
    const form = document.getElementById('registoForm');
    const mensagemErroDiv = document.getElementById('mensagemErroJS');

    form.addEventListener('submit', function(event) {
        const email = document.getElementById('email').value;
        const password = document.getElementById('palavraPasse').value;
        const confirmPassword = document.getElementById('confirmaPalavraPasse').value;
        let formIsValid = true;
        let errorMessage = '';
        mensagemErroDiv.style.display = 'none';
        mensagemErroDiv.textContent = '';
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        if (!emailRegex.test(String(email).toLowerCase())) {
            formIsValid = false;
            errorMessage = 'Por favor, introduza um endereço de e-mail com formato válido.';
        }
        const passwordRegex = /^(?=.*[A-Z]).{8,}$/;
        if (formIsValid && !passwordRegex.test(password)) {
            formIsValid = false;
            errorMessage = 'A palavra-passe deve ter no mínimo 8 caracteres e conter pelo menos uma letra maiúscula.';
        }
        if (formIsValid && password !== confirmPassword) {
            formIsValid = false;
            errorMessage = 'As palavras-passes não coincidem. Tente novamente!';
        }
        if (!formIsValid) {
            mensagemErroDiv.textContent = errorMessage;
            mensagemErroDiv.style.display = 'block';
            event.preventDefault();
        }
    });
</script>

<script src="js/bootstrap.bundle.min.js"></script>

</body>
</html>