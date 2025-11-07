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
        $stmt = $pdo->prepare('DELETE FROM Clientes WHERE id = ?');
        $stmt->execute([$_GET['excluir']]);
        $mensagem = 'Cliente excluído com sucesso!';
    } catch (PDOException $e) {
        $erro = 'Erro ao excluir cliente: ' . $e->getMessage();
    }
}

try {
    $stmt = $pdo->query('SELECT id, nome, email, data_nascimento FROM Clientes ORDER BY id DESC');
    $clientes = $stmt->fetchAll(PDO::FETCH_ASSOC);
} catch (PDOException $e) {
    die('Erro ao buscar clientes: ' . $e->getMessage());
}
?>
<!DOCTYPE html>
<html lang="pt">
<head>
    <meta charset="UTF-8">
    <title>pcNovo - Gestão de Utilizadores</title>
    <link rel="stylesheet" href="../css/style.css">
</head>
<body>
    <?php include '../includes/navbar.php'; ?>

    <main>
        <h1>Gestão de Utilizadores</h1>
        
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
                    <th>Email</th>
                    <th>Data de Nascimento</th>
                    <th>Ações</th>
                </tr>
            </thead>
            <tbody>
                <?php foreach ($clientes as $cliente): ?>
                    <tr>
                        <td><?php echo htmlspecialchars($cliente['id']); ?></td>
                        <td><?php echo htmlspecialchars($cliente['nome']); ?></td>
                        <td><?php echo htmlspecialchars($cliente['email']); ?></td>
                        <td><?php echo $cliente['data_nascimento'] ? date('d/m/Y', strtotime($cliente['data_nascimento'])) : ''; ?></td>
                        <td>
                            <a href="editar_usuario.php?id=<?php echo $cliente['id']; ?>">Editar</a>
                            <a href="?excluir=<?php echo $cliente['id']; ?>" onclick="return confirm('Tem certeza que deseja excluir este cliente?')">Excluir</a>
                        </td>
                    </tr>
                <?php endforeach; ?>
            </tbody>
        </table>

        <div class="acoes">
            <a href="admin_adicionar_usuario.php" class="btn">Adicionar Novo Cliente</a>
        </div>
    </main>

    <script>
        document.querySelectorAll('a[href*="excluir"]').forEach(link => {
            link.addEventListener('click', function(e) {
                if (!confirm('Tem certeza que deseja excluir este cliente?')) {
                    e.preventDefault();
                }
            });
        });
    </script>
</body>
</html>