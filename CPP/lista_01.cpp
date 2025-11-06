#include <stdio.h>
struct elemento{
	int valor;
	struct elemento *prox;
};
typedef struct elemento no; 
main(){
	no um, dois, tres, quatro;
	no *inicio=&um;
	um.valor=10;
	um.prox=&dois;
	dois.valor=20;
	dois.prox=&tres;
	tres.valor=30;
	tres.prox=NULL;
	// mostrar a lista
	printf("********* Mostra a lista de 3\n");
	while(inicio!=NULL){
		printf("%d",inicio->valor);
		getchar();
		inicio=inicio->prox;
	}
	tres.prox=&quatro;
	quatro.valor=40;
	quatro.prox=NULL;
	inicio=&um;
	printf(" Mostra a lista com mais um\n");
	while(inicio!=NULL){
		printf("%d",inicio->valor);
		getchar();
		inicio=inicio->prox;
	}
	inicio=&dois;
	printf("Avanca o inicio para o segundo\n");
	while(inicio!=NULL){
		printf("%d",inicio->valor);
		getchar();
		inicio=inicio->prox;
	}	
}
