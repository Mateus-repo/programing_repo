#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#define ROND_MAX 10
#define MAX 100
#define MIN 1

int i, op=0, ro=0, l[6]={0,1,0,0,0,0}, r[ROND_MAX];

void jogo(){

	/*

	*/
	for(i=0;i<ROND_MAX;i++){
			r[i]=0;	
	}
	for(i=0;i<6;i++){
		if(i!=1){
			l[i]=0;
		}else{
			l[i]=1;	
		}
	}
	i='1';
	do{
		if(ro!=0){
			printf("Se quiser jogar mais uma vez, clique em qualquer tecla menos no 0 a menos se não quiser jogar mais.\n\n");
			op=getch();
		}
		if(op!='0'){
			do{
				srand(time(NULL));
				l[0]=rand()%MAX+MIN;
				l[4]=MIN;
				l[5]=MAX;
				system("cls");
				do{
					printf("==--JOGADOR %d--==\n\nTente adivinhar o número aleatório entre %d e %d\n\nTentaviva número - %d\n\n", ro, l[4], l[5], l[1]);
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
								r[ro]=l[1];
								printf("\nAcertaste, era mesmo o número %d e em %d tentativas!\n\n", l[0], r[ro]);
								ro++;
								l[1]=1;
							}else{
								++l[1];
								system("cls");
							}
						}
					}
				}while(l[2]!=l[0]);
				printf("Mais um rodada?\n\n 1-Sim\n 0-Não\n");
				i=getch();
			}while(i=='1');
		}else{
			printf("OK Adeus\n\n");
			op=0;
		}
	}while(op!=0&&ro!=ROND_MAX);
	if(ro!=0){
		for(op=0;op<ROND_MAX;op++){
			if(op==0&&r[op+1]==0){
				ro=op;
				l[3]=r[op];
			}else{
				if(r[op]!=0&&r[op+1]!=0){
					if(r[op]<r[op+1]){
						ro=op;
						l[3]=r[op];
					}
				}
			}
		}
		system("cls");
		printf("======----------Ganhou o Jogador %d----------======\n\n==--O Jogador %d adivinhou em apenas %d tentivas--==\n\n", ro, ro, l[3]);
	}
}

main(){
	int i[2]={0,0};
	setlocale(LC_CTYPE,"portuguese");
	while(i[1]!='0'){
		printf("Quer jogar uma partida?\n\nSe sim clique no 1, senão clique no 0.\n\n");
		i[0]=getch();
		if(i[0]!='0'&&i[0]!='1'){
			printf("Erro, não clicou no botão certo, tente de novo.\n\n");
		}else{
			if(i[0]=='0'){
				printf("Adeus\n");
				return 0;
			}
			if(i[0]=='1'){
				jogo();
			}
		}
	}
}
