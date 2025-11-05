/*
Agrupamento de Escolas Marinha Grande Nascente
Curso: Curso Profissional de Programador de Informática
Disciplina: Computação Móvel
Tarefa: CM316_Array-Strings_

Número: 10
Nome: Mateus Almeida Feliciano
Links de pesquisa: https://www.w3schools.com/cpp/ - https://www.geeksforgeeks.org/ - https://stackoverflow.com/questions - https://www.quantstart.com/articles/Mathematical-Constants-in-C
	https://www.geeksforgeeks.org/cpp/how-to-use-cin-fail-method-in-cpp/ https://how.dev/answers/how-to-get-the-current-date-and-time-in-cpp
	https://stackoverflow.com/questions/11587426/get-current-username-in-c-on-windows https://www.w3schools.com/cpp/ref_math_round.asp
	https://www.w3schools.com/cpp/cpp_files.asp
*/
#define _USE_MATH_DEFINES
#define NOMINMAX
#include <cmath> // matematica functions
#include <iostream> // input - output
#include <fstream> // ficheiros
#include <cstdlib>
#include <limits> 
#include <conio.h>
#include <ctime> // tempo
#include <string>
#include <windows.h> // sistem operativo functions
#include <cctype> 
#include <Lmcons.h>
#define NOME_FICHEIRO "numAlunos.txt"
#define NOTAS_AMOUNT 3
#define NUM_ALUNOS_DEFAULT 3
using namespace std;

struct alunoStructure {
	string nome = "";
	double notas[NOTAS_AMOUNT];
};

void hold();
void endProgram();
int nomeValido(const string& nome);
void menu();
void inserirAlunos(alunoStructure alunosTemp[], int sizeNotas, int numAlunos);
void changeNumAlunos(int& numAlunosTemp);

int main() {
	int numAlunos = NUM_ALUNOS_DEFAULT;
	ofstream createFile(NOME_FICHEIRO, ios::app);
	createFile.close();
	ifstream infile(NOME_FICHEIRO);
	if (infile.peek() == ifstream::traits_type::eof()) {
		ofstream outfile(NOME_FICHEIRO);
		outfile << NUM_ALUNOS_DEFAULT;
		outfile.close();
		numAlunos = NUM_ALUNOS_DEFAULT;
	}
	else {
		infile >> numAlunos;
	}
	infile.close();
	alunoStructure* alunos = new alunoStructure[numAlunos];
	int sizeNotas = sizeof(alunos[0].notas) / sizeof(alunos[0].notas[0]);
	int tempEnd = 1;
	do {
		int tempInput = 0;
		menu();
		cin >> tempInput;
		if (cin.fail()) {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max()), '\n');
			system("cls");
			cout << "Entrada invalida! Digite um numero inteiro entre 1 e 6.\n";
			hold();
			continue;
		}
		switch (tempInput) {
			case 1:
				inserirAlunos(alunos, sizeNotas, numAlunos);
				break;
			case 2:
				changeNumAlunos(numAlunos);
				ofstream outfile(NOME_FICHEIRO, ios::trunc); // trunc apaga tudo no arquivo
				if (outfile.is_open()) {
					outfile << numAlunos;
					outfile.close();
				}
				cout << "\n As mudancas apenas irao ser aplicadas apos reiniciar a app!\n";
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				tempEnd = 0;
				break;
			default:
				cout << "Erro, nao ha opcoes acima de 6 ou abaixo de 1!" << endl;
		}
		if (tempEnd) {
			hold();
		}
	} while (tempEnd);
	endProgram(); delete[] alunos; return 0;
}

void hold() {
	cout << "\n(Prima \"Enter\" para continuar a execucao!)";
	char tempOut = _getch();
	system("cls");
	return;
}

void endProgram() {
	cout << "\n(Prima \"Enter\" para terminar a execucao!)";
	char tempOut = _getch();
	system("cls");
	return;
}

int nomeValido(const string& nome) {
	for (char c : nome) {
		if (!isalpha(c) && !isspace(c)) { //se nao tiver apenas espaços e letras dá return 0
			return 0;
		}
	}
	return 1;
}

void menu() {
	system("cls");
	cout << "################### MENU ###################" << endl;
	cout << "#                                          #" << endl;
	cout << "#  [1] - Inserir alunos                    #" << endl;
	cout << "#                                          #" << endl;
	cout << "#  [2] - Definir numero de alunos          #" << endl;
	cout << "#                                          #" << endl;
	cout << "#  [3] - Listar alunos e respetivas notas  #" << endl;
	cout << "#                                          #" << endl;
	cout << "#  [4] - Média geral                       #" << endl;
	cout << "#                                          #" << endl;
	cout << "#  [5] - Alunos com as nota mais altas     #" << endl;
	cout << "#                                          #" << endl;
	cout << "#  [6] - Fechar programa                   #" << endl;
	cout << "#                                          #" << endl;
	cout << "############################################" << endl;
}

void inserirAlunos(alunoStructure alunosTemp[], int sizeNotas, int numAlunos) {
	system("cls");
	int loopTempVar = 2;
	for (int j = 0; j < numAlunos; j++) {
		loopTempVar = 2;
		while (loopTempVar == 2) {
			string nomeTemp = "";
			cout << "Digite o nome do aluno numero " << j + 1 << " : ";
			cin >> nomeTemp;
			if (nomeTemp.empty()) {
				system("cls");
				cout << "Erro: o nome não pode estar vazio!\n";
				hold();
				continue;
			}
			if (!nomeValido(nomeTemp)) {
				system("cls");
				cout << "Nome invalido!";
				hold();
				continue;
			}
			else {
				loopTempVar--;
				alunosTemp[j].nome = nomeTemp;
			}
		}
		if (loopTempVar == 1) {
			double temp = 0;
			for (int i = 0; i < sizeNotas; i++) {
				cout << "Digite a nota numero " << i + 1 << " do/a " << alunosTemp[j].nome << " (0-20): ";
				cin >> temp;
				if (cin.fail()) {
					cin.clear();
					cin.ignore((numeric_limits<streamsize>::max()), '\n');
					system("cls");
					cout << "Entrada invalida! Digite um numero inteiro entre 0 e 20.\n";
					hold();
					i--;
					continue;
				}
				else if (temp > 20 || temp < 0) {
					system("cls");
					cout << "Entrada invalida! Digite um numero inteiro entre 0 e 20.\n";
					hold();
					i--;
					continue;
				}
				else {
					alunosTemp[j].notas[i] = temp;
				}
				system("cls");
			}
		}
	}
}

void changeNumAlunos(int& numAlunosTemp) {
	system("cls");
	int temp = 0;
	int loopVar = 1;
	while (loopVar) {
		cout << "Defina o numero de alunos : ";
		cin >> temp;
		if (cin.fail()) {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max()), '\n');
			system("cls");
			cout << "Entrada invalida! Digite um numero inteiro positivo.\n";
			hold();
			continue;
		}
		else if (temp <= 0) {
			system("cls");
			cout << "Entrada invalida! Digite um numero inteiro positivo.\n";
			hold();
			continue;
		}
		else {
			numAlunosTemp = temp;
			loopVar = 0;
		}
	}
}


