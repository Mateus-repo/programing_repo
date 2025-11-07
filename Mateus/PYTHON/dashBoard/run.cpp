// run_streamlit.cpp
// Programa simples em C++ que executa o comando:
//    py -m streamlit run main-2.py
// Use isto quando quiseres lançar o Streamlit a partir de um executável.
// Compilar (Windows com g++):
//    g++ -std=c++17 run_streamlit.cpp -o run_streamlit.exe
// Executar:
//    ./run_streamlit.exe

#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // Comando por defeito (pode alterar para outro ficheiro se quiseres)
    std::string command = "py -m streamlit run main-2.py";

    // Se o utilizador passou um argumento, usa-o como ficheiro Python
    if (argc >= 2) {
        std::string script = argv[1];
        // montar comando seguro (simples concatenação)
        command = "py -m streamlit run " + script;
    }

    std::cout << "A executar: " << command << std::endl;
    std::cout << "(Press Ctrl+C para interromper o Streamlit quando for necessario)" << std::endl;

    // Chama o comando no shell - bloqueante: o programa espera até o Streamlit terminar
    int ret = std::system(command.c_str());

    if (ret == -1) {
        std::cerr << "Erro: falha ao lancar o comando." << std::endl;
        return 1;
    }

    // system() devolve o código de saída do processo (dependente do sistema)
    std::cout << "Comando terminou com codigo: " << ret << std::endl;

    return 0;
}

