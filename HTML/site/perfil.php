<?php
session_start();
require_once 'includes/db.php';
require_once 'includes/auth.php';

if (!isLoggedIn()) {
    header('Location: login.php');
    exit();
}

$erro = '';
$sucesso = '';

try {
    checkConnection(); 
    $stmt = $pdo->prepare('SELECT * FROM Clientes WHERE id = ?');
    $stmt->execute([$_SESSION['user_id']]);
    $usuario = $stmt->fetch(PDO::FETCH_ASSOC);

    if (!$usuario) {
        header('Location: logout.php');
        exit();
    }
} catch (PDOException $e) {
    $erro = 'Erro ao buscar dados do usuário: ' . $e->getMessage();
    error_log('Erro em perfil.php ao buscar usuário: ' . $e->getMessage());
}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $nome = $_POST['nome'] ?? '';
    $email = $_POST['email'] ?? '';
    $senha_atual = $_POST['senha_atual'] ?? '';
    $nova_senha = $_POST['nova_senha'] ?? '';
    $confirma_senha = $_POST['confirma_senha'] ?? '';

    if (empty($nome) || empty($email)) {
        $erro = 'Nome e email são obrigatórios';
    } elseif (!empty($nova_senha)) {
        if (empty($senha_atual) || !password_verify($senha_atual, $usuario['senha'])) {
            $erro = 'Senha atual incorreta';
        } elseif ($nova_senha !== $confirma_senha) {
            $erro = 'As novas senhas não coincidem';
        } elseif (strlen($nova_senha) < 6) {
            $erro = 'A nova senha deve ter pelo menos 6 caracteres';
        }
    }

    if (empty($erro)) {
        try {
            checkConnection();
            
            $stmt = $pdo->prepare('UPDATE Clientes SET nome = ?, email = ? WHERE id = ?');
            $stmt->execute([$nome, $email, $_SESSION['user_id']]);
            
            $_SESSION['nome'] = $nome;
            $_SESSION['email'] = $email;
            
            $usuario['nome'] = $nome;
            $usuario['email'] = $email;
            
            $sucesso = 'Dados pessoais atualizados com sucesso!';

            if (!empty($nova_senha)) {
                checkConnection();
                $senha_hash = password_hash($nova_senha, PASSWORD_DEFAULT);
                $stmt = $pdo->prepare('UPDATE Clientes SET senha = ? WHERE id = ?');
                $stmt->execute([$senha_hash, $_SESSION['user_id']]);
                $sucesso = 'Perfil e senha atualizados com sucesso!';
            }
            
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
                    
                    if ($file_size > $max_size) {
                        $erro = 'A imagem é muito grande. O tamanho máximo é 1MB.';
                        error_log('Upload rejeitado - imagem muito grande: ' . $file_size . ' bytes');
                    } else {
                        $imagem_dados = file_get_contents($_FILES['imagem_perfil']['tmp_name']);
                        
                        checkConnection();
                        
                        try {
                            error_log('Tentando salvar imagem de perfil. Tamanho: ' . strlen($imagem_dados) . ' bytes');
                            
                            $stmt = $pdo->prepare('UPDATE Clientes SET imagem_perfil = ? WHERE id = ?');
                            $stmt->execute([$imagem_dados, $_SESSION['user_id']]);
                            
                            checkConnection();
                            $check = $pdo->prepare('SELECT COUNT(*) FROM Clientes WHERE id = ? AND imagem_perfil IS NOT NULL');
                            $check->execute([$_SESSION['user_id']]);
                            $result = $check->fetchColumn();
                            
                            if ($result > 0) {
                                $sucesso .= ' Imagem atualizada com sucesso.';
                                error_log('Imagem de perfil salva com sucesso para usuário ID: ' . $_SESSION['user_id']);
                            } else {
                                $erro = 'Falha ao salvar a imagem de perfil.';
                                error_log('Falha ao salvar imagem de perfil para usuário ID: ' . $_SESSION['user_id']);
                            }
                        } catch (PDOException $e) {
                            $erro = 'Erro ao salvar imagem: ' . $e->getMessage();
                            error_log('Erro PDO ao salvar imagem: ' . $e->getMessage());
                        }
                    }
                } else {
                    $erro = 'O arquivo enviado não é uma imagem válida.';
                    error_log('Upload rejeitado - tipo MIME inválido: ' . $mime_type);
                }
            }

        } catch (Exception $e) {
            $erro = 'Erro ao atualizar perfil: ' . $e->getMessage();
            error_log('Erro no perfil.php: ' . $e->getMessage());
        }
    }
}

try {
    checkConnection();
    $stmt = $pdo->prepare('SELECT imagem_perfil FROM Clientes WHERE id = ?');
    $stmt->execute([$_SESSION['user_id']]);
    $usuario['imagem_perfil'] = $stmt->fetchColumn();
} catch (PDOException $e) {
    error_log('Erro ao buscar imagem de perfil: ' . $e->getMessage());
}
?>
<!DOCTYPE html>
<html lang="pt">

<head>
    <meta charset="UTF-8">
    <title>pcNovo - Perfil</title>
    <link rel="stylesheet" href="css/style.css">
</head>

<body>
    <?php include 'includes/navbar.php'; ?>

    <main class="profile-container">
        <h1>Meu Perfil</h1>

        <?php if ($erro): ?>
            <p class="erro"><?php echo htmlspecialchars($erro); ?></p>
        <?php endif; ?>

        <?php if ($sucesso): ?>
            <p class="sucesso"><?php echo htmlspecialchars($sucesso); ?></p>
        <?php endif; ?>

        <?php if ($usuario['imagem_perfil']): ?>
            <div class="profile-image">
                <img src="exibir_imagem.php?tipo=perfil&id=<?php echo $_SESSION['user_id']; ?>&t=<?php echo time(); ?>"
                    alt="Imagem de perfil">
            </div>
        <?php endif; ?>

        <form method="POST" enctype="multipart/form-data" autocomplete="off">
            <div>
                <label for="nome">Nome:</label>
                <input type="text" id="nome" name="nome" value="<?php echo htmlspecialchars($usuario['nome']); ?>"
                    required>
            </div>

            <div>
                <label for="email">Email:</label>
                <input type="email" id="email" name="email" value="<?php echo htmlspecialchars($usuario['email']); ?>"
                    required>
            </div>

            <div class="file-input-container">
                <label for="imagem_perfil">Atualizar Imagem de Perfil:</label>
                <div>
                    <span class="custom-file-upload">
                        Escolher arquivo
                        <input type="file" id="imagem_perfil" name="imagem_perfil" accept="image/*">
                    </span>
                    <span id="file-selected">Nenhum arquivo selecionado</span>
                </div>
                <input type="hidden" name="MAX_FILE_SIZE" value="2097152"> <!-- 2MB -->
                <small style="color: #666; display: block; margin-top: 5px;">
                    Formatos permitidos: JPG, PNG, GIF. Tamanho máximo: 1MB.
                </small>
            </div>

            <hr>
            <h3>Alterar Senha</h3>
            <p>Preencha apenas se deseja alterar sua senha</p>

            <div>
                <label for="senha_atual">Senha Atual:</label>
                <input type="password" id="senha_atual" name="senha_atual">
            </div>

            <div>
                <label for="nova_senha">Nova Senha:</label>
                <input type="password" id="nova_senha" name="nova_senha">
            </div>

            <div>
                <label for="confirma_senha">Confirmar Nova Senha:</label>
                <input type="password" id="confirma_senha" name="confirma_senha">
            </div>

            <button type="submit">Atualizar Perfil</button>
        </form>
    </main>

    <script>
        document.getElementById('imagem_perfil').addEventListener('change', function (e) {
            const fileName = e.target.files[0]?.name || 'Nenhum arquivo selecionado';
            document.getElementById('file-selected').textContent = fileName;
        });
    </script>
</body>

</html>