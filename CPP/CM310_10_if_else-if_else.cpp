/*
 Agrupamento de Escolas Marinha Grande Nascente
 Curso: Curso Profissional de Programador de Informática
 Disciplina: Computação Móvel
 Tarefa: CM304_VC++_Nome e idade

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

void showNota(int nota);

void endProgram();

int main(){
	int nota = 0;
	while (true) {
        cout << "Digite a sua nota: ";
        cin >> nota;
        if (cin.fail()) {
            cin.clear(); // limpa o erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // da clear no buffer
            cout << "\nEntrada invalida! Digite um numero inteiro positivo.\n\n";
        } else {
        	if(nota<0 || nota>20){
        		cout << "\nEntrada invalida! Digite um numero inteiro positivo.\n\n";
			}else{ 
				system("cls");
            	break;
			}
        }
    }
	showNota(nota);
	endProgram();
	return 0;
}

void showNota(int nota){
	cout << "A sua nota e: ";
	switch(nota){
		case 0: case 1: case 2: case 3: case 4:
        case 5: case 6: case 7: case 8: case 9:
            cout << "insatisfaz!\n";
            break;
        case 10: case 11: case 12: case 13:
            cout << "Satisfaz!\n";
            break;
		case 14: case 15: case 16: case 17:
			cout << "Satisfaz bem!\n";
			break;
		case 18: case 19: case 20:
			cout << "Satisfaz muito bem!";
			break;
        default:
            cout << "Fora do intervalo\n";
    }
}

void endProgram(){
	cout << "\n(Prima \"Enter\" para terminar a execucao!)";
	char tempOut = _getch();
}

