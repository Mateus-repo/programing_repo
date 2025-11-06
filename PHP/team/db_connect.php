<?php
function conectarBD(){
    $host = '26.226.117.155'; #localhost = 127.0.0.1
    # radmin NetworkName - Glich321
    #        NetworkPassowrd - Glich123
    $user = 'userSQL';
    $pass = 'p@SQLgameServer';
    $db   = 'glitch';
    $port = 3306;
    $ligaBD = mysqli_connect($host, $user, $pass, $db, $port);

    if (!$ligaBD) {
        die("Erro de conexão: " . mysqli_connect_error());
    }
    return $ligaBD;
}
conectarBD();

?>