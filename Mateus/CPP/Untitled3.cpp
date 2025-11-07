#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
typedef struct dados{
    double num=NULL;
	struct dados *prox=NULL;
};
int cores(int cor);
void menuPag(int *pagina);
dados* criarFicha();
dados* inserir(dados *listaNums);
void ler(dados *novo);
double medias();
main(){
	int op[3]={0,0,1};
	int *pagina=&op[2];
	int descartavel,k=0;
	double resultados[100][2];
	setlocale(LC_CTYPE,"portuguese");
	do{
		menuPag(pagina);
		op[0]=getch();
		if(op[0]==224){
			op[1]=getch();	
		}
		if(op[0]==0){
			getch();
		}
		switch(op[0]){
			case '1':
				resultados[k][0]=medias();
				resultados[k][1]='1';
				break;
			case '2':
				break;
			case '3':
				break;
			case '4':
				break;
			case '5':
				break;
			case '6':
				break;
			case '7':
				break;
			case '8':
				break;
			case '9':
				break;
			case 'a':
				break;
			case 'b':
				break;
			case 'c':
				break;
			case 'd':
				break;
			case 'e':
				break;
			case 'f':
				break;
			case 'g':
				break;
			case 'h':
				break;
			case 'i':
				break;
			case 'j':
				break;
			case 'k':
				break;
			case 'l':
				system("cls");
				cores(7);printf("********************** S A I U **********************");cores(0);
				break;
			default:
				if((op[0]==224&&op[1]==80)&&*pagina<15){
					++*pagina;
				}else{
					if((op[0]==224&&op[1]==72)&&*pagina>1){
						--*pagina;
					}else{
						system("cls");
						cores(7);printf("Erro!!\n");cores(0);
						if(op[0]>='A'&&op[0]<='Z'){
							cores(11);printf("Desative o ");cores(10);printf("'CAPS LOCK'");cores(11);printf(" ou apenas escreva em letra pequena.\n");
						}
						cores(9);printf("Pressione ");cores(8);printf("qualquer");cores(9);printf(" botão para voltar ao inicio.\n");
						*pagina=1;
						descartavel=getch();
						if(descartavel==224||descartavel==0){
							getch();	
						}
						fflush(stdin);
					}
				}
				break;
		}
		++k;
	}while(op[0]!='l');
}
int cores(int cor){
	HANDLE corTerminal = GetStdHandle(STD_OUTPUT_HANDLE);
	if(cor>=0&&cor<=14){
		switch(cor){
			case 0://cinzento-claro
				SetConsoleTextAttribute(corTerminal,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
				break;
			case 1://vermelho
				SetConsoleTextAttribute(corTerminal,FOREGROUND_RED);
				break;
			case 2://verde
				SetConsoleTextAttribute(corTerminal,FOREGROUND_GREEN);
				break;
			case 3://azul
				SetConsoleTextAttribute(corTerminal,FOREGROUND_BLUE);
				break;
			case 4://amarelo
				SetConsoleTextAttribute(corTerminal,FOREGROUND_RED|FOREGROUND_GREEN);
				break;
			case 5://azul-claro
				SetConsoleTextAttribute(corTerminal,FOREGROUND_GREEN|FOREGROUND_BLUE);
				break;
			case 6://roxo
				SetConsoleTextAttribute(corTerminal,FOREGROUND_RED|FOREGROUND_BLUE);
				break;
			case 7://vermelho-claro
				SetConsoleTextAttribute(corTerminal,FOREGROUND_RED|FOREGROUND_INTENSITY);
				break;
			case 8://verde-claro
				SetConsoleTextAttribute(corTerminal,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
				break;
			case 9://azul-médio
				SetConsoleTextAttribute(corTerminal,FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				break;
			case 10://amarelo-lite
				SetConsoleTextAttribute(corTerminal,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
				break;
			case 11://ciano
				SetConsoleTextAttribute(corTerminal,FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				break;
			case 12://roxo-claro
				SetConsoleTextAttribute(corTerminal,FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				break;
			case 13://branco
				SetConsoleTextAttribute(corTerminal,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				break;
			case 14://cinzento
				SetConsoleTextAttribute(corTerminal,FOREGROUND_INTENSITY);
				break;
		}
	}
}
void menuPag(int *pagina){
	system("cls");
	int pagTemp=*pagina;
	pagTemp-=1;
	char opcoes[21][65]={
	{" Calcular Média                                                "},{" Calcular Desvio Padrão                                        "},
	{" Procurar amigo                                                "},{" Alterar amigo                                                 "},
	{" Eliminar amigo                                                "},{" Aniversarios                                                  "},{" Sem opção...                                                  "},
	{" Sem opção...                                                  "},{" Sem opção...                                                  "},{" Sem opção...                                                  "},
	{" Sem opção...                                                  "},{" Sem opção...                                                  "},{" Sem opção...                                                  "},
	{" Sem opção...                                                  "},{" Sem opção...                                                  "},{" Sem opção...                                                  "},
	{" Sem opção...                                                  "},{" Sem opção...                                                  "},{" Sem opção...                                                  "},
	{" Sem opção...                                                  "},{" Sair da calculadora                                           "}
	};
	char opcoesSimb[21]={'1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l'};
	int segimentoCores[21]={4,2,11,9,1,12,7,4,2,11,9,1,12,7,4,2,11,9,1,12,7};
	cores(8);printf("******************* M E N U   C A L C U L A D O R A *******************\n*                                                                     *\n");
	cores(8);printf("*");cores(5);printf("   %c ",opcoesSimb[0+pagTemp]);cores(14);printf("-");cores(segimentoCores[0+pagTemp]);printf("%s",opcoes[0+pagTemp]);cores(8);printf("*\n");	
	cores(8);printf("*");cores(5);printf("   %c ",opcoesSimb[1+pagTemp]);cores(14);printf("-");cores(segimentoCores[1+pagTemp]);printf("%s",opcoes[1+pagTemp]);cores(8);printf("*\n");	
	cores(8);printf("*");cores(5);printf("   %c ",opcoesSimb[2+pagTemp]);cores(14);printf("-");cores(segimentoCores[2+pagTemp]);printf("%s",opcoes[2+pagTemp]);cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   %c ",opcoesSimb[3+pagTemp]);cores(14);printf("-");cores(segimentoCores[3+pagTemp]);printf("%s",opcoes[3+pagTemp]);cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   %c ",opcoesSimb[4+pagTemp]);cores(14);printf("-");cores(segimentoCores[4+pagTemp]);printf("%s",opcoes[4+pagTemp]);cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   %c ",opcoesSimb[5+pagTemp]);cores(14);printf("-");cores(segimentoCores[5+pagTemp]);printf("%s",opcoes[5+pagTemp]);cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   %c ",opcoesSimb[6+pagTemp]);cores(14);printf("-");cores(segimentoCores[6+pagTemp]);printf("%s",opcoes[6+pagTemp]);cores(8);printf("*\n");
	cores(8);printf("*                                                                     *\n***********************************************************************\n");
	if(pagTemp==0){
		cores(14);printf("^ cima");cores(13);printf("                                                          baixo v\n");	
	}else{
		if(pagTemp==14){
			cores(13);printf("^ cima");cores(14);printf("                                                          baixo v\n");	
		}else{
			cores(13);printf("^ cima");cores(13);printf("                                                          baixo v\n");	
		}
	}
	cores(0);
}

dados* criarFicha(){
	dados *novo =(dados*)malloc(sizeof(dados));
	return novo;
}
dados* inserir(dados *listaNums){
	dados *novo=criarFicha();
	ler(novo);
	if(listaNums==NULL){
		novo->prox=NULL;
		listaNums=novo;
	}else{
		dados* aux=listaNums;
		while(aux->prox!=NULL){
			aux=aux->prox;	
		}
		novo->prox=NULL;
		aux->prox=novo;	
	}
	return(listaNums);
}
void ler(dados *novo){
	system("cls");   
	cores(8);printf("**************** M E N U   I N S E R E   N U M E R O S ****************\n\n");
	cores(11);printf("   Numero - ");
	cores(0);scanf("%d",&novo->num);
	fflush(stdin);
}
double medias(){
	dados* listaNums;
	int temp;
	double resultado=0;
	do{	
		fflush(stdin);
		listaNums=inserir(listaNums);
		cores(9);printf("   ESCAPE para parar de inserir numeros.\n\n");
	}while(getch()!=27);
	return(resultado);
	//INACABADO DEPOIS DE 4 HRS
}

