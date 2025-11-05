<?php
require_once 'includes/db.php';
require_once 'includes/auth.php';

$tipo = $_GET['tipo'] ?? '';
$id = $_GET['id'] ?? 0;

try {
    if ($tipo === 'produto') {
        $stmt = $pdo->prepare('SELECT imagem FROM Produtos WHERE id = ?');
        $coluna = 'imagem';
    } elseif ($tipo === 'perfil') {
        $stmt = $pdo->prepare('SELECT imagem_perfil FROM Clientes WHERE id = ?');
        $coluna = 'imagem_perfil';
    } else {
        header("HTTP/1.0 400 Bad Request");
        exit('Tipo de imagem inválido');
    }

    $stmt->execute([$id]);
    $resultado = $stmt->fetch(PDO::FETCH_ASSOC);

    $debug = false; 
    
    if ($resultado && !empty($resultado[$coluna])) {
        $imagem = $resultado[$coluna];
        
        if ($debug) {
            echo "Tamanho da imagem: " . strlen($imagem) . " bytes<br>";
            echo "Conteúdo binário presente: " . ($imagem ? 'Sim' : 'Não') . "<br>";
            exit();
        }
        
        $finfo = new finfo(FILEINFO_MIME_TYPE);
        $mime_type = $finfo->buffer($imagem);
        
        header("Content-Type: $mime_type");
        header("Content-Length: " . strlen($imagem));
        echo $imagem;
    } else {
        if ($tipo === 'perfil') {
            if ($id > 0) {
                $check_admin = $pdo->prepare('SELECT role FROM Clientes WHERE id = ?');
                $check_admin->execute([$id]);
                $user_role = $check_admin->fetchColumn();
                
                if ($user_role === 'admin') {
                    header('Location: images/admin-svg.svg');
                } else {
                    header('Location: images/cliente-svg.svg');
                }
            } else {
                header('Location: images/cliente-svg.svg');
            }
        } else {
            header('Location: images/placeholder.svg');
        }
    }
} catch (PDOException $e) {
    header("HTTP/1.0 500 Internal Server Error");
    exit('Erro ao buscar imagem: ' . $e->getMessage());
}