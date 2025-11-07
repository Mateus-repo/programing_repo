<?php
$valores = array();
$somaValores = 0;
$maiorValores = 0;
$menorValores = 0;
function aleatorio(){
    $randomNum = rand(-1000000000,1000000000);
    return($randomNum);
}
for($i = 0; $i<10; $i++){
    $anterior = 0;
    $valores[$i]= aleatorio();
    echo $valores[$i]." | ";
    if($i==1){
        $maiorValores = $menorValores = $valores[$i];
    }
    $somaValores += $valores[$i];
    if($valores[$i]>$maiorValores){
        $maiorValores = $valores[$i];
    }
    if($valores[$i]<$menorValores){
        $maiorValores = $valores[$i];
    }
}
echo "<br>"."A soma total de todos os valores é ".$somaValores."<br>";
echo "O maior valor é ".$maiorValores." e o menor é ".$menorValores."<br>";
?>