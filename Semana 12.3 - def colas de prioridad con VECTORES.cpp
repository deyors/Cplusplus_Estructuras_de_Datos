#include<iostream>
#include<stdlib.h>
#include<string>

using namespace std;
const int CAP_INICIAL = 2;

struct Mont{
	int capacidad = 0;
	int ultimo = 0;
	int * V;
};

Mont cp_vacia(){
	Mont M;
	M.V = new int[CAP_INICIAL];
	M.capacidad = 2;
	return M;
}

void flotar(int * & V, int j){
	int i = j;
	while( (i != 1) &&  ( V[i] < V[i / 2] ) ){
		int aux = V[i];
		V[i] = V[i / 2];
		V[i / 2] = aux;
		i = i / 2;
	}
}

void aniadir(Mont & M, int e){
	if(M.ultimo == M.capacidad){
		int cap = M.capacidad;
		cap = cap*2;
		int * auxV = new int[cap];
		for(int i = 0; i < M.ultimo; i ++){
			auxV[i] = M.V[i];
		}
		delete[] M.V;
		M.V = auxV;
		M.capacidad = cap;
		aniadir(M, e);
	}
	else{
		M.ultimo++;
		M.V[M.ultimo] = e;
		flotar(M.V, M.ultimo);
	}
}

void hundir(int * V, int j , int k){ //j es 1, k es el ultimo
	bool fin = false;
	int i = j, m;
	while( (2*i <= k) && (!fin) ){
		if( (2*i + 1 <= k) && V[2*i + 1] < V[2*i] ){
			m = 2*i + 1;
		}
		else{
			m = 2*i;
		}
		if( V[m] < V[i] ){
			int aux = V[i];
			V[i] = V[m];
			V[m] = aux;
			i = m;
		}
		else{
			fin = true;
		}
	}
}

void eliminar_min(Mont & M){
	if(M.ultimo == 0){
		cout << "Error. El vector es vacio.";
	}
	else{
		M.V[0] = M.V[M.ultimo - 1];
		M.ultimo = M.ultimo - 1;
		hundir(M.V, 1, M.ultimo);
	}
}

void mostrar(Mont M){
	cout << "{ ";
	for(int i = 0; i < M.ultimo - 1; i++){
		cout << M.V[i] << ", ";
	}
	if(M.ultimo != 0){
		cout << M.V[M.ultimo];
	}
	cout << " }" << endl;
}

int main(){
	Mont M = cp_vacia();
	int comando, elemento;
	while(comando != 3){
		cout << "El arbol monticulo ha sido creado." << endl;
		cout << "El vector tiene : " << M.ultimo << " elementos." << endl;
		cout << "La capacidad del vector es: " << M.capacidad << endl;
		cout << "M mostrado: " << endl;
		mostrar(M);
		cout << "\n\nEscoja entre las siguientes opciones: " << endl;
		cout << "1. Insertar elemento en el monticulo." << endl;
		cout << "2. Eliminar elemento minimo del monticulo." << endl;
		cout << "3. Salir" << endl;
		cin >> comando;
		switch(comando){
			case 1: 
				cout << "\nIntroduzca el numero que quiere insertar: " << endl;
				cin >> elemento;
				aniadir(M, elemento);break;
			case 2:
				eliminar_min(M); break;
			case 3:
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

