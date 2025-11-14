/*
Agrupamento de Escolas Marinha Grande Nascente
Curso: Curso Profissional de Programador de Informática
Disciplina: Computaçao Móvel
Tarefa: CM318_Classes-POO_Exercício2A_

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

#define NOMINMAX
#include <iostream>
#include <conio.h>
#include <limits>
#include <windows.h>
#include <string>
#define SHOWNAME(var) std::cout << #var;
using namespace std;

class cls_retangulo {
private:
    double atr_dbl_cls_retangulo_comprimento;
    double atr_dbl_cls_retangulo_largura;
public:
    cls_retangulo(double atr_dbl_cls_retangulo_comprimentoTemp, double atr_dbl_cls_retangulo_larguraTemp)
        : atr_dbl_cls_retangulo_comprimento(atr_dbl_cls_retangulo_comprimentoTemp),
        atr_dbl_cls_retangulo_largura(atr_dbl_cls_retangulo_larguraTemp)
    {
    }

    double met_dbl_cls_retangulo_getComprimento() const { return atr_dbl_cls_retangulo_comprimento; }
    double met_dbl_cls_retangulo_getLargura() const { return atr_dbl_cls_retangulo_largura; }

    double met_dbl_cls_retangulo_calcArea() {
        return (atr_dbl_cls_retangulo_comprimento * atr_dbl_cls_retangulo_largura);
    }

    double met_dbl_cls_retangulo_calcPerimetro() {
        return (2 * (atr_dbl_cls_retangulo_comprimento + atr_dbl_cls_retangulo_largura));
    }
};

void hold();
void endProgram();

int main() {
    double atr_dbl_main_comprimento, atr_dbl_main_largura;
    while(1){
        cout << "Digite o comprimento do retangulo: ";
        cin >> atr_dbl_main_comprimento;
        if (cin.fail()) {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max()), '\n');
            system("cls");
            cout << "Entrada invalida! Digite um numero positivo.\n";
            hold();
            continue;
        }else if (atr_dbl_main_comprimento<=0){
            cout << "Entrada invalida! Digite um numero positivo.\n";
            hold();
            continue;
        }
        else {
            break;
        }
    }
    while (1) {
        cout << "Digite a largura do retangulo: ";
        cin >> atr_dbl_main_largura;
        if (cin.fail()) {
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max()), '\n');
            system("cls");
            cout << "Entrada invalida! Digite um numero positivo.\n";
            hold();
            continue;
        }else if (atr_dbl_main_largura<=0){
            cout << "Entrada invalida! Digite um numero positivo.\n";
            hold();
            continue;
        }
        else {
            break;
        }
    }
    cls_retangulo obj_cls_retangulo1(atr_dbl_main_comprimento, atr_dbl_main_largura);
    cout << endl << "O "; SHOWNAME(obj_cls_retangulo1); cout << " tem: " << endl;
    cout << "   comprimento = " << obj_cls_retangulo1.met_dbl_cls_retangulo_getComprimento() << endl;
    cout << "   largura = " << obj_cls_retangulo1.met_dbl_cls_retangulo_getLargura() << endl;
    cout << "   area = " << obj_cls_retangulo1.met_dbl_cls_retangulo_calcArea() << endl;
    cout << "   perimetro = " << obj_cls_retangulo1.met_dbl_cls_retangulo_calcPerimetro() << endl;

    cls_retangulo obj_cls_retangulo2(obj_cls_retangulo1.met_dbl_cls_retangulo_getComprimento(), obj_cls_retangulo1.met_dbl_cls_retangulo_getLargura());
    cout << endl << "O "; SHOWNAME(obj_cls_retangulo2); cout << " tem: " << endl;
    cout << "   comprimento = " << obj_cls_retangulo2.met_dbl_cls_retangulo_getComprimento() << endl;
    cout << "   largura = " << obj_cls_retangulo2.met_dbl_cls_retangulo_getLargura() << endl;
    cout << "   area = " << obj_cls_retangulo2.met_dbl_cls_retangulo_calcArea() << endl;
    cout << "   perimetro = " << obj_cls_retangulo2.met_dbl_cls_retangulo_calcPerimetro() << endl;
    endProgram();

    return 0;
}

void hold() {
    cout << "\n(Prima \"Enter\" para continuar a execucao!)";
    char atr_chr_hld_tempOut = _getch();
    system("cls");
    return;
}

void endProgram() {
    cout << "\n\nPressione ENTER para sair...";
    char atr_chr_end_tempOut = _getch();
    system("cls");
    return;
}
