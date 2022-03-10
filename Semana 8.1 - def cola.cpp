#include<iostream>
#include<stdlib.h>

using namespace std;

struct Nodo{
	int dato;
	Nodo *siguiente;
};

struct Cola{
	Nodo *frente;
	Nodo *fin;
};

Cola cola_Vacia();
bool es_Cola_Vacia(Cola &c);
void agregar_Cola(Cola &c, int n);
void sacar_Cola(Cola &c);
void mostrar_Cola(Nodo *&frente);

int main(){
	int comando, elemento;
	Cola c;
	c = cola_Vacia();
	while(comando != 3){
		cout << "La cola ha sido creada." << endl;
		if(c.frente == NULL){
			cout << "La cola esta vacia.\n" << endl;
		}
		else{
			cout << "Los elementos de la cola son: { ";
			mostrar_Cola(c.frente);
		}
		cout << "Escoja entre las siguientes opciones: " << endl;
		cout << "1. Insertar elemento en la cola." << endl;
		cout << "2. Eliminar elemento de la cola." << endl;
		cout << "3. Salir.\n" << endl;
		cin >> comando;
		switch(comando){
			case 1:
				cout << "\nIntroduzca el numero que quiere insertar: " << endl;
				cin >> elemento;
				agregar_Cola(c, elemento); break;
			case 2:
				if(c.frente == NULL){
					cout << "\nNo es posible eliminar elementos." << endl;
					cout << "La cola esta vacia.\n" << endl;
					system("pause"); break;
				}
				else{
					sacar_Cola(c);
					cout << "\nEl elemento ha sido borrado." << endl;
					system("pause"); break;
				}
			case 3:
				cout << "Hasta luego!" << endl; system("pause"); break;
			default:
				cout << "\nLa opcion que ha marcado no existe." << endl;
				cout << "Por favor, marque una opcion disponible." << endl;
				system("pause"); break;
		}
		system("cls");
	}
	return 0;
}

Cola cola_Vacia(){
	Cola c;
	c.frente = NULL;
	c.fin = NULL;
	return c;
}

bool es_Cola_Vacia(Cola &c){
	if(c.frente == NULL){
		return true;
	}
	else{
		return false;
	}
}

void agregar_Cola(Cola &c, int n){
	Nodo *nuevo_nodo = new Nodo();
	nuevo_nodo -> dato = n;
	nuevo_nodo -> siguiente = NULL;
	if(es_Cola_Vacia(c)){
		c.frente = nuevo_nodo;
	}
	else{
		c.fin -> siguiente = nuevo_nodo;
	}
	c.fin = nuevo_nodo;
}

void sacar_Cola(Cola &c){
	int n = c.frente -> dato;
	Nodo *aux = c.frente;
	if(c.frente == c.fin){
		c.frente = NULL;
		c.fin = NULL;
	}
	else{
		c.frente = c.frente -> siguiente;
	}
	delete aux;
}

void mostrar_Cola(Nodo *&frente){
	if(frente -> siguiente == NULL){
		cout << frente -> dato << " }\n" << endl;
	}
	else{
		cout << frente -> dato << ", ";
		mostrar_Cola(frente -> siguiente);
	}
}
