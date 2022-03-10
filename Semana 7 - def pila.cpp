#include <iostream>
#include <stdlib.h>

using namespace std;

struct Nodo{
	int dato;
	Nodo *siguiente;
};

typedef Nodo *Pila;

Pila pila_Vacia();
void agregar_Pila(Pila & p, int n);
void sacar_Pila(Pila & p);
void mostrar_Pila(Pila p);


int main(){
	int comando, elemento;
	Pila p;
	p = pila_Vacia();
	while(comando != 3){
		cout << "La pila ha sido creada." << endl;
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

Pila pila_Vacia(){
	Pila p;
	p = NULL;
	return p;
}

void agregar_Pila(Pila & p, int n){
	Pila nuevo_nodo = new Nodo();
	nuevo_nodo -> dato = n;
	nuevo_nodo -> siguiente = p;
	p = nuevo_nodo;
}

void sacar_Pila(Pila & p){
	Pila aux = p;
	p = aux -> siguiente;
	delete aux;
}

void mostrar_Pila(Pila p){
	if(p -> siguiente == NULL){
		cout << p -> dato << " }\n" << endl;
	}
	else{
		cout << p -> dato << ", ";
		mostrar_Pila(p -> siguiente);
	}
}
