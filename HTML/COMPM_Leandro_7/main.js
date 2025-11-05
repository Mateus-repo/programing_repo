var play = true;
let player = true;
var tabuleiro = new Array(-1, -1, -1, -1, -1, -1, -1, -1, -1);

$('table tr td').click(function () {
  if (tabuleiro[$(this).data('index')] == -1 && play) {
    tabuleiro[$(this).data('index')] = player;
    $(this).css('background-image', 'url(imagens/' + (player ? 'x' : 'o') + '.png)');
    console.log('Tabuleiro: ' + tabuleiro);

    setTimeout('whoWon()',50);



/*

    setTimeout(function () {
      whoWon();
      
    }, 50);
    */
    //player = !player;
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
  //var global player;
  if (isWinner()) {
    alert(player ? 'Galo' : 'Ovo');
    play = false;
    $('#reset').css('visibility', 'visible');
  }
    player!=player;
 
}




