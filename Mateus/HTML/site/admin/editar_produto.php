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
$id = $_GET['id'] ?? null;

if (!$id || !is_numeric($id)) {
    die('ID de produto inválido');
}

try {
    $stmt = $pdo->prepare('SELECT * FROM Produtos WHERE id = ?');
    $stmt->execute([$id]);
    $produto = $stmt->fetch(PDO::FETCH_ASSOC);

    if (!$produto) {
        die('Produto não encontrado');
    }
} catch (PDOException $e) {
    die('Erro ao buscar produto: ' . $e->getMessage());
}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $nome = $_POST['nome'] ?? '';
    $descricao = $_POST['descricao'] ?? '';
    $specs = $_POST['specs'] ?? '';
    $preco = $_POST['preco'] ?? '';

    if (empty($nome) || empty($preco)) {
        $erro = 'Nome e preço são obrigatórios';
    } else {
        try {
            if (
                isset($_FILES['imagem']) && $_FILES['imagem']['error'] === UPLOAD_ERR_OK &&
                is_uploaded_file($_FILES['imagem']['tmp_name'])
            ) {

                $imagem = file_get_contents($_FILES['imagem']['tmp_name']);

                $tamanhoImagem = strlen($imagem);

                $stmt = $pdo->prepare('UPDATE Produtos SET nome=?, descricao=?, specs=?, preco=?, imagem=? WHERE id=?');
                $stmt->execute([$nome, $descricao, $specs, $preco, $imagem, $id]);

                $check = $pdo->prepare('SELECT imagem FROM Produtos WHERE id = ?');
                $check->execute([$id]);
                $imagemSalva = $check->fetch(PDO::FETCH_COLUMN);

                if ($imagemSalva) {
                    $sucesso = 'Produto atualizado com sucesso! Imagem (tamanho: ' . strlen($imagemSalva) . ' bytes) salva.';
                } else {
                    $sucesso = 'Produto atualizado, mas pode haver um problema com a imagem.';
                }
            } else {
                $stmt = $pdo->prepare('UPDATE Produtos SET nome=?, descricao=?, specs=?, preco=? WHERE id=?');
                $stmt->execute([$nome, $descricao, $specs, $preco, $id]);
                $sucesso = 'Produto atualizado com sucesso! (Sem alteração na imagem)';
            }

            $sucesso = 'Produto atualizado com sucesso!';

            $stmt = $pdo->prepare('SELECT * FROM Produtos WHERE id = ?');
            $stmt->execute([$id]);
            $produto = $stmt->fetch(PDO::FETCH_ASSOC);
        } catch (PDOException $e) {
            $erro = 'Erro ao atualizar produto: ' . $e->getMessage();
        }
    }
}
?>
<!DOCTYPE html>
<html lang="pt">

<head>
    <meta charset="UTF-8">
    <title>Editar Produto</title>
    <link rel="stylesheet" href="../css/style.css">
</head>

<body>
    <?php include '../includes/navbar.php'; ?>

    <main>
        <h1>Editar Produto</h1>

        <?php if ($erro): ?>
            <p class="erro"><?php echo htmlspecialchars($erro); ?></p>
        <?php endif; ?>

        <?php if ($sucesso): ?>
            <p class="sucesso"><?php echo htmlspecialchars($sucesso); ?></p>
        <?php endif; ?>

        <form method="POST" enctype="multipart/form-data">
            <div>
                <label for="nome">Nome:</label>
                <input type="text" id="nome" name="nome" required
                    value="<?php echo htmlspecialchars($produto['nome']); ?>">
            </div>

            <div>
                <label for="descricao">Descrição:</label>
                <textarea id="descricao" name="descricao"
                    rows="4"><?php echo htmlspecialchars($produto['descricao']); ?></textarea>
            </div>

            <div>
                <label for="specs">Especificações Técnicas:</label>
                <textarea id="specs" name="specs" rows="4"><?php echo htmlspecialchars($produto['specs']); ?></textarea>
            </div>

            <div>
                <label for="preco">Preço (€):</label>
                <input type="number" id="preco" name="preco" step="0.01" min="0" required
                    value="<?php echo htmlspecialchars($produto['preco']); ?>">
            </div>

            <div class="file-input-container">
                <label for="imagem">Atualizar Imagem:</label>
                <div class="custom-file-upload">
                    <input type="file" id="imagem" name="imagem" accept="image/*">
                </div>
                <small style="color: #aaa; display: block; margin-top: 5px;">Atual:
                    <?php echo $produto['imagem'] ? 'Imagem carregada' : 'Sem imagem'; ?></small>
            </div>

            <?php if ($produto['imagem']): ?>
                <div style="margin: 15px 0; text-align: center;">
                    <p>Imagem atual:</p>
                    <img src="../exibir_imagem.php?tipo=produto&id=<?php echo $id; ?>&t=<?php echo time(); ?>"
                        alt="Imagem do produto" style="max-width: 200px; max-height: 200px; border: 1px solid #ddd;">
                </div>
            <?php endif; ?>

            <button type="submit">Salvar Alterações</button>
        </form>

        <div class="acoes">
            <a href="gerir_produtos.php" class="btn">Voltar para Gestão de Produtos</a>
        </div>
    </main>

    <script>
        document.getElementById('imagem').addEventListener('change', function (e) {
            const fileName = e.target.files[0]?.name || 'Nenhum arquivo selecionado';
            const label = this.closest('.custom-file-upload');
            if (label) {
                label.textContent = fileName;
            }
        });
    </script>
</body>

</html>