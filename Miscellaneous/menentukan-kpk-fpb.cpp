#include <iostream>
using namespace std;

int hitungFPB(int a, int b) {
    while (b != 0) {
        int sisa = a % b;
        a = b;
        b = sisa;
    }
    return a;
}

int hitungKPK(int a, int b) {
    return (a * b) / hitungFPB(a, b);
}

int main() {
  char menu;
  int a, b , pilihan;

  do {
    cout << "----- Pilihan Opsi -----" << endl;
    cout << "1. Menentukan KPK" << endl;
    cout << "2. Menentukan FPB" << endl;
    cout << "3. Keluar" << endl;
    cout << "----------------------" << endl;
    cout << "Pilih Opsi : ";
    cin >> pilihan;
    cout << endl;

    switch (pilihan) {
      case 1: {
        cout << "Masukkan bilangan pertama : ";
        cin >> a;
        cout << "Masukkan bilangan kedua : ";
        cin >> b;

        int kpk = hitungKPK(a, b);
        hitungKPK(a, b);
        cout << "--------------------------------------------" << endl;
        cout << "KPK dari " << a << " dan " << b << " adalah: " << kpk << endl;
        cout << "--------------------------------------------" << endl;
        break;
      }
      
      case 2: {
        cout << "Masukkan bilangan pertama : ";
        cin >> a;
        cout << "Masukkan bilangan kedua : ";
        cin >> b;
        
        int fpb = hitungFPB(a, b);
        hitungFPB(a, b);
        cout << "--------------------------------------------" << endl;
        cout << "FPB dari " << a << " dan " << b << " adalah: " << fpb << endl;
        cout << "--------------------------------------------" << endl;
        break;
      }

      case 3: {
        cout << "Terima kasih telah menggunakan program ini" << endl;
        return 0;
      }

      default: {
        cout << "Pilihan tidak valid" << endl;
      }
    }

    cout << "Ingin kembali ke menu utama ? (y/n) : ";
    cin >> menu;

    system("cls");

  } while (menu == 'y' || menu == 'Y');
  
    cout << "Terima kasih telah menggunakan program ini" << endl;
    return 0;
}
