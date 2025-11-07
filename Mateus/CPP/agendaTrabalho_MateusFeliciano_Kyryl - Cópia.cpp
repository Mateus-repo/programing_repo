#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#define MAX 10
struct data{
	int dia=0, mes=0, ano=0;
};
struct amigo{
	char nome[50]="void";
	char telefone[10]; // o último caracter é o \0
	data dataNascimento;
};
void menu();
void menuSubstituir();
int anoBi(int ano,int mes);
int validarAno(int dia,int mes,int ano);
void intrudocaoData(amigo *ficha);
void leAmigo(amigo *ficha,int numeroAmigo);
void substituiAmigo(amigo *ficha,int numeroAmigo);
void infAntAmigo(amigo ficha,int numeroAmigo);
void mostraAmigo(amigo ficha);
int contaAmigos(amigo tabela[]);
main(){
	amigo agenda[MAX]={};

	FILE *f;
	if(f=fopen("data.bin","r+")){
		fread(agenda,sizeof(agenda),1,f);
		
	}
	char opcao,opcao1;
	char teste[50];
	int contador,y,j;
	amigo testeData;
	setlocale(LC_CTYPE,"portuguese");
	contador=contaAmigos(agenda);
	do{
		menu();
		opcao=getch();
		switch(opcao){
			case'1':
				do{
					system("cls");
					leAmigo(&agenda[contador++],contador);
					printf("\nESCAPE para sair.......");
					printf("\nQualquer botao para adicionar outro amigo...");
				}while(getch()!=27);
				break;
			case'2':
				system("cls");
				printf("Existem altualmente %d amigos\n",contador);
				for(int i=0;i<contador;i++){
					printf("Amigo nº%d\n\n",i+1);
					mostraAmigo(agenda[i]);
					printf("\n");
				}
				printf("Pressione qualquer botao para sair...\n");
				getch();
				break;
			case'3':
				do{
					j=0;
					y=1;
					system("cls");
					menuSubstituir();
					opcao1=getch();
					switch(opcao1){
						case '1':
							system("cls");
							printf("Introduza o nome do seu amigo: ");
							gets(teste);
							do{
								if(j!=MAX){
									y=strcmp(teste, agenda[j].nome);
									//printf("\nY=%d,J=%d",y,j);	
								}
								j++;
							}while(y!=0&&j<=MAX);
							if(y!=0){
								printf("\nNão foi encontrado um amigo com o nome inserido.");
								printf("\nPressione qualquer botao para sair...\n");
								getch();
								fflush(stdin);
							}
							if(y==0){
								do{
									fflush(stdin);
									substituiAmigo(&agenda[--j],j);
									j++;
								}while(getch()!=27);
							}	
							opcao1='4';	
							break;
						case '2':
							system("cls");
							printf("Introduza numero de telefone do seu amigo: ");
							gets(teste);
							do{
								if(j!=MAX){
									y=strcmp(teste, agenda[j].telefone);	
								}
								j++;
							}while(y!=0&&j<=MAX);
							if(y!=0){
								printf("\nNão foi encontrado um amigo com o numero de telefone inserido.");
								printf("\nPressione qualquer botao para sair...\n");
								getch();
							}
							if(y==0){
								do{
									fflush(stdin);
									substituiAmigo(&agenda[--j],j);
									j++;
								}while(getch()!=27);
							}
							opcao1='4';
							break;
						case '3':
							do{
								system("cls");
								intrudocaoData(&testeData);	
								if(validarAno(testeData.dataNascimento.dia,testeData.dataNascimento.mes,testeData.dataNascimento.ano)==0){
									system("cls");
									printf("A data inserida é invalida, tente outra vez.\nPressiona qualquer botao para proseguir...");
									getch();
									fflush(stdin);
								}	
							}while(validarAno(testeData.dataNascimento.dia,testeData.dataNascimento.mes,testeData.dataNascimento.ano)==0);
							do{
								if(j!=MAX){
									if(testeData.dataNascimento.dia==agenda[j].dataNascimento.dia&&testeData.dataNascimento.mes==agenda[j].dataNascimento.mes&&testeData.dataNascimento.ano==agenda[j].dataNascimento.ano){
										y=0;
										//printf("\nY=%d,J=%d",y,j);
									}	
								}
								j++;
							}while(y!=0&&j<=MAX);
							if(y!=0){
								printf("\nNão foi encontrado um amigo com a data de nascimento inserida.");
								printf("\nPressione qualquer botao para sair...\n");
								getch();
							}
							if(y==0){
								do{
									fflush(stdin);
									substituiAmigo(&agenda[--j],j);
									j++;
								}while(getch()!=27);
							}
							opcao1='4';
							break;
						case '4':
							break;
						default:
							printf("Erro!...\nPressione qualquer botao para voltar ao menu principal.\n");
							getch();
							break;
					}
				}while(opcao1!='4');
				break;
			case '4':
				break;
			default:
				system("cls");
				printf("Erro!...\nPressione qualquer botao para voltar ao menu de alterar dados.\n");
				getch();
				break;
		}
	}while(opcao!='4');
	
	//******************* guardar em ficheiro
	f=fopen("data.bin","w+");
	fwrite(agenda,sizeof(agenda),1,f);
	
	fclose(f);
	
	
}



void menu(){
	system("cls");
	printf("******************* M E N U *******************\n");
	printf("1 - Novo amigo\n");
	printf("2 - Lista todos os amigos\n");
	printf("3 - Altera dados de um amigo\n");
	printf("4 - Sair\n");	
}
void menuSubstituir(){
	system("cls");
	printf("Quer encontrar o seu amigo por qual tipo de dados?\n");
	printf("1 - Nome\n");
	printf("2 - Numero de Telefone\n");
	printf("3 - Data de nascimento\n");
	printf("4 - Sair\n");	
}
int anoBi(int ano,int mes){
	if(mes!=2){
		return(0);
	}
	if(ano%4==0){
		return(1);
	}
} 
int validarAno(int dia,int mes,int ano){
	int data[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	if(dia<=0||dia>31||mes<=0||mes>12||ano<1900||2024<ano){
		return(0);
	}
	if(data[mes-1]-anoBi(ano,mes)<dia){
		return(0);
	}
	return(1);
}
void intrudocaoData(amigo *datas){
	printf("	Dia de nascimento.....: ");
	scanf("%d", &datas->dataNascimento.dia);
	fflush(stdin);
	printf("	Mes de nascimento.....: ");
	scanf("%d", &datas->dataNascimento.mes);
	fflush(stdin);
	printf("	Ano de nascimento.....: ");
	scanf("%d", &datas->dataNascimento.ano);
	fflush(stdin);
}	
void leAmigo(amigo *ficha,int numeroAmigo){
	printf("Indique as informacoes do amigo nº%d.\n\n	Nome do amigo.........: ",numeroAmigo);
	gets(ficha->nome);
	fflush(stdin);
	printf("	Telefone do amigo.....: ");
	gets(ficha->telefone);
	fflush(stdin);
	do{
		intrudocaoData(ficha);
		/*printf("\nDia %d, Mes %d, Ano %d\n",ficha->dataNascimento.dia,ficha->dataNascimento.mes,ficha->dataNascimento.ano);
		getch();*/
		if(validarAno(ficha->dataNascimento.dia,ficha->dataNascimento.mes,ficha->dataNascimento.ano)==0){
			system("cls");
			printf("A data inserida é invalida, tente outra vez.\nPressiona qualquer botao para proseguir...");
			getch();
			system("cls");
			printf("Indique as informacoes do amigo nº%d.\n\n	Nome do amigo.........: %s\n",numeroAmigo,ficha->nome);
			printf("	Telefone do amigo.....: %s\n",ficha->telefone);
		}
	}while(validarAno(ficha->dataNascimento.dia,ficha->dataNascimento.mes,ficha->dataNascimento.ano)==0);
}
void substituiAmigo(amigo *ficha,int numeroAmigo){
	system("cls");
	printf("Informacoes anteriores do amigo nº%d.\n\n	Nome..................: %s\n",++numeroAmigo,ficha->nome);
	printf("	Telefone do amigo.....: %s\n",ficha->telefone);
	printf("	Data de nascimento....: %d/%d/%d\n",ficha->dataNascimento.dia,ficha->dataNascimento.mes,ficha->dataNascimento.ano);
	printf("\nSubstitua as informações do amigo.\n");
	printf("Indique as novas informacoes do amigo nº%d.\n\n	Nome do amigo.........: ",numeroAmigo);
	gets(ficha->nome);
	fflush(stdin);
	printf("	Telefone do amigo.....: ");
	gets(ficha->telefone);
	fflush(stdin);
	do{
		intrudocaoData(ficha);
		if(validarAno(ficha->dataNascimento.dia,ficha->dataNascimento.mes,ficha->dataNascimento.ano)==0){
			system("cls");
			printf("A data inserida é invalida, tente outra vez.\nPressiona qualquer botao para proseguir...");
			getch();
			system("cls");
			printf("Indique as informacoes do amigo nº%d.\n\n	Nome do amigo.........: %s\n",numeroAmigo,ficha->nome);
			printf("	Telefone do amigo.....: %s\n",ficha->telefone);
		}
	}while(validarAno(ficha->dataNascimento.dia,ficha->dataNascimento.mes,ficha->dataNascimento.ano)==0);
	printf("\nESCAPE para sair.............");
	printf("\nQualquer botao para repetir..");
}
void mostraAmigo(amigo ficha){
	printf("	Nome..................: %s\n",ficha.nome);
	printf("	Telefone do amigo.....: %s\n",ficha.telefone);
	printf("	Data de nascimento....: %d/%d/%d\n",ficha.dataNascimento.dia,ficha.dataNascimento.mes,ficha.dataNascimento.ano);
	fflush(stdin);
}

int contaAmigos(amigo tabela[]){
	int c=0;
	while(strcmp(tabela[c].nome,"void")){
		c++;
		if(c==10)
			return(10);
	};
	return(c);
}

