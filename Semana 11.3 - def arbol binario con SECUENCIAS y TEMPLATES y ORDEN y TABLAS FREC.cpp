#include<iostream>
#include<stdlib.h>
#include<string>

using namespace std;


//--------- ESTRUCTURAS

const string FLECHA = "↓";

template <typename T>
struct Nodo{
	T dato;
	Nodo<T> * siguiente;
};

template <typename T>
struct Secuencia{
	Nodo<T> * primero;
	Nodo<T> * anterior;
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

struct entrada{
       char letra;
       int frec;
};

bool operator <=(entrada e1, entrada e2){
     return e1.letra <= e2.letra;
}

bool operator ==(entrada e1, entrada e2){
     return e1.letra == e2.letra;
}


//--------- SECUENCIAS


template <typename T>
Secuencia<T> sec_Vacia(){
	Secuencia<T> s;
	Nodo<T> * fant = new Nodo<T>();
	s.primero = fant;
	s.anterior = fant;
	fant -> siguiente = NULL;
	return s;
}

template <typename T>
void insertar_Sec(Secuencia<T> & s, T e){
	Nodo<T> *nuevo_nodo = new Nodo<T>();
	nuevo_nodo -> dato = e;
	nuevo_nodo -> siguiente = s.anterior -> siguiente;
	s.anterior -> siguiente = nuevo_nodo;
	s.anterior = nuevo_nodo;
}

template <typename T>
void eliminar_Sec(Secuencia<T> & s){
	if (s.anterior -> siguiente == NULL){
		cout << "\nError. No existe punto de interes que eliminar." << endl;
	}
	else{
		Nodo<T> * aux = s.anterior -> siguiente;
		s.anterior -> siguiente = aux -> siguiente;
		delete aux;
	}
}

template <typename T>
T dame_actual_Sec(Secuencia<T> s){
	T punto_interes;
	if (s.anterior -> siguiente == NULL){
		cout << "\nError. No existe punto de interes que consultar." << endl;
	}
	else{
		punto_interes = (s.anterior -> siguiente ) -> dato;
		return(punto_interes);
	}
}

template <typename T>
void avanzar_Sec(Secuencia<T> & s){
	if (s.anterior -> siguiente == NULL){
		cout << "\nError. No existe punto de interes al que avanzar." << endl;
		system("pause");
	}
	else{
		s.anterior = s.anterior -> siguiente;
	}
}

template <typename T>
void reiniciar_Sec(Secuencia<T> & s){
	s.anterior = s.primero;
}

template <typename T>
bool fin_Sec(Secuencia<T> s){
	return (s.anterior -> siguiente == NULL);
}

template <typename T>
void liberar_Sec(Secuencia<T> s){
	reiniciar_Sec(s);
	while(!fin_Sec(s)){
		eliminar_Sec(s);
	}
	delete s.primero;
}

template <typename T>
bool es_Sec_Vacia(Secuencia<T> s){
	return(s.primero -> siguiente == NULL);
}

void mostrar_Sec_entradas(Secuencia<entrada> s){
	int contador = 0;
	if (es_Sec_Vacia(s)){
		cout << "La secuencia es vacia.";
	}
	else{
		cout << "{ " << endl;
		Nodo<entrada> * aux = s.primero;
		contador++;
		aux = s.primero -> siguiente;
		while (aux -> siguiente != NULL){
			cout << aux -> dato.letra << " (" << aux -> dato.frec << ")" << ", " << endl;
			contador++;
			if (aux == s.anterior){
				cout << " -> ";
			}
			aux = aux -> siguiente;	
		}
		cout << aux -> dato.letra << " (" << aux -> dato.frec << ")" << ". " << endl;
		cout << "}" << endl;
	}
}


//--------- ARBOL


template<typename T>
Nodo_Arbol<T> * abb_Vacio(){
	return NULL;
}

template <typename T>
bool es_abb_vacio(const Nodo_Arbol<T> * a){
     return a == NULL;
}

template<typename T>
Nodo_Arbol<T> * hijo_izq(Nodo_Arbol<T> * a){
	if (a == NULL){
		cout << "Error. El arbol es vacio." << endl;
	}
	else{
		Nodo_Arbol<T> * b = a -> hijo_izq;
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

//Dado un arbol binario, calcula su altura
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

//Calcula la distancia entre dos numeros enteros
int diferencia(int n, int m){ 
	int d;
	if (n >= m){
		d = n - m;
	}
	else{
		d = m - n;
	}
	return d;
}

/*Dado un arbol binario, devuelve un booleano que decide si esta equilibrado
o no, y la altura maxima de desequilibrio que contiene.*/
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

void insertar_Abb(Nodo_Arbol<entrada> * & a, entrada e){
     if(es_abb_vacio(a)){
        a = new Nodo_Arbol<entrada>;
        a -> dato = e;
     }
     else if(!(a -> dato <= e)){
        insertar_Abb(a -> hijo_izq,e);
     }
     else if(a -> dato == e){
     	(a -> dato).frec++;
	 }
     else{
          insertar_Abb(a -> hijo_der,e);
     }
}

template <typename T>
void in_orden_aux(Nodo_Arbol<T> * & a,Secuencia<T> & s){
     if(!es_abb_vacio(a)){
          in_orden_aux( a->hijo_izq, s);
          insertar_Sec(s,a->dato);
          in_orden_aux( a->hijo_der, s);
     }
}

template <typename T>
Secuencia<T> in_orden(Nodo_Arbol<T> * & a){
     Secuencia<T> result = sec_Vacia<T>();
     in_orden_aux(a,result);
     return result;
}

template <typename T>
void liberar(Nodo_Arbol<T> * & a){
       if(a!=NULL){
           liberar(a->hijo_izq);
           liberar(a->hijo_der);
           delete a;
       }
}

typedef Nodo_Arbol<entrada> * Tabla_frec;

int main(){
	int comando, actual, i;
	Nodo_Arbol<entrada> * a;
	Secuencia<entrada> s;
	string mensaje;
	entrada e;
	tupla_Bool_Alt equilibrado;
	
	cout << "Inserte un mensaje: " << endl << endl;
	getline(cin,mensaje);
	for(i = 0; i < mensaje.length(); i++){
		e.letra = mensaje[i];
		e.frec = 1;
		insertar_Abb(a, e);
	}
	cout << "\nLa arbol ha sido creado." << endl;
	equilibrado = es_abb_Equilibrado(a);
	if(equilibrado.eq){
		cout << "El arbol creado a partir del texto es equilibrado." << endl;
	}
	else{
		cout << "El arbol creado a partir del texto no es equilibrado." << endl;
		cout << "La distancia maxima entre las alturas del arbol es: " << equilibrado.alt << endl;
	}
	cout << "El mensaje que ha escrito tiene la siguiente tabla de frecuencias: " << endl;
	cout << "(Ordenado por letras)" << endl << endl;
	s = in_orden(a); mostrar_Sec_entradas(s); cout << endl << endl;
	system("pause");
	return 0;
}
