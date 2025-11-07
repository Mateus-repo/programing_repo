#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

int cores(int cor);
void menuPag1();
void menuPag2();
void menuPag3();
main(){
	int op[3][2];
	for(int i=0;i<3;i++){
		for(int j=0;j<2;j++){
			op[i][j]=0;
		}
	}
	setlocale(LC_CTYPE,"portuguese");
	do{
		menuPag1();
		op[0][0]=getch();
		if(op[0][0]==224){
			op[0][1]=getch();	
		}
		if(op[0][0]==0){
			getch();
		}
		switch(op[0][0]){
			case '1':
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
			default:
				//if((op[0]==224)&&(op[1]==75||op[1]==72)){
				if(/*...*/){
					do{
						menuPag2();
						op[1][0]=getch();
						if(op[1][0]==224){
							op[1][1]=getch();	
						}
						if(op[1][0]==0){
							getch();
						}
						fflush(stdin);
						switch(op[1][0]){
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
							default:
								//if((op[0]==224)&&(op[1]==75||op[1]==72)){
								if(op[1][0]==224&&op[1][1]==77){
									do{
										menuPag3();
										op[2][0]=getch();
										if(op[2][0]==224){
											op[2][1]=getch();	
										}
										if(op[2][0]==0){
											getch();
										}
										switch(op[2][0]){
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
												op[2][1]='l';
												break;
											default:
												if(op[2][0]==224&&op[2][1]==75){
													;
												}else{
													int temp3;
													system("cls");
													cores(7);printf("Erro!!\n");cores(0);printf("Pressione ");cores(8);printf("qualquer");cores(0);printf(" botão para voltar á pagina 3.\n");
													temp3=getch();
													if(temp3==224||temp3==0){
														getch();	
													}
													fflush(stdin);
												}
												break;
										}
									}while(op[2][0]!=224&&op[2][1]!=75);
								}else{
									if(op[1][0]==224&&op[1][1]==75){
										;
									}else{
										system("cls");
										cores(7);printf("Erro!!\n");cores(0);printf("Pressione ");cores(8);printf("qualquer");cores(0);printf(" botão para á pagina 2.\n");
										if(getch()==224||getch()==0){
											getch();	
										}
										fflush(stdin);
									}
								}
								break;	
						}
					}while(op[1][1]!=75&&op[1][0]!=224);
				}else{
					system("cls");
					cores(7);printf("Erro!!\n");cores(0);printf("Pressione ");cores(8);printf("qualquer");cores(0);printf(" botão para voltar á pagina 1.\n");
					if(getch()==224||getch()==0){
						getch();	
					}
					fflush(stdin);
				}
				break;	
		}
	}while(op[2][1]!='l');
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
void menuPag1(){
	system("cls");                                                                            
	cores(8);printf("************** M E N U   I N I C I A L   P A G I N A   1 **************\n*                                                                     *\n");
	cores(8);printf("*");cores(5);printf("   1 ");cores(14);printf("-");cores(4);printf(" Calcular Média                                                ");cores(8);printf("*\n");	
	cores(8);printf("*");cores(5);printf("   2 ");cores(14);printf("-");cores(2);printf(" Calcular Desvio Padrão                                        ");cores(8);printf("*\n");	
	cores(8);printf("*");cores(5);printf("   3 ");cores(14);printf("-");cores(11);printf(" Procurar amigo                                                ");cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   4 ");cores(14);printf("-");cores(9);printf(" Alterar amigo                                                 ");cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   5 ");cores(14);printf("-");cores(1);printf(" Eliminar amigo                                                ");cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   6 ");cores(14);printf("-");cores(12);printf(" Aniversarios                                                  ");cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   7 ");cores(14);printf("-");cores(7);printf(" Sem opção...                                                  ");cores(8);printf("*\n");
	cores(8);printf("*                                                                     *\n***********************************************************************\n");
	cores(5);printf("                                                       proxima página >\n");cores(0);
}
void menuPag2(){
	system("cls");                                                                            
	cores(8);printf("************** M E N U   I N I C I A L   P A G I N A   2 **************\n*                                                                     *\n");
	cores(8);printf("*");cores(5);printf("   8 ");cores(14);printf("-");cores(4);printf(" Sem opção...                                                  ");cores(8);printf("*\n");	
	cores(8);printf("*");cores(5);printf("   9 ");cores(14);printf("-");cores(2);printf(" Sem opção...                                                  ");cores(8);printf("*\n");	
	cores(8);printf("*");cores(5);printf("   a ");cores(14);printf("-");cores(11);printf(" Sem opção...                                                  ");cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   b ");cores(14);printf("-");cores(9);printf(" Sem opção...                                                  ");cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   c ");cores(14);printf("-");cores(1);printf(" Sem opção...                                                  ");cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   d ");cores(14);printf("-");cores(12);printf(" Sem opção...                                                  ");cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   e ");cores(14);printf("-");cores(7);printf(" Sem opção...                                                  ");cores(8);printf("*\n");
	cores(8);printf("*                                                                     *\n***********************************************************************\n");
	cores(5);printf("< página anterior                                      proxima página >\n");cores(0);
}
void menuPag3(){
	system("cls");                                                                            
	cores(8);printf("************** M E N U   I N I C I A L   P A G I N A   3 **************\n*                                                                     *\n");
	cores(8);printf("*");cores(5);printf("   f ");cores(14);printf("-");cores(4);printf(" Sem opção...                                                  ");cores(8);printf("*\n");	
	cores(8);printf("*");cores(5);printf("   g ");cores(14);printf("-");cores(2);printf(" Sem opção...                                                  ");cores(8);printf("*\n");	
	cores(8);printf("*");cores(5);printf("   h ");cores(14);printf("-");cores(11);printf(" Sem opção...                                                  ");cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   i ");cores(14);printf("-");cores(9);printf(" Sem opção...                                                  ");cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   j ");cores(14);printf("-");cores(1);printf(" Sem opção...                                                  ");cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   k ");cores(14);printf("-");cores(12);printf(" Sem opção...                                                  ");cores(8);printf("*\n");
	cores(8);printf("*");cores(5);printf("   l ");cores(14);printf("-");cores(7);printf(" Sair da calculadora                                           ");cores(8);printf("*\n");
	cores(8);printf("*                                                                     *\n***********************************************************************\n");
	cores(5);printf("< página anterior                                                      \n");cores(0);	
}
