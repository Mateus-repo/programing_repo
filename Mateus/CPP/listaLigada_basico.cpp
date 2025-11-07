#include <stdio.h>
#include <conio.h>

struct elemento{
	int valor;
	struct elemento *prox;
};

typedef struct elemento no;

main(){
	no um, dois, tres;
	// declarar um ponteiro para um elemento
	no *inicio;
	// apontar para o 1º elemento (um)
	inicio=&um;
	// fazer uma lista de 3 elementos
	um.prox=&dois;
	dois.prox=&tres;

	//ler 3 valores inteiros para guardar nos 3 elementos (um, dois e três)
	printf("3 valores: ");
	scanf("%d",&um.valor);
	scanf("%d",&dois.valor);
	scanf("%d",&tres.valor);
	
	printf("%x", tres.prox);
	
/*	
// lista dos elementos usando o inicio e um ciclo while

// valor do tres MAS através do inicio
printf("%d \n",inicio->prox->prox->valor);

// mostrar os três com 3 printfs

printf("primeiro valor %d\n",inicio->valor);
printf("segundo valor %d\n",inicio->prox->valor);
printf("terceiro valor %d\n",inicio->prox->prox->valor);
printf("quarto valor %d\n",inicio->prox->prox->prox->valor);	
printf("quinto valor %d\n",inicio->prox->prox->prox->prox->valor);	
printf("sexto valor %d\n",inicio->prox->prox->prox->prox->prox->valor);	

// num ciclo while precisamos de parar

// 10 20 30*/
inicio=&um;
int contador=0;
while(inicio!=NULL){
	printf(":-> %d",inicio->valor);
	inicio=inicio->prox;
	contador++;
	
}

printf("\n:%d",contador);
getch();


}



// mostrar os três elementos
// adicionar um elemento no fim
// eliminar um elemento no início
