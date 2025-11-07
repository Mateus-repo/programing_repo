/*----------------------Constantes-----------------------*/
const defaultTimeout = 300;
const defaultTemporizador = 330;
const defaultTimeToLookSeconds = 30 //em segundos (s)
/*-------------------------------------------------------*/

/*-----------------------Variaveis-----------------------*/
var cardNum = 32;// 8 ou 32
var tabuleiro = Array();
var primeiraCarta = true;
var cartaEscolhida1;
var cartaEscolhida2;
var pontos = 0;
var numJogadas = 0;
var documentState = false;
var temporizador = defaultTemporizador;
var intervaloTempo;
var stopTimer=false;
/*-------------------------------------------------------*/

/*-------------------Funções e JQuery--------------------*/

function mainSize(){
    $("#main").css("width", cardNum>8 ? 1360 : 700 + "px")
    $("#main").css("height", cardNum>8 ? 830 : 420 + "px")
}

function criarCartas() {
  for (let i = 0; i < cardNum; i++) {
    const cartaClass = i < (cardNum>8 ? 8 : 4) ? 'topCard' : '';
    const cartaHTML = `<div class="carta ${cartaClass}" data-index="${i}" id="c${i}"></div>`;
    $('#main').append(cartaHTML);
  }
}

function arrayUpdate(){
    for (var tempVar1 = 0, tempVar2 = 1; tempVar1 < cardNum; tempVar1++) {
        tabuleiro[tempVar1] = tempVar2;
        if ((tempVar1 + 1) % 2 == 0) {
            tempVar2++;
        }
    }
}

function criaPag(){
    $('#main').empty(); 
    mainSize();
    criarCartas();
    arrayUpdate();
}
function esconde(id) {
    $("#c" + id).css("transform", "rotateY(90deg)");
    setTimeout(() => {
        $("#c" + id).css("background-image", "url(assets/back.png)");
        $("#c" + id).css("transform", "rotateY(0deg)");
    }, defaultTimeout);
}

function troca(p1, p2) {
    temp = tabuleiro[p1];
    tabuleiro[p1] = tabuleiro[p2];
    tabuleiro[p2] = temp;
}

function baralha(n) {
    for (i = 1; i <= n; i++) {
        troca(parseInt(Math.random() * cardNum), parseInt(Math.random() * cardNum));
    }
}

function scoreCounter() {
    localStorage.setItem("pontos", pontos);
    setTimeout(() => {
        if (pontos != 1) {
        console.log("Pontuação: " + pontos + " pontos");
        $("#score").text("Pontuação : " + pontos + " pontos");
        } else {
        console.log("Pontuação: " + pontos + " ponto");
        $("#score").text("Pontuação : " + pontos + " ponto");
        }
    }, defaultTimeout);
}

function fim() {
    for (var i = 0; i < cardNum; i++) {
        if (tabuleiro[i] > 0) {
            return false;
        }
    }
    console.log("Game Ended");
    alert("Parabéns por acabares o jogo em " + numJogadas + " jogadas");
    return true;
}

function formatTime(seconds) {
    let minutes = Math.floor(seconds / 60);
    let secs = seconds % 60;
    if(secs>=10){
        return (minutes+":"+secs);
    }else{
        return (minutes+":0"+secs);
    }
    
}

function temporizadorFunction(){
    intervaloTempo = setInterval(function (){
        if(stopTimer){
            clearInterval(intervaloTempo);
            temporizador=defaultTemporizador;
            scoreCounter();
        }
        if(temporizador<0){
            clearInterval(intervaloTempo);
            scoreCounter();
            documentState=false;
            if(fim()==false){
                alert("Perdes-te! Que pena... fizeste " + (--numJogadas) + " jogadas!")
            }
        }else{
            if (pontos != 1) {
                $("#score").text("Pontuação : " + pontos + " pontos     " + formatTime(temporizador));
            } else {
                $("#score").text("Pontuação : " + pontos + " ponto     " + formatTime(temporizador));
            }
        }
        temporizador--;
    },1000);
}

function gameStart() {
    if (documentState == true) {
        documentState = false;
        numJogadas++;
        temporizadorFunction();
        $(".carta").each(function () {
            $(this).css("transform", "rotateY(90deg)");
            setTimeout(() => {
                $(this).css("background-image", "url(assets/" + Math.abs(tabuleiro[$(this).data("index")]) + ".png)");
                $(this).css("transform", "rotateY(0deg)");
            }, defaultTimeout);
        });

        setTimeout(function() {
            $(".carta").each(function () {
                esconde($(this).data("index"));
            });
            documentState = true;
            
        }, defaultTimeToLookSeconds*1000);
    }

};

$(document).on("click", ".carta", function ()  {
    if(documentState==true){
        if (fim() == false) {
            console.log("Clicou em " + $(this).data("index") + " com valor de " + tabuleiro[$(this).data("index")]);
            if(cardNum!=8&&numJogadas==0){
                gameStart();
            }else{
                if (tabuleiro[$(this).data("index")] > 0 && $(this).data("index") != cartaEscolhida1) {
                    $(this).css("transform", "rotateY(90deg)");
                    setTimeout(() => {
                        $(this).css("background-image","url(assets/" + Math.abs(tabuleiro[$(this).data("index")]) + ".png)");
                        $(this).css("transform", "rotateY(0deg)");
                    }, defaultTimeout);
                    console.log(tabuleiro[$(this).data("index")]);
                    numJogadas++;
                    if (primeiraCarta) {
                        cartaEscolhida1 = $(this).data("index");
                        primeiraCarta = false;
                        console.log("primeiraCarta = false");
                    } else {
                        cartaEscolhida2 = $(this).data("index");
                        if (tabuleiro[cartaEscolhida1] == tabuleiro[cartaEscolhida2]) {
                            tabuleiro[cartaEscolhida1] *= -1;
                            tabuleiro[cartaEscolhida2] *= -1;
                            ++pontos;
                            if(cardNum==8){
                                scoreCounter();
                            }
                            setTimeout(() => {
                                fim();
                            }, defaultTimeout * 2);
                        } else {
                            setTimeout("esconde(" + cartaEscolhida1 + ")", defaultTimeout * 2.2);
                            setTimeout("esconde(" + cartaEscolhida2 + ")", defaultTimeout * 4.4);
                            if(cardNum!=8){
                                temporizador-=30;
                            }
                        }
                        primeiraCarta = true;
                        console.log("primeiraCarta = true");
                        cartaEscolhida1 = -1;
                        cartaEscolhida2 = -1;
                    }
                }
            }
        }
        console.log(tabuleiro);
    }
});

$("document").ready(function () {
    criaPag();
    baralha(2*cardNum);
    $("#difficultyChanger").text("Mudar Dificuldade para " + (cardNum > 8 ? "facíl" : "difícil")); 
    if (isNaN(localStorage.getItem("pontos")) || localStorage.getItem("pontos") == null) {
        console.log("localStorage pontos não era um numero era " + localStorage.getItem("pontos"));
        localStorage.setItem("pontos", 0);
    }
    pontos = localStorage.getItem("pontos");
    console.log("localStorage pontos é " + localStorage.getItem("pontos"));
    scoreCounter();
    documentState = true;
    setTimeout(function(){
        $('.preLoader').css("opacity", "0");
        $('.preLoader').css("visibility", "hidden");
    }, 1000);
});

$("#restart").click(function () {
    if(documentState==true){
        documentState=false;
    }
    stopTimer=true;
    var tempVar = 0;
    const intervalID = setInterval(function () {
        esconde(tempVar);
        ++tempVar;
        console.log(tempVar);
        if (tempVar >= cardNum) {
            clearInterval(intervalID);
        }
    }, cardNum>8?50:200);
    numJogadas = 0;
    arrayUpdate();
    baralha(2*cardNum);
    primeiraCarta = true;
    console.log(tabuleiro);
    temporizador = defaultTemporizador;
    
    setTimeout(function(){
        documentState=true;
        stopTimer=false;
    }, (cardNum>8?50:200)*cardNum+100);
});

$("#difficultyChanger").click(function(){
    $('.preLoader').css("opacity", "100");
    $('.preLoader').css("visibility", "visible");
    stopTimer=true;
    
    setTimeout(function(){
        $('#main').empty(); 
        if(documentState==true){
            documentState=false;
        }
            cardNum = (cardNum>8 ? 8 : 32);
            $("#difficultyChanger").text("Mudar Dificuldade para " + (cardNum > 8 ? "fácil" : "difícil")); 
            numJogadas = 0;
            criaPag();
            baralha(2*cardNum);
            primeiraCarta = true;
            console.log(tabuleiro);
            temporizador = defaultTemporizador;
            numJogadas=0;
        
    }, 1000);
    
    setTimeout(function(){
        $('.preLoader').css("opacity", "0");
        $('.preLoader').css("visibility", "hidden");
        stopTimer=false;
        documentState=true;
    }, 1500);
    
});

$("#scoreReset").click(function () {
    localStorage.setItem("pontos", 0);
    pontos = localStorage.getItem("pontos");
    scoreCounter();
});

/*-------------------------------------------------------*/