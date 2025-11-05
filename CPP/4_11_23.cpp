#include <stdio.h>
#include <conio.h>

main(){
	int simbolo;
	int a, b;
		printf("   Escolha um meio para calcular:   \n");
		printf("1- Soma\n") ;
		printf("2- Subtracao\n") ;
		printf("3- Multiplicacao\n") ;
		printf("4- Divisao\n") ;
		scanf ("%d" ,&simbolo) ;
		if(simbolo<1 || simbolo >4) {
			printf("Impossivel continuar a operacao\n");	
		}else{
			printf("Identifique o primeiro numero a\n");
			scanf("%d", &a);
			printf("Identifique o numero b\n");
			scanf("%d", &b);
			if(b==0){
				printf("Erro, impossivel dividir por 0\n");
			}else{
				if(simbolo==1){
				printf("%d\n", a + b );
				}else{
					if(simbolo==2){
					printf("%d\n", a - b );
					}else{
						if(simbolo==3){
						printf("%d\n", a * b );
						}else{
							printf("%d\n", a / b );
						}
					}
				}
		
			}
		}
		
	}   

