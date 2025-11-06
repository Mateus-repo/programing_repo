#include <stdio.h>

void trocaCorrecta(int *p1, int *p2){
	int temp=*p1;
	*p1=*p2; // onde estava o 10, passa a estar o 20
	*p2=temp; // onde estava o 20, passa a estar o 10
}

void trocaErrada(int *p1, int *p2){
	int *temp=p1;
	p1=p2; // trocam de locais para onde estão a apontar
	p2=temp; 
}


 main(){
 	// declaração de uma variável inteira
 	int i;
 	
 	// declaração de um ponteiro para inteiro
 	int *p;
 	
 	// atribuição do valor 10 à variável inteira
 	i=10;
 	
 	// atribuição do endereço da variável inteira ao ponteiro
 	p=&i;
 	
 	// alteração do valor da variável inteira (+15) através do ponteiro
 	//*p => o que o "p" aponta
 	*p=*p+15; // *p+=15
 /*	
 	funções que manipulam ponteiros:
 		
 	o que recebem? endereços
	
	qual o tipo da variável que recebe esse endereço? 	ponteiros
	*/
	
	int a=10, b=20;
	
	trocaCorrecta(&a,&b); // no final da função, a=20 e b=10
				// quais são os parâmetros enviados? endereço de a e endereço de b
				// que tipo de variável/parâmetro está na função à espera? ponteiros 
	
	// envio os originais - parâmetro passado por referência
	
 	printf("Novos valores a: %d b:%d", a, b);
 	
 	printf("\n******************************\n\n");
 	a=10;
	b=20;
 	trocaErrada(&a,&b);
  	printf("Novos valores a: %d b:%d", a, b);	
 }
