#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

void jogo(){
	int op, l[6]={0,1,0,0,0,0};
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
				printf("Tente adivinhar o número aleatório entre %d e %d\n\nTentaviva número - %d\n\n", l[4], l[5], l[1]);
				scanf("%d", &l[2]);
				if(l[2]==l[4]&&l[4]!=l[0]||l[2]==l[5]&&l[5]!=l[0]){
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
							system("cls");
							printf("\nAcertaste, era mesmo o número %d!\n\n", l[0]);
							l[1]=1;		
						}else{
							++l[1];
						}	
					}
				}
			}while(l[2]!=l[0]);
		}else{
			printf("OK Adeus");
			op=0;
		}
	}while(op);
}

main(){
	setlocale(LC_CTYPE,"portuguese");
	jogo();
}
