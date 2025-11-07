<?php
global $mysqli;
require "../includes/db_connect.php";
/* --------------------------- Coisas para fazer ---------------------------

    Penalidades no tempo dos corredores
    Fatores aleatorios de batidas
    Funcao de curvas
    Pistas

*/
#$IDRace = $lastRaceID + 1;

function sqlCommandSFWOLD2( $SELECT, $FROM, $WHERE, $EQUAL, $mysqli)
{
    $stmt = $mysqli->prepare("SELECT " + $SELECT + " FROM " + $FROM + " WHERE " + $WHERE + " = " + $EQUAL);
    if (!$stmt) {
        die("Erro no prepare: " . $mysqli->error);
    }
    $stmt->execute();
    $tempVariable = 0;
    $stmt->bind_result($tempVariable);
    $stmt->close();
    return $tempVariable;
}

function sqlQueryOLD2($Query, $mysqli)
{
    $stmt = $mysqli->prepare($Query);
    if (!$stmt) {
        die("Erro no prepare: " . $mysqli->error);
    }
    $stmt->execute();
    $tempVariable = 0;
    $stmt->bind_result($tempVariable);
    $stmt->close();
    return $tempVariable;
}

$carDefault = array(
    "speed" => 0, # m/s
    "maxSpeed" => 0, # m/s
    "acceleration" => 0, # m/s^2
    "maxAcceleration" => 0,
    "tire" => "Normal", # either Normal, Rain or Snow
    "time" => 0, #in milliseconds
    "pilot" => 0, #range from 0 to 100
    "durability" => 100 #range from 0 to 100
);

function definePista(array $tempPistaDB): array
{
    $pistaTemp = [];
    $explodePistaDB = explode(";", $tempPistaDB["code"]);
    foreach ($explodePistaDB as $dados) {
        if (trim($dados) === "") continue;
        $dadosDividos = explode(",", $dados);
        $pistaTemp[$dadosDividos[0]-1] = [
            "type" => $dadosDividos[1], # either curve or line
            "size" => $dadosDividos[2] # in meters
        ];
    }

    return $pistaTemp; # $pistaTemp[index][dataName]
}

function defineCarro($idCompetidor, $carTemp, $mysqli): array
{
    $idUser = sqlCommandSFW ("userId", "competidores", "competidorId", $idCompetidor, $mysqli);
    $maxSpeed = 0;
    $maxAccel = 0;

    # $piloto =
    # Vai buscar ao inventario do user qual piloto está ativo, depois vai á tabela inventario_pilotos
    # com o id do piloto ativo buscar o valor no campo "qualidadePiloto"

    # $pneuEquipado =
    # Vai buscar ao inventario do user qual penu está ativo, depois vai á tabela inventario_pneus
    # com o id do piloto ativo buscar o valor no campo "pneu"

    return $carTemp;
}

$idCorrida = sqlQuery("SELECT MAX(corridaId) FROM corridas");
$idPista = sqlCommandSFW("codigo","pistas","pistasId", $idCorrida, $mysqli);
$pistaDB = array(
    "code" => ""
);
$pistaDB["code"] = sqlCommandSFW("codigo","pistas","pistasId", $idPista, $mysqli);
$pista = definePista(['code' => $pistaDB["code"]]);
$numCars = sqlQuery("SELECT COUNT(*) FROM competidores");

function calcTyrePenality($car, $weather, $a)
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

function calcCurva($size, $car, $weather)
{
    $t=0;
    return $t * 1000;
}
function calcReta($size, $car, $weather)
{
    $t=0;
    $vI = $car["speed"];
    $vMax = $car["maxSpeed"];
    $a = calcTyrePenality($car, $weather, $car["acceleration"]);
    $aMax = calcTyrePenality($car, $weather, $car["maxAcceleration"]);
    if($vI==0 && $a==0) {
        $a = $aMax;
        // 2 ** 3 é o mesmo que 2 elevado a 3
        $s1 = ($vMax ** 2) / (2 * $a);// Distância necessária para atingir a velocidade máxima
        if ($size <= $s1) { // se não atingir a velocidade maxima
            $t = sqrt((2 * $size) / $a);
        } else { // calcula o tempo que demora até chegar a velocidade maxima e depois calcula com a velocidade maximo o restante tempo ate acabar a reta
            $t1 = $vMax / $a;
            $s2 = $size - $s1;
            $t2 = $s2 / $vMax;
            $t = $t1 + $t2;
        }
    } else {
        if ($a == 0) {
            $t = $size / $vI;
        } else {
            $temp = $vI ** 2 + 2 * $a * $size;
            $t = (-$vI + sqrt($temp)) / $a;
        }
    }

    return $t * 1000;
}



$mysqli->close();
?>