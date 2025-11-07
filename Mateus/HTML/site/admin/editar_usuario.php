<?php
session_start();
require_once '../includes/db.php';
require_once '../includes/auth.php';

if (!isAdmin()) {
    header('Location: ../home.php');
    exit();
}

$erro = '';
$sucesso = '';

if (!isset($_GET['id']) || !is_numeric($_GET['id'])) {
    header('Location: gerir_utilizadores.php');
    exit();
}
$id = (int) $_GET['id'];

try {
    $stmt = $pdo->prepare('SELECT * FROM Clientes WHERE id = ?');
    $stmt->execute([$id]);
    $cliente = $stmt->fetch(PDO::FETCH_ASSOC);
    if (!$cliente) {
        header('Location: gerir_utilizadores.php');
        exit();
    }
} catch (PDOException $e) {
    $erro = 'Erro ao buscar cliente: ' . $e->getMessage();
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $nome = trim($_POST['nome'] ?? '');
    $email = trim($_POST['email'] ?? '');
    $data_nasc = $_POST['data_nascimento'] ?? null;
    $role = $_POST['role'] ?? 'cliente';
    $nova_senha = trim($_POST['nova_senha'] ?? '');
    $imagem_perfil = $_FILES['imagem_perfil']['tmp_name'] ?? null;

    if (empty($nome) || empty($email)) {
        $erro = 'Nome e email são obrigatórios.';
    } elseif (!empty($nova_senha) && strlen($nova_senha) < 6) {
        $erro = 'A nova senha deve ter ao menos 6 caracteres.';
    }

    if (empty($erro)) {
        try {
            if (
                isset($_FILES['imagem_perfil']) && $_FILES['imagem_perfil']['error'] === UPLOAD_ERR_OK &&
                is_uploaded_file($_FILES['imagem_perfil']['tmp_name'])
            ) {
                $imgDados = file_get_contents($_FILES['imagem_perfil']['tmp_name']);
                $stmt = $pdo->prepare('UPDATE Clientes SET nome=?, email=?, data_nascimento=?, role=?, imagem_perfil=? WHERE id=?');
                $params = [$nome, $email, $data_nasc ?: null, $role, $imgDados, $id];
            } else {
                $stmt = $pdo->prepare('UPDATE Clientes SET nome=?, email=?, data_nascimento=?, role=? WHERE id=?');
                $params = [$nome, $email, $data_nasc ?: null, $role, $id];
            }

            $stmt->execute($params);
            if ($id === $_SESSION['user_id']) {
                $_SESSION['role'] = $role;
            }

            if (!empty($nova_senha)) {
                $hash = password_hash($nova_senha, PASSWORD_DEFAULT);
                $pdo->prepare('UPDATE Clientes SET senha = ? WHERE id = ?')
                    ->execute([$hash, $id]);
            }

            $sucesso = 'Cliente atualizado com sucesso!';
            $cliente['nome'] = $nome;
            $cliente['email'] = $email;
            $cliente['data_nascimento'] = $data_nasc;
            $cliente['role'] = $role;

        } catch (PDOException $e) {
            $erro = 'Erro ao atualizar cliente: ' . $e->getMessage();
        }
    }
}
?>
<!DOCTYPE html>
<html lang="pt">

<head>
    <meta charset="UTF-8">
    <title>Editar Utilizador</title>
    <link rel="stylesheet" href="../css/style.css">
</head>

<body>
    <?php include '../includes/navbar.php'; ?>
    <main>
        <h1>Editar Utilizador</h1>

        <?php if ($erro): ?>
            <p class="erro"><?= htmlspecialchars($erro) ?></p>
        <?php endif; ?>
        <?php if ($sucesso): ?>
            <p class="sucesso"><?= htmlspecialchars($sucesso) ?></p>
        <?php endif; ?>

        <form method="POST" enctype="multipart/form-data">
            <div>
                <label for="nome">Nome:</label>
                <input type="text" id="nome" name="nome" value="<?= htmlspecialchars($cliente['nome']) ?>" required>
            </div>

            <div>
                <label for="email">Email:</label>
                <input type="email" id="email" name="email" value="<?= htmlspecialchars($cliente['email']) ?>" required>
            </div>

            <div>
                <label for="data_nascimento">Data de Nascimento:</label>
                <input type="date" id="data_nascimento" name="data_nascimento"
                    value="<?= htmlspecialchars($cliente['data_nascimento']) ?>">
            </div>

            <div>
                <label for="role">Função:</label>
                <select name="role" id="role">
                    <option value="cliente" <?= $cliente['role'] === 'cliente' ? 'selected' : '' ?>>Cliente</option>
                    <option value="admin" <?= $cliente['role'] === 'admin' ? 'selected' : '' ?>>Admin</option>
                </select>
            </div>

            <div>
                <label for="nova_senha">Nova Senha (opcional):</label>
                <input type="password" id="nova_senha" name="nova_senha" placeholder="Deixe vazio para manter a atual">
            </div>

            <div class="file-input-container">
                <label for="imagem_perfil">Imagem de Perfil (opcional):</label>
                <div class="custom-file-upload">
                    <input type="file" id="imagem_perfil" name="imagem_perfil" accept="image/*">
                </div>
                <small style="color: #aaa; display: block; margin-top: 5px;">
                    <?= $cliente['imagem_perfil'] ? 'Imagem atual carregada' : 'Sem imagem de perfil' ?>
                </small>
            </div>

            <div style="display: flex; gap: 15px; justify-content: center; margin-top: 20px;">
                <button type="submit" class="btn">Atualizar Utilizador</button>
                <a href="gerir_utilizadores.php" class="btn">Cancelar</a>
            </div>
        </form>
    </main>

    <script>
        document.getElementById('imagem_perfil').addEventListener('change', function (e) {
            const fileName = e.target.files[0]?.name || 'Nenhum arquivo selecionado';
            const label = this.closest('.custom-file-upload');
            if (label) {
                label.textContent = fileName;
            }
        });
    </script>
</body>

</html>