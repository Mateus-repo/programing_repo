#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void ze(){
	printf("ola");
}

main(){
	int posicoes[9]={0,0,0,0,0,0,0,0,0};
	printf("***********JOGO DO GALO***********\nEm que posicao quer jogar?\n");
	scanf("%d", &posicoes[1]);
	printf("%d", posicoes[0]);
}
