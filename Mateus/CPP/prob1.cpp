#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define ENTER 13
#define ESCAPE 27
struct data{
	int dia=0, mes=0, ano=0;   //!! fazer com que a pessoa só consiga colocar 2 numeros (apenas numeros), no dia e mes e 4 numeros no ano
};
struct amigo{
	char nome[50]="vazio";
	char telefone[10]; // o último caracter é o "9"       /// fazer com que a pessoa não consiga colocar letras
	data dataNascimento;
};
void menu();
int voltar();
void validar();
void mostraFicha(amigo ficha);
void insereFicha(amigo *ficha);
void validarNome(amigo *ficha);/////////////////////////// - mome não pode ter números
int validarAno(int dia,int mes, int ano);
int procurarFicha(amigo agenda[], char nome[]);
void mudarDados(amigo agenda[]);

main(){
//	int pessoas;
//	amigo agenda[pessoas];
	char back;
	char simNao;
	amigo agenda[10]={};
	char opcao;
	int contador=0;
	int i;
	/////////////////////////////////////  APRENDER  ///////////////////////////////////////
	FILE *f; // variável f é um ponteiro para o disco                                 //////
	                                                                                  //////
	if(f=fopen("agenda.bin","r+")){// abre o ficheiro do disco                        //////
		fread(agenda,sizeof(agenda),1,f); // lê o array para RAM do ficheiro          //////
	}                                                                                 //////
	////////////////////////////////////////////////////////////////////////////////////////
	setlocale(LC_CTYPE,"portuguese");
	/*switch(getch()){
		case '1':
			break;
		etc...
	*/
	do{
		menu();
		opcao=getch();
		if(opcao=='1'){	
			do{
				do{
					insereFicha(&agenda[contador]);
					mostraFicha(agenda[contador]);
					/* primeiro carater no dia e no mês é *10, no ano o primeiro caracter é *1000, 
					o segundo do ano é *100 e o terceiro é *10; *10|0\*10|0\*1000|*100|*10
					substituir os scanf's por getche's*/
				//	fflush(stdin);
				}while(strcmp(agenda[contador].nome,"vazio")==0);
				contador++;
				//"strcmp" - compara duas strings se devolver 0 as strings são iguais, se devolver 1 a string da esquerda é maior alfabeticamente do que a da direita, se devolver -1 a da direita é maior alfabeticament
			}while(voltar()!=ESCAPE);
			
		}
		if(opcao=='2'){
			printf("\n*************** L I S T A  A M I G O S ***************\n");
			for(int i=0;i<contador;i++){
				mostraFicha(agenda[i]);
			}
			printf("\nFim da listagem....\n");
			getch();
		}
		if(opcao=='3'){
			do{
				//char op;
				printf("\n*************** A L T E R A R  D A D O S ***************\n");
				/*for(int i=0;i<contador;i++){
					mostraFicha(agenda[i]);
					printf("é este?");
					op=getch();
				}	
				getch();*/
			char nome[50];
			int posicao;
			system("cls");
			printf("Qual é o amigo que deseja trocar os dados: \n");
			gets(nome);
			if((posicao=procurarFicha(agenda,nome))==-1){
				printf("O nome não existe!\n");
			}else{
				mostraFicha(agenda[posicao]);
			};
			char op1;
			printf("Quer mudar dados?\n1 - Sim\n2 - Não\n");
			fflush(stdin);
			op1=getch();
			fflush(stdin);
			if (op1=='1'){
				for(int i=0;i<=contador;i++){
					mudarDados(agenda);
				}
			}else{
				;
			}	
			////////////////////////////////////////////////////////////////////////////////////
			/*	printf("Qual é o amigo que deseja trocar os dados: %s \n",agenda[i].nome);
			gets(agenda[contador].nome);
			}*/
			}while(voltar()!=ESCAPE);
		}
	}while(opcao!='4');
		f=fopen("agenda.bin","w+");// cria o ficheiro de raiz
		fwrite(agenda,sizeof(agenda),1,f); // escreve o array da RAM para o novo ficheiro
		fclose(f); // fecha o ficheiro
		system("cls");
		printf("\n*************** S A I U ***************\n");

}
//--------------------------------------------------------------  MAIN  ------------------------------------------------------------------------------------------//

void insereFicha(amigo *ficha){
	system("cls");
	printf("\n*************** N O V O  A M I G O ***************\n");
	printf("\nNome: ");
	gets(ficha->nome);
	fflush(stdin);
	//validarNome(ficha);
	printf("\nTelefone: ");
	gets(ficha->telefone);
	printf("\n");
	fflush(stdin);
	do{
		printf("Data de nascimento - ");
		printf("Dia:  ");
		scanf("%d",&ficha->dataNascimento.dia);
		fflush(stdin);
		printf("                   - Mês: ");
		scanf("%d",&ficha->dataNascimento.mes);
		fflush(stdin);
		printf("                   - Ano: ");
		scanf("%d",&ficha->dataNascimento.ano);
		fflush(stdin); //apaga inputs, dantes escritos pelo teclado
	}while(validarAno(ficha->dataNascimento.dia,ficha->dataNascimento.mes,ficha->dataNascimento.ano)==0);
}
void mostraFicha(amigo ficha){
	printf("------------------------------------------\n");
	printf("Nome:  %s\n",ficha.nome);
	printf("Telefone:  %s\n",ficha.telefone);
	printf("Data de nascimento: %d/%d/%d \n\n",ficha.dataNascimento.dia,ficha.dataNascimento.mes,ficha.dataNascimento.ano);

}
int anoBisexto(int ano, int mes){
	if(mes!=2){
		return(0);
	}
	if(ano%4==0){
		return(1);
	}
}
///////////////////////////////
//problemas para resolver
void validarNome(amigo *ficha){
	/*if(nome=='1'||'2'||'3'||'4'||'5'||'6'||'7'||'8'||'9'||'0'){
		printf("Erro! Só pode usar caracteres!");
		return(0);
	}else{
		;
	}
	return(1);*/
	amigo nada;
	int i=0;
	do{
		printf("\nNome: ");
		gets(ficha->nome);
		fflush(stdin);
		do{
			if(ficha->nome[i]<='9'&&ficha->nome[i]>='0'){
				for(int j=0;j<50;j++){
			    	ficha->nome[j]=nada.nome[j];
				}
			}
			i++;
		}while(i<50||strcmp(ficha->nome,nada.nome));
		if(strcmp(ficha->nome,nada.nome)==0){
			system("cls");
			printf("Nome invalido, lembre-se de nao colocar outros carateres sem ser letras no nome!\n");
		}
	}while(strcmp(ficha->nome,nada.nome)==0);
}
/////////////////////////////
int validarAno(int dia,int mes,int ano){
	int data [12]={31,28,31,30,31,30,31,31,30,31,30,31};
	if(dia<=0||dia>31||mes<=0||mes>12||ano<1927||ano>2024){
		printf("Erro! Data incorreta!\n");
		return(0);
	}else{
		;
	}
	if(data[mes-1]-anoBisexto(ano,mes)<dia){
		return(0); // a diferença entre getch() e return(0), é que o return(0) é considerado o fim de uma função e não ocupa espaço na memória.
	}
	return(1);
}
void menu(){
	system("cls");
	printf("\n******************* M E N U *******************\n");
	printf("\n1 - Novo amigo\n");
	printf("2 - Lista todos os amigos\n");
	printf("3 - Altera dados de um amigo\n");
	printf("4 - Sair\n");
}
int voltar(){
	printf("\nEscape..........................para Voltar\n");
	printf("Precione qualquer tecla...........para Continuar\n\n");
	return(getch());
}
int procurarFicha(amigo agenda[], char nome[]){
	int contador=0;
	for(int i=0;i<=contador;i++){										
		if(strcmp(agenda[i].nome,nome)==0){						
			return(i);	
		}
	}
	return -1;
}
void mudarDados(amigo agenda[]){
	char nome[50];
	int contador=0;
	int op1;
	for(int i=0;i<=contador;i++){
		int dia, mes, ano;
		printf("\n--------------------------------------\n");
		printf("1 - Mudar nome\n2 - Mudar telefone\n3 - Mudar data nascimento\n");
		op1=getch();
		if(op1=='1'){
			system("cls");
			printf("Nome: ");
			gets(agenda[i].nome);
			getch();
		}
		if(op1=='2'){
			system("cls");
			printf("Telefone: ");
			gets(agenda[i].telefone);
			getch();
		}
		if(op1=='3'){
			system("cls");
			printf("Data de nascimento  ");
			printf("Dia: ");
			scanf("%d",&agenda[i].dataNascimento.dia);
			printf("Mês: ");
			scanf("%d",&agenda[i].dataNascimento.mes);
			printf("Ano: ");
			scanf("%d",&agenda[i].dataNascimento.ano);	
			fflush(stdin);
			getch();
		}
	}
}
