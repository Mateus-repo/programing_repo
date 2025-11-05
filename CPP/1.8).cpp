#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

main(){
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
}
