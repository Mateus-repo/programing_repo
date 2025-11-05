#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#define ROND_MAX 10

void jogo(){
	int op, ro=0, l[6]={0,1,0,0,0,0}, r[ROND_MAX];
	do{
		printf("Se quiser jogar clique em qualquer tecla menos no 0 a menos se não quiser jogar.\n\n");
		op=getch();
		if(op!='0'){
			srand(time(NULL));
			l[0]=rand()%100+1;
			system("cls");
			l[4]=1;
			l[5]=100;
			do{
				printf("Jogador %d, tente adivinhar o número aleatório entre %d e %d\n\nTentaviva número - %d\n\n", ro, l[4], l[5], l[1]);
				scanf("%d", &l[2]);
				if(l[2]==l[4]||l[2]==l[5]){
					printf("\n---ERRO---\n\nEste número já foi jogado , tenta outro.\n\n");
				}else{
					if(l[2]<l[4]||l[2]>l[5]){
						printf("\n---ERRO---\n\nEste número não esta na escala, tenta outro.\n\n");
					}else{
						if(l[2]<l[0]){
							printf("\nO número é maior.\n\n");
							l[4]=l[2];
						}
						if(l[2]>l[0]){
							printf("\nO número é menor.\n\n");
							l[5]=l[2];
						}
						if(l[2]==l[0]){
							printf("\nAcertaste, era mesmo o número %d!\n\n", l[0]);
							r[ro]=l[1];
							printf("%d\n\n", r[ro]);
							ro++;
							l[1]=0;
						}else{
							++l[1];
						}
					}
				}
			}while(l[2]!=l[0]);
		}else{
			printf("OK Adeus\n\n");
			op=0;
		}
	}while(op!=0&&ro!=ROND_MAX);
	ro=0;
	for(op=0;op<ROND_MAX;op++){
		if(r[op]<r[op+1]){
			if(op%2==0){
				ro=2;
			}else{
				ro=1;
			}
			l[3]=r[op];
		}
	}
	printf("Ganhou o Jogador%d\n\nFizeste em %d tentivas\n", ro, l[3]);
}

main(){
	setlocale(LC_CTYPE,"portuguese");
	jogo();
}
