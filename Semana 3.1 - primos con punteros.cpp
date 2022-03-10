#include <iostream>

using namespace std;

typedef int * Lista_int;

// Dado un entero devuelve el numero de factores que tiene
int num_factores(int);

/* Dado un entero, un puntero lista con espacios reservados para los primos del entero y el numero de primos del entero, 
rellena los espacios reservados con los primos del entero insertado.*/
void descomponer(int n, Lista_int primos, int num_primos);

//Dado un puntero lista con num_primos elementos, imprime cada uno de ellos en pantalla. 
void mostrar(Lista_int primos, int num_primos);

int main(){
	int n, num_fact;
	Lista_int primos;
	cout << "Introduce el numero que deseas factorizar" << endl;
	cin >> n;
	num_fact = num_factores(n);
	cout << "\nEl numero de factores es: " << num_factores(n) << endl;
	primos = new int[num_fact];
	descomponer(n, primos, num_fact);
	cout << "Los primos son los siguientes: ";
	mostrar(primos, num_fact);
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

void descomponer(int n, Lista_int primos, int num_primos){
	int descomp = n, factor = 2, i = 0;
	while(descomp != 1){
		if(descomp % factor == 0){
			primos[i] = factor;
			descomp = descomp / factor;
			i++;
		}
		else{
			factor++;
		}
	} 
}

void mostrar(Lista_int primos, int num_primos){
	for(int i = 0; i < num_primos - 1; i++){
		cout << primos[i] << ", ";
	}
	cout << primos[num_primos - 1] << ".";
}
