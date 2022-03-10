#include<iostream>
#include<conio.h>

using namespace std;

// Introduce un numero entero mayor que 1 y te devuelve su descomposicion factorial

//defino la lista de primos y el numero maximo de primos para hacerlo por array
const int MAX_PRIMOS = 100;
typedef int Lista_Primos[MAX_PRIMOS];

//defino las funciones que me serviran para la tercera parte del ejercicio

void descomponer(int numero_func, Lista_Primos primos_func, int & num_primos_func);
void mostrar(Lista_Primos primos_func, int num_elements);


int main(){
	int numero, descomp, primos_cout = 2; //Esto es para el cout directo

	int num_primos = 0, prueba_primo = 2; Lista_Primos lista_primos; //Esto para salida por arrays
	
	int numero_func, num_primos_func = 0; Lista_Primos lista_primos_func; //Esto es para salida por funcion
	
	cout<<"Hola que tal, escribe un numero y te lo descompongo en factores pls: "<<endl;
	cin >> numero;
	while(numero<=1){
		cout<<"Por favor, escribe un numero mayor que 1."<<endl;
		cin>>numero;
	}
	
	cout<<"\nLos factores usando el cout a medida que salen son: \n"<<endl;
	descomp = numero;
	while(descomp != 1){
		if(descomp % primos_cout == 0){
			cout<<primos_cout<<endl; 
			descomp = descomp / primos_cout;
		}
		else{
			primos_cout++;
		}
	}
	
	cout<<"\nLos factores calculando primero todos y sacandolos por array son: \n"<<endl;
	descomp = numero;
	while(descomp != 1){
		if (descomp % prueba_primo == 0){
			lista_primos[num_primos] = prueba_primo;
			num_primos ++;
			descomp = descomp / prueba_primo;
		}
		else{
			prueba_primo ++;
		}
	}
	for(int i = 0; i < num_primos;i++){
		cout<<lista_primos[i]<<" ";	
	}
	
	cout<<"\n\nLos factores calculando primero todos USANDO FUNCIONES y sacandolos por un array son: \n"<<endl;
	numero_func = numero;
	descomponer(numero_func, lista_primos_func, num_primos_func);
	mostrar(lista_primos_func, num_primos_func);
	
	cout<<"PULSE UNA TECLA PARA SALIR"<<endl;
	getch();
	
	return 0;
}

void descomponer(int numero_func, Lista_Primos primos_func, int & num_primos_func){
	int prueba_primos_func = 2, desc = numero_func;
	while(desc != 1){
		if(desc % prueba_primos_func == 0){
			primos_func[num_primos_func] = prueba_primos_func;
			desc = desc / prueba_primos_func;
			num_primos_func ++;
		}
		else{
			prueba_primos_func ++;
		}
	}
}

void mostrar(Lista_Primos primos_func, int num_elements){
	for(int i = 0; i<num_elements; i++){
		cout<<primos_func[i]<<" ";
	}
	cout<<"\n\nYA ESTAN TODOSS!!! BUENA TARDE CABALLERO"<<endl;
}
