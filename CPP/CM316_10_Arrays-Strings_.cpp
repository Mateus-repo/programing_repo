/*
Agrupamento de Escolas Marinha Grande Nascente
Curso: Curso Profissional de Programador de Informática
Disciplina: Computação Móvel
Tarefa: CM316_Array-Strings_

Número: 10
Nome: Mateus Almeida Feliciano
Links de pesquisa: https://www.w3schools.com/cpp/ - https://www.geeksforgeeks.org/ - https://stackoverflow.com/questions - https://www.quantstart.com/articles/Mathematical-Constants-in-C
	https://www.geeksforgeeks.org/cpp/how-to-use-cin-fail-method-in-cpp/ - https://how.dev/answers/how-to-get-the-current-date-and-time-in-cpp
	https://stackoverflow.com/questions/11587426/get-current-username-in-c-on-windows - https://www.w3schools.com/cpp/ref_math_round.asp
	https://www.w3schools.com/cpp/cpp_files.asp - https://stackoverflow.com/questions/7571326/why-does-dividing-two-int-not-yield-the-right-value-when-assigned-to-double
	https://www.w3schools.com/cpp/cpp_structs.asp - https://www.google.com/search?q=isalpha+cpp&rlz=1C1GCEA_enPT1173PT1173&oq=isalpha+cpp&gs_lcrp=EgZjaHJvbWUyBggAEEUYOTIJCAEQABgNGIAEMggIAhAAGA0YHjIICAMQABgNGB4yCAgEEAAYDRgeMggIBRAAGA0YHjIICAYQABgNGB4yCAgHEAAYDRgeMggICBAAGA0YHjIICAkQABgNGB7SAQgxMjM1ajBqNKgCALACAA&sourceid=chrome&ie=UTF-8
	https://www.programiz.com/cpp-programming/library-function/cctype/isalpha - https://www.programiz.com/c-programming/library-function/ctype.h/isspace
	https://www.programiz.com/c-programming/library-function/ctype.h/isspace - https://www.geeksforgeeks.org/cpp/structures-in-cpp/ - https://www.studyplan.dev/pro-cpp/file-streams/q/understanding-ios-trunc
	https://www.geeksforgeeks.org/cpp/file-handling-c-classes/ - https://www.programiz.com/cpp-programming/file-handling - https://www.w3schools.com/cpp/ref_string_empty.asp
	https://en.cppreference.com/w/cpp/language/range-for.html - https://www.geeksforgeeks.org/cpp/range-based-loop-c/
	https://www.w3schools.com/cpp/cpp_vectors.asp - https://www.geeksforgeeks.org/cpp/vector-in-cpp-stl/
*/
#define _USE_MATH_DEFINES // constantes da matematica
#define NOMINMAX // para resolver o erro do max() no verificador de cin
#include <cmath> // matematica functions
#include <iostream> // input - output
#include <fstream> // ficheiros
#include <cstdlib> // rand()
#include <limits>  // numeric_limits
#include <conio.h> //_getch()
#include <ctime> // tempo
#include <string> // strings 
#include <windows.h> // sistema operativo functions
#include <cctype> // funcoes para caracteres
#define NOME_FICHEIRO "numAlunos.txt"
#define NOTAS_AMOUNT 3
#define NUM_ALUNOS_DEFAULT 3
using namespace std;

struct alunoStructure {
	string nome = "";
	double notas[NOTAS_AMOUNT] = { 0.0 };
};
struct notaAltaStructure {
	string nome = "";
	double nota = 0.0;
};

void hold();
void endProgram();
void limparStructure(alunoStructure alunosTemp[], const int sizeNotas, const int numAlunos);
int nomeValido(const string& nome);
void menu();
void inserirAlunos(alunoStructure alunosTemp[], const int sizeNotas, const int numAlunos);
void changeNumAlunos(int& numAlunosTemp);
void listarAlunos(alunoStructure alunosTemp[], const int sizeNotas, const int numAlunos);
double mediaAlunos(alunoStructure alunosTemp[], const int sizeNotas, const int numAlunos);
void notaAlta(alunoStructure alunosTemp[], const int sizeNotas, const int numAlunos);
void gerarAlunos(alunoStructure alunosTemp[], const int sizeNotas, const int numAlunos);

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
	limparStructure(alunos, sizeNotas, numAlunos);
	int tempEnd = 1;
	do {
		int tempInput = 0;
		menu();
		cout << "\n Escolha uma opcao: ";
		cin >> tempInput;
		if (cin.fail()) {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max()), '\n');
			system("cls");
			cout << "Entrada invalida! Digite um numero inteiro entre 1 e 8.\n";
			hold();
			continue;
		}
		switch (tempInput) {
			case 1:
				inserirAlunos(alunos, sizeNotas, numAlunos);
				break;
			case 2: {
				changeNumAlunos(numAlunos);
				ofstream outfile(NOME_FICHEIRO, ios::trunc); // trunc apaga tudo no arquivo
				if (outfile.is_open()) {
					outfile << numAlunos;
					outfile.close();
				}
				cout << "\nAs mudancas apenas irao ser aplicadas apos reiniciar a app!\n";
				break;
			}
			case 3:
				listarAlunos(alunos, sizeNotas, numAlunos);
				break;
			case 4:
				system("cls");
				if (mediaAlunos(alunos, sizeNotas, numAlunos) > 0.0) {
					cout << "A media total e : " << mediaAlunos(alunos, sizeNotas, numAlunos) << endl;
				}
				else {
					cout << "Nao a registos sufecientes para fazer a media!" << endl;
				}
				break;
			case 5:
				notaAlta(alunos, sizeNotas, numAlunos);
				break;
			case 6:
				limparStructure(alunos, sizeNotas, numAlunos);
				system("cls");
				cout << "Limpo com sucesso!" << endl;
				break;
			case 7:
				gerarAlunos(alunos, sizeNotas, numAlunos);
				break;
			case 8:
				tempEnd = 0;
				break;
			default:
				cout << "Entrada invalida! Digite um numero inteiro entre 1 e 8.\n";
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

void limparStructure(alunoStructure alunosTemp[], const int sizeNotas, const int numAlunos) {
	for (int i = 0; i < numAlunos; i++) {
		alunosTemp[i].nome = "";
		for (int j = 0; j < NOTAS_AMOUNT; j++) {
			alunosTemp[i].notas[j] = 0.0;
		}
	}
}

int nomeValido(const string& nome) {
	for (char c : nome) { // vai a todos os caracteres dentro da string
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
	cout << "#  [4] - Media geral                       #" << endl;
	cout << "#                                          #" << endl;
	cout << "#  [5] - Alunos com as nota mais altas     #" << endl;
	cout << "#                                          #" << endl;
	cout << "#  [6] - Limpar registos                   #" << endl;
	cout << "#                                          #" << endl;
	cout << "#  [7] - Gerar alunos aleatorios           #" << endl;
	cout << "#                                          #" << endl;
	cout << "#  [8] - Fechar programa                   #" << endl;
	cout << "#                                          #" << endl;
	cout << "############################################" << endl;
	return;
}

void inserirAlunos(alunoStructure alunosTemp[], const int sizeNotas, const int numAlunos) {
	int loopTempVar = 2;
	for (int j = 0; j < numAlunos; j++) {
		loopTempVar = 2;
		while (loopTempVar == 2) {
			system("cls");
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
				system("cls");
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
		if (j < numAlunos - 1) {
			while (true) {
				system("cls");
				cout << "Quer continuar a inserir alunos?: [1] - Sim ; [2] - Nao " << endl;
				char opcao = _getch();
				if (opcao == '1') {
					break;
				}
				else if (opcao == '2') {
					return;
				}
				else {
					system("cls");
					cout << "\nOpcao invalida! Pressione 1 ou 2! " << endl;
					hold();
				}
			}
		}
	}
	cout << "Dados atualizados com sucesso!";
	return;
}

void changeNumAlunos(int& numAlunosTemp) {
	system("cls");
	int temp = 0;
	int loopVar = 1;
	while (loopVar) {
		cout << "Numero de alunos anterior : " << numAlunosTemp << endl;
		cout << "Defina o numero de alunos : ";
		cin >> temp;
		if (cin.fail()) {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max()), '\n');
			system("cls");
			cout << "Entrada invalida! Digite um numero inteiro positivo.\n";
			hold();
			continue;
		}else if (temp <= 0) {
			system("cls");
			cout << "Entrada invalida! Digite um numero inteiro positivo.\n";
			hold();
			continue;
		}else {
			numAlunosTemp = temp;
			loopVar = 0;
		}
	}
	return;
}

void listarAlunos(alunoStructure alunosTemp[], const int sizeNotas, const int numAlunos) {
	system("cls");
	for (int j = 0; j < numAlunos; j++) {
		cout << "##########################################" << endl;
		cout << endl;
		cout << "    Nome : " << alunosTemp[j].nome << endl;
		for (int i = 0; i < sizeNotas; i++) {
			cout << "    Nota numero " << i + 1 << " : " << alunosTemp[j].notas[i] << endl;
		}
		cout << endl;
	}
	cout << "##########################################" << endl;
	return;
}

double mediaAlunos(alunoStructure alunosTemp[], const int sizeNotas, const int numAlunos) {
	double total = 0.0;
	for (int i = 0; i < numAlunos; i++) {
		for (int j = 0; j < sizeNotas; j++) {
			total += alunosTemp[i].notas[j];
		}
	}if (total > 0) {
		double var_media = total / (double)((double)numAlunos * (double)sizeNotas);
		var_media = round(var_media * 100) / 100.0;
		return var_media;
	}else {
		return 0.0;
	}
}

void notaAlta(alunoStructure alunosTemp[], const int sizeNotas, const int numAlunos) {
	system("cls");
	notaAltaStructure* alunoNotas = new notaAltaStructure[sizeNotas];
	for (int n = 0; n < sizeNotas; n++) {
		alunoNotas[n].nota = 0.0;
	}
	int notVazio = 0;
	for (int i = 0; i < numAlunos; i++) {
		int temNota = 0;
		for (int j = 0; j < sizeNotas; j++) {
			if (alunosTemp[i].notas[j] > 0.0) {
				temNota = 1;
				break;
			}
		}
		if (temNota)
			notVazio++;
	}
	if (notVazio >= 2)
	{
		for (int i = 0; i < numAlunos; i++) {
			for (int j = 0; j < sizeNotas; j++) {
				if (alunosTemp[i].notas[j] > alunoNotas[j].nota) {
					alunoNotas[j].nota = alunosTemp[i].notas[j];
					alunoNotas[j].nome = alunosTemp[i].nome;
				}
			}
		}
		cout << "##########################################" << endl; cout << endl;
		for (int m = 0; m < sizeNotas; m++) {
			cout << "Aluno com a nota numero " << m + 1 << " mais alta é o/a " << alunoNotas[m].nome << " e teve : " << alunoNotas[m].nota << endl;
			cout << endl;
		}
		cout << "##########################################" << endl;
	}else {
		cout << "Nao a registos sufecientes para comparar!" << endl;
	}
	return;
}

void gerarAlunos(alunoStructure alunosTemp[], const int sizeNotas, const int numAlunos) {
	system("cls");
	string nomesTemp[] = {
		"Joao", "Rafeal", "Mateus", "Afonso", "Alberto", "Ricardo",
		"Kyryl", "Tiago", "Ismael", "Vera", "Laura", "David",
		"Tomas", "Goncalo", "Pedro", "Dora", "Diogo", "Ruben",
		"Roberto", "Mario", "Luis", "Santiago", "Henrique", "Domingues",
		"Martim", "Mafalda", "Matilde", "Eric", "Clara"
	};
	const int sizeNomesTemp = sizeof(nomesTemp) / sizeof(nomesTemp[0]);
	srand(static_cast<unsigned int>(time(0)));
	for (int j = 0; j < numAlunos; j++) {
		alunosTemp[j].nome = nomesTemp[rand() % sizeNomesTemp];
		for (int i = 0; i < sizeNotas; i++) {
			alunosTemp[j].notas[i] = rand() % 21;
		}
	}
	cout << "Alunos aleatorios inseridos com sucesso!" << endl;
	return;
}

