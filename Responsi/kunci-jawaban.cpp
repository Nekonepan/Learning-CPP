#include <iostream>
using namespace std;

class Penyewa {
public:
   string id, nama, jenisPS, bonus;
   int lamaSewa, harga;
   double total, diskon, totalBayar;

   void input() {
       cout << "ID Penyewa : ";
       cin >> id;
       cin.ignore();

       cout << "Nama Penyewa : ";
       getline(cin, nama);

       cout << "Jenis PS (PS3/PS4/PS5): ";
       cin >> jenisPS;

       cout << "Lama Sewa : ";
       cin >> lamaSewa;

       hitung();
   }

   void hitung() {

       if (jenisPS == "PS3")
           harga = 10000;
       else if (jenisPS == "PS4")
           harga = 15000;
       else
           harga = 20000;

       total = harga * lamaSewa;

       if (total >= 200000)
           diskon = total * 0.20;
       else if (total >= 100000)
           diskon = total * 0.10;
       else
           diskon = 0;

       totalBayar = total - diskon;

       if (lamaSewa >= 8)
           bonus = "Gratis mie + minuman";
       else if (lamaSewa >= 5)
           bonus = "Gratis minuman";
       else
           bonus = "Tidak ada bonus";
   }

   void tampil() {
       cout << "\nID : " << id << endl;
       cout << "Nama : " << nama << endl;
       cout << "Jenis PS : " << jenisPS << endl;
       cout << "Lama : " << lamaSewa << " jam" << endl;
       cout << "Total : Rp" << total << endl;
       cout << "Diskon : Rp" << diskon << endl;
       cout << "Bayar : Rp" << totalBayar << endl;
       cout << "Bonus : " << bonus << endl;
   }
};

int main() {

   Penyewa p1, p2, p3;
   int pilih, jumlah = 0;
   string cari;

   do {
       cout << "\n=== MENU ===\n";
       cout << "1. Input Data\n";
       cout << "2. Tampil Data\n";
       cout << "3. Cari ID\n";
       cout << "4. Keluar\n";
       cout << "Pilih: ";
       cin >> pilih;

       switch(pilih) {

       case 1:
           jumlah++;

           if(jumlah == 1)
               p1.input();
           else if(jumlah == 2)
               p2.input();
           else if(jumlah == 3)
               p3.input();
           break;

       case 2:
           if(jumlah >= 1) p1.tampil();
           if(jumlah >= 2) p2.tampil();
           if(jumlah >= 3) p3.tampil();
           break;

       case 3:
           cout << "Cari ID: ";
           cin >> cari;

           if(p1.id == cari)
               p1.tampil();
           else if(p2.id == cari)
               p2.tampil();
           else if(p3.id == cari)
               p3.tampil();
           else
               cout << "Data tidak ditemukan";
           break;

       case 4:
           cout << "Program selesai";
           break;

       default:
           cout << "Pilihan salah";
       }

   } while(pilih != 4);

   return 0;
}
