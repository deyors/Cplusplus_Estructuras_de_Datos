#include<iostream>
#include<stdlib.h>
#include<string>

using namespace std;

template<typename T>
struct Nodo_Mont{
	T dato;
	Nodo_Mont<T> * hijo_izq = NULL;
	Nodo_Mont<T> * hijo_der = NULL;
};

template<typename T>
bool es_ab_vacio(Nodo_Mont<T> * cp){
	return cp == NULL;
}

template<typename T>
int altura(Nodo_Mont<T> * cp){
	int alt = 0;
	if (es_ab_vacio(cp)){
		return alt;
	}
	else{
		alt = 1 + max(altura(cp->hijo_izq), altura(cp->hijo_der));
		return alt;
	}
}

template<typename T> //Un nodo está lleno si está vacio, tiene los dos hijos o no tiene ninguno.
bool esta_Lleno(Nodo_Mont<T> * cp){
	bool result;
	if (cp == NULL){
		result = true;
	}
	else{
		if ((cp->hijo_izq != NULL) && (cp->hijo_der != NULL)){
			result = true;
		}
		else if ((cp->hijo_izq == NULL) && (cp->hijo_der == NULL)){
			return true;
		}
		else{
			result = false;
		}
	}
	return result;
}

Nodo_Mont<int>* insertar(Nodo_Mont<int> * & cp, int e){
	Nodo_Mont<int> * arbol = new Nodo_Mont<int>();
	if (es_ab_vacio(cp)){
		arbol -> dato = e;
		arbol -> hijo_izq = NULL;
		arbol -> hijo_der = NULL;
	}
	else{
		bool bool1, bool2;
		bool1 = (altura(cp -> hijo_izq) > altura(cp -> hijo_der)) && !(esta_Lleno(cp -> hijo_izq));
		bool2 = (altura(cp->hijo_izq) == altura(cp->hijo_der)) && (esta_Lleno(cp->hijo_der));
		if (bool1 || bool2){
			arbol -> dato = max(cp->dato, e);
			arbol -> hijo_izq = insertar(cp->hijo_izq, min(cp->dato, e));
			arbol -> hijo_der = cp->hijo_der;
		}
		else{
			arbol -> dato = max(cp->dato, e);
			arbol -> hijo_izq = cp->hijo_izq;
			arbol -> hijo_der = insertar(cp->hijo_der, min(cp->dato, e));
		}
	}
	return arbol;
}

template <typename T>
void in_orden_aux(Nodo_Mont<T> * a){
	if(a != NULL){
		cout << "( ";
		in_orden_aux(a -> hijo_izq);
		cout << (a -> dato) << ",";
		in_orden_aux(a -> hijo_der);
		cout <<" )"<<endl;
	}
}

template <typename T>
void mostrar_Mont(Nodo_Mont<T> * a){
	if(a != NULL){
		cout << "DATO = " << a -> dato << endl;
		cout << "HIJO IZQ = ";
		mostrar_Mont(a -> hijo_izq);
		cout << endl;
		cout << "HIJO DER = ";
		cout << endl;
		mostrar_Mont(a -> hijo_der);
	}
}

template <typename T>
void in_orden(Nodo_Mont<T> * a){
	if(es_ab_vacio(a)){
		cout << "Este arbol esta vacio." << endl;
	}
	else{
		in_orden_aux(a);
	}
}

int main(){
	Nodo_Mont<int> * cp = NULL;
	int comando, elemento, actual;
	while(comando != 7){
		cout << "El arbol monticulo ha sido creado." << endl;
		mostrar_Mont(cp);
		cout << "\n\nEscoja entre las siguientes opciones: " << endl;
		cout << "1. Insertar elemento en el monticulo." << endl;
		cout << "2. NO DISPONIBLE." << endl;
		cout << "3. NO DISPONIBLE." << endl;
		cout << "4. NO DISPONIBLE." << endl;
		cout << "5. NO DISPONIBLE." << endl;
		cout << "6. NO DISPONIBLE." << endl;
		cout << "7. Salir.\n" << endl;
		cin >> comando;
		switch(comando){
			case 1: 
				cout << "\nIntroduzca el numero que quiere insertar: " << endl;
				cin >> elemento;
				cp = insertar(cp, elemento); break;
			case 2:
				cout << "NO."; break;
			case 3:
				cout << "NO."; break;
			case 4:
				cout << "NO."; break;
			case 5:
				cout << "NO."; break;
			case 6:
				cout << "NO."; break;
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
