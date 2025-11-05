#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#define NUM 4

void linha(int numero, char carater, int enter){
	for(int i=1;i<=numero;i++){
		printf("%c", carater);
	}
	if(enter){
		printf("\n\n");
	}
}

main(){
	//ex1
	for(int i=1;i<=NUM;i++){
		linha(i,'*',1);
	}
	printf("--------------\n\n");
	//ex2
	for(int i=1;i<=NUM;i++){
		linha(NUM,'*',1);
	}
	printf("--------------\n\n");
	//ex3
	for(int i=0;i<NUM;i++){
		linha(NUM-i,'*',1);
	}
	printf("--------------\n\n");
	//ex4
	for(int i=1;i<=NUM;i++){
		linha(NUM-i,' ',0);
		linha(i,'*',1);
	}
	printf("--------------\n\n");
	//ex5
	for(int i=1;i<=NUM;i++){
		for(int j=1;j<=NUM;j++){
			if(j==1||i==1||j==NUM||i==NUM){
				linha(1,'*',0);
			}else{
				linha(1,' ',0);
			}
		}
		linha(0,' ',1);
	}
	printf("--------------\n\n");
	//ex6
	for(int i=1;i<=NUM;i++){
		linha(i-1,' ',0);
		linha(NUM*2+1-i*2,'*',1);
	}
	printf("--------------\n\n");
	//ex7
	for(int i=1;i<=NUM+3;i++){
		if(i<=NUM){
			linha(NUM-i,' ',0);
			linha(i*2-1,'*',1);
		}else{
			linha(NUM-1,' ',0);
			linha(1,'*',1);
		}
	}
	printf("--------------\n\n");
	//ex8
	for(int i=1;i<NUM;i++){
		linha(NUM-1-i,' ',0);
		linha(i*2-1,'*',1);
	}
	for(int i=1;i<NUM;i++){
		linha(i,' ',0);
		linha((NUM-2)*2+1-i*2,'*',1);
	}
	printf("--------------\n\n");
	//ex9
	for(int i=1;i<NUM;i++){
		linha(NUM-1-i,' ',0);
		linha(1,'*',0);
		linha(i*2-3,' ',0);
		if(i!=1){
			linha(1,'*',1);
		}else{
			linha(0,'*',1);
		}
	}
	for(int i=1, j=1;i<NUM-1;i++){
		linha(i,' ',0);
		linha(1,'*',0);
		linha((NUM-3)*2+1-i*2,' ',0);
		if(i!=NUM-2){
			linha(1,'*',1);
		}else{
			linha(0,'*',1);
		}
	}
	printf("--------------\n\n");
	//ex10
	for(int i=1;i<NUM;i++){
		for(int i=1, j=1;i<NUM-1;i++){
		linha(i,' ',0);
		linha(1,'*',0);
		linha((NUM-3)*2+1-i*2,' ',0);
		if(i!=NUM-2){
			linha(1,'*',1);
		}else{
			linha(0,'*',1);
		}
	}
	for(int i=1;i<NUM;i++){
		linha(NUM-1-i,' ',0);
		linha(1,'*',0);
		linha(i*2-3,' ',0);
		if(i!=1){
			linha(1,'*',1);
		}else{
			linha(0,'*',1);
		}
	}
	}
}
