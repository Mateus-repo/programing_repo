<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Glitch</title>
    <link href="../css/bootstrap.min.css" rel="stylesheet">

    <style>
        .dropdown {
            position: fixed !important;
            top: 20px !important;
            right: 20px !important;
            left: auto !important;
            z-index: 1000 !important;
            margin: 0 !important;
        }

        #dropdownMenuButton {
            background: linear-gradient(135deg, #3c0001 0%, #7d2a19 100%) !important;
            color: #fff !important;
            border: 2px solid #3c0001 !important;
            border-radius: 25px !important;
            padding: 12px 30px !important;
            font-size: 16px !important;
            font-weight: 600 !important;
            cursor: pointer !important;
            transition: all 0.3s ease !important;
            box-shadow: 0 4px 15px rgba(255, 255, 255, 0.94) !important;
            letter-spacing: 0.5px !important;
            display: block !important;
        }

        #dropdownMenuButton:hover {
            background: linear-gradient(135deg, #3c0001 0%, #3c0001 100%) !important;
            transform: translateY(-2px) !important;
            box-shadow: 0 6px 20px rgb(255, 255, 255) !important;
            border-color: #3c0001 !important;
        }

        #dropdownMenuButton:active {
            transform: translateY(0) !important;
            box-shadow: 0 2px 10px rgba(217, 132, 158, 0.3) !important;
        }

        .dropdown-menu {
            background: linear-gradient(180deg, #3c0001 0%, #7d2a19 100%) !important;
            border: 2px solid #3c0001 !important;
            border-radius: 15px !important;
            box-shadow: 0 8px 25px rgba(255, 255, 255, 0.51) !important;
            margin-top: 10px !important;
            padding: 8px 0 !important;
            min-width: 200px !important;
            right: 0 !important;
            left: auto !important;
        }

        .dropdown-item {
            color: #fb9caf !important;
            padding: 12px 20px !important;
            font-weight: 500 !important;
            transition: all 0.3s ease !important;
            border-radius: 8px !important;
            margin: 4px 8px !important;
        }

        .dropdown-item:hover {
            background: linear-gradient(135deg, #3c0001 0%, #4e0304 100%) !important;
            color: #ffcfd7 !important;
            transform: translateX(5px) !important;
        }

        .dropdown-item:active {
            background: #ffffff !important;
            color: #fff !important;
        }

        .dropdown-divider {
            border-top: 2px solid #d4849e !important;
            opacity: 0.3 !important;
            margin: 8px 12px !important;
        }

        body > a[href="login.php"] {
            position: fixed !important;
            top: 20px !important;
            right: 20px !important;
            left: auto !important;
            background: linear-gradient(135deg, #d4849e 0%, #c96d8b 100%) !important;
            color: #fff !important;
            text-decoration: none !important;
            border: 2px solid #b85a7a !important;
            border-radius: 25px !important;
            padding: 12px 30px !important;
            font-size: 16px !important;
            font-weight: 600 !important;
            transition: all 0.3s ease !important;
            box-shadow: 0 4px 15px rgba(217, 132, 158, 0.3) !important;
            display: inline-block !important;
            z-index: 1000 !important;
        }

        body > a[href="login.php"]:hover {
            background: linear-gradient(135deg, #e09bb0 0%, #d4849e 100%) !important;
            transform: translateY(-2px) !important;
            box-shadow: 0 6px 20px rgba(217, 132, 158, 0.4) !important;
            border-color: #c96d8b !important;
        }

        @keyframes slideIn {
            from {
                opacity: 0;
                transform: translateY(-10px);
            }
            to {
                opacity: 1;
                transform: translateY(0);
            }
        }

        .dropdown-menu.show {
            animation: slideIn 0.3s ease !important;
        }

        @media (max-width: 768px) {
            .dropdown {
                top: 15px !important;
                right: 15px !important;
            }

            #dropdownMenuButton,
            body > a[href="login.php"] {
                padding: 10px 20px !important;
                font-size: 14px !important;
            }

            .dropdown-menu {
                min-width: 180px !important;
            }
        }
    </style>

</head>
<body>
    <?php if (isset($_SESSION['registoId'])): ?>
        <div class="dropdown">
            <button type="button" id="dropdownMenuButton" data-bs-toggle="dropdown" aria-expanded="false">
                <?php echo htmlspecialchars($_SESSION['nomeUtilizador']); ?>
            </button>
            <ul class="dropdown-menu" aria-labelledby="dropdownMenuButton">
                <li><a class="dropdown-item" href="settings.php">Definições</a></li>
                <li><hr class="dropdown-divider"></li>
                <li><a class="dropdown-item" href="logout.php">Logout</a></li>
            </ul>
        </div>
    <?php else: ?>
        <a href="login.php">Login</a>
    <?php endif; ?>
<script src="../js/bootstrap.bundle.min.js"></script>
</body>
</html>