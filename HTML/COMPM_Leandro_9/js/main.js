/*----------------------Constantes-----------------------*/
const defaultTimeout = 300;
/*-------------------------------------------------------*/

/*-----------------------Variaveis-----------------------*/
var tabuleiro = Array(1, 1, 2, 2, 3, 3, 4, 4);
var primeiraCarta = true;
var cartaEscolhida1;
var cartaEscolhida2;
var y = 0;
var pontos = 0;
var numJogadas = 0;
/*-------------------------------------------------------*/

/*-------------------Funções e JQuery--------------------*/
function esconde(id) {
    $('#c' + id).css('transform', 'rotateY(90deg)');
    setTimeout(() => {
        $('#c' + id).css('background-image', 'url(assets/-1.png)');
        $('#c' + id).css('transform', 'rotateY(0deg)')
    }, defaultTimeout);
}

function troca(p1, p2) {
    temp = tabuleiro[p1];
    tabuleiro[p1] = tabuleiro[p2];
    tabuleiro[p2] = temp;
}

function baralha(n) {
    for (i = 1; i <= n; i++) {
        troca(parseInt(Math.random() * 7), parseInt(Math.random() * 7));

    }
}

function scoreCounter() {
    localStorage.setItem("pontos", pontos);
    setTimeout(() => {
        if (pontos != 1) {
            console.log("Pontuação: " + pontos + " pontos");
            $('#score').text("Pontuação : " + pontos + " pontos");
        } else {
            console.log("Pontuação: " + pontos + " ponto");
            $('#score').text("Pontuação : " + pontos + " ponto");
        }
    }, defaultTimeout);

}

function fim() {

    for (var i = 0; i < 8; i++) {
        if (tabuleiro[i] > 0) {
            return (false);
        }
    }
    console.log("Game Ended");
    alert("Parabéns por acabares o jogo em " + numJogadas + " jogadas");
    return (true);
};

$('.carta').click(function () {
    if (fim() == false) {
        console.log("Clicou em " + $(this).data('index') + " com valor de " + tabuleiro[$(this).data('index')])
        if (tabuleiro[$(this).data('index')] > 0 && $(this).data('index')!=cartaEscolhida1) {
            $(this).css('transform', 'rotateY(90deg)');
            setTimeout(() => {
                $(this).css('background-image', 'url(assets/' + tabuleiro[$(this).data('index')] + '.png)');
                $(this).css('transform', 'rotateY(0deg)')
            }, defaultTimeout);
            console.log(tabuleiro[$(this).data('index')])
            numJogadas++;
            if (primeiraCarta) {

                cartaEscolhida1 = $(this).data('index');
                primeiraCarta = false;
                console.log("primeiraCarta = false");

            } else {

                cartaEscolhida2 = $(this).data('index');
                if (tabuleiro[cartaEscolhida1] == tabuleiro[cartaEscolhida2]) {
                    setTimeout(() => {
                        tabuleiro[cartaEscolhida1] *= -1;
                        tabuleiro[cartaEscolhida2] *= -1;
                        ++pontos;
                        scoreCounter();
                    }, defaultTimeout);
                    setTimeout(() => {
                        fim();
                    }, defaultTimeout * 2);


                } else {
                    setTimeout('esconde(' + cartaEscolhida1 + ')', defaultTimeout*2.2);
                    setTimeout('esconde(' + cartaEscolhida2 + ')', defaultTimeout*4.4);
                }
                primeiraCarta = true;
                console.log("primeiraCarta = true")
                cartaEscolhida1 = -1
                cartaEscolhida2 = -1
            }
        }
    }
    console.log(tabuleiro)
});

function restartCards(){
    setInterval(function (){
        var tempVar1=0;
        setTimeout(() => {
            $('#c' + tempVar).css('transform', 'rotateY(90deg)');
            setTimeout(() => {
                $('#c' + tempVar1).css('background-image', 'url(assets/-1.png)');
                $('#c' + tempVar1).css('transform', 'rotateY(0deg)');
            }, 100); 
        }, 200);
        tempVar1++;
        if(tempVar1>=8){
            return(0);
        }
    }, 100);
}

$('document').ready(function () {
    baralha(10);
    if (isNaN(localStorage.getItem("pontos"))){
        console.log("localStorage pontos não era um numero era " + localStorage.getItem("pontos"));
        localStorage.setItem("pontos", 0);
    }
    pontos = localStorage.getItem("pontos");
    console.log("localStorage pontos é " + localStorage.getItem("pontos"));
    scoreCounter();
});


$('#restart').click(function() {
    restartCards();
    var tempVar2 = 1;
    
        
       
    numJogadas=0;
    for(var tempVar = 0; tempVar <8; tempVar++){
        tabuleiro[tempVar]=tempVar2;
        if((tempVar+1)%2==0){
            tempVar2++;
        }
    };
    baralha(10);
    primeiraCarta = true;
    console.log(tabuleiro)
});

$('#scoreReset').click(function(){
    localStorage.setItem("pontos", 0);
    pontos = localStorage.getItem("pontos");
    scoreCounter();
});
/*-------------------------------------------------------*/