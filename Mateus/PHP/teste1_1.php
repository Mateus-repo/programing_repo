<?php

echo "Qual o numero a? \n";
$test1 = (int)trim(fgets(STDIN));

echo "Qual o numero b? \n";
$test2 = (int)trim(fgets(STDIN));

if ($test1 == $test2) {
    echo "O numero a e b sao iguais \n";
} else {
    if ($test1 < $test2) {
        echo "O numero a é menor que b \n";
    } else {
        echo "O numero b é menor que a \n";
    }
}
?>
