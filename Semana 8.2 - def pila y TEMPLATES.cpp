#include <iostream>
#include <stdlib.h>
#include<cstring>

using namespace std;

template <typename T>
struct Nodo{
	T dato;
	Nodo<T> *siguiente;
};

template <typename T>
Nodo<T> * pila_Vacia(){
	Nodo<T> * p;
	p = NULL;
	return p;
}

template <typename T>
void agregar_Pila(Nodo<T> * & p, T n){
	Nodo<T> * nuevo_nodo = new Nodo<T>();
	nuevo_nodo -> dato = n;
	nuevo_nodo -> siguiente = p;
	p = nuevo_nodo;
}

template <typename T>
void sacar_Pila(Nodo<T> * & p){
	Nodo<T> * aux = p;
	p = aux -> siguiente;
	delete aux;
}

template <typename T>
void mostrar_Pila(Nodo<T> * p){
	if(p -> siguiente == NULL){
		cout << p -> dato << " }\n" << endl;
	}
	else{
		cout << p -> dato << ", ";
		mostrar_Pila(p -> siguiente);
	}
}

int main(){
	int comando;
	string elemento;
	Nodo<string> * p;
	p = pila_Vacia<string>();
	while(comando != 3){
		cout << "La pila de STRING ha sido creada." << endl;
		if(p == NULL){
		cout << "La pila esta vacia.\n" << endl;
		}
		else{
			cout << "Los elementos de la pila son: { ";
			mostrar_Pila(p);
		}
		cout << "Escoja entre las siguientes opciones: " << endl;
		cout << "1. Insertar elemento en la pila." << endl;
		cout << "2. Eliminar elemento de la pila." << endl;
		cout << "3. Salir.\n" << endl;
		cin >> comando;
		switch(comando){
			case 1: 
				cout << "\nIntroduzca el numero que quiere insertar: " << endl;
				cin >> elemento;
				agregar_Pila(p, elemento); break;
			case 2:
				if(p == NULL){
					cout << "\nNo es posible eliminar elementos." << endl;
					cout << "La pila esta vacia.\n" << endl;
					system("pause"); break;
				}
				else{
					sacar_Pila(p);
					cout << "\nEl elemento ha sido borrado." << endl;
					system("pause"); break;
				}
			case 3: 
				cout << "\nHasta luego!" << endl; system("pause"); break;
			default:
				cout << "\nLa opcion que ha marcado no existe." << endl;
				cout << "Por favor, marque una opcion disponible." << endl;
				system("pause"); break;
		}
		system("cls");
	}
	return 0;
}
