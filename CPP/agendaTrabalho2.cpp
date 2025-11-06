#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>


struct data{
	int dia, mes, ano;
};
struct amigo{
	char nome[50]="VOID";
	char telefone[10]; // o último caracter é o \0
	data dataNascimento;
};
int noInfCheck(char nome[50], char telefone[10]){//0=que tem informacao nos dois/1=que tem inf apenas do telefone/2=tem inf apenas do nome/3=nao tem inf
	int i=0, y=-1;
	printf("Nome...........:%s\nTelefone.......:%s", nome,telefone);
	do{
		y++;
		if(y==49&&nome[49]==0||nome[49]==' '||nome[49]=='\n'){
			i+=1;
		}
		printf("\ni = %d y = %d",i,y);
	}while((nome[y]==0||nome[y]==' '||nome[y]=='\n')&&y<50);
	y=-1;
	do{
		y++;
		if(y==9&&(telefone[y]==0||telefone[y]==' ')){
			i+=2;
		}
	}while((telefone[y]==0||telefone[y]==' '||telefone[y]=='\n')&&y<=9);
	return(i);
}

void menu(){
	system("cls");
	printf("******************* M E N U *******************\n");
	printf("1 - Novo amigo\n");
	printf("2 - Lista todos os amigos\n");
	printf("3 - Altera dados de um amigo\n");
	printf("4 - Sair\n");	
}

	
main(){
	amigo agenda[10];
	char opcao;
	setlocale(LC_CTYPE,"portuguese");
	fgets(agenda[0].nome,50,stdin);
	agenda[0].nome[strlen(agenda[0].nome)-1]=0;
	fgets(agenda[0].telefone,10,stdin);
	agenda[0].telefone[strlen(agenda[0].telefone)-1]=0;
	printf("\n%d", noInfCheck(agenda[0].nome,agenda[0].telefone));
	/*do{
		menu();
		opcao=getch();
		if(opcao=='1'){
			;
		}		
		if(opcao=='2'){
			;
		}
		if(opcao=='3'){
			;
		}
	}while(opcao!='4');
	*/
}














