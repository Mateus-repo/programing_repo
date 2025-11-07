<html>    
    <body>
        <?php
        echo "Qual o teu nome?\n";
        ?>
    <form name="send_data_form" method="post" action="">
        <input type="text" name="name">
        <input type="submit" name="submit" value="Send">
    </form>
        <?php $name=$_POST["name"];
        echo $name;
        ?>
    </body>
</html>