<!DOCTYPE html>
<html>
<head>
    <title>Comparação de Números</title>
</head>
<body>
    <h1>Comparação de Números</h1>
    <!-- Início do formulário -->
    <form method="post" action="">
        <!-- Campo para o primeiro número -->
        <label for="num1">Insira o primeiro número:</label>
        <input type="number" name="num1" id="num1" required><br><br>

        <!-- Campo para o segundo número -->
        <label for="num2">Insira o segundo número:</label>
        <input type="number" name="num2" id="num2" required><br><br>

        <!-- Botão de envio do formulário -->
        <input type="submit" value="Comparar">
    </form>
    <!-- Fim do formulário -->

    <?php
    // Verifica se o formulário foi submetido
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        // Obtém os valores inseridos pelo usuário
        $num1 = $_POST["num1"];
        $num2 = $_POST["num2"];

        // Compara os números e exibe o resultado
        if ($num1 == $num2) {
            echo "Os números são iguais.";
        } elseif ($num1 < $num2) {
            echo "O primeiro número ($num1) é menor que o segundo número ($num2).";
        } else {
            echo "O segundo número ($num2) é menor que o primeiro número ($num1).";
        }
    }
    ?>
</body>
</html>
