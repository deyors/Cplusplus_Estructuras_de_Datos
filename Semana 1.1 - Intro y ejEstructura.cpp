#include<iostream>
#include<conio.h>

using namespace std;

struct Triple_int{
	int d;
	int x;
	int y;
};

int gcd(int a, int b);
Triple_int bezout(int a, int b);


int main(){
	int n,m, final;
	Triple_int t;
	cout<<"Hola mundo, introduce dos numeros:"<<endl;
	cin>>n;
	cin>>m;
	final = gcd(n,m);
	cout<<"\nEl maximo comun divisor es: "<<final;
	t = bezout(n,m);
	cout<<"\nAdemas: "<<t.d<<" = "<<t.x<<" * "<<n<<" + ("<<t.y<<" * "<<m<<")"<<endl;
	cout<<"PULSE UNA TECLA PARA SALIR"<<endl;
	getch();
	return 0;
}


int gcd(int a, int b){
	int r;
	while(b!=0){
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}


Triple_int bezout(int a, int b){
	Triple_int result; 
	if(b == 0){
		result.d = a;
		result.x = 1;
		result.y = 0;
	}
	else{
		int c = a / b;
		int r = a % b; 
		Triple_int result1 = bezout(b,r);
		// d = result1.x * b + result1.y * r ademas a = c * b + r
		result.d = result1.d;
		result.x = result1.y;
		result.y = (result1.x - c * result1.y);
	}
	return result;
}


