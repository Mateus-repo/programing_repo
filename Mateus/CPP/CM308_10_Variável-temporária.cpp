/*
 Agrupamento de Escolas Marinha Grande Nascente
 Curso: Curso Profissional de Programador de Informática
 Disciplina: Computação Móvel
 Tarefa: CM304_VC++_Nome e idade

 Número: 10
 Nome: Mateus Almeida Feliciano
 Links de pesquisa: https://www.w3schools.com/cpp/ - https://www.geeksforgeeks.org/ - https://stackoverflow.com/questions - https://www.quantstart.com/articles/Mathematical-Constants-in-C
*/
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <conio.h>
#define SHOW(var) std::cout << #var << " = " << (var);
#define SHOWNAME(var) std::cout << #var;
using namespace std;

int main(){
	int a = 23;
	SHOWDIF(a);
	double numero_1 = 0, numero_2 = 0;
	cout << "Digite o "; SHOWNAME(numero_1); cout << " : ";
	cin >> numero_1; cout << "\n";
	cout << "Digite o "; SHOWNAME(numero_2); cout << " : ";
	cin >> numero_2; cout << "\n";
	double temp = numero_1;
	numero_1 = numero_2;
	numero_2 = temp;
	system("cls");
	SHOW(numero_1); cout << " e "; SHOW(numero_2); cout << "\n";
	cout << "\n(Prima \"Enter\" para terminar a execucao!)";
	char tempOut = _getch();
	return 0;
}
