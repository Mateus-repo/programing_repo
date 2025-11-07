<?php
session_start();
require_once '../includes/db.php';
require_once '../includes/auth.php';

if (!isAdmin()) {
    header('Location: ../home.php');
    exit();
}

if (isset($_GET['excluir']) && is_numeric($_GET['excluir'])) {
    try {
        $stmt = $pdo->prepare('DELETE FROM Produtos WHERE id = ?');
        $stmt->execute([$_GET['excluir']]);
        $mensagem = 'Produto excluído com sucesso!';
    } catch (PDOException $e) {
        $erro = 'Erro ao excluir produto: ' . $e->getMessage();
    }
}

try {
    $stmt = $pdo->query('SELECT id, nome, preco, descricao, specs FROM Produtos ORDER BY id DESC');
    $produtos = $stmt->fetchAll(PDO::FETCH_ASSOC);
} catch (PDOException $e) {
    die('Erro ao buscar produtos: ' . $e->getMessage());
}
?>
<!DOCTYPE html>
<html lang="pt">
<head>
    <meta charset="UTF-8">
    <title>pcNovo - Gestão de Produtos</title>
    <link rel="stylesheet" href="../css/style.css">
</head>
<body>
    <?php include '../includes/navbar.php'; ?>

    <main>
        <h1>Gestão de Produtos</h1>
        
        <?php if (isset($mensagem)): ?>
            <p class="sucesso"><?php echo htmlspecialchars($mensagem); ?></p>
        <?php endif; ?>
        
        <?php if (isset($erro)): ?>
            <p class="erro"><?php echo htmlspecialchars($erro); ?></p>
        <?php endif; ?>

        <table>
            <thead>
                <tr>
                    <th>ID</th>
                    <th>Nome</th>
                    <th>Preço</th>
                    <th>Descrição</th>
                    <th>Especificações</th>
                    <th>Ações</th>
                </tr>
            </thead>
            <tbody>
                <?php foreach ($produtos as $produto): ?>
                    <tr>
                        <td><?php echo htmlspecialchars($produto['id']); ?></td>
                        <td><?php echo htmlspecialchars($produto['nome']); ?></td>
                        <td><?php echo number_format($produto['preco'], 2, ',', '.'); ?> €</td>
                        <td><?php echo htmlspecialchars(substr($produto['descricao'], 0, 50) . '...'); ?></td>
                        <td><?php echo htmlspecialchars(substr($produto['specs'], 0, 50) . '...'); ?></td>
                        <td>
                            <a href="editar_produto.php?id=<?php echo $produto['id']; ?>">Editar</a>
                            <a href="?excluir=<?php echo $produto['id']; ?>" onclick="return confirm('Tem certeza que deseja excluir este produto?')">Excluir</a>
                        </td>
                    </tr>
                <?php endforeach; ?>
            </tbody>
        </table>

        <div class="acoes">
            <a href="adicionar_produto.php" class="btn">Adicionar Novo Produto</a>
        </div>
    </main>

    <script>
        document.querySelectorAll('a[href*="excluir"]').forEach(link => {
            link.addEventListener('click', function(e) {
                if (!confirm('Tem certeza que deseja excluir este produto?')) {
                    e.preventDefault();
                }
            });
        });
    </script>
</body>
</html>
