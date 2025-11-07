#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <string.h>

main(){
	int a,g[40];
	FILE *textFile;
	textFile=fopen("test.txt","r+");
	fputc('!',textFile);
	fputs("Ola mundo",textFile);
	a=fgetc(textFile);
	fgets(g,40,textFile);
	printf("%c %s %c",a,g,a);
	fclose(textFile);
}
