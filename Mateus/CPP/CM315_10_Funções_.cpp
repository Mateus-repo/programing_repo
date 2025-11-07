/*
 Agrupamento de Escolas Marinha Grande Nascente
 Curso: Curso Profissional de Programador de Informática
 Disciplina: Computação Móvel
 Tarefa: CM315_Funções_

 Número: 10
 Nome: Mateus Almeida Feliciano
 Links de pesquisa: https://www.w3schools.com/cpp/ - https://www.geeksforgeeks.org/ - https://stackoverflow.com/questions - https://www.quantstart.com/articles/Mathematical-Constants-in-C
    https://www.geeksforgeeks.org/cpp/how-to-use-cin-fail-method-in-cpp/ https://how.dev/answers/how-to-get-the-current-date-and-time-in-cpp
    https://stackoverflow.com/questions/11587426/get-current-username-in-c-on-windows https://www.w3schools.com/cpp/ref_math_round.asp
*/
#define _USE_MATH_DEFINES
#define NOMINMAX 
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <conio.h>
#include <ctime>
#include <string>
#include <windows.h>
#include <Lmcons.h>
#define NOTAS_AMOUNT 3
using namespace std;

void getClassfications(int notasTemp[], int size);
int getTotal(int notasTemp[], int size);
void getAvg(double& media, int notasTemp[], int size);
void hold();
void endProgram();  

int main() {
    int notas[NOTAS_AMOUNT];
    int size = sizeof(notas) / sizeof(notas[0]);
    getClassfications(notas, size);
    int total = getTotal(notas, size);
    double var_media = 0.0;
    getAvg(var_media, notas, size);
    var_media = round(var_media * 100) / 100.0; //Exemplo var_media = 100.2332, var_media * 100 = 10023.32, round(var_media) = 10023, 10023/100 = 100.23
    system("cls");
    cout << "O total das suas notas da: " << total << ", e a media da: " << var_media << " \n"; 
    endProgram();return 0;
}

void getClassfications(int notasTemp[], int size) {
    int temp = 0;
    for (int i = 0; i < size; i++) {
        cout << "Digite a sua nota numero " << i + 1 << " (0-20): ";
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
            notasTemp[i] = temp;
        }
        system("cls");
    }
}

int getTotal(int notasTemp[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += notasTemp[i];
    }
    return total;
}

void getAvg(double& media, int notasTemp[], int size) {
    int total = getTotal(notasTemp, size);
    media = (double)total / size;
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
