/* trabalho prático de avaliação: Máquina de venda de produtos
Notas:
	- usar programação procedimental
	- usar parâmetros
	- NUNCA usar varáveis globais
	
Versões:
	A 	- Venda de 3 tipos de produtos: (bebidas, sandes, doces)
		- Menus (nível 1)
		- Deve indicar qual o produto comprado e quanto custa
		- Deve permitir voltar a comprar
	
	B 	- Implementa a versão A
		- Menus (nível 2)
		- Permite pedir moedas e devolver troco
		
	C 	- Implementa a versão B
		- Permite comprar mais que um produto

NOME: Kyryl Ostapchuk
VERSÃO: A;B;C.
*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include "defines.cpp"

void menu(){
	system("cls");
	printf("******************* M E N U *******************\n");
	printf("1 - Bebidas\n");
	printf("2 - Comidas\n");
	printf("3 - Doces\n");
	printf("Enter - Sair\n");	
}
void menuInt(int op){
	char *bcd[3]={"B E B I D A S","C O M I D A S","D O C E S"};
	system("cls");
	printf("******************* M E N U  %s *******************\n", bcd[op]);
	printf("1 - Quente\n");
	printf("2 - Frio\n");
	printf("Enter - Sair\n");
}
void menuSegPla(int quantDeOP, int opPrimNiv, int QuentOFrio){
	char *bcd[3]={"B E B I D A S","C O M I D A S","S O B R E M E S A S"};
	char *qf[2]={"Q U E N T E S","F R I A S"};
	char *menu[DIM_MENU][DIM_INT][DIM_PRODUTO] = {
		{ {"CAFE", "LEITE", "CAPUCHINO"},{"COCA COLA","SUMO","Agua"} },
		{ {"STAKE","SOPA","ARROZ COM CARNE"},{"SANDES MISTO", "PAO COM CHORISO", "SANDES ATUM"} },
		{ {"CREME DE LEITE", "BROWNIES", "CREPE DE CHOCOLATE"},{"MUSSE DE CHOCOLATE", "BABA DE CAMELO", "BOLO DE BOLACHA"} }
	};
	float prices[DIM_MENU][DIM_INT][DIM_PRODUTO] = {
		{ {1, 1, 1.5},{2, 1.5, 1} },
		{ {3, 1.5, 2.5},{1.5, 2, 1} },
		{ {1.5, 1, 2},{2, 2.5, 1.5} }
	};	
	system("cls");
	printf("******************* M E N U  %s %s*******************\n", bcd[opPrimNiv], qf[QuentOFrio]);
	for(int i=1;i<=quantDeOP;i++){
		printf("%d - %s - %.2f€\n", i, menu[opPrimNiv][QuentOFrio][i-1], prices[opPrimNiv][QuentOFrio][i-1]);	
	}
	printf("Enter - Sair\n");
}
/*sistema de faturas*/
void mostraProdutos(int produtos[DIM_MENU][DIM_INT][DIM_PRODUTO],float prices[DIM_MENU][DIM_INT][DIM_PRODUTO]){
	char *menu[DIM_MENU][DIM_INT][DIM_PRODUTO] = {
		{ {"CAFE", "LEITE", "CAPUCHINO"},{"COCA COLA","SUMO","Agua"} },
		{ {"STAKE","SOPA","ARROZ COM CARNE"},{"SANDES MISTO", "PAO COM CHORISO", "SANDES ATUM"} },
		{ {"CREME DE LEITE", "BROWNIES", "CREPE DE CHOCOLATE"},{"MUSSE DE CHOCOLATE", "BABA DE CAMELO", "BOLO DE BOLACHA"} }
	};
	for(int i=0;i<DIM_MENU;i++){
		for(int j=0;j<DIM_INT;j++){
			for(int k=0;k<DIM_PRODUTO;k++){
				if(produtos[i][j][k]!=0){
					printf("%s %d %.2f\n", menu[i][j][k], produtos[i][j][k], produtos[i][j][k]*prices[i][j][k]);
				}
			}
		}
	}
}
float somaTotal(int produtos[DIM_MENU][DIM_INT][DIM_PRODUTO],float prices[DIM_MENU][DIM_INT][DIM_PRODUTO]){
	float total=0;
	for(int i=0;i<DIM_MENU;i++){
		for(int j=0;j<DIM_INT;j++){
			for(int k=0;k<DIM_PRODUTO;k++){
				if(produtos[i][j][k]!=0)
					total+=produtos[i][j][k]*prices[i][j][k];
			}
		}
	}
	return(total);
}


main(){
	int banks=8;
	float precoTotal=0.0;
	int opcao,opcao1,opcao2;
	double bank[banks] = {0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00, 2.00};
	float prices[DIM_MENU][DIM_INT][DIM_PRODUTO] = {
	{ {1, 1, 1.5},{2, 1.5, 1} },
	{ {3, 1.5, 2.5},{1.5, 2, 1} },
	{ {1.5, 1, 2},{2, 2.5, 1.5} }
	};
	int produtos[DIM_MENU][DIM_INT][DIM_PRODUTO]={};
	setlocale(LC_CTYPE,"portuguese");
	do{
		menu();
		opcao=getch();
		switch(opcao){
			case '1':
				do{
					menuInt(0);
					opcao1=getch();
					switch(opcao1){
							case '1':
								do{
									menuSegPla(DIM_PRODUTO,BEBIDA,QUENTE);
									opcao2=getch();
									switch(opcao2){
										case '1':produtos[BEBIDA][QUENTE][CAFE]++;
												break;
										case '2':produtos[BEBIDA][QUENTE][LEITE]++;
												break;
										case '3':produtos[BEBIDA][QUENTE][CAPUCHINO]++;
												break;
										default:;										
									}									
								}while(opcao2!=13);
								break;
							case '2':
								do{
									menuSegPla(DIM_PRODUTO,BEBIDA,FRIO);
									opcao2=getch();
									switch(opcao2){
										case '1':produtos[BEBIDA][FRIO][COCA_COLA]++;
												break;
										case '2':produtos[BEBIDA][FRIO][SUMO]++;
												break;
										case '3':produtos[BEBIDA][FRIO][Agua]++;
												break;
										default:;
									}									
								}while(opcao2!=13);
								break;
							default:;
					}
				}while(opcao1!=13);
				break;
			case '2':
				do{
					menuInt(1);
					opcao1=getch();
					switch(opcao1){
							case '1':
								do{
									menuSegPla(DIM_PRODUTO,COMIDA,QUENTE);
									opcao2=getch();
									switch(opcao2){
										case '1':produtos[COMIDA][QUENTE][STAKE]++;
												break;
										case '2':produtos[COMIDA][QUENTE][SOPA]++;
												break;
										case '3':produtos[COMIDA][QUENTE][ARROZ_COM_CARNE]++;
												break;
										default:;
									}									
								}while(opcao2!=13);
								break;
							case '2':
								do{
									menuSegPla(DIM_PRODUTO,COMIDA,FRIO);
									opcao2=getch();
									switch(opcao2){
										case '1':produtos[COMIDA][FRIO][SANDES_MISTO]++;
												break;
										case '2':produtos[COMIDA][FRIO][PAO_COM_CHORISO]++;
												break;
										case '3':produtos[COMIDA][FRIO][SANDES_ATUM]++;
												break;
										default:;
									}									
								}while(opcao2!=13);
								break;
							default:;		
					}
				}while(opcao1!=13);
				break;
			case '3':
				do{
					menuInt(2);
					opcao1=getch();
					switch(opcao1){
							case '1':
								do{
									menuSegPla(DIM_PRODUTO,SUBREMESAS,QUENTE);
									opcao2=getch();
									switch(opcao2){
										case '1':produtos[SUBREMESAS][QUENTE][CREME_DE_LEITE]++;
												break;
										case '2':produtos[SUBREMESAS][QUENTE][BROWNIES]++;
												break;
										case '3':produtos[SUBREMESAS][QUENTE][CREPE_DE_CHOCOLATE]++;
												break;
										default:;
									}									
								}while(opcao2!=13);
								break;
							case '2':
								do{
									menuSegPla(DIM_PRODUTO,SUBREMESAS,FRIO);
									opcao2=getch();
									switch(opcao2){
										case '1':produtos[SUBREMESAS][FRIO][MUSSE_DE_CHOCOLATE]++;
												break;
										case '2':produtos[SUBREMESAS][FRIO][BABA_DE_CAMELO]++;
												break;
										case '3':produtos[SUBREMESAS][FRIO][BOLO_DE_BOLACHA]++;
												break;
										default:;
									}									
								}while(opcao2!=13);
								break;
							default:;		
					}
				}while(opcao1!=13);
				break;				
		}
	}while(opcao!=13);
	system("cls");
	mostraProdutos(produtos,prices);
	float total = somaTotal(produtos,prices);
	getch();
	while(total>0){
		system("cls");
		printf("Total ainda a pagar: %.2f\n", total);
		for(int i=0;i<banks;i++){
	    printf("%d: %.2f euro\n", i+1, bank[i]);
		}
		printf("Escolha o tipo de pagamento\n");
		opcao=getch();
		fflush(stdin);
		total-=bank[opcao-49];
	}
	if(total){
		printf("O seu troco é: %.2f", -1*total);
	}
}
