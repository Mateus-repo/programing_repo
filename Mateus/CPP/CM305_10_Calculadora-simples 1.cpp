/*
 Agrupamento de Escolas Marinha Grande Nascente
 Curso: Curso Profissional de Programador de Informática
 Disciplina: Computação Móvel
 Tarefa: CM304_VC++_Nome e idade

 Número: 10
 Nome: Mateus Almeida Feliciano
 Links de pesquisa: https://www.w3schools.com/cpp/ - https://www.geeksforgeeks.org/ - https://stackoverflow.com/questions
*/

#include <iostream>
#include <cstdlib>
#include <conio.h>
using namespace std;

void result(int numTemp1, int numTemp2, char operador) {
    switch (operador) {
    case '+':
        cout << "\nO resultado da adicao e " << numTemp1 + numTemp2 << "!\n";
        break;
    case '-':
        cout << "\nO resultado da subtracao e " << numTemp1 - numTemp2 << "!\n";
        break;
    case '*':
        cout << "\nO resultado da multiplicacao e " << numTemp1 * numTemp2 << "!\n";
        break;
    case '/':
        cout << "\nO resultado da divisao e " << (double)numTemp1 / numTemp2 << "!\n"; // as variaveis são do tipo int, para divisões têm de ser do tipo double
        break;
    default:
        cout << "ERRO!!";
    }
}

int main()
{
    int num[2] = { 0,0 };
    char opcao = 0;
    int loopVal = 1;
    char temp;
    for (int i = 0; i < 2; i++) {
        cout << "Define o numero #" << i + 1 << "!\n";
        cin >> num[i];
    }
    while (loopVal) {
        system("cls");
        cout << "Que operacao quer fazer? (Prima o butao correspondente)\n" << "   1 - Adicao\n   2 - Subtracao\n   3 - Multiplicacao\n   4 - Divisao\n   5 - Sair\n";
        opcao = _getch();
        switch (opcao) {
        case '1':
            result(num[0], num[1], '+');
            break;
        case '2':
            result(num[0], num[1], '-');
            break;
        case '3':
            result(num[0], num[1], '*');
            break;
        case '4':
            result(num[0], num[1], '/');
            break;
        case '5':
            return 0;
            break;
        default:
            system("cls");
            cout << "Opcao desconhecida! Tente de novo!\n";
            temp = _getch();
            loopVal++;
        }
        loopVal--;
    }
    cout << "\n(Prima \"Enter\" para terminar a execucao!)";
    temp = _getch();
}

