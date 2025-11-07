#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

void jogo(){
	int linha[3]={0,0,0};
	srand(time(NULL));
	linha[0]=rand()%100+1;
	system("cls");
	do{
		printf("Tente adivinhar o numero aleatorio entre 1 e 100\n\nTentaviva numero - %d\n\n", ++linha[1]);
		scanf("%d", &linha[2]);
		if(linha[2]<linha[0]){
			printf("\nO numero e maior\n\n");
		}
		if(linha[2]>linha[0]){
			printf("\nO numero e menor\n\n");
		}
		if(linha[2]==linha[0]){
			printf("\nAcertaste, era mesmo o numero %d!\n\n", linha[0]);	
		}
	}while(linha[2]!=linha[0]);
}

main(){
	int op;
	do{
		printf("Se quiser jogar clique em qualquer tecla menos no 0 a menos se n�o quiser jogar?\n\n");
		op=getch();
		if(op!='0'){
			jogo();
		}else{
			printf("OK Adeus");
			op=0;
		}
	}while(op!=0);
}
