<?php
session_start();
require_once 'includes/db.php';
require_once 'includes/auth.php';

// Sim, este arquivo foi inteiramente feito para redirecionar para o home.php
// Revolucionário, não é?

header('Location: home.php');
exit();
?>