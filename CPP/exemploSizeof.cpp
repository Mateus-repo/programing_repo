#include <stdio.h>

struct tipo{
	int a,b,c;
};
struct data{
	int dia, mes, ano;
};
struct amigo{
	char nome[50];
	char telefone[10]; // o último caracter é o \0
	data dataNascimento;
};



main(){
	amigo agenda[10];
	printf("%d\n",sizeof(struct tipo));
	printf("%d\n",sizeof(struct data));
	
}
