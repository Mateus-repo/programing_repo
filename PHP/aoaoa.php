<?php
    $a = $_POST["num1"];
    $b = $_POST["num2"];
    if($b){
        echo $a/$b;
    }else{
        echo "Divisão por zero";
    }
?>