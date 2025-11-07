<?php
session_start();
include('includes/db_connect.php');
$ligaBD = conectarBD();
include 'includes/button_dropdown.php';

if (!isset($_SESSION["registoId"])) {
    header("Location: login.php");
    exit();
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Glitch</title>
    <link href="css/bootstrap.min.css" rel="stylesheet">
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: Arial, sans-serif;
            min-height: 100vh;
            background-image: url('assets/background index.png');
            background-size: cover;
            background-position: center;
            background-repeat: no-repeat;
            background-attachment: fixed;
        }

        .main-container {
            min-height: 100vh;
            display: flex;
            align-items: center;
            padding: 2em;
        }

        .content-wrapper {
            display: flex;
            flex-direction: column;
            align-items: flex-start;
            max-width: 400px;
            width: 100%;
        }

        .logo {
            display: block;
            margin: 0 0 2em 0;
            max-width: 700px;
            height: auto;
            animation: swing 3s ease-in-out infinite;
        }

        @keyframes swing {
            0%, 100% {
                transform: rotate(0deg);
            }
            25% {
                transform: rotate(2deg);
            }
            75% {
                transform: rotate(-2deg);
            }
        }

        .btn {
            align-self: flex-start;
            border-radius: 15px;
            outline: none;
            border: none;
            color: #ffffff;
            background-color: #fd92be;
            font-weight: bold;
            letter-spacing: 0.1em;
            transition: .4s ease-in-out background-color, .1s ease-in-out transform;
            padding: 1.2em 3em;
            box-shadow: 0px 4px 6px rgb(255, 118, 158);
            width: 10000%;
            max-width: 700px;
            font-size: 1.1em;
            cursor: pointer;
            margin-top: 10px;
        }

        .btn:hover {
            background-color: rgba(253, 146, 190, 0.93);
        }

        .btn:active {
            transform: translateY(2px);
            box-shadow: 0px 2px 4px rgb(255, 255, 255);
        }

        @media (max-width: 768px) {
            .content-wrapper {
                align-items: center;
                margin: 0 auto;
            }

            .logo {
                max-width: 150px;
            }

            .btn {
                align-self: center;
            }
        }
    </style>
</head>
<body>

<div class="main-container">
    <div class="content-wrapper">
        <img src="assets/logo.png" alt="Logo" class="logo">
        <button class="btn" onclick="window.location.href='startpage.php'">PLAY</button>
    </div>
</div>

<script src="js/bootstrap.bundle.min.js"></script>
</body>
</html>