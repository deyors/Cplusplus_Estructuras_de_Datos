#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

//Estructura de los pares de enteros para definir un tipo de secuencia.
struct par_int{
  int primero ;
  int segundo ;
};

//Dados dos numeros, crea una estructura de pares de enteros.
par_int nuevo_par(int p,int s){
    par_int result;
    result.primero = p;
    result.segundo = s;
    return result;
};

//Operador <= para comparar dos pares de enteros.
bool operator <=(par_int e1,par_int e2){
  return e1.segundo<=e2.segundo;
};

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

template <typename T>
Secuencia<T> sec_Vacia(){
	Secuencia<T> s;
	Nodo<T> * fant = new Nodo<T>();
	s.primero = fant;
	s.anterior = fant;
	fant -> siguiente = NULL;
	return s;
}

//Dada una secuencia y un elemento, incluye ese elemento en la secuencia.
template <typename T>
void insertar_Sec(Secuencia<T> & s, T e){
	Nodo<T> *nuevo_nodo = new Nodo<T>();
	nuevo_nodo -> dato = e;
	nuevo_nodo -> siguiente = s.anterior -> siguiente;
	s.anterior -> siguiente = nuevo_nodo;
	s.anterior = nuevo_nodo;
}

//Dada una secuencia, elimina su elemento actual, si existe.
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

//Dada una estructura de pares de enteros, los muestra en pantalla.
void mostrar_ParInt(par_int par){
	cout <<  "(" << par.primero << ", " << par.segundo << ")";
}

//Dada una secuencia, imprime en pantalla su elemento actual, si lo tiene.
template <typename T>
void actual_Sec(Secuencia<T> s){
	T punto_interes;
	if (s.anterior -> siguiente == NULL){
		cout << "\nError. No existe punto de interes que consultar." << endl;
	}
	else{
		punto_interes = (s.anterior -> siguiente ) -> dato;
		cout << "\nEl punto de interes es: " << punto_interes << endl;
	}
}

//Dada una secuencia de pares de enteros, imprime en pantalla su elemento actual, si lo tiene.
void actual_Sec_ParInt(Secuencia<par_int> s){
	par_int punto_interes;
	if (s.anterior -> siguiente == NULL){
		cout << "\nError. No existe punto de interes que consultar." << endl;
	}
	else{
		punto_interes = (s.anterior -> siguiente ) -> dato;
		cout << "\nEl punto de interes es: ";
		mostrar_ParInt(punto_interes); cout << endl;
	}
}

//Dada una secuencia, devuelve su elemento actual.
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

//Dada una secuencia, avanza en un elemento su elemento actual.
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

//Dada una secuencia, situa el elemento actual al principio de esta.
template <typename T>
void reiniciar_Sec(Secuencia<T> & s){
	s.anterior = s.primero;
}

//Dada una secuencia, devuelve un booleano que analiza si su elemento actual es final.
template <typename T>
bool fin_Sec(Secuencia<T> s){
	return (s.anterior -> siguiente == NULL);
}

//Dada una secuencia, libera la memoria de la misma.
template <typename T>
void liberar_Sec(Secuencia<T> s){
	reiniciar_Sec(s);
	while(!fin_Sec(s)){
		eliminar_Sec(s);
	}
	delete s.primero;
}

//Dada una secuencia, devuelve un booleano que analiza si es vacia.
template <typename T>
bool es_Sec_Vacia(Secuencia<T> s){
	return(s.primero -> siguiente == NULL);
}

//Dada una secuencia, la muestra en pantalla.
template <typename T>
void mostrar_Sec(Secuencia<T> s){
	int contador = 0;
	if (es_Sec_Vacia(s)){
		cout << "La secuencia es vacia.";
	}
	else{
		cout << "{ ";
		Nodo<T> * aux = s.primero;
		if (aux == s.anterior){
				cout << "-> ";
			}
		contador++;
		aux = s.primero -> siguiente;
		while ((aux -> siguiente != NULL) && (contador < 20)){
			cout << aux -> dato << ", ";
			contador++;
			if (aux == s.anterior){
				cout << " -> ";
			}
			aux = aux -> siguiente;	
		}
		cout << aux -> dato;
		if (aux == s.anterior){
				cout << ", -> ";
			}
		if (aux -> siguiente != NULL){
			cout << "...";
		}
		cout << " }";
	}
}

//Dada una secuencia de pares de enteros, la muestra en pantalla.
void mostrar_Sec_ParInt(Secuencia<par_int> s){
	int contador = 0;
	if (es_Sec_Vacia(s)){
		cout << "La secuencia es vacia.";
	}
	else{
		cout << "{ ";
		Nodo<par_int> * aux = s.primero;
		if (aux == s.anterior){
				cout << "-> ";
			}
		contador++;
		aux = s.primero -> siguiente;
		while ((aux -> siguiente != NULL) && (contador < 20)){
			mostrar_ParInt(aux -> dato); cout << ", ";
			contador++;
			if (aux == s.anterior){
				cout << " -> ";
			}
			aux = aux -> siguiente;	
		}
		mostrar_ParInt(aux -> dato); cout << ", ";
		if (aux == s.anterior){
				cout << ", -> ";
			}
		if (aux -> siguiente != NULL){
			cout << "...";
		}
		cout << " }";
	}
}

//Dada una secuencia, la ordena utilizando el procedimiento QuickSort.
template <typename T>
Secuencia<T> quick_sort_Sec(Secuencia<T> s){
	if(!es_Sec_Vacia(s)){
		Secuencia<T> menores = sec_Vacia<T>();
		Secuencia<T> mayores = sec_Vacia<T>();
		Secuencia<T> iguales = sec_Vacia<T>();
		Secuencia<T> result = sec_Vacia<T>();
		reiniciar_Sec(s);
		T pivote = dame_actual_Sec(s);
		while(!fin_Sec(s)){
			if(!(dame_actual_Sec(s) <= pivote)){
				insertar_Sec(mayores, dame_actual_Sec(s));
			}
			else if(!(pivote <= dame_actual_Sec(s))){
				insertar_Sec(menores, dame_actual_Sec(s));
			}
			else{
				insertar_Sec(iguales, dame_actual_Sec(s));
			}
			avanzar_Sec(s);
		}
		Secuencia<T> menores_ord = quick_sort_Sec(menores);
		Secuencia<T> mayores_ord = quick_sort_Sec(mayores);
		reiniciar_Sec(menores_ord);
		reiniciar_Sec(iguales);
		reiniciar_Sec(mayores_ord);
		while(!fin_Sec(menores_ord)){
			insertar_Sec(result, dame_actual_Sec(menores_ord));
			avanzar_Sec(menores_ord);
		}
		while(!fin_Sec(iguales)){
			insertar_Sec(result, dame_actual_Sec(iguales));
			avanzar_Sec(iguales);
		}
		while(!fin_Sec(mayores_ord)){
			insertar_Sec(result, dame_actual_Sec(mayores_ord));
			avanzar_Sec(mayores_ord);
		}
		reiniciar_Sec(result);
		liberar_Sec(menores);
      	liberar_Sec(mayores);
      	liberar_Sec(iguales);
      	liberar_Sec(menores_ord);
      	liberar_Sec(mayores_ord);
      	return result;
	}
	else{
		return sec_Vacia<T>();
	}
}

/*Ejecuta un programa que crea una secuencia en funcion del parametro elegido,
permitiendo la insercion y eliminacion de elementos, asi como su ordenacion, 
consulta de elemento actual, avance y reinicio. Tambien permite la liberacion
de la secuencia.*/
template <typename T>
void ejecutar_programa(int modalidad){
	int comando, cantidad = 0, metodo_ord;
	T elemento, actual, rango_A, rango_B;
	Secuencia<T> s, s_ord;
	s = sec_Vacia<T>();
	time_t t0, t1;
	system("cls");
	while(comando != 7){
		switch(modalidad){
			case 1: cout << "Actualmente se halla en: Secuencia de Int" << endl; break;
			case 2: cout << "Actualmente se halla en: Secuencia de Float" << endl; break;
			case 3: cout << "Actualmente se halla en: Secuencia de Char" << endl; break;
			case 4: cout << "Actualmente se halla en: Secuencia de String" << endl; break;
		}
		cout << "La secuencia ha sido creada." << endl;
		if (cantidad > 20){
			cout << "La secuencia tiene " << cantidad << " elementos." << endl;
			cout << "Representando los primeros 20 elementos: " << endl;
		}
		else if (cantidad != 0){
			if (cantidad == 1){
				cout << "La secuencia tiene " << cantidad << " elemento." << endl;
			}
			else{
				cout << "La secuencia tiene " << cantidad << " elementos." << endl;
			}
		}
		mostrar_Sec(s);
		cout << "\n\nEscoja entre las siguientes opciones: " << endl;
		cout << "1. INSERTAR un numero delante del punto de interes en la secuencia." << endl;
		cout << "2. ELIMINAR el numero en el punto de interes de la secuencia." << endl;
		cout << "3. CONSULTAR el elemento del punto de interes." << endl;
		cout << "4. AVANZAR en un elemento el punto de interes." << endl;
		cout << "5. REINICIAR la secuencia (trasladar el punto de interes al inicio)." << endl;
		cout << "6. ORDENAR la secuencia." << endl;
		cout << "7. LIBERAR la secuencia y SALIR.\n" << endl;
		cin >> comando;
		switch(comando){
			case 1:
				cout << "\nIntroduzca el numero que quiere insertar: " << endl;
				cin >> elemento;
				insertar_Sec(s, elemento); cantidad++; break;
			case 2:
				if (s.anterior -> siguiente != NULL){
					cout << "\nEl elemento ha sido borrado." << endl;
					cantidad--;
				}
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
				while(metodo_ord != 1){
					cout << "\nElija el metodo de ordenacion que desea emplear: " << endl;
					cout << "1. Quicksort" << endl;
					cin >> metodo_ord;
					switch(metodo_ord){
						case 1: 
							t0 = clock();
							s_ord = quick_sort_Sec(s);
							t1 = clock();
							cout << "\nLa secuencia se ha ordenado." << endl;
							cout << "QuickSort ejecutado en: " << ((float)(t1-t0))/CLOCKS_PER_SEC << " segundos" << endl;
							liberar_Sec(s);
							s = s_ord; break;
						default: 
							cout << "\nLa opcion que ha marcado no existe." << endl;
							cout << "Por favor, marque una opcion disponible." << endl; break;
					}
				}
				system("pause"); break;
			case 7:
				liberar_Sec(s);
				cout << "\nLa secuencia ha sido liberada." << endl;
				cout << "\nHasta luego!" << endl; system("pause"); break;
			default:
				cout << "\nLa opcion que ha marcado no existe." << endl;
				cout << "Por favor, marque una opcion disponible." << endl;
				system("pause"); break;
		}
		system("cls");
	}
}

/*Modalidad especial del programa anterior que crea una secuencia de pares de
enteros, incluyendo el numero de elementos que se desee. Permite la eliminacion
de elementos, ordenacion, reinicio y avance.*/
void prueba_QuickSort_ParInt(){
	int cantidad, comando;
	Secuencia<par_int> s, s1;
	time_t t0,t1;
    s = sec_Vacia<par_int>();
    cout << "\nIndique cuantos pares de enteros quiere que tenga su secuencia: " << endl;
    cin >> cantidad;
    for(int i = 0; i < cantidad + 1; i ++){
    	int n = rand() %10000;
    	insertar_Sec(s, nuevo_par(i,n));
	}
	system("cls");
	while(comando != 6){
		cout << "La secuencia ha sido creada." << endl;
		if (cantidad > 20){
			cout << "La secuencia tiene " << cantidad << " elementos." << endl;
			cout << "Representando los primeros 20 elementos: " << endl;
		}
		else if (cantidad != 0){
			if (cantidad == 1){
				cout << "La secuencia tiene " << cantidad << " elemento." << endl;
			}
			else{
				cout << "La secuencia tiene " << cantidad << " elementos." << endl;
			}
		}
		mostrar_Sec_ParInt(s);
		cout << "\n\nEscoja entre las siguientes opciones: " << endl;
		cout << "1. ELIMINAR el elemento en el punto de interes de la secuencia." << endl;
		cout << "2. CONSULTAR el elemento del punto de interes." << endl;
		cout << "3. AVANZAR en un elemento el punto de interes." << endl;
		cout << "4. REINICIAR la secuencia (trasladar el punto de interes al inicio)." << endl;
		cout << "5. ORDENAR la secuencia." << endl;
		cout << "6. LIBERAR la secuencia y volver al incio.\n" << endl;
		cin >> comando;
		switch(comando){
			case 1:
				if (s.anterior -> siguiente != NULL){
					cout << "\nEl elemento ha sido borrado." << endl;
					cantidad--;
				}
				eliminar_Sec(s);
				system("pause"); break;
			case 2:
				actual_Sec_ParInt(s);
			 	system("pause"); break;
			case 3:
				avanzar_Sec(s); break;
			case 4:
				reiniciar_Sec(s); break;
			case 5:
				t0 = clock();
				s1 = quick_sort_Sec(s);
				t1 = clock();
				cout << "\nLa secuencia se ha ordenado." << endl;
				cout << "QuickSort ejecutado en: " << ((float)(t1-t0))/CLOCKS_PER_SEC << " segundos" << endl;
				liberar_Sec(s);
				s = s1;
				system("pause"); break;
			case 6:
				liberar_Sec(s);
				cout << "\nLa secuencia ha sido liberada." << endl;
				system("pause"); main(); break;
			default:
				cout << "\nLa opcion que ha marcado no existe." << endl;
				cout << "Por favor, marque una opcion disponible." << endl;
				system("pause"); break;
		}
		system("cls");
	}
}

/*Funcion principal donde se declara el tipo de dato con el que se va a tratar
la secuencia. Desde esta funcion se ejecutan los demas programas, en funcion 
de las opciones disponibles.*/
int main(){
	int  tipo, modalidad;
	cout << "Elija entre los distintos tipos de secuencias que quiere definir:\n"<<endl;
	cout << "1. Secuencia de int." << endl;
	cout << "2. Secuencia de float." << endl;
	cout << "3. Secuencia de char." << endl;
	cout << "4. Secuencia de string" << endl;
	cout << "5. Prueba de QUICKSORT (aplicado a duplas en secuencias con gran cantidad de elementos)" << endl;
	cout << "6. Salir del programa.\n"<< endl;
	cin >> tipo;
	while(tipo != 6){
		switch(tipo){
			case 1:
				modalidad = 1;
				ejecutar_programa<int>(modalidad); tipo = 6; break;
			case 2: 
				modalidad = 2;
				ejecutar_programa<float>(modalidad); tipo = 6; break;
			case 3:
				modalidad = 3;
				ejecutar_programa<char>(modalidad); tipo = 6; break;
			case 4: 
				modalidad = 4;
				ejecutar_programa<string>(modalidad); tipo = 6; break;
			case 5:
				prueba_QuickSort_ParInt(); tipo = 6; break;
			case 6:
				cout << "Hasta luego!"; break;
			default:
				cout << "\nLa opcion que ha marcado no existe." << endl;
				cout << "Por favor, marque una opcion disponible." << endl;
				system("pause"); break;
			}	
	}
	return 0;
}
