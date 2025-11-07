//CM311_switch_case_break_default
/*
 Agrupamento de Escolas Marinha Grande Nascente
 Curso: Curso Profissional de Programador de Informática
 Disciplina: Computação Móvel
 Tarefa: CM313_while_

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
	double total = 0;
	double temp = 1;
	while(temp>0){
		cout << "Insere um numero: ";
		cin >> temp;
		if (cin.fail()) {
            cin.clear(); // limpa o erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // da clear no buffer
            cout << "\n\nEntrada invalida! Digite um numero.\n\n";
            temp = 1;
            continue;
        } else {
        	system("cls");
        	total += temp;
        }
	}
	cout << "O total e igual a : " << total;
	endProgram();
	return 0;
}

void endProgram() {
	cout << "\n(Prima \"Enter\" para terminar a execucao!)";
	char tempOut = _getch();
}

