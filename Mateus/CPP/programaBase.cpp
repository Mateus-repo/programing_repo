// aula de dia 13

#include <stdio.h>
#include <conio.h>
#include <malloc.h>

struct elemento{
	int valor;
	struct elemento *prox=NULL;
};

typedef struct elemento no;



main(){
	no *inicio=NULL;

	int numSenha=1;
	do{
		menu();	
		op=getch();
		if(op=='1'){
			inserirLista(inicio,numSenha);
			numSenha++; 
		}
			
	}while(op!='5');
	
}
