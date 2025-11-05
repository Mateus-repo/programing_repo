/*
 Agrupamento de Escolas Marinha Grande Nascente
 Curso: Curso Profissional de Programador de Informática
 Disciplina: Computação Móvel
 Tarefa: CM309_Operadores lógicos

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
#define SHOW(var) std::cout << #var << " = " << (var);
#define SHOWNAME(var) std::cout << #var;
using namespace std;

void endProgram();

int main(){
	int idade = 0;
	while (true) {
        cout << "Digite a sua idade em anos: ";
        cin >> idade;
        if (cin.fail()) {
            cin.clear(); // limpa o erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // da clear no buffer
            cout << "\nEntrada invalida! Digite um numero inteiro positivo.\n\n";
        } else {
        	if(idade<0 || idade>150){
        		cout << "\nEntrada invalida! Digite um numero inteiro positivo (realista).\n\n";
			}else{ 
				system("cls");
            	break;
			}
        }
    }
	if(idade >= 18){
		cout << "Voce pode votar!\n";
	}else{
		cout << "Voce nao pode votar!\n";
	}
	endProgram();
	return 0;
}

void endProgram(){
	cout << "\n(Prima \"Enter\" para terminar a execucao!)";
	char tempOut = _getch();
}

