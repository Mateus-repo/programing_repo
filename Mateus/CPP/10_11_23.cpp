#include <stdio.h>
#include <conio.h>

main(){
	int nota;
	printf("Qual a nota [1...5]?\n");
	scanf("%d", &nota);
	printf("%c\n", nota<1 || nota>5?'#': nota<3?'I': nota<4?'S': nota<5?'B':'M');
}
