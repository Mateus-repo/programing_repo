<?php
    $radio = $_POST["pay_method"];
    $quantity = $_POST["quantitiy"];
    define ("PRODUTO", 5.99);
    function quantEcho($pepinoNum){
        if($pepinoNum==1){
            echo $pepinoNum." pepino é ";
        }else{
            echo $pepinoNum." pepinos são ";
        }
        
    }
    if($radio){
        quantEcho($quantity);
        switch($radio){
            case "pay_check":
                echo PRODUTO * $quantity * 0.90."€";
                break;
            case "pay_credit":
                echo PRODUTO * $quantity * 0.95."€";
                break;
            case "pay_no_juros":
                echo PRODUTO * $quantity."€";
                break;
            case "pay_juros_10":
                echo PRODUTO * $quantity * 1.10."€";
                break;
        }
    }
?>
