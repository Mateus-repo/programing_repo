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
	char telefone[10]=""; // o último caracter é o \0
	data dataNascimento;
};
void menu();
void menuEncontrar();
int anoBi(int ano,int mes);
int validarAno(int dia,int mes,int ano);
void intrudocaoData(amigo *ficha);
void leAmigo(amigo *ficha,int numeroAmigo);
void substituiAmigo(amigo *ficha,int numeroAmigo);
void inntAmigo(amigo ficha,int numeroAmigo);
void mostraAmigo(amigo ficha);
int contaAmigos(amigo tabela[]);
void eliminaAmigo(amigo *ficha);
int tolowerl(int c);
void organizaAlfabetica(amigo *ficha[MAX]);
void encontraAmigoNome(amigo *ficha,char inserido[50]);
//void encontra+Amigo(amigo *agenda[], int *numeroAmigo);
//TORNAR O MAIN MAIS PEQUENO (AINDA EM ESPERA)
//strcmp(se a da esquerda for menor alfabeticamente entao retorna -1,se a da direita for menor alfabeticamente entao retorna 1)// se forem iguais retorna 0
main(){
	amigo agenda[MAX]={};
	FILE *f;
	if(f=fopen("data.bin","r+")){
		fread(agenda,sizeof(agenda),1,f);
	}
	char opcao,opcao1;
	int contador,i,y,j,nA;
	amigo teste;
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
					printf("***** A l t e r a  d a d o s  d e  u m  a m i g o *****\n");
					menuEncontrar();
					opcao1=getch();
					switch(opcao1){
						case '1':
							system("cls");
							printf("Introduza o nome do seu amigo: ");
							gets(teste.nome);
							fflush(stdin);
							while(teste.nome[i]=tolowerl(teste.nome[i])){
								i++;		
							}
							/*for(int i;i<MAX;i++){
								encontraAmigoNome(&agenda[i],teste.nome);
							}*/
							//testes
							//getch();
							do{
								if(j!=MAX){
									y=strcmp(teste.nome, agenda[j].nome);
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
							gets(teste.telefone);
							do{
								if(j!=MAX){
									y=strcmp(teste.telefone, agenda[j].telefone);	
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
								intrudocaoData(&teste);	
								if(validarAno(teste.dataNascimento.dia,teste.dataNascimento.mes,teste.dataNascimento.ano)==0){
									system("cls");
									printf("A data inserida é invalida, tente outra vez.\nPressiona qualquer botao para proseguir...");
									getch();
									fflush(stdin);
								}	
							}while(validarAno(teste.dataNascimento.dia,teste.dataNascimento.mes,teste.dataNascimento.ano)==0);
							do{
								if(j!=MAX){
									if(teste.dataNascimento.dia==agenda[j].dataNascimento.dia&&teste.dataNascimento.mes==agenda[j].dataNascimento.mes&&teste.dataNascimento.ano==agenda[j].dataNascimento.ano){
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
			//	organizaAlfabetica(&agenda);
				break;
			case '5':
				//Em testes
				system("cls");
				printf("************* E l i m i n a r  a m i g o  *************\n");
				menuEncontrar();
				opcao1=getch();
				switch(opcao1){
					case '1':
							//encontraAmigoNome(&agenda[i], &nA0);
						break;
					default:
						break;
				}
				
				eliminaAmigo(&agenda[1]);
				
				//EM TESTES
				break;                                          
			case '6':
				system("cls");
				printf("*********************** S A I U ***********************");
				break;
			default:
				system("cls");
				printf("Erro!...\nPressione qualquer botao para voltar ao menu inicial.\n");
				getch();
				break;
		}
	}while(opcao!='6');
	//******************* guardar em ficheiro
	f=fopen("data.bin","w+");
	fwrite(agenda,sizeof(agenda),1,f);
	fclose(f);
}
void menu(){
	system("cls");
	printf("*********************** M E N U ***********************\n\n");
	printf(" 1 - Novo amigo\n");
	printf(" 2 - Lista todos os amigos\n");
	printf(" 3 - Altera dados de um amigo\n");
	printf(" 4 - Odernar lista alfabeticamente\n");
	printf(" 5 - Eliminar um amigo\n");
	printf(" 6 - Sair\n");	
}
void menuEncontrar(){
	printf("Quer encontrar o seu amigo por qual tipo de dados?\n\n");
	printf(" 1 - Nome\n");
	printf(" 2 - Numero de Telefone\n");
	printf(" 3 - Data de nascimento\n");
	printf(" 4 - Sair\n");	
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
	int i=0;
	printf("Indique as informacoes do amigo nº%d.\n\n	Nome do amigo.........: ",numeroAmigo);
	gets(ficha->nome);
	while(ficha->nome[i]=tolowerl(ficha->nome[i])){
		i++;		
	}
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
void eliminaAmigo(amigo *ficha){
	amigo nada;
	for(int i;i<50;i++){
		ficha->nome[i]=nada.nome[i];
		if(i<10){
			ficha->telefone[i]=nada.telefone[i];
		}
	}
	ficha->dataNascimento.dia=0;
	ficha->dataNascimento.mes=0;
	ficha->dataNascimento.ano=0;
}
int tolowerl(int c){
	if(c>='A'&&c<='Z')
		return(c+('A'>'a'?(-1*('A'-'a')):'a'-'A')); 
	else
		return(c);
}
void encontraAmigoNome(amigo *ficha,char inserido[50]){
	int i=0,j,verifica[MAX+1];
	int numChar=-1;
	do{
		numChar++;
	}while(inserido[numChar]!=0);
	do{
		verifica[i]=0;
		do{
			if(ficha->nome[j]==inserido[j]){
				verifica[i]++;
				verifica[MAX]=1;
			}
		}while(j<numChar);
		i++;	
	}while(i<MAX);
	if(verifica[MAX]){
		system("cls");
		printf("Qual destes amigos é o procurado?\nPressione o numero do amigo procurado.\n");
	}
	for(int y=0;y<MAX;y++){
		printf("%d-O amigo nº%d\n",y+1,y+1);
		printf("	Nome..................: %s\n",ficha->nome);
		printf("	Telefone do amigo.....: %s\n",ficha->telefone);
		printf("	Data de nascimento....: %d/%d/%d\n",ficha->dataNascimento.dia,ficha->dataNascimento.mes,ficha->dataNascimento.ano);
		fflush(stdin);
		printf("\n");
	}
}
void organizaAlfabetica(amigo *ficha[MAX]){
	int org[MAX]={};
	int max,y;
	for(y=0;y<MAX-1;y++){
		max=0;
		for(int i=0;i<MAX-1-i;i++){
			if(strcmp(ficha[max]->nome,ficha[i]->nome)==-1){
				max=i;
			}
		}
		org[MAX-1-y]=max;
	}
	system("cls");
	for(int i=0;i<MAX;i++){
		printf("%s\n",ficha[org[i]]->nome);
	}
}
//testes
