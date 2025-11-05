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
$nome = $descricao = $specs = $preco = '';

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $nome = $_POST['nome'] ?? '';
    $descricao = $_POST['descricao'] ?? '';
    $specs = $_POST['specs'] ?? '';
    $preco = $_POST['preco'] ?? '';
    $imagem = null;
    if (empty($nome) || empty($preco)) {
        $erro = 'Nome e preço são obrigatórios';
    } else {
        try {
            checkConnection();
            if (
                isset($_FILES['imagem']) &&
                $_FILES['imagem']['error'] === UPLOAD_ERR_OK &&
                is_uploaded_file($_FILES['imagem']['tmp_name'])
            ) {
                $finfo = new finfo(FILEINFO_MIME_TYPE);
                $mime_type = $finfo->file($_FILES['imagem']['tmp_name']);
                if (strpos($mime_type, 'image/') === 0) {
                    $max_size = 2 * 1024 * 1024; // 2MB
                    $file_size = filesize($_FILES['imagem']['tmp_name']);

                    if ($file_size <= $max_size) {
                        $imagem = file_get_contents($_FILES['imagem']['tmp_name']);
                    } else {
                        $erro = 'A imagem é muito grande. O tamanho máximo é 2MB.';
                    }
                } else {
                    $erro = 'O arquivo enviado não é uma imagem válida.';
                }
            }
            if (empty($erro)) {
                $stmt = $pdo->prepare('INSERT INTO Produtos (nome, descricao, specs, preco, imagem) VALUES (?, ?, ?, ?, ?)');
                $stmt->execute([$nome, $descricao, $specs, $preco, $imagem]);

                $sucesso = 'Produto adicionado com sucesso!';
                $nome = $descricao = $specs = $preco = '';
            }
        } catch (PDOException $e) {
            $erro = 'Erro ao adicionar produto: ' . $e->getMessage();
        }
    }
}
?>
<!DOCTYPE html>
<html lang="pt">
<head>
    <meta charset="UTF-8">
    <title>pcNovo - Adicionar Produto</title>
    <link rel="stylesheet" href="../css/style.css">
</head>
<body>
    <?php include '../includes/navbar.php'; ?>
    <main class="profile-container">
        <h1>Adicionar Novo Produto</h1>
        <?php if ($erro): ?>
            <p class="erro"><?php echo htmlspecialchars($erro); ?></p>
        <?php endif; ?>
        <?php if ($sucesso): ?>
            <p class="sucesso"><?php echo htmlspecialchars($sucesso); ?></p>
        <?php endif; ?>
        <form method="POST" enctype="multipart/form-data">
            <div>
                <label for="nome">Nome do Produto:</label>
                <input type="text" id="nome" name="nome" required value="<?php echo htmlspecialchars($nome); ?>">
            </div>
            <div>
                <label for="descricao">Descrição:</label>
                <textarea id="descricao" name="descricao"
                    rows="4"><?php echo htmlspecialchars($descricao); ?></textarea>
            </div>
            <div>
                <label for="specs">Especificações Técnicas:</label>
                <textarea id="specs" name="specs" rows="6"><?php echo htmlspecialchars($specs); ?></textarea>
            </div>
            <div>
                <label for="preco">Preço (€):</label>
                <input type="number" id="preco" name="preco" step="0.01" min="0" required
                    value="<?php echo htmlspecialchars($preco); ?>">
            </div>
            <div class="file-input-container">
                <label for="imagem">Imagem do Produto:</label>
                <div>
                    <span class="custom-file-upload">
                        Escolher arquivo
                        <input type="file" id="imagem" name="imagem" accept="image/*">
                    </span>
                    <span id="file-selected">Nenhum arquivo selecionado</span>
                </div>
                <input type="hidden" name="MAX_FILE_SIZE" value="2097152">
                <small style="color: #666; display: block; margin-top: 5px;">
                    Formatos permitidos: JPG, PNG, GIF. Tamanho máximo: 2MB.
                </small>
            </div>
            <button type="submit">Adicionar Produto</button>
        </form>
        <div class="acoes" style="margin-top: 20px;">
            <a href="gerir_produtos.php" class="btn">Voltar para Gestão de Produtos</a>
        </div>
    </main>
    <script>
        document.getElementById('imagem').addEventListener('change', function (e) {
            const fileName = e.target.files[0]?.name || 'Nenhum arquivo selecionado';
            document.getElementById('file-selected').textContent = fileName;
        });
    </script>
</body>

</html>