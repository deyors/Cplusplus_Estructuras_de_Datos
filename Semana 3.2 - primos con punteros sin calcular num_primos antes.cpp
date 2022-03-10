#include <iostream>

using namespace std;

typedef int * Lista_int;
const int CAP_INICIAL = 2;

/* Dado un entero y un puntero lista con espacios reservados para los primos del entero, 
rellena los primos del entero insertado.*/
int descomponer(int, Lista_int &);

//Dado un puntero lista, imprime cada uno de sus elementos en pantalla. 
void mostrar(Lista_int, int);

int main(){
	int n, num_primos; // num_primos se calcula a medida que vayamos descomponiendo, esa es la diferencia.
	Lista_int primos;
	cout << "Introduce el numero que deseas factorizar: ";
	cin >> n;
	primos = new int[CAP_INICIAL];
	num_primos = descomponer(n, primos);
	cout << "\nLos primos son los siguientes: ";
	mostrar(primos, num_primos);
	cout << "\nEl numero de primos es: " << num_primos;
	delete[] primos;
	
	return 0;
}

int num_factores(int numero){
	int descomp = numero, factor = 2, num_factores = 0;
	while(descomp != 1){
		if(descomp % factor == 0){
			descomp = descomp / factor;
			num_factores++;
		}
		else{
			factor++;
		}
	}
	return num_factores;
}

int descomponer(int n, Lista_int & primos){
	int descomp = n, factor = 2, i = 0;
	int cap = CAP_INICIAL;
	int num_primos = 0;
	while(descomp != 1){
		if(descomp % factor == 0){
			//Aquí viene que ocurre si la capacidad es igual al numero de primos y como ampliarla.
			if(cap == num_primos){
				cap = cap*2;
				Lista_int aux = new int[cap];
				for(i = 0; i < num_primos; i++){
					aux[i] = primos[i];
				}
				delete[] primos;
			    primos = aux;
			}
			primos[i] = factor;
			descomp = descomp / factor;
			i++;
			num_primos++;
		}
		else{
			factor++;
		}
	}
	return num_primos;
}

void mostrar(Lista_int primos, int num_primos){
	for(int i = 0; i < num_primos - 1; i++){
		cout << primos[i] << ", ";
	}
	cout << primos[num_primos - 1] << ".";
}
