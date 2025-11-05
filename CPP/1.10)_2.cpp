#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

main(){
	int i;
	for(i=1;i<=19;i++){
		if(i<=5||i>=15){
			if(i==15){
				printf("\n");
			}
			printf("*");
			if(i==5){
				printf("\n");
			}
		}
		if(i>=6&&i<=14){
			if(i==5||i==6){
				printf("*");
				if(i==6){
					printf("  ");
				}
			}
			if(i==9||i==10||i==12){
				printf("* ");
			}
			if(i==12){
				printf(" *");
			}
		}
		if(i==8||i==11){
			printf("\n");
		}
	}
}
