<?php

require "includes/db_connect.php";
require "includes/sql_commands.php";
require "includes/functions.php";

$mysqli = conectarBD();

$carDefault = [
    "speed" => 0, # m/s
    "maxSpeed" => 0, # m/s
    "acceleration" => 0, # m/s^2
    "maxAcceleration" => 0,
    "tire" => "Normal", # either Normal, Rain or Snow
    "time" => 0, #in milliseconds
    "pilot" => 0, #range from 0 to 100
    "durability" => 100 #range from 0 to 100
];

$setor = array("id" => 0, "maxId" => 0, "type" => "default", "time" => 0);

$idCorrida = sqlQuery("SELECT MAX(corridaId) FROM corridas", $mysqli, "", []);
$weather = sqlQuery("SELECT metreologia FROM corridas", $mysqli, "", []);
$idPista = sqlQuery("SELECT corridaPistaId FROM corridas WHERE corridaId = ?", $mysqli, "i", [$idCorrida]);
$setor["id"] = sqlQuery("SELECT MIN(setorId) FROM setores WHERE setorPistaId = ?", $mysqli, "i", [$idPista]);
$setor["maxId"] = sqlQuery("SELECT MAX(setorId) FROM setores WHERE setorPistaId = ?", $mysqli, "i", [$idPista]);
$setor["time"] = setorTime($setor["id"]);





