#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

main(){
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
}
