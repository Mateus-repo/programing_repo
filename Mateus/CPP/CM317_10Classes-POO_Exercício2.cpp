/*
Agrupamento de Escolas Marinha Grande Nascente
Curso: Curso Profissional de Programador de Informática
Disciplina: Computação Móvel
Tarefa: CM317_Classes-POO_Exercício2

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

#include <iostream>
#include <string>
using namespace std;
//Classe base
class cls_Carro {
protected:
	// 'protected' permite que classes derivadas acedam aos atributos diretamente (ao contrario de private)
	string atr_str_cls_Carro_carroMarca;
	string atr_str_cls_Carro_carroModelo;
	int atr_int_cls_Carro_carroAno;

public:
	// Construtor da classe base
	cls_Carro(const string& atr_str_cls_Carro_marcaTemp, const string& atr_str_cls_Carro_modeloTemp, int atr_int_cls_Carro_anoTemp)
		: atr_str_cls_Carro_carroMarca(atr_str_cls_Carro_marcaTemp), atr_str_cls_Carro_carroModelo(atr_str_cls_Carro_modeloTemp), atr_int_cls_Carro_carroAno(atr_int_cls_Carro_anoTemp) {
	}

	//Métodos de acesso (getters)
	string met_str_cls_Carro_getCarroMarca() const { return atr_str_cls_Carro_carroMarca; }
	string met_str_cls_Carro_getCarroModelo() const { return atr_str_cls_Carro_carroModelo; }
	int met_int_cls_Carro_getCarroAno() const { return atr_int_cls_Carro_carroAno; }

	//Método virtual: pode ser reescrito por classes derivadas
	virtual void met_vod_cls_Carro_mostrarInfo() const {
		cout << "Marca: " << atr_str_cls_Carro_carroMarca
			<< ", Modelo: " << atr_str_cls_Carro_carroModelo
			<< ", Ano: " << atr_int_cls_Carro_carroAno << endl;
	};

};
// Classe derivada

class cls_Carro_CarroEletrico : public cls_Carro {
private:
	int atr_int_cls_Carro_CarroEletrico_carroEletricoAutonomia; // km de autonomia da bateria
public:
	// Construtor da classe derivada
	cls_Carro_CarroEletrico(const string& atr_str_cls_Carro_CarroEletrico_marcaTemp, const string& atr_str_cls_Carro_CarroEletrico_modeloTemp, int atr_int_cls_Carro_CarroEletrico_anoTemp, int atr_int_cls_Carro_CarroEletrico_autonomiaTemp)
		: cls_Carro(atr_str_cls_Carro_CarroEletrico_marcaTemp, atr_str_cls_Carro_CarroEletrico_modeloTemp, atr_int_cls_Carro_CarroEletrico_anoTemp), atr_int_cls_Carro_CarroEletrico_carroEletricoAutonomia(atr_int_cls_Carro_CarroEletrico_autonomiaTemp) {
	}
	//chama o construtor da base
	int met_int_cls_Carro_CarroEletrico_getCarroEletricoAutonomia() const { return atr_int_cls_Carro_CarroEletrico_carroEletricoAutonomia; }

	//Sobrescrita (override) do metodo base
	void met_vod_cls_Carro_mostrarInfo() const override {
		// Podemos reutilizar o metodo da classe base
		cls_Carro::met_vod_cls_Carro_mostrarInfo();
		cout << ", Autonomia: " << atr_int_cls_Carro_CarroEletrico_carroEletricoAutonomia << " km" << endl;
	}
};
void endProgram(){
	cout << "\n\nPressione ENTER para sair...";
	cin.get();
}

int main() {
	cls_Carro c1("Toyota", "Yaris", 2020);
	cls_Carro_CarroEletrico ce1("Tesla", "Model 3", 2023, 480);

	cout << "--- Carro Convencional ---" << endl;
	c1.met_vod_cls_Carro_mostrarInfo();

	cout << "--- Carro Eletrico ---" << endl;
	ce1.met_vod_cls_Carro_mostrarInfo();
	endProgram();
	return 0;
	/*
		Output:

			--- Carro Convencional ---
			Marca: Toyota, Modelo: Yaris, Ano: 2020

			--- Carro Elétrico ---
			Marca: Tesla, Modelo: Model 3, Ano 2023, Autonomia 480 km
	*/
}


