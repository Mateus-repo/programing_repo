#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#define MAX 5
main(){
	int seila[MAX]={-1,-1,-1,-1,-1};
	seila[0]=getch();
	seila[1]=getch();
	for(int i=0;i<MAX;i++){
		if(seila[i]!=-1){
			printf("%d - <%d>\n",i+1,seila[i]);
		}
	}
}
