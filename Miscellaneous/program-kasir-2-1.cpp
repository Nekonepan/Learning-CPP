#include <iostream>
using namespace std;
int main()
{
  int jumlah_pesan;
  int pilihan1, pilihan2;
  int harga_makanan = 0, harga_minuman = 0, total_harga = 0;
  char pesan_lagi;

  do{
    for (int i=0; i<=12; i++) cout<<"-";
    cout<<"MENU MAKANAN";
    for (int i=0; i<=12; i++) cout<<"-";
    cout<<endl;

    cout<<"1. Ayam Goreng \t\t[Rp. 15.000]"<<endl;
    cout<<"2. Lele Goreng \t\t[Rp. 13.000]"<<endl;
    cout<<"3. Bebek Goreng \t[Rp. 18.000]"<<endl;

    do{
    cout<<endl<<"Pilih menu makanan anda (0 jika ingin berhenti memilih) : ";
    cin>>pilihan1;

    int harga_per_item = 0;
      
    if (pilihan1 == 0) break;
    switch (pilihan1){
      case 1:
        cout<<"- [Ayam Goreng]"<<endl;
        harga_per_item += 15;
        break;
      case 2:
        cout<<"- [Lele Goreng]"<<endl;
        harga_per_item += 13;
        break;
      case 3:
        cout<<"- [Bebek Goreng]"<<endl;
        harga_per_item += 18;
        break;
      default:
        cout<<"Pilihan ada tidak ada di menu"<<endl;
        continue;
    }

    cout<<"Ingin memesan berapa banyak : ";
    cin>>jumlah_pesan;

    harga_makanan += harga_per_item * jumlah_pesan;

    } while (true);

    for (int i=0; i<=12; i++) cout<<"-";
    cout<<"MENU MINUMAN";
    for (int i=0; i<=12; i++) cout<<"-";
    cout<<endl;
    
    cout<<"1. Air Putih \t[Rp. 1.000]"<<endl;
    cout<<"2. Teh \t\t[Rp. 3.000]"<<endl;
    cout<<"3. Jeruk \t[Rp. 5.000]"<<endl;
    cout<<"4. Kopi \t[Rp. 4.000]"<<endl;

    do{
      cout<<endl<<"Pilih menu minuman anda (0 jika ingin berhenti memilih) : ";
      cin>>pilihan2;
      
      int harga_per_item = 0;
      
      if (pilihan2 == 0) break;
      switch (pilihan2){
        case 1:
          cout<<"- [Air Putih]"<<endl;
          harga_per_item += 1;
          break;
        case 2:
          cout<<"- [Teh]"<<endl;
          harga_per_item += 3;
          break;
        case 3:
        cout<<"- [Jeruk]"<<endl;
          harga_per_item += 5;
        break;
        case 4:
        cout<<"- [Kopi]"<<endl;
          harga_per_item += 4;
        break;
        default:
        cout<<"Pilihan anda tidak ada di menu"<<endl;
        continue;
      }
      
      cout<<"Ingin memesan berapa banyak : ";
      cin>>jumlah_pesan;

      harga_minuman += harga_per_item * jumlah_pesan;
      
    } while (true);

    if (pilihan1 == 0 && pilihan2 == 0){
      cout<<"Apakah anda ingin memesan lagi (Y/N) : ";
      cin>>pesan_lagi;
      pesan_lagi = toupper(pesan_lagi);
      if (pesan_lagi == 'Y'){
        system("cls");
      }
    }
  } while (pesan_lagi == 'Y');

  total_harga = harga_makanan + harga_minuman;

  for (int i=0; i<=36; i++) cout<<"=";
  cout<<endl;
  cout<<"Harga makanan : \t[Rp. "<<harga_makanan<<".000]"<<endl;
  cout<<"Harga minuman : \t[Rp. "<<harga_minuman<<".000]"<<endl;
  cout<<"Total harga : \t\t[Rp. "<<total_harga<<".000]"<<endl;
  for (int i=0; i<=36; i++) cout<<"=";

  return 0;
}
