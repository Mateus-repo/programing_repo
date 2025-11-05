<?php
$prefix = '';
if (strpos($_SERVER['PHP_SELF'], '/site/admin/') !== false) {
    $prefix = '../';
}
?>

<nav class="navbar">
  <div class="navbar-container">
    <!-- LOGO--------------------------------------------------------------------------------------------------- -->
    <a href="<?php echo $prefix; ?>home.php" class="logo-link">
      <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 500 300" class="logo-pcnovo">
        <path d="M50 50 L150 30 L150 220 L50 240 Z" fill="black" />
        <path d="M50 50 L150 30 L150 220 L50 240 Z" fill="none" stroke="#ff8833" stroke-width="2" />
        
        <circle cx="75" cy="190" r="8" fill="#ff8833" />
        
        <rect x="70" y="80" width="60" height="15" fill="#ff8833" />
        
        <path d="M180 50 L380 50 L380 200 L180 200 Z" fill="black" stroke="#ff8833" stroke-width="2" />
        <path d="M180 50 L380 50 L380 200 L180 200 L180 50" fill="none" stroke="#ff8833" stroke-width="2" />
        
        <rect x="190" y="60" width="180" height="130" fill="black" stroke="#ff8833" stroke-width="1" />
        
        <path d="M250 200 L310 200 L330 240 L230 240 Z" fill="black" stroke="#ff8833" stroke-width="2" />
        
        <rect x="180" y="250" width="200" height="30" rx="5" fill="black" stroke="#ff8833" stroke-width="2" />
        
        <line x1="210" y1="260" x2="350" y2="260" stroke="#ff8833" stroke-width="1" />
        <line x1="210" y1="270" x2="350" y2="270" stroke="#ff8833" stroke-width="1" />
      </svg>
    </a>
    <!-- ------------------------------------------------------------------------------------------------------- -->
    
    <ul>
      <li><a href="<?php echo $prefix; ?>home.php">Home</a></li>
      <li><a href="<?php echo $prefix; ?>produtos.php">Produtos</a></li>
    </ul>
    
    <?php if (isLoggedIn()): ?>
      <div class="perfil-menu">
        <?php
          $tipoImagem  = isAdmin() ? 'admin' : 'cliente';
          $userId      = $_SESSION['user_id'];
          $perfilRoute = $prefix . "exibir_imagem.php?id=$userId&tipo=perfil";
          $onErrorSrc  = $prefix . "images/{$tipoImagem}-svg.svg";
        ?>
        <img
          src="<?php echo $perfilRoute; ?>"
          onerror="this.onerror=null; this.src='<?php echo $onErrorSrc; ?>'"
          alt="Perfil"
          class="perfil-imagem"
        >
        <div class="perfil-dropdown">
          <a href="<?php echo $prefix; ?>perfil.php">Meu Perfil</a>
          <?php if (isAdmin()): ?>
            <a href="<?php echo $prefix; ?>admin/gerir_utilizadores.php">Gerir Utilizadores</a>
            <a href="<?php echo $prefix; ?>admin/gerir_produtos.php">Gerir Produtos</a>
          <?php endif; ?>
          <a href="<?php echo $prefix; ?>logout.php">Sair</a>
        </div>
      </div>
    <?php else: ?>
      <ul>
        <li><a href="<?php echo $prefix; ?>login.php">Entrar</a></li>
      </ul>
    <?php endif; ?>
  </div>
</nav>
