#include <stdio.h>
main(){
	int a=10;
	int *p=&a;//ponteiro para inteiro "p aponta para a"
	printf("valor de a:%d\nendereco de a:%0x\n",a,&a);
	printf("valor de p:%0x\nendereco de p%0x\nconteudo de p (o que p aponta):%d\n",p,&p,*p);
/*	
	(*p)++; // o pós fixado vem primeiro
	printf("a:%d endereco de p%0x conteudo de p:%d\n",a, &p,*p);
		// o ponteiro passou a apontar para a frente
	p++;
	printf("a:%d endereco de p%0x conteudo de p:%d\n",a, &p,*p);

*/	
	
	
	
}
