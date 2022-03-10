#include<iostream>
#include<conio.h>

using namespace std;

int gcd(int a, int b);
void bezout_var(int a, int b, int & d, int & x, int & y);

int main(){
	int n,m,d;
	int x,y;
	cout << "Dame un numero: "<<endl;
	cin >> n;
	cout << "\nDame otro numero: "<<endl;
	cin >> m;
	bezout_var(n,m,d,x,y);
	cout << "El mcd de " << n << " y " << m << " es: " << d << endl;
	cout << d << " = " << x << "*" << n << " + " << y << "*" << m << endl;
	cout<<"PULSE UNA TECLA PARA SALIR"<<endl;
	getch();
}

void bezout_var(int a, int b, int & d, int & x, int & y){
	if (b == 0){
		d = a;
		x = 1;
		y = 0;
	}
	else{
		int c = a / b;
		int r = a % b;
		int x1,y1;
		bezout_var(b,r,d,x1,y1);
		x = y1;
		y = (x1 - c * y1);
	}
}
