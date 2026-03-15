#include <iostream>
using namespace std;
int main ()
{
  char skala_asal, skala_tujuan;
  double suhu_asal, suhu_tujuan;

  cout<<"Masukkan skala asal (C/F/K) : ";
  cin>>skala_asal;
  skala_asal=toupper(skala_asal);
  cout<<"Masukkan suhu asal dalam "<<skala_asal<<" : ";
  cin>>suhu_asal;
  cout<<"Masukkan skala tujuan (C/F/K) : ";
  cin>>skala_tujuan;
  skala_tujuan=toupper(skala_tujuan);

  if (skala_asal=='C' && skala_tujuan=='F'){
    suhu_tujuan=(suhu_asal*9/5)+32; //C ke F
  } else if (skala_asal=='C' && skala_tujuan=='K'){
    suhu_tujuan=suhu_asal+273; //C ke K
  } else if (skala_asal=='F' && skala_tujuan=='C'){
    suhu_tujuan=(suhu_asal-32)*5/9; //F ke C
  } else if (skala_asal=='F' && skala_tujuan=='K'){
    suhu_tujuan=(suhu_asal-32)*5/9+273; //F ke K
  } else if (skala_asal=='K' && skala_tujuan=='C'){
    suhu_tujuan=suhu_asal-273; //K ke C
  } else if (skala_asal=='K' && skala_tujuan=='F'){
    suhu_tujuan=(suhu_asal-273)*9/5+32; //K ke F
  } else if (skala_asal==skala_tujuan){
    suhu_tujuan=suhu_asal; //Jika suhu asal dan tujuan sama
  } else {
    cout<<"Skala tidak valid"<<endl;
    return 1;
  }
   cout <<suhu_asal<<" derajat "<<skala_asal<<" sama dengan "<<suhu_tujuan<<" derajat "<<skala_tujuan << endl;
   return 0;
}