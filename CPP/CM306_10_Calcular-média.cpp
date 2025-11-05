/*
 Agrupamento de Escolas Marinha Grande Nascente
 Curso: Curso Profissional de Programador de Informática
 Disciplina: Computação Móvel
 Tarefa: CM304_VC++_Nome e idade

 Número: 10
 Nome: Mateus Almeida Feliciano
 Links de pesquisa: https://www.w3schools.com/cpp/ - https://www.geeksforgeeks.org/ - https://stackoverflow.com/questions
*/
#define TAMANHO 3
#include <iostream>
#include <cstdlib>
#include <conio.h>
using namespace std;

double media(double num[], int size) {
	double total = 0;
	for (int i = 0;i < size;i++) {
		total += num[i];
	}
	return(total / size);
}

int main() {
	double num[TAMANHO];
	for (int i = 0;i < 3;i++) {
		cout << "Escreva o numero #" << i + 1 << ": ";
		cin >> num[i];
		cout << "\n";
	}
	system("cls");
	cout << "A media e igual a : " << media(num, sizeof(num) / sizeof(num[0]));
	cout << "\n(Prima \"Enter\" para terminar a execucao!)";
	char temp = _getch();
}
