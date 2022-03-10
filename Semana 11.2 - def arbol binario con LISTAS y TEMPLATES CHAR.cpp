#include<iostream>
#include<stdlib.h>

using namespace std;

template<typename T>
struct Nodo_Lista{
	T dato;
	Nodo_Lista<T> * siguiente = NULL;
	Nodo_Lista<T> * anterior = NULL;
};

//template <typename T>
//using Abb =  Nodo_arbol<T> *; (NO NOS HA FUNCIONADO CON TEMPLATES, NO SABEMOS POR QUE)

template<typename T>
struct Lista{
	int longitud = 0;
	Nodo_Lista<T> * primero = NULL;
	Nodo_Lista<T> * ultimo = NULL;
};

struct tupla_Bool_Alt{
	bool eq;
	int alt;
};

template<typename T>
struct Nodo_Arbol{
	T dato;
	Nodo_Arbol<T> * hijo_izq = NULL;
	Nodo_Arbol<T> * hijo_der = NULL;
};

//------ DEF LISTA (PARA RECORRIDO)

template<typename T>
int longitud(Lista<T> l){
	return l.longitud;
}

template<typename T>
Lista<T> lista_Vacia(){
	Lista<T> l;
	l.longitud = 0;
	l.primero = NULL;
	l.ultimo = NULL;
	return l;
}

template<typename T>
void mostrar_Lista(Lista<T> l){
	Nodo_Lista<T> * actual = l.primero;
	cout << "[ ";
	while (actual != NULL){
		cout << actual -> dato << ", ";
		actual = actual -> siguiente;
	}
	cout << " ]" << endl;
}

template<typename T>
void aniadir_der(Lista<T> & l, T e){
	Nodo_Lista<T> * nuevo_nodo = new Nodo_Lista<T>();
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

template<typename T>
void aniadir_izq(Lista<T> & l, T e){
	Nodo_Lista<T> * nuevo_nodo = new Nodo_Lista<T>();
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

template<typename T>
int izq_Lista(Lista<T> l){
	T e;
	if(l.primero == NULL){
		cout << "Error, la lista es vacia";
	}
	else{
		e = l.primero -> dato;
		return e;
	}
}

template<typename T>
void eliminar_izq(Lista<T> & l){
	Nodo_Lista<T> * aux = new Nodo_Lista<T>();
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

template<typename T>
int der_Lista(Lista<T> l){
	T e;
	if(l.ultimo == NULL){
		cout << "Error, la lista es vacia";
	}
	else{
		e = l.ultimo -> dato;
		return e;
	}
}

template<typename T>
void eliminar_der(Lista<T> & l){
	Nodo_Lista<T> * aux = new Nodo_Lista<T>();
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

template<typename T>
Lista<T> concatenar_Lista(Lista<T> & l, Lista<T> & m){
	Lista<T> result = lista_Vacia<T>();
	Nodo_Lista<T> * aux1 = l.primero;
	Nodo_Lista<T> * aux2 = m.primero;
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

//---------- DEF ARBOL

template<typename T>
Nodo_Arbol<T> * abb_Vacio(){
	return NULL;
}

template<typename T>
Nodo_Arbol<T> * plantar(Nodo_Arbol<T> * izq, T e, Nodo_Arbol<T> * der){
	Nodo_Arbol<T> * nuevo_nodo = new Nodo_Arbol<T>();
	nuevo_nodo -> dato = e;
	nuevo_nodo -> hijo_izq = izq;
	nuevo_nodo -> hijo_der = der;
	return nuevo_nodo;
}

template<typename T>
Nodo_Arbol<T> * hijo_izq(Nodo_Arbol<T> * a){
	if (a == NULL){
		cout << "Error. El arbol es vacio." << endl;
	}
	else{
		Nodo_Arbol<char> *  b = a -> hijo_izq;
		return b;
	}
}

template<typename T>
Nodo_Arbol<T> * hijo_der(Nodo_Arbol<T> * a){
	if (a == NULL){
		cout << "Error. El arbol es vacio." << endl;
	}
	else{
		Nodo_Arbol<T> * b = a -> hijo_der;
		return b;
	}
}

template<typename T>
T raiz(Nodo_Arbol<T> * a){
	if (a == NULL){
		cout << "Error. El arbol es vacio." << endl;
	}
	else{
		int e = a -> dato;
		return e;
	}
}

template<typename T>
bool es_abb_Vacio(Nodo_Arbol<T> * a){
	return a == NULL;
}

template<typename T>
int altura(Nodo_Arbol<T> * a){
	int alt = 0;
	if (es_abb_Vacio(a)){
		return alt;
	}
	else{
		alt = 1 + max(altura(hijo_izq(a)), altura(hijo_der(a)));
		return alt;
	}
}

int diferencia(int n, int m){ //Calcula la diferencia entre dos numeros enteros
	int d;
	if (n >= m){
		d = n - m;
	}
	else{
		d = m - n;
	}
	return d;
}

template<typename T>
tupla_Bool_Alt es_abb_Equilibrado(Nodo_Arbol<T> * a){
	tupla_Bool_Alt result, result1, result2;
	if (es_abb_Vacio(a)){
		result.eq = true;
		result.alt = 0;
		return result;
	}
	else{
		result1 = es_abb_Equilibrado(hijo_izq(a));
		result2 = es_abb_Equilibrado(hijo_der(a));
		result.eq = result1.eq && result2.eq && (diferencia(altura(hijo_izq(a)),altura(hijo_der(a))) <= 1);
		result.alt = 1 + max(result1.alt, result2.alt);
		return result;
	}
}

template<typename T>
Lista<T> preorden(Nodo_Arbol<T> * a){
	Lista<T> aux = lista_Vacia<T>();
	Lista<T> aux2 = lista_Vacia<T>();
	Lista<T> result = lista_Vacia<T>();
	Nodo_Arbol<T> * hijo_derecha;
	T e;
	if(es_abb_Vacio(a)){
		return result;
	}
	else{
		aux = preorden(hijo_izq(a));
		e = raiz(a);
		aniadir_izq(aux, e);
		hijo_derecha = hijo_der(a);
		aux2 = preorden(hijo_derecha);
		result = concatenar_Lista(aux, aux2);
	}
	return result;
}

template<typename T>
Lista<T> inorden(Nodo_Arbol<T> * a){
	Lista<T> aux = lista_Vacia<T>();
	Lista<T> aux2 = lista_Vacia<T>();
	Lista<T> result = lista_Vacia<T>();
	Nodo_Arbol<T> * hijo_derecha;
	T e;
	if(es_abb_Vacio(a)){
		return result;
	}
	else{
		aux = inorden(hijo_izq(a));
		e = raiz(a);
		aniadir_der(aux, e);
		hijo_derecha = hijo_der(a);
		aux2 = inorden(hijo_derecha);
		result = concatenar_Lista(aux, aux2);
	}
	return result;
}

template<typename T>
Lista<T> postorden(Nodo_Arbol<T> * a){
	Lista<T> aux = lista_Vacia<T>();
	Lista<T> aux2 = lista_Vacia<T>();
	Lista<T> result = lista_Vacia<T>();
	Nodo_Arbol<T> * hijo_derecha;
	T e;
	if(es_abb_Vacio(a)){
		return result;
	}
	else{
		aux = postorden(hijo_izq(a));
		e = raiz(a);
		hijo_derecha = hijo_der(a);
		aux2 = postorden(hijo_derecha);
		result = concatenar_Lista(aux, aux2);
		aniadir_der(result, e);
	}
	return result;
}

int main(){
	int comando, actual;
	char elemento;
	Lista<char> aux_Lista1, aux_Lista2, aux_Lista3;
	Nodo_Arbol<char> * a = abb_Vacio<char>();
	Nodo_Arbol<char> * b = abb_Vacio<char>();
	Nodo_Arbol<char> * c = abb_Vacio<char>();
	Nodo_Arbol<char> * aux1 = abb_Vacio<char>();
	Nodo_Arbol<char> * aux2 = abb_Vacio<char>();
	tupla_Bool_Alt equilibrado;
	
	while(comando != 7){
		cout << "La arbol DE CHAR ha sido creado." << endl;
		cout << "Preorden: ";
		aux_Lista1 = preorden(a); mostrar_Lista(aux_Lista1); cout << endl;
		cout << "Inorden: ";
		aux_Lista2 = inorden(a); mostrar_Lista(aux_Lista2); cout << endl;
		cout << "Postorden: ";
		aux_Lista3 = postorden(a); mostrar_Lista(aux_Lista3); cout << endl;
		equilibrado = es_abb_Equilibrado(a);
			if(equilibrado.eq){
				cout << "El arbol esta equilibrado." << endl;
			}
			else{
				cout << "El arbol no esta equilibrado." << endl;
				cout << "La distancia maxima entre alturas es: " << equilibrado.alt << endl;
			}
		cout << "\n\nEscoja entre las siguientes opciones: " << endl;
		cout << "1. Plantar un primer elemento." << endl;
		cout << "2. Representar un arbol que ya esta exo xd." << endl;
		cout << "3. OPCION NO DISPONIBLE." << endl;
		cout << "4. OPCION NO DISPONIBLE." << endl;
		cout << "5. OPCION NO DISPONIBLE." << endl;
		cout << "6. OPCION NO DISPONIBLE." << endl;
		cout << "7. Salir.\n" << endl;
		cin >> comando;
		switch(comando){
			case 1: 
				cout << "\nIntroduzca el numero que quiere insertar: " << endl;
				cin >> elemento;
				a = plantar<char>(aux1, elemento, aux2); break;
			case 2:
				b = plantar(a, 'a', aux1);
				c = plantar(aux1, 'x', b);
				a = plantar(c, 't', b);
				break;
			case 3:
				cout << "NADA DE MOMENTO"; break;
			case 4:
				cout << "NADA DE MOMENTO"; break;
			case 5:
				cout << "NADA DE MOMENTO"; break;
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
