#include <stdio.h>
#include <conio.h>

main(){
	int n1, n2, n3;
	printf("Qual o numero 1?\n");
	scanf("%d", &n1);
	printf("Qual o numero 2?\n");
	scanf("%d", &n2);
	printf("Qual o numero 3?\n");
	scanf("%d", &n3);
	if(n1==n2&&n2==n3){
		printf("Sao todos iguais.\n");
	}else{
		if(n1 < n2){
			if(n2 < n3){
				printf("O maior e %d", n3, ".\n");
			}else{
				printf("O maior e %d", n2, ".\n");
			}
		}else{
			printf("O maior e %d", n1, ".\n");
		}
	if(n1==n3){
		printf("Os numeros 1 e 3 sao iguais.\n");
	}else{
		if(n1==n2){
			printf("Os nunmeros 1 e 2 sao iguais.\n");
		}else{
			if(n2==n3){
				printf("Os numeros 2 e 3 sao iguais.\n");
				}
			}
		}
	}

}
