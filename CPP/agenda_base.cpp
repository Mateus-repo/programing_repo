#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
struct data{
	int dia, mes, ano;
};
struct amigo{
	char nome[50];
	char telefone[10]; // o último caracter é o \0
	data dataNascimento;
};
void menu(){
	system("cls");
	printf("******************* M E N U *******************\n");
	printf("1 - Introduz dados\n");
	printf("2 - Mostra dados\n");
//	printf("3 - Altera dados\n");
	printf("4 - Sair\n");	
}	
main(){
	FILE *f; // ponteiro para o feicheiro em disco
	amigo ficha;
	char opcao;
	setlocale(LC_CTYPE,"portuguese");
	if((f=fopen("turma1d.dat","r+")/*tenta abrir*/)==NULL/*se não existir*/)
		f=fopen("turma1d.dat","w+");
	else
		fread(&ficha,sizeof(ficha),1,f); // ler do disco
	do{
		menu();
		opcao=getch();
		system("cls");
		switch(opcao){
			system("cls");
			case '1':
				printf("Qual o nome: ");
				gets(ficha.nome);
				fflush(stdin);
				printf("Qual o numero de telefone: ");
				gets(ficha.telefone);
				fflush(stdin);
				printf("Qual a data de nascimento [dia]: ");
		        scanf("%d",&ficha.dataNascimento.dia);
		        fflush(stdin);
		        printf("Qual a data de nascimento [mes]: ");
		        scanf("%d",&ficha.dataNascimento.mes);
		        fflush(stdin);
		        printf("Qual a data de nascimento [ano]: ");
	      		scanf("%d",&ficha.dataNascimento.ano);  
	      		fflush(stdin);
				break;
			case '2':
				printf("Nome: %s \n",ficha.nome);
				printf("Telefone: %s \n",ficha.telefone);
				printf("Data de nascimento: %d/%d/%d\n",ficha.dataNascimento.dia,ficha.dataNascimento.mes,ficha.dataNascimento.ano);
		        printf("Pressione qualquer botao para sair...\n");
		        getch(); 
		        fflush(stdin);	
				break;
			case '3':
				printf("Isto está muito vazio por aqui...\n");
				printf("Pressione qualquer botao para sair...\n");
		        getch();
		        fflush(stdin);
				break;
			case '4':
				printf("******** S A I U ********");
				return 0;
				break;
			default:
				printf("Pressionou um botão errado!\nPor favor tente de novo.\n");
				printf("Pressione qualquer botao para sair...\n");
				getch();
				fflush(stdin);
				break;
		}
	}while(1/*opcao!='4'*/);
	//f=fopen("turma1d.dat","w+");
	fseek(f,0,SEEK_END);
	fwrite(&ficha,sizeof(ficha),1,f);// escreve no disco	
	fclose(f);// fecha o ficheiro
}
