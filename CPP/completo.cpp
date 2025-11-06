#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

typedef struct hora{

    int hora;
    int minuto;

};

typedef struct dados{

    char nome[50];
    struct hora entrada;
	struct dados *prox=NULL;
	
};

void format_time(int *hora, int *minuto){
	time_t my_time;
	struct tm * timeinfo; 
	time (&my_time);
	timeinfo = localtime (&my_time);
	*hora=timeinfo->tm_hour;
	*minuto=timeinfo->tm_min;
}

dados* criarFicha(){
	dados *novo =(dados*)malloc(sizeof(dados));
	return novo;
}

void ler(dados *novo){
	system("cls");
	printf("\nNome:");
	gets(novo->nome);
	format_time(&novo->entrada.hora,&novo->entrada.minuto);
}

dados* inserir(dados *lista){
	dados *novo=criarFicha();
	ler(novo);
	if(lista==NULL){
		novo->prox=NULL;
		lista=novo;
	}
	else{
		dados* aux=lista;
		while(aux->prox!=NULL){
			aux=aux->prox;	
		}
		novo->prox=NULL;
		aux->prox=novo;	
	}
	return(lista);
}

void mostrarLista(dados* lista){
	dados* aux=lista;
	while(aux!=NULL){
		printf("\nNome: %s ",aux->nome);
		printf("\nHora de entrada: %d:%d", aux->entrada.hora,aux->entrada.minuto);
		aux=aux->prox;
	}
	printf("\nPressione qualquer tecla para sair!");
	getch();
}

menu(int i){
	system("cls");
	printf("Pessoas na fila: %d\n",i);
	printf("1-Nova Senha\n");
	printf("2-Passar a vez\n");
	printf("3-Mostrar Fila\n");
	printf("4-Sair\n");
};

main(){
	int i=0;
	char ch;
	dados *lista=NULL;
	do{
		menu(i);
		ch=getch();
		if(ch=='1'){
			lista=inserir(lista);
			i++;
		}
		if(ch=='2'){
			lista=lista->prox;
			i--;
		}
		if(ch=='3'){
			mostrarLista(lista);
		}		
	}while(ch!='4');
	
}

