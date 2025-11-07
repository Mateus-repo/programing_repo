<!DOCTYPE html>
<html>
<body>
    <h1>Comparacao de numeros</h1>
    <form method="post" action="">
        <!-- Aqui cria um formulário para inserir os numeros e o butao -->
        <!-- Variaveis numero1 ; numero2 -->     
        <!-- campo para inserir o numero1 -->
        <label for=numero1> Qual o numero 1? </label>
        <input type="number" name="numero1" id="numero1" required><br><br>

        <!-- campo para inserir o nunero2 -->
        <label for=numero2> Qual o numero 2? </label>
        <input type="number" name="numero2" id="numero2" required><br><br>

        <!-- butao de "enviar" -->
        <input type="submit" value="Comparar">
    </form>
    <!-- Aqui acaba o formulario -->

    <?php
    //agora o codigo vai vereficar se o formulario foi submetido
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $numero1 = $_POST["numero1"];
        $numero2 = $_POST["numero2"];
        //a definir variavel

        if ($numero1 < $numero2){
            echo"O numero 1 é menor.";
            //escrever em funcao das variaveis
        }else{
            if ($numero2 < $numero1){
                echo"O numero 2 é menor.";
                //escrever em funcao das variaveis

            }else{
                echo"O numero 1 e 2 sao iguais.";
                //escrever em funcao das variaveis
            }
        }
    }
    ?>
</body>
</html>