<?php
require "dbConnection.php";
require "sql_commands.php";

function generateVerificationCode() {
    return str_pad(random_int(0, 999999), 6, '0', STR_PAD_LEFT);
}


function calcTyrePenality($car, $weather, $a): int
{
    if($car["tire"] != $weather) {
        if($car["tire"] == "Normal") {
            if($weather == "Rain") {
                $a*=0.90;
            }else{
                $a*=0.75;
            }
        }
        if($car["tire"] == "Rain") {
            if($weather == "Snow") {
                $a*=0.7;
            }
        }

    }
    return $a;
}
function setorTime($idSetor, $mysqli): int
{
    $tempo = sqlQuery("SELECT setorTempoBase FROM setores WHERE setorId = ?", $mysqli, "i", [$idSetor]);
    return $tempo;#in Milliseconds
}

function getUserItems($raceId, $userId, $mysqli){
    $numItems = sqlQuery("
        SELECT COUNT(*) FROM corridaUtilizadorItens 
        WHERE corridaUtilizadorItemCorridaId = ? 
        AND corridaUtilizadorItemUtilizadorId = ?",
        $mysqli,
        "ii",
        [$raceId, $userId]
    );

}
#corridaUtilizadorItens

#corridaUtilizadorItemCorridaId
#corridaUtilizadorItemUtilizadorId
#corridaUtilizadorItemItemId