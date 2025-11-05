<?php
session_start();
require_once 'includes/db.php';
require_once 'includes/auth.php';


if (!isset($_GET['id']) || !is_numeric($_GET['id'])) {
    die('ID inválido');
}

$id = (int) $_GET['id'];

try {
    $stmt = $pdo->prepare('SELECT * FROM Produtos WHERE id = ?');
    $stmt->execute([$id]);
    $produto = $stmt->fetch(PDO::FETCH_ASSOC);

    if (!$produto) {
        die('Produto não encontrado');
    }
} catch (PDOException $e) {
    die('Erro: ' . $e->getMessage());
}
?>
<!DOCTYPE html>
<html lang="pt">

<head>
    <meta charset="UTF-8">
    <title><?php echo htmlspecialchars($produto['nome']); ?> - Detalhes</title>
    <link rel="stylesheet" href="css/style.css">
    <style>
        .preco-actions {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-top: 20px;
            margin-bottom: 20px;
        }

        .preco {
            font-size: 1.5rem;
            font-weight: bold;
            margin: 0;
        }

        .btn {
            display: inline-flex;
            align-items: center;
            gap: 8px;
            background-color: #3498db;
            color: white;
            text-decoration: none;
            padding: 10px 16px;
            border-radius: 5px;
            transition: background-color 0.3s;
        }

        .btn:hover {
            background-color: #2980b9;
            color: white;
        }
        .tab-content.specs {
            font-family: 'Consolas', 'Monaco', monospace;
            font-size: 1.1rem;
            line-height: 1.4;
            padding: 25px;
            overflow-x: auto;
            white-space: pre-wrap;
            word-wrap: break-word;
            max-height: 500px;
            overflow-y: auto;
            color: #ffffff;
            letter-spacing: 0.5px;
        }
        .tab-content.descricao {
            font-size: 1.05rem;
            line-height: 1.5;
            padding: 25px;
        }
        .imagem-produto {
            max-height: 450px;
        }
        .tab-content.specs strong,
        .tab-content.specs b {
            color: #ff9933;
            font-weight: 700;
        }
        .admin-actions {
            margin-top: 20px;
            display: flex;
            justify-content: center;
        }
        .admin-actions .btn {
            display: inline-flex;
            align-items: center;
            gap: 8px;
            background-color: #3498db;
            color: white;
            text-decoration: none;
            padding: 10px 16px;
            border-radius: 5px;
            transition: background-color 0.3s;
        }

        .admin-actions .btn:hover {
            background-color: #2980b9;
            color: white;
        }
    </style>
</head>

<body>
    <?php include 'includes/navbar.php'; ?>

    <div class="detalhes-container">
        <h1><?php echo htmlspecialchars($produto['nome']); ?></h1>
        <img src="exibir_imagem.php?id=<?php echo $produto['id']; ?>&tipo=produto" alt="Imagem do Produto"
            class="imagem-produto">
        <div class="preco-actions">
            <p class="preco">€ <?php echo number_format($produto['preco'], 2, ',', '.'); ?></p>

            <?php if (isAdmin()): ?>
                <a href="admin/editar_produto.php?id=<?php echo $produto['id']; ?>" class="btn">
                    <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none"
                        stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                        <path d="M11 4H4a2 2 0 0 0-2 2v14a2 2 0 0 0 2 2h14a2 2 0 0 0 2-2v-7"></path>
                        <path d="M18.5 2.5a2.121 2.121 0 0 1 3 3L12 15l-4 1 1-4 9.5-9.5z"></path>
                    </svg>
                    Editar Produto
                </a>
            <?php endif; ?>
        </div>


        <div class="tabs">
            <div class="tab ativo" onclick="mostrarTab(0)">Detalhes do Produto</div>
            <div class="tab" onclick="mostrarTab(1)">Informações Técnicas</div>
        </div>

        <div class="tab-content descricao ativo">
            <p><?php echo nl2br(htmlspecialchars($produto['descricao'])); ?></p>
        </div>
        <div class="tab-content specs">
            <?php echo nl2br(htmlspecialchars($produto['specs'])); ?>
        </div>
    </div>

    <script>
        function mostrarTab(indice) {
            const tabs = document.querySelectorAll('.tab');
            const conteudos = document.querySelectorAll('.tab-content');
            tabs.forEach((tab, i) => {
                tab.classList.toggle('ativo', i === indice);
                conteudos[i].classList.toggle('ativo', i === indice);
            });
        }
    </script>
</body>

</html>