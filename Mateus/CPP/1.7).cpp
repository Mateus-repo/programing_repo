#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

main(){
	int i;
	for(i=1;i<=9;i++){
		if(i%3==0){
			printf("*\n\n");
		}else{
			printf("*");
		}
	}
}
