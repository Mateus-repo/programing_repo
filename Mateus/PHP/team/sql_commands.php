<?php
require "db_connect.php";
function sqlCommandSFW( $SELECT, $FROM, $WHERE, $EQUAL, $mysqli)
{
    if($mysqli==Null){
        $mysqli=conectarBD();
    }
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

function oldSqlQuery($Query, $mysqli)
{
    if($mysqli==Null){
        $mysqli=conectarBD();
    }
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

function sqlQuery($query, $mysqli, $types, $params) {
    if ($mysqli == null) {
        $mysqli = conectarBD();
    }

    $stmt = $mysqli->prepare($query);
    if (!$stmt) {
        die("Erro no prepare: " . $mysqli->error);
    }

    $bindParams = [];
    $bindParams[] = $types;
    foreach ($params as $key => $value) {
        $bindParams[] = &$params[$key];
    }

    call_user_func_array([$stmt, 'bind_param'], $bindParams);

    $stmt->execute();

    $result = 0;
    $stmt->bind_result($result);
    $stmt->fetch();
    $stmt->close();

    return $result;
}