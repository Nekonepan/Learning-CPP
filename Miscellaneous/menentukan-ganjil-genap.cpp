#include <iostream>
using namespace std;
int main ()
{
	int angka;
	cout<<"Masukkan satu bilangan bulat : ";
	cin>>angka;
	cout<<endl;
	
	if (angka%2==0){
		cout<<"Bilangan tersebut genap";
	}
	else{
		cout<<"Bilangan tersebut ganjil";
	}
}
