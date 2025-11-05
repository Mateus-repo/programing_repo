var play = true;
var player = true;
var tabuleiro = new Array(-1, -1, -1, -1, -1, -1, -1, -1, -1);

if (window.localStorage) {
  var vitorias = new Array()
  console.log(vitorias[0]=localStorage.getItem("playerTrueWins2"));
  vitorias[1]=localStorage.getItem("playerFalseWins2");
console.log(localStorage.getItem("playerTrueWins2"));
  console.log(vitorias);
}else{
  console.log('Erro!'+Error().lineNumber);
}

if (localStorage.playerTrueWins2 === undefined) {
  localStorage.setItem("playerTrueWins2", 0);
}else{
  console.log('Já existe na playerTrueWins storage');
  alert(localStorage.playerTrueWins2);
}


if (localStorage.playerFalseWins2 === undefined) {
  localStorage.setItem("playerFalseWins2", 0);
}else{
  console.log('Já existe na playerFalseWins storage');
}

function winCounter() {
  $('#xWins').text(vitorias[true])
  $('#oWins').text(vitorias[false])
}

document.addEventListener('DOMContentLoaded', winCounter(), false);

$('table tr td').click(function () {
  if (tabuleiro[$(this).data('index')] == -1 && play) {
    tabuleiro[$(this).data('index')] = player;
    $(this).css('background-image', 'url(imagens/' + (player ? 'x' : 'o') + '.png)');
    console.log('Tabuleiro: ' + tabuleiro);
    setTimeout('whoWon()', 10);
    setTimeout(() => {
      player = !player;
    }, 10);
    $('#reset').css('visibility', 'visible');
  }
});

$('#reset').click(function () {
  location.reload();
})

function isWinner() {
  for (var i = 0; i < 9; i++) {
    if (tabuleiro[i] != -1 && tabuleiro[i] == tabuleiro[++i] && tabuleiro[i] == tabuleiro[++i]) {
      return 1;
    }
  }
  for (var i = 0; i < 3; i++) {
    if (tabuleiro[i] != -1 && tabuleiro[i] == tabuleiro[i + 3] && tabuleiro[i] == tabuleiro[i + 6]) {
      return 1;
    }
  }
  if (tabuleiro[0] != -1 && tabuleiro[0] == tabuleiro[4] && tabuleiro[4] == tabuleiro[8]) {
    return 1;
  }
  if (tabuleiro[2] != -1 && tabuleiro[2] == tabuleiro[4] && tabuleiro[4] == tabuleiro[6]) {
    return 1;
  }
}
function whoWon() {
  if (isWinner()) {
    //vitorias[player]++;
    console.log('Vitorias do Galo: ' + vitorias[true] + '; e vitórias do ovo: ' + vitorias[false] +'.');
    winCounter();
    alert((player ? 'Galo ganhou pela ' : 'Ovo ganhou pela') + vitorias[parseInt(player)] + ' vez!');
    play = false;
  }
}