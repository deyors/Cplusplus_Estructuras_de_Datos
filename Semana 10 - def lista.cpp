#include<iostream>
#include <stdlib.h>

using namespace std;

struct Nodo_Lista{
	int dato;
	Nodo_Lista * siguiente = NULL;
	Nodo_Lista * anterior = NULL;
};

struct Lista{
	int longitud = 0;
	Nodo_Lista * primero = NULL;
	Nodo_Lista * ultimo = NULL;
};

int longitud(Lista l){
	return l.longitud;
}

Lista lista_Vacia(){
	Lista l;
	l.longitud = 0;
	l.primero = NULL;
	l.ultimo = NULL;
	return l;
}

void aniadir_der(Lista & l, int e){
	Nodo_Lista * nuevo_nodo = new Nodo_Lista();
	nuevo_nodo -> dato = e;
	nuevo_nodo -> siguiente = NULL;
	if (l.ultimo == NULL){
		nuevo_nodo -> anterior = NULL;
		l.primero = nuevo_nodo;
	}
	else{
		nuevo_nodo -> anterior = l.ultimo;
		l.ultimo -> siguiente = nuevo_nodo;
	}
	l.ultimo = nuevo_nodo;
	l.longitud++;
}

void aniadir_izq(Lista & l, int e){
	Nodo_Lista * nuevo_nodo = new Nodo_Lista();
	nuevo_nodo -> dato = e;
	nuevo_nodo -> anterior = NULL;
	if (l.primero == NULL){
		nuevo_nodo -> siguiente = NULL;
		l.ultimo = nuevo_nodo;
	}
	else{
		nuevo_nodo -> siguiente = l.primero;
		l.primero -> anterior = nuevo_nodo;
	}
	l.primero = nuevo_nodo;
	l.longitud++;
}

int izq_Lista(Lista l){
	int e;
	if(l.primero == NULL){
		cout << "Error, la lista es vacia";
	}
	else{
		e = l.primero -> dato;
		return e;
	}
}

void eliminar_izq(Lista & l){
	Nodo_Lista * aux = new Nodo_Lista();
	if (l.primero == NULL){
		cout << "Error, la lista es vacia";
	}
	else{
		aux = l.primero;
		l.primero = aux -> siguiente;
		if(l.primero == NULL){
			l.ultimo = NULL;
		}
		else{
			l.primero -> anterior = NULL;
		}
		l.longitud = l.longitud - 1;
		delete aux;
	}
}

int der_Lista(Lista l){
	int e;
	if(l.ultimo == NULL){
		cout << "Error, la lista es vacia";
	}
	else{
		e = l.ultimo -> dato;
		return e;
	}
}

void eliminar_der(Lista & l){
	Nodo_Lista * aux = new Nodo_Lista();
	if (l.ultimo == NULL){
		cout << "Error, la lista es vacia";
	}
	else{
		aux = l.ultimo;
		l.ultimo = aux -> anterior;
		if(l.ultimo == NULL){
			l.primero = NULL;
		}
		else{
			l.ultimo -> siguiente = NULL;
		}
		l.longitud = l.longitud - 1;
		delete aux;
	}
}

Lista concatenar_Lista(Lista & l, Lista & m){
	Lista result = lista_Vacia();
	Nodo_Lista * aux1 = l.primero;
	Nodo_Lista * aux2 = m.primero;
	while(aux1 != NULL){
		aniadir_der(result, aux1 -> dato);
		aux1 = aux1 -> siguiente;
		eliminar_izq(l);
	}
	while(aux2 != NULL){
		aniadir_der(result, aux2 -> dato);
		aux2 = aux2 -> siguiente;
		eliminar_izq(m);
	}
	return result;
}

void mostrar_Lista(Lista l){
	Nodo_Lista * actual = l.primero;
	cout << "[ ";
	while (actual != NULL){
		cout << actual -> dato << ", ";
		actual = actual -> siguiente;
	}
	cout << " ]" << endl;
}

int main(){
	int comando, elemento, actual;
	Lista l, m, n, result;
	l = lista_Vacia();
	m = lista_Vacia();
	n = lista_Vacia();
	while(comando != 7){
		cout << "La lista ha sido creada." << endl;
		mostrar_Lista(l);
		cout << "\n\nEscoja entre las siguientes opciones: " << endl;
		cout << "1. Insertar elemento a la izquierda." << endl;
		cout << "2. Insertar un elemento a la derecha de la lista." << endl;
		cout << "3. Eliminar un elemento a la izquierda de la lista." << endl;
		cout << "4. Eliminar un elemento a la derecha de la lista." << endl;
		cout << "5. Concatenar las listas [3,2,1] y [4,5,6]." << endl;
		cout << "6. OPCION NO DISPONIBLE." << endl;
		cout << "7. Salir.\n" << endl;
		cin >> comando;
		switch(comando){
			case 1:
				cout << "\nIntroduzca el numero que quiere insertar: " << endl;
				cin >> elemento;
				aniadir_izq(l, elemento); break;
			case 2:
				cout << "\nIntroduzca el numero que quiere insertar: " << endl;
				cin >> elemento;
				aniadir_der(l, elemento); break;
			case 3:
				eliminar_izq(l);
			 	system("pause"); break;
			case 4:
				eliminar_der(l);
			 	system("pause"); break;
			case 5:
				aniadir_der(m, 3);
				aniadir_der(m, 2);
				aniadir_der(m, 1);
				aniadir_der(n, 4);
				aniadir_der(n, 5);
				aniadir_der(n, 6);
				mostrar_Lista(m);
				cout << " ++ ";
				mostrar_Lista(n);
				cout << " = ";
				result = concatenar_Lista(m,n);
				mostrar_Lista(result);
				system("pause"); break;
			case 6:
				cout << "NADA DE MOMENTO"; break;
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
