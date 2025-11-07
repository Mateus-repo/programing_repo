<?php
session_start();
require_once 'includes/db.php';
require_once 'includes/auth.php';
?>
<!DOCTYPE html>
<html lang="pt">
<head>
  <meta charset="UTF-8">
  <title>pcNovo - Home</title>
  <link rel="stylesheet" href="css/style.css">
  
</head>
<body>
  <?php include 'includes/navbar.php'; ?>

  <main>
    <section class="hero">
      <h1>Bem-vindo à <strong>pcNovo</strong>!</h1>
      <p>Descobre a tua nova loja de confiança em tecnologia! Computadores, gaming, acessórios e muito mais — tudo com qualidade garantida, preços competitivos e suporte especializado.</p>
    </section>

    <section class="destaques">
      <div class="destaque-item">
        <img src="images/home_pc1.png" alt="Computador Moderno 1">
        <div class="info">
          <h2>Performance sem limites</h2>
          <p>Equipamentos de alto desempenho para gamers, designers e profissionais exigentes.</p>
        </div>
      </div>

      <div class="destaque-item">
        <img src="images/home_pc2.png" alt="Computador Moderno 2">
        <div class="info">
          <h2>Estilo e potência</h2>
          <p>Design moderno com hardware de última geração. Leva o teu setup para outro nível.</p>
        </div>
      </div>
    </section>
  </main>
</body>
</html>
