<?php
$a = $_POST["num1"];
$b = $_POST["num2"];
$radio = $_POST["fav_language"];
function multiplicacao($numA,$numB){
    $result = 0;
    $result = $numA * $numB;
    return $result;
}
function divisao($numA,$numB){
    $result = 0;
    if($numB){
        $result = $numA / $numB;
    }
    return $result;
}
function soma($numA,$numB){
    $result = 0;
    $result = $numA + $numB;
    return $result;
}
function subtracao($numA,$numB){
    $result = 0;
    $result = $numA - $numB;
    return $result;
}
    if($radio=="+"){
        echo soma($a, $b);
    }else if($radio=="-"){
        echo subtracao($a, $b);
    }else if($radio=="*"){
        echo multiplicacao($a, $b);
    }else if($radio=="/"){
        if(divisao($a, $b)){
            echo divisao($a, $b);
        }else{
            echo "Erro! Impossível dividir por zero!";
        }
    }else{
        echo "Erro!";
    }
?>