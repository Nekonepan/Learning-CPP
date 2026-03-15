#include <iostream>
using namespace std;

int main(){
  int n;
  cout<<"Masukkan jumlah element : ";
  cin>>n;

  cout<<endl;
  cout<<"NOTE : Tidak boleh input element dengan angka 0"<<endl;

  int arr1[n];
  cout<<"Array pertama :"<<endl;
  for (int i=0; i<n; i++){
    cout<<"Masukkan element ke-"<<i+1<<" : ";
    cin>>arr1[i];
  }

  cout<<endl;

  int arr2[n];
  cout<<"Array kedua :"<<endl;
  for (int i=0; i<n; i++){
    cout<<"Masukkan element ke-"<<i+1<<" : ";
    cin>>arr2[i];
  }

  cout<<endl;

  do{
  int pilihan;
  cout<<"Pilih pengoperasian array"<<endl;
  cout<<"=========================="<<endl;
  cout<<"1. Penjumlahan array"<<endl;
  cout<<"2. Pengurangan array"<<endl;
  cout<<"3. Perkalian array"<<endl;
  cout<<"4. Pembagian array"<<endl;
  cout<<"5. Modulus array"<<endl;
  cout<<"6. EXIT"<<endl;

  cout<<endl;
  cout<<"Pilih pengoperasian : ";
  cin>>pilihan;
  cout<<endl;

  int hasil[n];
  switch (pilihan){
    case 1:
      for (int i=0; i<n; i++){
        hasil[i] = arr1[i] + arr2[i];
      }
      break;

      case 2:
      for (int i=0; i<n; i++){
        hasil[i] = arr1[i] - arr2[i];
      }
      break;

      case 3:
      for (int i=0; i<n; i++){
        hasil[i] = arr1[i] * arr2[i];
      }
      break;

      case 4:
      for (int i=0; i<n; i++){
        hasil[i] = arr1[i] / arr2[i];
      }
      break;

      case 5:
      for (int i=0; i<n; i++){
        hasil[i] = arr1[i] % arr2[i];
      }
      break;

      case 6:
      return 0;
      break;

      default:
      cout<<"Pilihan tidak tersedia"<<endl;
      continue;
    }

  cout << "Array pertama      : ";
    for (int i = 0; i < n; i++) {
        cout << arr1[i] << " ";
    }
    
  cout << endl;

  cout << "Array kedua        : ";
    for (int i = 0; i < n; i++) {
        cout << arr2[i] << " ";
    }
    
  cout << endl;

    cout << "Hasil              : ";
    for (int i = 0; i < n; i++) {
        cout << hasil[i] << " ";
    }
    
  cout << endl;

  system("pause");

  } while (true);
}