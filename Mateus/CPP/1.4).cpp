#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

main(){
	int i;
	for(i=1;i<=5;i++){
		if(i%2==0){
			printf("*");
		}else{
			printf("#");
		}
	}
}
