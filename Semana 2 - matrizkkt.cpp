#include<iostream>
#include<string>
#include<fstream>
#include<math.h> //Para floor

/*La función lee dos archivos de texto, a especificar, con dos matrices 
donde se especifique el valor, número de filas y columnas y espresión completa, 
para seguidamente representarlas como matrices KK, sumarlas y averiguar sus 
traspuestas.

RECIBE: 

Dos archivos de texto (.txt) de 4 o más líneas, distribuidas de la siguiente
forma: 
Línea 1 -> k (DOUBLE) El valor central de la matriz KK
Línea 2 -> f (INT) El número de filas de la matriz inicial
Línea 3 -> c (INT) El número de columnas de la matriz inicial
Líneas sucesivas -> Los valores por orden de la matriz completa inicial, todos en 
formato DOUBLE. Estos valores tienen que reflejar el número de filas y columnas 
de la matriz antes especificados. 

DEVUELVE: 

La respresentación de las matrices en formato Matriz KK, la suma de las matrices
especificadas y cada una de sus traspuestas.*/

using namespace std;

const int MAX = 20;

//Cada una de las correspondientes filas de la submatriz m de la matriz KK. 
struct Mat_elem{
	double valor;
	int i; // fila
	int j; // columna
};

//La lista completa de la submatriz m de la matriz KK. 
typedef Mat_elem Array_elems[MAX];

/*La lista completa anterior más un número que especifica el número de filas que 
tiene la matriz m.*/
struct Lista_elems{
	Array_elems entradas;
	int num_entradas = 0;
};

/*El elemento completo de matriz KK, que consta de la lista anterior más los datos
sobre el valor central y el número de filas y columnas.*/
struct MatrizKK{
	Lista_elems m;
	double k;
	int f;
	int c;
};

//Cuenta el número de dígitos de un entero a para hacer el objetivo anterior.
int num_digitos(int a);

/*Cuenta el número de espacios que ocupa la representación de un dígito, según 
su naturaleza.*/
int espacio_digitos(double a);

//Muestra el elemento Mat_elem en pantalla.
void mostrar(Mat_elem e);

//Muestra el elemento Matriz KK en pantalla.
void mostrar(MatrizKK mat);

//Crea un nuevo elemento Mat_elem con el valor, fila y columna especificados.
Mat_elem new_Mat_elem(double val, int f, int c);

//Lee un archivo.txt y agrega su informacion a una matriz KK.
bool leer(string file_name, MatrizKK & mat);

//Aniade un nuevo Mat_elem a una Lista_elem, de forma ordenada lexicograficamente.
bool aniadir_ord(Lista_elems & l, Mat_elem & e);

/*Dada una matriz KK y un elemento Mat_elem, aniade el elemento e devolviendo la 
matriz KK resultante.*/
MatrizKK aniadir_ord(MatrizKK mat, Mat_elem e);

/*Dada una matrizKK, da la informacion sobre si un elemento Mat_elem con las 
cooredenadas especificadas esta dentro de la parte m de la matriz.*/
bool esta_en_m(MatrizKK mat, int i, int j);

/*Dada una matriz KK y unas coordenadas, da el valor del elemento Mat_elem que 
se encuentre en la parte m de esa matriz y tenga esas coordenadas.*/
double dame_valor(MatrizKK mat, int i, int j);

//Dada una matrizKK, devuelve su traspuesta. 
MatrizKK traspuesta(MatrizKK mat);

//Elimina de la lista de elementos el elemento de la posición (i,j), si lo tiene.
Lista_elems eliminar(Lista_elems & l, int i, int j);

//Dadas dos matrices KK, devuelve la suma entre ellas, si es posible sumarlas.
MatrizKK suma(MatrizKK mat1, MatrizKK mat2);

int main(){
	string archivo1, archivo2;
	MatrizKK matriz1;
	MatrizKK matriz2;
	MatrizKK mat_traspuesta1;
	MatrizKK mat_traspuesta2;
	MatrizKK mat_suma;
	MatrizKK mat_suma_traspuesta;
	cout << "Introduzca la primera matriz casi constante: ";
	cin >> archivo1;
	cout << "Introduzca la segunda matriz casi constante: ";
	cin >> archivo2;
	if(leer(archivo1,matriz1) && leer(archivo2,matriz2)){
		cout << "\nLa primera matriz que ha introducido es: " << endl;
		mostrar(matriz1);
		cout << "\n\nSu matriz traspuesta es: " << endl;
		mat_traspuesta1 = traspuesta(matriz1);
		mostrar(mat_traspuesta1);
		cout << "\n\nLa segunda matriz que ha introducido es: " << endl;
		mostrar(matriz2);
		cout << "\n\nSu matriz traspuesta es: " << endl;
		mat_traspuesta2 = traspuesta(matriz2);
		mostrar(mat_traspuesta2);
		cout<<"\n\nLa suma de las matrices es: "<<endl;
		mat_suma = suma(matriz1,matriz2);
		mostrar(mat_suma);
		cout<<"\n\nLa traspuesta de la matriz suma es: "<<endl;
		mat_suma_traspuesta = traspuesta(mat_suma);
		mostrar(mat_suma_traspuesta);	
	}
	else{
		cout << "Error en la lectura de las matrices. Por favor, intentelo de nuevo.\n";
	}
	return 0;
}

int espacio_digitos(double a){
	int result = 0, reduced1, reduced2, nat_dig, dec_dig;
	double reduced = a; 
	if(reduced<0){
		reduced = reduced*(-1);
		result = result + 1;
	}
	if(reduced - floor(reduced) != 0){
		while(reduced - floor(reduced) != 0){
		reduced = reduced*10;
		}
		result = result + 1 + num_digitos(reduced);
	}
	else{
		result = result + num_digitos(reduced);
	}
	if(reduced == 0){
		result = 1;
	}
	return result;
}

int num_digitos(int a){
	double reduced = a; int result = 0;
	while(reduced >= 1){
		reduced = reduced / 10;
		result = result + 1;
	}
	return result;
}


void mostrar(Mat_elem e, int num1, int num2, int num3){
	cout<<"( "<<e.valor;
	for(int a = 0;a<num1;a++){
		cout<<" ";
	}
	cout<<e.i;
	for(int b = 0;b<num2;b++){
		cout<<" ";
	}
	cout<<e.j;
	for(int c = 0;c<num3;c++){
		cout<<" ";
	}
	cout<<")";
}

void mostrar(MatrizKK mat){
	int fila_medio;
	int max1 = 1, max2 = 1, max3 = 1, num1, num2, num3;
	for(int a = 0; a<mat.m.num_entradas; a++){
		if(max1 < espacio_digitos(mat.m.entradas[a].valor)){
			max1 = espacio_digitos(mat.m.entradas[a].valor);
		}
		if(max2 < espacio_digitos(mat.m.entradas[a].i)){
			max2 = espacio_digitos(mat.m.entradas[a].i);
		}
		if(max3 < espacio_digitos(mat.m.entradas[a].j)){
			max3 = espacio_digitos(mat.m.entradas[a].j);
		}
	}
	switch(mat.m.num_entradas){
		case 0: cout<<"El numero de entradas no puede ser 0";break;
		case 1: cout<<" _\n";
				cout<<"| \n| ";
				num1 = max1 - espacio_digitos(mat.m.entradas[0].valor)+1;
				num2 = max2 - espacio_digitos(mat.m.entradas[0].i)+1;
				num3 = max3 - espacio_digitos(mat.m.entradas[0].j)+1;
				mostrar(mat.m.entradas[0],num1,num2,num3); 
				cout<<"  "<<mat.k<<",  "<<mat.f<<",  "<<mat.c<<" ||";
				cout<<"\n|_ ";break;
		case 2: cout<<" _\n";
				cout<<"| \n| ";
				num1 = max1 - espacio_digitos(mat.m.entradas[0].valor)+1;
				num2 = max2 - espacio_digitos(mat.m.entradas[0].i)+1;
				num3 = max3 - espacio_digitos(mat.m.entradas[0].j)+1;
				mostrar(mat.m.entradas[0],num1,num2,num3); cout<<endl<<"| ";
				num1 = max1 - espacio_digitos(mat.m.entradas[1].valor)+1;
				num2 = max2 - espacio_digitos(mat.m.entradas[1].i)+1;
				num3 = max3 - espacio_digitos(mat.m.entradas[1].j)+1;
				mostrar(mat.m.entradas[1],num1,num2,num3); 
				cout<<"  "<<mat.k<<",  "<<mat.f<<",  "<<mat.c<<" ||";
				cout<<"\n|_ ";break;
		default: 
				if (mat.m.num_entradas % 2 == 0){
					fila_medio = (mat.m.num_entradas / 2);
				}
				else{
					fila_medio = floor (mat.m.num_entradas / 2);
				}
				cout<<" _\n";
				cout<<"| \n";
				for(int h = 0;h<fila_medio;h++){
					num1 = max1 - espacio_digitos(mat.m.entradas[h].valor)+1;
					num2 = max2 - espacio_digitos(mat.m.entradas[h].i)+1;
					num3 = max3 - espacio_digitos(mat.m.entradas[h].j)+1;
					cout<<"| "; mostrar(mat.m.entradas[h],num1,num2,num3); cout<<endl;
				}
				num1 = max1 - espacio_digitos(mat.m.entradas[fila_medio].valor)+1;
				num2 = max2 - espacio_digitos(mat.m.entradas[fila_medio].i)+1;
				num3 = max3 - espacio_digitos(mat.m.entradas[fila_medio].j)+1;
				cout<<"| "; mostrar(mat.m.entradas[fila_medio],num1,num2,num3); 
				cout<<"  "<<mat.k<<",  "<<mat.f<<",  "<<mat.c<<" ||";
				cout<<endl;
				for(int h = fila_medio+1;h < mat.m.num_entradas;h++){
					num1 = max1 - espacio_digitos(mat.m.entradas[h].valor)+1;
					num2 = max2 - espacio_digitos(mat.m.entradas[h].i)+1;
					num3 = max3 - espacio_digitos(mat.m.entradas[h].j)+1;
					cout<<"| "; mostrar(mat.m.entradas[h],num1,num2,num3); cout<<endl;
				}
				cout<<"|_ ";
				break;	
	}
}

Mat_elem new_Mat_elem(double val, int f, int c){
	Mat_elem result;
	result.valor = val;
	result.i = f;
	result.j = c;
	return result;
}

bool aniadir_ord(Lista_elems & l, Mat_elem & e){
	bool result = true;
	if(l.num_entradas < MAX){
		if(l.num_entradas == 0){
			l.entradas[0] = e;
			l.num_entradas++;
		}
		else{
			int pos = l.num_entradas;
			//averiguamos la posición más pequeña en la que puede estar el nuevo elem
			for(int a = l.num_entradas -1; a > -1; a--){
				bool e_i_menor = (e.i < l.entradas[a].i);
				bool e_i_igual = (e.i == l.entradas[a].i);
				bool e_j_menor = (e.j < l.entradas[a].j);
				//Definimos el orden lexicográfico
				if(e_i_menor || (e_i_igual && e_j_menor)){
					pos = a;
				}
			}
			/*Desplazamos todos los elementos de la derecha de pos una vez hacia su
			derecha*/
			for(int b = l.num_entradas - 1;b > pos - 1;b--){
				l.entradas[b+1] = l.entradas[b];
			}
			//Asignamos el valor del elemento en la posición que corresponde
			l.entradas[pos] = e;
			l.num_entradas++;
		}
	}
	else{
		cout << "Se ha superado el numero maximo de entradas"<<endl;
		result = false;
	}
	
	return result;
}

MatrizKK aniadir_ord(MatrizKK mat, Mat_elem e){
	MatrizKK mat_result = mat;
	if(mat.m.num_entradas < MAX){
		if(mat_result.m.num_entradas == 0){
			mat_result.m.entradas[0] = e;
			mat_result.m.num_entradas++;
		}
		else{
			int pos = mat_result.m.num_entradas;
			//averiguamos la posición más pequeña en la que puede estar el nuevo elem
			for(int a = mat_result.m.num_entradas -1; a > -1; a--){
				bool e_i_menor = (e.i < mat_result.m.entradas[a].i);
				bool e_i_igual = (e.i == mat_result.m.entradas[a].i);
				bool e_j_menor = (e.j < mat_result.m.entradas[a].j);
				//Definimos el orden lexicográfico
				if(e_i_menor || (e_i_igual && e_j_menor)){
					pos = a;
				}
			}
			/*Desplazamos todos los elementos de la derecha de pos una vez hacia su
			derecha*/
			for(int b = mat_result.m.num_entradas - 1;b > pos - 1;b--){
				mat_result.m.entradas[b+1] = mat_result.m.entradas[b];
			}
			//Asignamos el valor del elemento en la posición que corresponde
			mat_result.m.entradas[pos] = e;
			mat_result.m.num_entradas++;
		}
    }
	else{
		cout << "Se ha superado el numero maximo de entradas"<<endl;
		cout << "No se pueden incorporar nuevas entradas";
	}
	return mat_result;
}


bool leer(string file_name, MatrizKK & mat){
	 ifstream archivo;
	 int f,c;
	 double k,valor;
	 bool result = true; 
	 archivo.open(file_name.c_str(),ios::in);
	 archivo >> k >> f >> c;
	 mat.k = k;
	 mat.f = f;
	 mat.c = c;
	 for(int i = 0; i<f; i++){
		 for(int j = 0; j<c; j++){
		 	archivo>>valor;
		 	if(valor!=k){
				 Mat_elem e;
				 e = new_Mat_elem(valor,i,j);
				 result = aniadir_ord(mat.m,e);
				 if(!result){
					 return false;
				}
			}
		}
	}
	archivo.close();
	return true;
}

bool esta_en_m(MatrizKK mat, int i, int j){
	bool result = false;
	for(int a = 0; a < mat.m.num_entradas;a++){
		bool i_esta = (i == mat.m.entradas[a].i);
		bool j_esta = (j == mat.m.entradas[a].j);
		if(i_esta && j_esta){
			result = true;
		}
	}
	return result;
}

double dame_valor(MatrizKK mat, int i, int j){
	double result;
	for(int a = 0; a < mat.m.num_entradas;a++){
		bool i_esta = (i == mat.m.entradas[a].i);
		bool j_esta = (j == mat.m.entradas[a].j);
		if(i_esta && j_esta){
			result = mat.m.entradas[a].valor;
		}
	}
	return result;
}

MatrizKK traspuesta(MatrizKK mat){
	MatrizKK mat_result;
	
	//Condicional para que el programa no se ejecute si la matriz esta vacia.
	if(mat.c != 0){
		mat_result.k = mat.k;
		mat_result.f = mat.c;
		mat_result.c = mat.f;
		for(int i = 0; i < mat.f;i++){
			for(int j = 0; j < mat.c; j++){
				if(esta_en_m(mat,i,j)){
					Mat_elem nuevo_e; 
					nuevo_e.valor = dame_valor(mat,i,j);
					nuevo_e.i = j;
					nuevo_e.j = i;
					mat_result = aniadir_ord(mat_result, nuevo_e);
				}
			}
		}
	}

	else{
		cout << "Estas matrices no se pueden sumar." << endl;
		mat_result = mat;
	}
	return mat_result;
}

Lista_elems eliminar(Lista_elems & l, Mat_elem e){
	Lista_elems result;
	result.num_entradas = 0;
	for(int a = 0; a < l.num_entradas; a++){
		bool i_no_coincide = (l.entradas[a].i != e.i);
		bool j_no_coincide = (l.entradas[a].j != e.j);
		if(i_no_coincide || j_no_coincide){
			result.entradas[result.num_entradas] = l.entradas[a];
			result.num_entradas++;
		}
	}
	return result;
}

MatrizKK suma(MatrizKK mat1, MatrizKK mat2){
	Lista_elems m1 = mat1.m, m2 = mat2.m;
	MatrizKK mat_suma;
	mat_suma.k = mat1.k + mat2.k;
	mat_suma.f = mat1.f;
	mat_suma.c = mat1.c;
	
	if(mat1.c == mat2.c && mat1.f == mat2.f){
		mat_suma.k = mat1.k + mat2.k;
	    mat_suma.f = mat1.f;
	    mat_suma.c = mat1.c;
	    
	    //Paso por m1, y si hay en m2, meto el elemento en mat_suma y elimino de m1 y m2.
		for(int a = 0; a < mat1.m.num_entradas; a++){
			for(int b = 0; b < mat2.m.num_entradas; b++){
				int i1 = mat1.m.entradas[a].i, i2 = mat2.m.entradas[b].i;
				int j1 = mat1.m.entradas[a].j, j2 = mat2.m.entradas[b].j;
				double val1 = mat1.m.entradas[a].valor;
				if((i1 == i2) && (j1 == j2)){
					double val2 = mat2.m.entradas[b].valor;
					double val = val1 + val2;
					if(val != mat_suma.k){
						mat_suma = aniadir_ord(mat_suma, new_Mat_elem(val, i1, j1));
					}
					m1 = eliminar(m1, mat1.m.entradas[a]);
					m2 = eliminar(m2, mat2.m.entradas[b]);
				}
			}
		}
	
		//Ahora paso por m1 y m2 para meter el resto de elementos que se han quedado atras.
		for(int c = 0; c < m1.num_entradas; c++){
			double val = m1.entradas[c].valor + mat2.k;
			int i1 = m1.entradas[c].i;
			int j1 = m1.entradas[c].j;
			if(val != mat_suma.k){
				mat_suma = aniadir_ord(mat_suma, new_Mat_elem(val, i1, j1));
			}
		}
	
		for(int c = 0; c < m2.num_entradas; c++){
			double val = m2.entradas[c].valor + mat1.k;
			int i1 = m2.entradas[c].i;
			int j1 = m2.entradas[c].j;
			if(val != mat_suma.k){
				mat_suma = aniadir_ord(mat_suma, new_Mat_elem(val, i1, j1));
			}
		}
	}
	
	else{
		cout << "Estas matrices no se pueden sumar." << endl;
		Mat_elem e;
		e.valor = 0;
		e.i = 0;
		e.j = 0;
		mat_suma.k = 0;
	    mat_suma.f = 0;
	    mat_suma.c = 0;
	    mat_suma = aniadir_ord(mat_suma, e);
	}

	return mat_suma;
}


