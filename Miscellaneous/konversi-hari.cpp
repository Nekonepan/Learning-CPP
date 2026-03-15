#include <iostream>
using namespace std;
int main ()
{
	int total_hari, tahun, bulan, hari;
	
	cout<<"Masukkan hari : ";
	cin>>total_hari;
	system("pause");
	system("cls");
	
	cout<<"Konversi dari "<<total_hari<<" hari adalah : "<<endl;
	
	tahun=total_hari/365;
	total_hari%=365;
	bulan=total_hari/30;
	hari=total_hari %30;
	
	cout<<tahun<<" Tahun "<<bulan<<" Bulan "<<hari<<" Hari "<<endl;
	return 0;
}

