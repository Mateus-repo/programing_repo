<?php
session_start();
require_once 'includes/db.php';
require_once 'includes/auth.php';

try {
    $stmt = $pdo->query('SELECT id, nome, preco, descricao, specs, imagem IS NOT NULL AS tem_imagem FROM Produtos ORDER BY id DESC');
    $produtos = $stmt->fetchAll(PDO::FETCH_ASSOC);
} catch (PDOException $e) {
    die('Erro ao buscar produtos: ' . $e->getMessage());
}
?>
<!DOCTYPE html>
<html lang="pt">

<head>
    <meta charset="UTF-8">
    <title>pcNovo - Produtos</title>
    <link rel="stylesheet" href="css/style.css">
    <style>
        .produto-card form {
            margin: 10px 0 0;
            width: 100%;
            display: flex;
            justify-content: center;
        }
        .produto-card .ver-detalhes {
            margin: 0;
        }
        .produto-card .preco {
            margin-top: 10px;
        }
        
        .adicionar-produto {
            position: fixed;
            bottom: 30px;
            right: 30px;
            background-color: #ff6b00;
            color: white;
            border-radius: 50%;
            width: 60px;
            height: 60px;
            display: flex;
            justify-content: center;
            align-items: center;
            box-shadow: 0 4px 10px rgba(0, 0, 0, 0.3);
            transition: all 0.3s ease;
            z-index: 10;
        }
        .adicionar-produto:hover {
            transform: scale(1.1);
            background-color: #ff8833;
            box-shadow: 0 6px 15px rgba(0, 0, 0, 0.4);
        }
        .adicionar-produto svg {
            width: 30px;
            height: 30px;
        }
        
        .adicionar-produto .tooltip {
            position: absolute;
            right: 70px;
            background: #242730;
            padding: 5px 12px;
            border-radius: 4px;
            font-size: 0.8rem;
            opacity: 0;
            transition: opacity 0.3s;
            pointer-events: none;
            white-space: nowrap;
        }
        .adicionar-produto:hover .tooltip {
            opacity: 1;
        }
    </style>
</head>

<body>
    <?php include 'includes/navbar.php'; ?>

    <main>
        <h1>Nossos Produtos</h1>

        <div class="produtos-grid">
            <?php foreach ($produtos as $produto): ?>
                <div class="produto-card">
                    <?php if ($produto['tem_imagem']): ?>
                        <img src="exibir_imagem.php?id=<?php echo $produto['id']; ?>&tipo=produto" alt="Imagem do Produto">
                    <?php else: ?>
                        <img src="imagens/sem_imagem.png" alt="Sem imagem disponível">
                    <?php endif; ?>

                    <h2><?php echo htmlspecialchars($produto['nome']); ?></h2>
                    <p><?php echo nl2br(htmlspecialchars(substr($produto['descricao'], 0, 120))) . '...'; ?></p>
                    <form action="produto_detalhe.php" method="get">
                        <input type="hidden" name="id" value="<?php echo $produto['id']; ?>">
                        <button type="submit" class="ver-detalhes">Ver detalhes</button>
                    </form>
                    <p class="preco">€ <?php echo number_format($produto['preco'], 2, ',', '.'); ?></p>
                </div>
            <?php endforeach; ?>
        </div>
    </main>

    <?php if (isAdmin()): ?>
    <a href="admin/adicionar_produto.php" class="adicionar-produto">
        <span class="tooltip">Adicionar Produto</span>
        <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
            <line x1="12" y1="5" x2="12" y2="19"></line>
            <line x1="5" y1="12" x2="19" y2="12"></line>
        </svg>
    </a>
    <?php endif; ?>
</body>

</html>