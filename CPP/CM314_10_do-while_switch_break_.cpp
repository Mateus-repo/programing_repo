/*
 Agrupamento de Escolas Marinha Grande Nascente
 Curso: Curso Profissional de Programador de Informática
 Disciplina: Computação Móvel
 Tarefa: CM313_do-while_switch_break_

 Número: 10
 Nome: Mateus Almeida Feliciano
 Links de pesquisa: https://www.w3schools.com/cpp/ - https://www.geeksforgeeks.org/ - https://stackoverflow.com/questions - https://www.quantstart.com/articles/Mathematical-Constants-in-C
	https://www.geeksforgeeks.org/cpp/how-to-use-cin-fail-method-in-cpp/ https://how.dev/answers/how-to-get-the-current-date-and-time-in-cpp
	https://stackoverflow.com/questions/11587426/get-current-username-in-c-on-windows
*/
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <conio.h>
#include <ctime>
#include <string>
#include <windows.h>
#include <Lmcons.h>
#define MAX 10
#define MIN 1
#define SHOW(var) std::cout << #var << " = " << (var);
#define SHOWNAME(var) std::cout << #var;
using namespace std;	

void menu();
void hold();
char* getLocalTime_Date();
string displayUsername();
void endProgram();

main(){
	int running = 1;
	int choice = 0;
	while(running){
		menu();
		cout << "\nEscolha uma opcao: ";
		cin >> choice;
		if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            system("cls");
            cout << "Entrada invalida! Digite um numero inteiro entre 1 e 3.\n\n";
            hold();
            continue;
        }
        system("cls");
        switch(choice){
        	case 1:
        		cout << getLocalTime_Date();
        		hold();
        		break;
        	case 2:
        		cout << "O nome do seu utilizador e : " << displayUsername() << "!\n";
        		hold();
        		break;
        	case 3:
        		running = 0;
        		break;
        	default:
        		cout << "Entrada invalida! Digite um numero inteiro entre 1 e 3.\n\n";
        		hold();
		}
		system("cls");
	}
	return 0;
}

void menu(){
	cout << "############ MENU ############" << "\n";
	cout << "#                            #" << "\n";
	cout << "#    1 - Data atual          #" << "\n";
	cout << "#                            #" << "\n";
	cout << "#    2 - Nome do utilizador  #" << "\n";
	cout << "#                            #" << "\n";
	cout << "#    3 - Sair do Programa    #" << "\n";
	cout << "#                            #" << "\n";
	cout << "##############################" << "\n";
	return;
}

char* getLocalTime_Date(){
	time_t now = time(0);
	struct tm *local_time = localtime(&now);
	char* date_time = asctime(local_time);
	return(date_time);
}

string displayUsername(){
	char username[UNLEN+1];
	DWORD username_len = sizeof(username);
	GetUserName(username, &username_len);
	return string(username);
}

void hold(){
	cout << "\n(Prima \"Enter\" para continuar a execucao!)";
	char tempOut = _getch();
	system("cls");
	return;
}

void endProgram(){
	cout << "\n(Prima \"Enter\" para terminar a execucao!)";
	char tempOut = _getch();
	system("cls");
	return;
}
