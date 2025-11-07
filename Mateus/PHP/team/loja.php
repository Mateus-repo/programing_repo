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
    <title>Loja</title>
    <link href="css/bootstrap.min.css" rel="stylesheet">
    <style>
        body {
            background-image: url('assets/background1.jpg');
            background-size: cover;
            background-position: center;
            background-attachment: fixed;
            min-height: 100vh;
            padding: 20px;
        }

        .loja-container {
            max-width: 1400px;
            margin: 0 auto;
        }

        .titulo-principal {
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
            font-size: 3em;
        }

        .secao-titulo {
            padding-left: 0.8em;
            color: #ffb7d5;
            background-color: transparent;
            letter-spacing: .5em;
            text-align: center;
            padding-top: 0.5em;
            padding-bottom: 1em;
            text-shadow: inset -1px -1px 1px #DAA06D;
            margin: 40px 0 30px 0;
            font-family: blippo, fantasy;
            font-size: 2em;
        }

        .items-grid {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(280px, 1fr));
            gap: 25px;
            margin-bottom: 40px;
        }

        .item-card {
            background: rgba(255, 255, 255, 0.95);
            border: 3px dashed #ff769e;
            border-radius: 15px;
            padding: 15px;
            text-align: center;
            transition: all 0.3s ease;
            box-shadow: 0 4px 15px rgba(0,0,0,0.2);
            background-image: url("assets/formw1.png");
        }

        .item-card:hover {
            transform: translateY(-5px);
            box-shadow: 0 8px 25px rgba(0,0,0,0.3);
            border-color: #ff769e;
        }

        .item-nome {
            font-size: 20px;
            font-weight: bold;
            color: #ffa1c9;
            margin-bottom: 15px;
        }

        .item-imagem {
            width: 100%;
            height: 130px;
            background: linear-gradient(135deg, #ffffff 0%, #ffffff 100%);
            border-radius: 10px;
            margin-bottom: 15px;
            display: flex;
            align-items: center;
            justify-content: center;
            color: #fff;
            font-size: 48px;
            font-weight: bold;
        }

        .item-info-container {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin: 15px 0;
            gap: 10px;
        }

        .item-info {
            color: #ffffff;
            font-size: 20px;
            font-weight: bold;
            display: flex;
            align-items: center;
            gap: 5px;
        }

        .item-preco {
            display: flex;
            align-items: center;
            gap: 8px;
            font-size: 20px;
            font-weight: bold;
            color: #ffffff;
        }

        .moeda-icon {
            width: 25px;
            height: 25px;
            background-image: url('assets/blissbite.png');
            background-size: cover;
            background-position: center;
            border-radius: 50%;
            display: inline-block;
        }

        .btn-comprar {
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

        .btn-comprar:hover {
            opacity: 0.8;
        }

        .btn-comprar:active {
            transform: translateX(0.1em) translateY(0.1em);
            box-shadow: none;
        }

        .btn-voltar {
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
            cursor: pointer;
            font-size: 16px;
            margin: 20px auto;
            display: block;
        }

        .btn-voltar:hover {
            opacity: 0.8;
        }

        .btn-voltar:active {
            transform: translateX(0.1em) translateY(0.1em);
            box-shadow: none;
        }

    </style>
</head>
<body>
<div class="loja-container">
    <h1 class="titulo-principal">LOJA</h1>
    <?php

    //pilotos:

    $pilotos = "SELECT nomePiloto, qualidadePiloto, precoPiloto FROM pilotos";

    $result = mysqli_query($ligaBD, $pilotos);

    if ($result && mysqli_num_rows($result) > 0) {
        echo '<h2 class="secao-titulo">PILOTOS</h2>';
        echo '<div class="items-grid">';
        while($row = mysqli_fetch_assoc($result)) {
            echo '<div class="item-card">';
            echo '<h3 class="item-nome">' . htmlspecialchars($row['nomePiloto']) . '</h3>';
            echo '<div class="item-imagem"></div>';
            echo '<div class="item-info-container">';
            echo '<div class="item-info">⭐ Qualidade: ' . htmlspecialchars($row['qualidadePiloto']) . '</div>';
            echo '<div class="item-preco"><span class="moeda-icon"></span>' . htmlspecialchars($row['precoPiloto']) . '</div>';
            echo '</div>';
            echo '<button class="btn-comprar">Contratar</button>';
            echo '</div>';
        }
        echo '</div>';
    }

    //Pneus:

    $pneus = "SELECT nomePneu, tipoPneu, pesoPneu, precoPneu FROM pneus";

    $result = mysqli_query($ligaBD, $pneus);

    if ($result && mysqli_num_rows($result) > 0) {
        echo '<h2 class="secao-titulo">PNEUS</h2>';
        echo '<div class="items-grid">';
        while($row = mysqli_fetch_assoc($result)) {
            echo '<div class="item-card">';
            echo '<h3 class="item-nome">' . htmlspecialchars($row['nomePneu']) . '</h3>';
            echo '<div class="item-imagem"></div>';
            echo '<div class="item-info-container">';
            echo '<div class="item-info">Tipo: ' . htmlspecialchars($row['tipoPneu']) . ' | Peso: ' . htmlspecialchars($row['pesoPneu']) . ' Kg</div>';
            echo '<div class="item-preco"><span class="moeda-icon"></span>' . htmlspecialchars($row['precoPneu']) . '</div>';
            echo '</div>';
            echo '<button class="btn-comprar">Comprar</button>';
            echo '</div>';
        }
        echo '</div>';
    }

    //Spoilers:

    $spoiler = "SELECT spoilerNome, spoilerPeso, spoilerPreco FROM spoilers";

    $result = mysqli_query($ligaBD, $spoiler);

    if ($result && mysqli_num_rows($result) > 0) {
        echo '<h2 class="secao-titulo">SPOILERS</h2>';
        echo '<div class="items-grid">';
        while($row = mysqli_fetch_assoc($result)) {
            echo '<div class="item-card">';
            echo '<h3 class="item-nome">' . htmlspecialchars($row['spoilerNome']) . '</h3>';
            echo '<div class="item-imagem"></div>';
            echo '<div class="item-info-container">';
            echo '<div class="item-info">Peso: ' . htmlspecialchars($row['spoilerPeso']) . ' Kg</div>';
            echo '<div class="item-preco"><span class="moeda-icon"></span>' . htmlspecialchars($row['spoilerPreco']) . '</div>';
            echo '</div>';
            echo '<button class="btn-comprar">Comprar</button>';
            echo '</div>';
        }
        echo '</div>';
    }

    //Skins:

    $skins = "SELECT skinNome, skinDescricao, skinPreco FROM skins";

    $result = mysqli_query($ligaBD, $skins);

    if ($result && mysqli_num_rows($result) > 0) {
        echo '<h2 class="secao-titulo">SKINS</h2>';
        echo '<div class="items-grid">';
        while($row = mysqli_fetch_assoc($result)) {
            echo '<div class="item-card">';
            echo '<h3 class="item-nome">' . htmlspecialchars($row['skinNome']) . '</h3>';
            echo '<div class="item-imagem"></div>';
            echo '<div class="item-info-container">';
            echo '<div class="item-info">' . htmlspecialchars($row['skinDescricao']) . '</div>';
            echo '<div class="item-preco"><span class="moeda-icon"></span>' . htmlspecialchars($row['skinPreco']) . '</div>';
            echo '</div>';
            echo '<button class="btn-comprar">Comprar</button>';
            echo '</div>';
        }
        echo '</div>';
    }
    ?>
</div>
<button class="btn-voltar" onclick="window.location.href='startpage.php'">Voltar</button>
</body>
<script src="js/bootstrap.bundle.min.js"></script>
</html>