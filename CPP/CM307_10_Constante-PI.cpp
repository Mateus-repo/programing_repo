/*
 Agrupamento de Escolas Marinha Grande Nascente
 Curso: Curso Profissional de Programador de Informática
 Disciplina: Computação Móvel
 Tarefa: CM304_VC++_Nome e idade

 Número: 10
 Nome: Mateus Almeida Feliciano
 Links de pesquisa: https://www.w3schools.com/cpp/ - https://www.geeksforgeeks.org/ - https://stackoverflow.com/questions - https://www.quantstart.com/articles/Mathematical-Constants-in-C
*/
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <conio.h>
using namespace std;

double calcAreaCirculo(double raio){
	double area = raio*raio*M_PI;
	return(area);
}

int main(){
	double raio = 0;
	cout << "Escreva o raio do circulo: ";
	cin >> raio;
	system("cls");
	cout << "A area do circulo e: " << calcAreaCirculo(raio) << "\n";
	cout << "\n(Prima \"Enter\" para terminar a execucao!)";
	char temp = _getch();
	return 0;
}
