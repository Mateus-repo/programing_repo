<?php
session_start();
include('includes/db_connect.php');
$ligaBD = conectarBD();
include 'includes/button_dropdown.php';
?>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Start</title>
    <link href="css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<button onclick="window.location.href='editpage.php'">Editar</button>
<button onclick="window.location.href='loja.php'">Loja</button>
<button onclick="window.location.href='historico.php'">Histórico</button>
</body>
<script src="js/bootstrap.bundle.min.js"></script>
</html>
