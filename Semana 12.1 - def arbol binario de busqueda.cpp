#include<iostream>
#include<stdlib.h>
#include<string>

using namespace std;

//--------- ESTRUCTURAS

template <typename T>
struct entrada{
    char clave;
    T valor;
};

template <typename T>
struct Nodo{
	entrada<T> dato;
	Nodo<T> * siguiente;
};

template<typename T>
struct Nodo_Abbus{
	entrada<T> dato;
	Nodo_Abbus<T> * hijo_izq = NULL;
	Nodo_Abbus<T> * hijo_der = NULL;
};

template<typename T>
struct tabla{
	entrada<T> dato;
	tabla<T> * hijo_izq = NULL;
	tabla<T> * hijo_der = NULL;
};

template<typename U>
struct arbol_h{
	entrada<U> dato;
	arbol_h<U> * hijo_izq = NULL;
	arbol_h<U> * hijo_der = NULL;
};

//TABLA

template <typename T>
bool operator <=(entrada<T> e1, entrada<T> e2){
     return e1.clave <= e2.clave;
}

template <typename T>
bool operator ==(entrada<T> e1, entrada<T> e2){
     return e1.clave == e2.clave;
}

//ARBOL DE HUFFMAN



//--------- OPERACIONES TABLA

template <typename T>
tabla<T> * tabla_vacia(){
	return NULL;
}

template <typename T>
bool es_tabla_vacia(tabla<T> * a){
	return a == NULL;
}

void insertar_tabla_int(entrada<int> e, tabla<int> * & a){
	if(es_tabla_vacia(a)){
		a = new tabla<int>();
		a -> dato = e;
		a -> hijo_izq = NULL;
		a -> hijo_der = NULL;
	}
	else if(!(a -> dato <= e)){
		insertar_tabla_int(e, a -> hijo_izq);
	}
	else if(a -> dato == e){
		(a -> dato).valor++;
	}
	else{
		insertar_tabla_int(e, a -> hijo_der);
	}
}

void insertar_tabla_string(entrada<string> e, tabla<string> * & a){
	if(es_tabla_vacia(a)){
		a = new tabla<string>();
		a -> dato = e;
		a -> hijo_izq = NULL;
		a -> hijo_der = NULL;
	}
	else if(!(a -> dato <= e)){
		insertar_tabla_string(e, a -> hijo_izq);
	}
	else{
		insertar_tabla_string(e, a -> hijo_der);
	}
}

//Consultar devuelve el valor del elemento 
//AYLAGAS DEL FUTURO: DE NADA

template <typename T>
T consultar(tabla<T> * a, char c){
	T v;
	if (!es_tabla_vacia(a)){
		if((a -> dato).clave == c){
			v = (a -> dato).valor;
		}
		else if((a -> dato).clave < c){
			v = consultar(a -> hijo_izq, c);
		}
		else{
			v = consultar(a -> hijo_der, c);
		}
	}
	return v;
}

template <typename T>
bool esta_clave(tabla<T> * a, char c){
	bool b;
	if(es_tabla_vacia(a)){
		b = false;
	}
	else{
		if((a -> dato).clave == c){
			b = true;
		}
		else if((a -> dato).clave < c){
			b = esta_clave(a -> hijo_izq, c);
		}
		else{
			b = esta_clave(a -> hijo_der, c);
		}
	}
	return b;
}

template <typename T>
void eliminar_aux(tabla<T> * & a, tabla<T> * & b){
	tabla<T> * aux;
	if (!es_tabla_vacia(b -> hijo_izq)){
		eliminar_aux(a, b -> hijo_izq);
	}
	else{
		a -> dato = b -> dato;
		aux = b;
		b = b -> hijo_der;
		delete aux;
	}
}

template <typename T>
void eliminar(char clave, tabla<T> * & a){
	tabla<T> * aux;
	if(!es_tabla_vacia(a)){
		if(clave == (a -> dato).letra){
			if(es_tabla_vacia(a -> hijo_der)){
				aux = a;
				a = a -> hijo_izq;
				delete aux;
			}
			else if(es_tabla_vacia(a -> hijo_izq)){
				aux = a;
				a = a -> hijo_der;
				delete aux;
			}
			else{
				eliminar_aux(a, a -> hijo_der);
			}
		}
		else if(clave < (a -> dato).letra){
			eliminar(clave, a -> hijo_izq);
		}
		else{
			eliminar(clave, a -> hijo_der);
		}
	}
}

template <typename T>
void in_orden(tabla<T> * a){
	if(es_tabla_vacia(a)){
		return;
	}
	else{
		in_orden(a -> hijo_izq);
		cout << (a -> dato).clave << " (" << (a -> dato).valor << "),"<< endl;
		in_orden(a -> hijo_der);
	}
}

template <typename T>
void mostrar_tabla(tabla<T> * a){
	cout << "{" << endl;
	in_orden(a);
	cout << "}";
}


//--------- OPERACIONES ARBOL HUFFMAN

template <typename U>
bool es_arbol_vacio(arbol_h<U> * h){
	return (h == NULL);
}

arbol_h<int> * hoja(entrada<int> e){
	arbol_h<int> * h = new arbol_h<int>();
	h -> dato = e; 
	h -> hijo_izq = NULL;
	h -> hijo_der = NULL;
	return h;
}

arbol_h<int> * plantar(arbol_h<int> * h1, arbol_h<int> * h2){
	arbol_h<int> * nuevo_nodo = new arbol_h<int>();
	(nuevo_nodo -> dato).clave = 'W'; //Sólo lo tendrá en cuenta si los dos hijos son NULL. 
	(nuevo_nodo -> dato).valor = (h1 -> dato).valor + (h2 -> dato).valor;
	nuevo_nodo -> hijo_izq = h1;
	nuevo_nodo -> hijo_der = h2;
	return nuevo_nodo;
}

template <typename U>
void cto_elementos(arbol_h<U> * h){
	cout << "{ ";
	cto_elementos_aux(h);
	cout << " }";
}

template <typename U>
void cto_elementos_aux(arbol_h<U> * h){
	if(!es_arbol_vacio(h)){
		if(es_arbol_vacio(h -> hijo_izq) && es_arbol_vacio(h -> hijo_der)){
			cout << (h -> dato).clave << ", ";
		}
		else if(!es_arbol_vacio(h -> hijo_izq)){
			cto_elementos_aux(h -> hijo_izq);
		}
		else{
			cto_elementos_aux(h -> hijo_der);
		}
	}
}

tabla<string> * tabla_codigos_aux(arbol_h<int> * h, tabla<string> * a, string s){
	entrada<string> e;
	if(es_arbol_vacio(h -> hijo_izq) && es_arbol_vacio(h -> hijo_der)){
		e.clave = (h -> dato).clave;
		e.valor = s;
		insertar_tabla_string(e, a);
		s = string("");
	}
	if(!es_arbol_vacio(h -> hijo_izq)){
		s =  s.append("0");
		tabla_codigos_aux(h -> hijo_izq, a, s);
	}
	if(!es_arbol_vacio(h -> hijo_der)){
			s =  s.append("1");
			tabla_codigos_aux(h -> hijo_der, a, s);
	}
}

tabla<string> * tabla_codigos(arbol_h<int> * h){
	tabla<string> * a;
	string s;
	a = tabla_vacia<string>();
	s = string("");
	a = tabla_codigos_aux(h, a, s);
	return a;
}

int main(){
	int comando, actual, i;
	tabla<int> * a;
	string mensaje;
	entrada<int> e;
	cout << "Inserte un mensaje: " << endl << endl;
	getline(cin,mensaje);
	for(i = 0; i < mensaje.length(); i++){
		e.clave = mensaje[i];
		e.valor = 1;
		insertar_tabla_int(e, a);
	}
	cout << "\nLa tabla ha sido creada." << endl;
	cout << "El mensaje que ha escrito tiene la siguiente tabla de frecuencias: " << endl;
	cout << "(Ordenado por letras)" << endl << endl;
	mostrar_tabla(a);
	cout << endl;
	system("pause");
	return 0;
}

