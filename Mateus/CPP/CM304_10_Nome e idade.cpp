/*
 Agrupamento de Escolas Marinha Grande Nascente
 Curso: Curso Profissional de Programador de Informática
 Disciplina: Computação Móvel 
 Tarefa: CM304_VC++_Nome e idade

 Número: 10
 Nome: Mateus Almeida Feliciano
 Links de pesquisa: https://www.w3schools.com/cpp/
*/

#include <iostream>
using namespace std;

int main() {
    int idade;
    string nome;

    cout << "Qual o seu nome?\n";
    cin >> nome;
    cout << "Qual a sua idade?\n";
    cin >> idade;
    cout << "Ola " << nome << ", tu tens " << idade << " anos!\n";
    return 0;
}
