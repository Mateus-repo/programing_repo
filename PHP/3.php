<?php
$pais = "Portugal";
$frase = "Estou a frequentar o curso de Informática";
echo substr(string:$pais, offset:3,  length: 2);
echo ('<br>');  
echo strlen(string:$pais);
echo ('<br>');  
echo strtoupper(string:$pais);
echo ('<br>');  
echo str_replace("Informática","Programador de Informática", $frase);
?>