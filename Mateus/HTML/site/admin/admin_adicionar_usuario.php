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
$nome = $email = $data_nasc = '';
$role = 'cliente';

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $nome = trim($_POST['nome'] ?? '');
    $email = trim($_POST['email'] ?? '');
    $senha = trim($_POST['senha'] ?? '');
    $confirmar_senha = trim($_POST['confirmar_senha'] ?? '');
    $data_nasc = $_POST['data_nascimento'] ?? null;
    $role = $_POST['role'] ?? 'cliente';
    
    if (empty($nome) || empty($email) || empty($senha)) {
        $erro = 'Nome, email e senha são obrigatórios.';
    } elseif ($senha !== $confirmar_senha) {
        $erro = 'As senhas não coincidem.';
    } elseif (strlen($senha) < 6) {
        $erro = 'A senha deve ter pelo menos 6 caracteres.';
    } else {
        try {
            checkConnection();

            $stmt = $pdo->prepare('SELECT id FROM Clientes WHERE email = ?');
            $stmt->execute([$email]);
            if ($stmt->fetch()) {
                $erro = 'Este email já está em uso.';
            } else {
                $hash = password_hash($senha, PASSWORD_DEFAULT);

                $imgDados = null;
                if (
                    isset($_FILES['imagem_perfil']) && 
                    $_FILES['imagem_perfil']['error'] === UPLOAD_ERR_OK &&
                    is_uploaded_file($_FILES['imagem_perfil']['tmp_name'])
                ) {
                    $finfo = new finfo(FILEINFO_MIME_TYPE);
                    $mime_type = $finfo->file($_FILES['imagem_perfil']['tmp_name']);
                    
                    if (strpos($mime_type, 'image/') === 0) {

                        $max_size = 2 * 1024 * 1024; // 2MB
                        $file_size = filesize($_FILES['imagem_perfil']['tmp_name']);
                        
                        if ($file_size <= $max_size) {
                            $imgDados = file_get_contents($_FILES['imagem_perfil']['tmp_name']);
                        } else {
                            $erro = 'A imagem é muito grande. O tamanho máximo é 1MB.';
                        }
                    } else {
                        $erro = 'O arquivo enviado não é uma imagem válida.';
                    }
                }
                
                if (empty($erro)) {
                    $stmt = $pdo->prepare('INSERT INTO Clientes (nome, email, senha, data_nascimento, role, imagem_perfil) VALUES (?, ?, ?, ?, ?, ?)');
                    $stmt->execute([$nome, $email, $hash, $data_nasc ?: null, $role, $imgDados]);
                    
                    $sucesso = 'Cliente adicionado com sucesso!';
                    $nome = $email = $data_nasc = '';
                    $role = 'cliente';
                }
            }
        } catch (PDOException $e) {
            $erro = 'Erro ao adicionar cliente: ' . $e->getMessage();
        }
    }
}
?>
<!DOCTYPE html>
<html lang="pt">

<head>
    <meta charset="UTF-8">
    <title>pcNovo - Adicionar Utilizador</title>
    <link rel="stylesheet" href="../css/style.css">
</head>

<body>
    <?php include '../includes/navbar.php'; ?>

    <main class="profile-container">
        <h1>Adicionar Novo Utilizador</h1>

        <?php if ($erro): ?>
            <p class="erro"><?= htmlspecialchars($erro) ?></p>
        <?php endif; ?>

        <?php if ($sucesso): ?>
            <p class="sucesso"><?= htmlspecialchars($sucesso) ?></p>
        <?php endif; ?>

        <form method="POST" enctype="multipart/form-data">
            <div>
                <label for="nome">Nome:</label>
                <input type="text" id="nome" name="nome" value="<?= htmlspecialchars($nome) ?>" required>
            </div>

            <div>
                <label for="email">Email:</label>
                <input type="email" id="email" name="email" value="<?= htmlspecialchars($email) ?>" required>
            </div>

            <div>
                <label for="senha">Senha:</label>
                <input type="password" id="senha" name="senha" required>
            </div>

            <div>
                <label for="confirmar_senha">Confirmar Senha:</label>
                <input type="password" id="confirmar_senha" name="confirmar_senha" required>
            </div>

            <div>
                <label for="data_nascimento">Data de Nascimento:</label>
                <input type="date" id="data_nascimento" name="data_nascimento" 
                       value="<?= htmlspecialchars($data_nasc) ?>">
            </div>

            <div>
                <label for="role">Função:</label>
                <select name="role" id="role">
                    <option value="cliente" <?= $role === 'cliente' ? 'selected' : '' ?>>Cliente</option>
                    <option value="admin" <?= $role === 'admin' ? 'selected' : '' ?>>Admin</option>
                </select>
            </div>

            <div class="file-input-container">
                <label for="imagem_perfil">Imagem de Perfil (opcional):</label>
                <div>
                    <span class="custom-file-upload">
                        Escolher arquivo
                        <input type="file" id="imagem_perfil" name="imagem_perfil" accept="image/*">
                    </span>
                    <span id="file-selected">Nenhum arquivo selecionado</span>
                </div>
                <input type="hidden" name="MAX_FILE_SIZE" value="1048576"> <!-- 1MB -->
                <small style="color: #666; display: block; margin-top: 5px;">
                    Formatos permitidos: JPG, PNG, GIF. Tamanho máximo: 1MB.
                </small>
            </div>

            <div style="display: flex; gap: 15px; justify-content: center; margin-top: 20px;">
                <button type="submit" class="btn">Adicionar Utilizador</button>
                <a href="gerir_utilizadores.php" class="btn">Cancelar</a>
            </div>
        </form>
    </main>

    <script>
        document.getElementById('imagem_perfil').addEventListener('change', function(e) {
            const fileName = e.target.files[0]?.name || 'Nenhum arquivo selecionado';
            document.getElementById('file-selected').textContent = fileName;
        });
    </script>
</body>

</html>