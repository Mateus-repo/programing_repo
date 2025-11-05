//CM311_switch_case_break_default
/*
 Agrupamento de Escolas Marinha Grande Nascente
 Curso: Curso Profissional de Programador de Informática
 Disciplina: Computação Móvel
 Tarefa: CM311_switch_case_break_default

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
#define MAX 7
#define MIN 1
#define SHOW(var) std::cout << #var << " = " << (var);
#define SHOWNAME(var) std::cout << #var;
using namespace std;

void endProgram();

int lerNumEntre();

void diaDaSemana(int dia);

int main(){
	int diaWeek = lerNumEntre();
	system("cls");
	diaDaSemana(diaWeek);
	endProgram();
	return 0;
}

void endProgram(){
	cout << "\n(Prima \"Enter\" para terminar a execucao!)";
	char tempOut = _getch();
}

int lerNumEntre(){
	int num = 0;
	int check=1;
	while(check){
		cout << "Escreva um numero entre 1 e 7 : ";
		cin >> num;
		if(cin.fail()){ 
		 	system("cls");
			cout << "Erro, o numero tem de ser entre " << MIN << " e " << MAX << ".\n\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpa o buffer
            continue;
        }
		
		if(num>MAX || num<MIN){
			system("cls");
			cout << "Erro, o numero tem de ser entre " << MIN << " e " << MAX << ".\n\n";
 		}else{
 			check = 0;
		}
	}
	
	return num;
}

void diaDaSemana(int dia){
	string stringDia = "";
	switch(dia) {
        case 1:
            stringDia = "Domingo";
            break;
        case 2:
            stringDia = "Segunda";
            break;
        case 3:
            stringDia = "Terca";
            break;
        case 4:
            stringDia = "Quarta";
            break;
        case 5:
            stringDia = "Quinta";
            break;
        case 6:
            stringDia = "Sexta";
            break;
        case 7:
            stringDia = "Sabado";
            break;
        default:
            stringDia = "\nDia inválido\n";
            break;
    }
    cout << "O dia da semana correspondente e: " << stringDia << ".";
}
