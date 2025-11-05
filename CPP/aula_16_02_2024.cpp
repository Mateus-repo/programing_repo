#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#define NUM 4

void asteriscos(int numero){
	for(int i=1;i<=numero;i++){
		printf("*");
	}
	printf("\n\n");
}

void asteriscosEx2(int numero){
	for(int i=1;i<=numero;i++){
		printf("*");
	}
	printf("\n\n");
}

void asteriscosEx3(int numero){
	for(int i=1;i<=5-numero;i++){
		printf("*");
	}
	printf("\n\n");
}

void asteriscosEx4(int numero){
	for(int i=1;i<=4-numero;i++){
		printf(" ");
	}
	for(int i=1;i<=numero;i++){
		printf("*");
	}
	printf("\n\n");
}

void asteriscosEx5(int numero){
	for(int i=1;i<=NUM;i++){
		for(int j=1;j<=NUM;j++){
			if(i==1||i==NUM||j==NUM||j==1){
				printf("*");
			}else{
				printf(" ");
			}
		}
	}
	printf("\n\n");
}

void asteriscosEx6(int numero){
	for(int i=1;i<=numero;i++){
		printf("*");
	}
	printf("\n");
}

main(){
	for(int i=1;i<=NUM;i++){
		asteriscos(i);
	}
	printf("\n--------------\n");
	for(int i=1;i<=NUM;i++){
		asteriscosEx2(4);
	}
	printf("\n--------------\n");
	for(int i=1;i<=NUM;i++){
		asteriscosEx3(i);
	}
	printf("\n--------------\n");
	for(int i=1;i<=NUM;i++){
		asteriscosEx4(i);
	}
	printf("\n--------------\n");
	for(int i=1;i<=NUM;i++){
		asteriscosEx5(i);
	}
	/*
	for(int i=1;i<=NUM;i++){
		asteriscosEx6(i);
	}*/
}
