<?php
$prato = $_POST["Prato"];
$sobremesa = $_POST["Sobremesa"];
$bebida = $_POST["Bebida"];
switch ($prato) {
    case 180:
        $pratoName = "Vegetariano";
        break;
    case 230:
        $pratoName = "Peixe";
        break;
    case 250:
        $pratoName = "Frango";
        break;
    case 350:
        $pratoName = "Carne";
        break;
}
switch ($sobremesa) {
    case 75:
        $sobremesaName = "Abacaxi";
        break;
    case 110:
        $sobremesaName = "Gelado diet";
        break;
    case 170:
        $sobremesaName = "Mouse diet";
        break;
    case 200:
        $sobremesaName = "Mouse chocolate";
        break;
}
switch ($bebida) {
    case 20:
        $bebidaName = "Cha";
        break;
    case 70:
        $bebidaName = "Sumo de laranja";
        break;
    case 100:
        $bebidaName = "Sumo de melão";
        break;
    case 65:
        $bebidaName = "Refrigerante";
        break;
}
echo  "Total de calorias de uma refeição: ".$prato+$sobremesa+$bebida."<br>"."Produtos pedidos: ".$pratoName.", ".$bebidaName." e ".$sobremesaName.".";
?>