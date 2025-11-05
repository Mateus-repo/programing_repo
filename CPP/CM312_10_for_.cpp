//CM311_switch_case_break_default
/*
 Agrupamento de Escolas Marinha Grande Nascente
 Curso: Curso Profissional de Programador de Informática
 Disciplina: Computação Móvel
 Tarefa: CM312_for_

 Número: 10
 Nome: Mateus Almeida Feliciano
 Links de pesquisa: https://www.w3schools.com/cpp/ - https://www.geeksforgeeks.org/ - https://stackoverflow.com/questions - https://www.quantstart.com/articles/Mathematical-Constants-in-C
	https://www.geeksforgeeks.org/cpp/how-to-use-cin-fail-method-in-cpp/
*/
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <conio.h>
#include <ctime>
#include <string>
#define MAX 10
#define MIN 1
#define SHOW(var) std::cout << #var << " = " << (var);
#define SHOWNAME(var) std::cout << #var;
using namespace std;

void endProgram();

int main() {
	int num[2] = { 0,0 };
	int tempLoop = 1;
	while (tempLoop) {
		cout << "Insira dois numeros entre " << MIN << " e " << MAX << " :\n";
		cout << "Primeiro numero : ";
		cin >> num[0];
		if (cin.fail()) {
			cin.clear(); // limpa o erro
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // da clear no buffer
			cout << "\nEntrada invalida! Digite um numero positivo.\n\n";
			continue;
		}
		if (MIN > num[0] || MAX < num[0]) {
			system("cls");
			cout << "Erro, o numero nao pode ser maior de " << MAX << " ou menor de " << MIN << ".\n\n";
		}
		else {
			tempLoop = 0;
			system("cls");
			break;
		}
	}
	while (tempLoop == 0) {
		cout << "Insira dois numeros entre " << MIN << " e " << MAX << " :\n";
		cout << "Primeiro numero : " << num[0] << " \n";
		cout << "Segundo numero : ";
		cin >> num[1];
		if (cin.fail()) {
			cin.clear(); // limpa o erro
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // da clear no buffer
			system("cls");
			cout << "\nEntrada invalida! Digite um numero positivo.\n\n";
			continue;
		}
		if (num[1]<num[0] || num[1]>MAX) {
			system("cls");
			cout << "O segundo numero tem de ser maior ou igual a " << num[0] << " e nao pode ser maior de " << MAX << " ou menor de " << MIN << " \n\n";
		}
		else {
			tempLoop = 1;
			break;
		}

	}
	system("cls");
	cout << "Primeiro numero : " << num[0] << " \n";
	cout << "Segundo numero : " << num[1] << " \n\n";
	for (int i = num[0]; i <= num[1]; i++) {
		cout << "Tabela de multiplicao do num " << i << " \n";
		for (int j = 0; j < MAX; j++) {
			cout << i << " * " << j + 1 << " = " << i * (j + 1) << " \n";
		}
		cout << "\n";
	}
	endProgram();
	return 0;
}

void endProgram() {
	cout << "\n(Prima \"Enter\" para terminar a execucao!)";
	char tempOut = _getch();
}
