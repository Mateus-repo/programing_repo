#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

void ex01(){
	int i;
	for(i=1;i<=5;i++){
		printf("%d",i);
	}
	printf("\n\n");
}
void ex02(){
	int i;
	for(i=1;i<=5;i++){
		printf("%d\n",i);
	}
	printf("\n");
}
void ex03(){
	int i;
	for(i=1;i<=5;i++){
		if(i==2){
			printf("dois\n");
		}else{
			printf("%d\n",i);
		}		
	}	
	printf("\n");
}
void ex04(){
	int i;
	for(i=1;i<=5;i++){
		if(i%2==0){
			printf("*");
		}else{
			printf("#");
		}
	}
	printf("\n\n");
}
void ex05(){
	int i;
	for(i=1;i<=10;i++){
		if(i%2==0){
			printf("*");
		}else{
			if(i==3||i==9){
				printf("#");
			}else{
				printf("%d", i);
			}
		}
	}
	printf("\n");
}
void ex06(){
	int i;
	for(i=1;i<=10;i++){
		if(i%2==0){
			printf("*");
		}else{
			if(i==3||i==9){
				printf("#");
			}else{
				if(i==7){
					printf("#%d", i);
				}else{
					printf("%d", i);	
				}
			}
		}
	}
	printf("\n");
}
void ex07(){
	int i;
	for(i=1;i<=9;i++){
		if(i%3==0){
			printf("*\n\n");
		}else{
			printf("*");
		}
	}
	printf("\n");
}
void ex08(){
	int i, j;
	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			if(i==1||i==3){
				printf("*");
			}else{
				if(i==2){
					printf("@");
				}
			}
			if(i==2&&j==3||i==1&&j==3){
				printf("\n");
			}
		}
	}
	printf("\n");
}
void ex09(){
	int i, j;
	for(i=1;i<=4;i++){
		for(j=1;j<=4;j++){
			if(i==1||i==4||j==1||j==4){
				printf("*");
			}else{
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("\n");
}
void ex10(){
	int i, j;
	for(i=0;i<=4;i++){
		for(j=0;j<=4;j++){
			if(i==0||i==4||j==0||j==4){
				printf("*");
			}else{
				if(i==j){
					printf("*");
				}else{
					printf(" ");
				}
			}
		}
		printf("\n");
	}
	printf("\n");
}
void ex11(){
	int i, j;
	for(i=0;i<=4;i++){
		for(j=0;j<=4;j++){
			if(j<=i){
				printf("*");
			}
		}
		printf("\n");
	}
	printf("\n");
}
void ex12(){
	
	int i, j;
	for(i=1;i<=5;i++){
		for(j=1;j<=5;j++){
			if(j>5-i){
				printf("*");
			}else{
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("\n");
}
void ex13(){
	int i, j;
	for(i=1;i<=5;i++){
		for(j=1;j<=5-i;j++){
			printf(" ");
		}
		for(j=1;j<=i*2-1;j++){
			printf("*");
		}
		printf("\n");
	}
	printf("\n");
}
void ex14(){
	int i, j;
	for(i=1;i<=6;i++){
		for(j=1;j<=i-1;j++){
			printf(" ");
		}
		for(j=1;j<=6*2-1+2*-i;j++){
			printf("*");
		}
		printf("\n");
	}
	printf("\n");
}
void ex15(){
	int i, j;
	for(i=1;i<=5;i++){
		for(j=1;j<=5-i;j++){
			printf(" ");
		}
		for(j=1;j<=i*2-1;j++){
			printf("*");
		}
		printf("\n");
	}
	printf("\n");	
}
void simples(){
	int ll, op;
	ll++;
	while(ll>0){
		printf("Para qual exercicio quer ir?\n\n 1-exercicio 01\n 2-exercicio 02\n 3-exercicio 03\n 4-Voltar\n\n");
		op=getch();
		if(op!='1'&&op!='2'&&op!='3'&&op!='4'){
			printf("Por favor insere um numero\n\n");
		}else{
			switch(op){
				case '1':
					ex01();
					break;
				case '2':
					ex02();
					break;
				case '3':
					ex03();
					break;
				case '4':
					ll=0;
					break;
				default:
					printf("--!!Erro!!--\n\n");
					break;
			}	
		}
	}
}
void medio(){
	int ll, op;
	ll++;
	while(ll>0){
		printf("Para qual exercicio quer ir?\n\n 1-exercicio 04\n 2-exercicio 05\n 3-exercicio 06\n 4-exercicio 07\n 5-exercicio 08\n 6-Voltar\n\n");
		op=getch();
		if(op!='1'&&op!='2'&&op!='3'&&op!='4'&&op!='5'&&op!='6'){
			printf("Por favor insere um numero\n\n");
		}else{
			switch(op){
				case '1':
					ex04();
					break;
				case '2':
					ex05();
					break;
				case '3':
					ex06();
					break;
				case '4':
					ex07();
					break;
				case '5':
					ex08();
					break;
				case '6':
					ll=0;
					break;
				default:
					printf("--!!Erro!!--\n\n");
					break;
			}	
		}
	}
}
void dificil(){
	int ll, op;
	ll++;
	while(ll>0){
		printf("Para qual exercicio quer ir?\n\n 1-exercicio 09\n 2-exercicio 10\n 3-exercicio 11\n 4-exercicio 12\n 5-Voltar\n\n");
		op=getch();
		if(op!='1'&&op!='2'&&op!='3'&&op!='4'&&op!='5'){
			printf("Por favor insere um numero\n\n");
		}else{
			switch(op){
				case '1':
					ex09();
					break;
				case '2':
					ex10();
					break;
				case '3':
					ex11();
					break;
				case '4':
					ex12();
					break;
				case '5':
					ll=0;
					break;
				default:
					printf("--!!Erro!!--\n\n");
					break;
			}	
		}
	}
}
void ui(){
	int ll, op;
	ll++;
	while(ll>0){
		printf("Para qual exercicio quer ir?\n\n 1-exercicio 13\n 2-exercicio 14\n 3-exercicio 15\n 4-Voltar\n\n");
		op=getch();
		if(op!='1'&&op!='2'&&op!='3'&&op!='4'){
			printf("Por favor insere um numero\n\n");
		}else{
			switch(op){
				case '1':
					ex13();
					break;
				case '2':
					ex14();
					break;
				case '3':
					ex15();
					break;
				case '4':
					ll=0;
				default:
					printf("--!!Erro!!--\n\n");
					break;
			}	
		}
	}
}
main(){
	int l, op;
	l++;
	while(l>0){
		printf("Para qual exercicio quer ir?\n\n 1-Simpels\n 2-Medio\n 3-Dificil\n 4-UI\n 5-Sair\n\n");
		op=getch();
		if(op!='1'&&op!='2'&&op!='3'&&op!='4'&&op!='5'){
			printf("Por favor insere um numero\n\n");
			l++;
		}else{
			switch(op){
				case '1':
					simples();
					break;
				case '2':
					medio();
					break;
				case '3':
					dificil();
					break;
				case '4':
					ui();
					break;
				case '5':
					l=0;
					break;
				default:
					printf("--!!Erro!!--\n\n");
					break;
			}	
		}
	}
}
