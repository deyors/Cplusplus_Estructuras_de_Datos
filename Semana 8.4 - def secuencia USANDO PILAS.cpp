#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

template <typename T>
struct Nodo{
	T dato;
	Nodo<T> * siguiente;
};

template <typename T>
struct Secuencia{
	Pila<T> iz;
	Pila<T> dr;
};

//----------------------------------------------------

template <typename T>
Secuencia<T> crear();

template <typename T>
bool es_sec_vacia(Secuencia<T> );

template <typename T>
void insertar(Secuencia<T> & , T );

template <typename T>
void eliminar(Secuencia<T> & );

template <typename T>
T actual(Secuencia<T> ){

template <typename T>
void avanzar(Secuencia<T> & );

template <typename T>
void reiniciar(Secuencia<T> & );

//----------------------------------------------------

int main(){
	return 0;
}

template <typename T>
Secuencia<T> crear(){
	Secuencia<T> s;
	s.iz = pila_vacia<T>();
	s.dr = pila_vacia<T>();
	return s;
}

template <typename T>
bool es_sec_vacia(Secuencia<T> s){
	if(s.iz == NULL & s.dr == NULL){
		return true;
	}
	else{
		return false;
	}
}

template <typename T>
void insertar(Secuencia<T> & s, T e){
	apilar<T>(s.iz, e);
}

template <typename T>
void eliminar(Secuencia<T> & s){
	if(s.dr == NULL){
		cout << "\nNo existe actual." << endl;
	}
	else{
		desapilar(s.dr);
	}
}

template <typename T>
T actual(Secuencia<T> s){
	if(s.dr == NULL){
		cout << "\nNo existe actual.";
	}
	else{
		cout << "\nActual es: ";
		return s.dr -> dato;
	}
}

template <typename T>
void avanzar(Secuencia<T> & s){
	int b;
	if(s.dr == NULL){
		cout << "\nNo existe actual." << endl;
	}
	else{
		b = s.dr -> dato;
		apilar(s.iz, b);
		desapilar(s.dr);
	}
}

template <typename T>
void reiniciar(Secuencia<T> & s){
	if(s.iz == NULL){
		cout << "La pila ha sido reiniciada." << endl;
	}
	else{
		apilar(s.dr, s.iz -> dato);
		desapilar(s.iz);
		reiniciar_Sec(s);
	}
}


