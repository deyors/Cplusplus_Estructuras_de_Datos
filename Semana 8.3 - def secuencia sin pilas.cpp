#include<iostream>
#include <stdlib.h>

using namespace std;

struct Nodo{
	int dato;
	Nodo * siguiente;
};

struct Secuencia{
	Nodo * primero;
	Nodo * anterior;
};

Secuencia sec_Vacia(){
	Secuencia s;
	Nodo * fant = new Nodo();
	s.primero = fant;
	s.anterior = fant;
	fant -> siguiente = NULL;
	return s;
}

void insertar_Sec(Secuencia & s, int e){
	Nodo *nuevo_nodo = new Nodo();
	nuevo_nodo -> dato = e;
	nuevo_nodo -> siguiente = s.anterior -> siguiente;
	s.anterior -> siguiente = nuevo_nodo;
	s.anterior = nuevo_nodo;
}

void eliminar_Sec(Secuencia & s){
	if (s.anterior -> siguiente == NULL){
		cout << "Error. No existe punto de interes que eliminar." << endl;
	}
	else{
		Nodo * aux = s.anterior -> siguiente;
		s.anterior -> siguiente = aux -> siguiente;
		delete aux;
		cout << "\nEl elemento ha sido borrado." << endl;
	}
}

void actual_Sec(Secuencia s){
	int punto_interes;
	if (s.anterior -> siguiente == NULL){
		cout << "Error. No existe punto de interes que consultar." << endl;
	}
	else{
		punto_interes = (s.anterior -> siguiente ) -> dato;
		cout << "El punto de interes es: " << punto_interes << endl;
	}
}

void avanzar_Sec(Secuencia & s){
	if (s.anterior -> siguiente == NULL){
		cout << "Error. No existe punto de interes al que avanzar.";
	}
	else{
		s.anterior = s.anterior -> siguiente;
	}
}

void reiniciar_Sec(Secuencia & s){
	s.anterior = s.primero;
}

bool fin_Sec(Secuencia s){
	return (s.anterior -> siguiente == NULL);
}

bool es_Sec_Vacia(Secuencia s){
	return(s.primero -> siguiente == NULL);
}

void mostrar_Sec(Secuencia s){
	if (es_Sec_Vacia(s)){
		cout << "La secuencia es vacia.";
	}
	else{
		cout << "{ ";
		Nodo * aux = s.primero;
		if (aux == s.anterior){
				cout << "-> ";
			}
		aux = s.primero -> siguiente;
		while (aux -> siguiente != NULL){
			cout << aux -> dato << ", ";
			if (aux == s.anterior){
				cout << " -> ";
			}
			aux = aux -> siguiente;	
		}
		cout << aux -> dato;
		if (aux == s.anterior){
				cout << ", -> ";
			}
		cout << " }";
	}
}

int main(){
	int comando, elemento, actual;
	Secuencia s;
	s = sec_Vacia();
	while(comando != 7){
		cout << "La secuencia ha sido creada." << endl;
		mostrar_Sec(s);
		cout << "\n\nEscoja entre las siguientes opciones: " << endl;
		cout << "1. Insertar elemento delante del punto de interes en la secuencia." << endl;
		cout << "2. Eliminar elemento en el punto de interes de la secuencia." << endl;
		cout << "3. Consultar el elemento del punto de interes." << endl;
		cout << "4. Avanzar en un elemento el punto de interes." << endl;
		cout << "5. Trasladar el punto de interes al comienzo de la secuencia (reiniciar)." << endl;
		cout << "6. Comprobar si se esta al final de la lista." << endl;
		cout << "7. Salir.\n" << endl;
		cin >> comando;
		switch(comando){
			case 1: 
				cout << "\nIntroduzca el numero que quiere insertar: " << endl;
				cin >> elemento;
				insertar_Sec(s, elemento); break;
			case 2:
				eliminar_Sec(s);
					system("pause"); break;
			case 3:
				actual_Sec(s);
			 	system("pause"); break;
			case 4:
				avanzar_Sec(s); break;
			case 5:
				reiniciar_Sec(s); break;
			case 6:
				if (fin_Sec(s)){
					cout << "\nSe ha llegado al final de la secuencia." << endl;
				}
				else{
					cout << "\nNo se ha llegado al final de la secuencia." << endl;
				}
				system("pause"); break;
			case 7: 
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
