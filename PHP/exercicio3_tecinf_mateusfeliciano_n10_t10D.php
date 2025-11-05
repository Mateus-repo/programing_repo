<html>
<body>
Qual o teu nome?
<!-- Esta linha apresenta o texto "Qual o teu nome?" -->
    <form action="" method="post" name="send_data_form"> 
        <!--Nesta linha o action esta vazio oque significa que sera enviado quando o botao enviar for pressionado-->
        <!--O atributo "method" esta defenido como "post"-->
        <!--O atributo "name" define o nome do documento como "send_data_form"-->
        <input type="text" name="name" valeu="">
        <!--Nesta linha o atributo name é definido como name e o atributo valeu como vazio-->
        <input type="submit" value="Enviar">
        <!--Aqui e definido o butao de envio -->
    </form>
    <?php
        $name="";
        //Aqui cria a variavel name e poe na vazia
        if(isset($_POST["name"])){
            //A variavel name e definida como $_POST
            
            $name=$_POST["name"];
            //se foi enviado algum nome então a variavel $name torna-se no texto que esta na variavel $_POST
            echo "Ola ", $name;
            //nesta linha escreve ola e a variavel $name
        }
    ?>
</body>
</html>