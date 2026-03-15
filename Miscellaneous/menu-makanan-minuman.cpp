#include <iostream>
using namespace std;
int main (){
	int h_makan1=0;
	int h_makan2=0;
	int h_minum1=0;
	int h_minum2=0;
	int ma1=15000;
	int ma2=13000;
	int ma3=18000;
	int mi1=2000;
	int mi2=3000;
	int mi3=5000;
	
	//Makanan
	cout<<"===DAFTAR MENU==="<<endl;
	cout<<endl;
	cout<<"Daftar Makanan"<<endl;
	cout<<endl;
	cout<<"1. Ayam Goreng 		[Rp. 15.000]"<<endl;
	cout<<"2. Lele Goreng 		[Rp. 13.000]"<<endl;
	cout<<"3. Bebek Goreng 	[Rp. 18.000]"<<endl;
	cout<<endl;
	cout<<"Masukkan pilihan 1 : ";
	cin>>p_makan1;
	cout<<"Masukkan pilihan 2 : ";
	cin>>p_makan2;
	cout<<endl;
	
	
	//Minuman
	cout<<"Daftar Minuman"<<endl;
	cout<<endl;
	cout<<"1. Air Putih 	(Es/Panas) 	[Rp. 2.000]"<<endl;
	cout<<"2. Teh 		(Es/Panas) 	[Rp. 3.000]"<<endl;
	cout<<"3. Jeruk 	(Es/Panas) 	[Rp. 5.000]"<<endl;
	cout<<endl;
	cout<<"Masukkan pilihan : ";
	cin>>p_minum1;
	cout<<"Masukkan pilihan : ";
	cin>>p_minum2;
	cout<<endl;
	
	//Pilihan untuk makanan
	switch (p_makan1){
		case 1:
			cout<<"-> Ayam Goreng : 		[Rp. 15.000]"<<endl;
			h_makan1=ma1;
			break;
		case 2:
			cout<<"-> Lele Goreng : 		[Rp. 13.000]"<<endl;
			h_makan1=ma2;
			break;
		case 3:
			cout<<"-> Bebek Goreng : 		[Rp. 18.000]"<<endl;
			h_makan1=ma3;
			break;
		default:
			cout<<"Pilihan tidak valid"<<endl;
			break;
			return 0;
	}
	
	switch (p_makan2){
		case 1:
			cout<<"-> Ayam Goreng : 		[Rp. 15.000]"<<endl;
			h_makan2=ma1;
			break;
		case 2:
			cout<<"-> Lele Goreng : 		[Rp. 13.000]"<<endl;
			h_makan2=ma2;
			break;
		case 3:
			cout<<"-> Bebek Goreng : 		[Rp. 18.000]"<<endl;
			h_makan2=ma3;
			break;
		default:
			cout<<"Pilihan tidak valid"<<endl;
			break;
			return 0;
	}
	
	//Pilihan untuk minuman
	if (p_minum1==1){
		cout<<"-> Air Putih (Es/Panas) : 	[Rp. 2.000]"<<endl;
		h_minum1=mi1;
	}else if (p_minum1==2){
		cout<<"-> Teh (Es/Panas) : 		[Rp. 3.000]"<<endl;
		h_minum1=mi2;
	}else if (p_minum1==3){
		cout<<"-> Jeruk (Es/Panas) : 		[Rp. 3.000]"<<endl;
		h_minum1=mi3;
	}else{
		cout<<"Pilihan tidak valid"<<endl;
		return 0;
	}
	
	if (p_minum2==1){
		cout<<"-> Air Putih (Es/Panas) : 	[Rp. 2.000]"<<endl;
		h_minum2=mi1;
	}else if (p_minum2==2){
		cout<<"-> Teh (Es/Panas) : 		[Rp. 3.000]"<<endl;
		h_minum2=mi2;
	}else if (p_minum2==3){
		cout<<"-> Jeruk (Es/Panas) : 		[Rp. 3.000]"<<endl;
		h_minum2=mi3;
	}else{
		cout<<"Pilihan tidak valid"<<endl;
		return 0;
	}
	
	//Total biaya
	total=h_makan1+h_makan2+h_minum1+h_minum2;
	cout<<"Total biaya : 			"<<"[Rp. "<<total<<"]"<<endl;
	return 0;
}
