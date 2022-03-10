#include<iostream>
#include<stdlib.h>

using namespace std;

//---------- DEF LISTA (Para el recorrido)

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

struct tupla_Bool_Alt{
	bool eq;
	int alt;
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

void mostrar_Lista(Lista l){
	Nodo_Lista * actual = l.primero;
	cout << "[ ";
	while (actual != NULL){
		cout << actual -> dato << ", ";
		actual = actual -> siguiente;
	}
	cout << " ]" << endl;
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

//---------- DEF ARBOL

struct Nodo_Arbol{
	int dato;
	Nodo_Arbol * hijo_izq = NULL;
	Nodo_Arbol * hijo_der = NULL;
};

typedef Nodo_Arbol * Abb;

Abb abb_Vacio(){
	return NULL;
}

Abb plantar(Abb izq, int e, Abb der){
	Abb nuevo_nodo = new Nodo_Arbol();
	nuevo_nodo -> dato = e;
	nuevo_nodo -> hijo_izq = izq;
	nuevo_nodo -> hijo_der = der;
	return nuevo_nodo;
}

Abb hijo_izq(Abb a){
	if (a == NULL){
		cout << "Error. El arbol es vacio." << endl;
	}
	else{
		Abb b = a -> hijo_izq;
		return b;
	}
}

Abb hijo_der(Abb a){
	if (a == NULL){
		cout << "Error. El arbol es vacio." << endl;
	}
	else{
		Abb b = a -> hijo_der;
		return b;
	}
}

int raiz(Abb a){
	if (a == NULL){
		cout << "Error. El arbol es vacio." << endl;
	}
	else{
		int e = a -> dato;
		return e;
	}
}

bool es_abb_Vacio(Abb a){
	return a == NULL;
}

int altura(Abb a){
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

tupla_Bool_Alt es_abb_Equilibrado(Abb a){
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

Lista preorden(Abb a){
	Lista aux = lista_Vacia();
	Lista aux2 = lista_Vacia();
	Lista result = lista_Vacia();
	Abb hijo_derecha;
	int e;
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

Lista inorden(Abb a){
	Lista aux = lista_Vacia();
	Lista aux2 = lista_Vacia();
	Lista result = lista_Vacia();
	Abb hijo_derecha;
	int e;
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

Lista postorden(Abb a){
	Lista aux = lista_Vacia();
	Lista aux2 = lista_Vacia();
	Lista result = lista_Vacia();
	Abb hijo_derecha;
	int e;
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
	int comando, elemento, actual;
	Lista aux_Lista1, aux_Lista2, aux_Lista3;
	Abb a = abb_Vacio();
	Abb b = abb_Vacio();
	Abb c = abb_Vacio();
	Abb aux1 = abb_Vacio();
	Abb aux2 = abb_Vacio();
	tupla_Bool_Alt equilibrado;
	
	while(comando != 7){
		cout << "La arbol ha sido creado." << endl;
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
		cout << "2. Representar un arbol que ya esta exo xd (Ver en codigo)" << endl;
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
				a = plantar(aux1, elemento, aux2);
				break;
			case 2:
				b = plantar(a, 4, aux1);
				c = plantar(aux1, 5, b);
				a = plantar(c, 8, b);
				equilibrado = es_abb_Equilibrado(a);
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
