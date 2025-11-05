#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

main(){
	int i, j;
	for(i=1;i<=5;i++){
		for(j=1;j<=9;j++){
			if(j>9-i||j==5){
				printf("*");
			}else{
				printf(" ");
			}
		}
		printf("\n");
	}
}
