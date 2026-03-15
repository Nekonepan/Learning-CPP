#include <iostream>
using namespace std;

class Program {
  private: 
  int angka[8] = {5, 8, 3, 6, 7, 1, 4, 9};
  string kalimat = "Algoritma dan Pemograman";

  bool is_vokal(char huruf) {
    if (huruf=='a'||huruf=='i'||huruf=='u'||huruf=='e'||huruf=='o'||
      huruf=='A'||huruf=='I'||huruf=='U'||huruf=='E'||huruf=='O') {
        return true;
      }

      return false;
  }

  public:
  void sort_angka() {
    int temp;

    for (int i = 0; i < 8 - 1; i++) {
      for (int j = i + 1; j < 8; j++) {
          if (angka[i] > angka[j]) {
            temp = angka[i];
            angka[i] = angka[j];
            angka[j] = temp;
          }
      }
    }
  }

  void proses() {
    sort_angka();

    int jumlah_vokal = 0;
    
    for (int i = 0; kalimat[i] != '\0'; i++) {
      if (is_vokal(kalimat[i])) {
        jumlah_vokal++;
      }
    }

    int vokal_ke = 0;
    int index_angka = 0;
    string hasil = "";

    for (int i = 0; kalimat[i] != '\0'; i++) {
      char c = kalimat[i];

        if (is_vokal(c)) {
        vokal_ke++;

        if (vokal_ke != jumlah_vokal) {
          hasil += char(angka[index_angka] + '0');
          index_angka++;
        } else {
          hasil += c;
        }
      } else {
        hasil += c;
      }
    }

    cout << hasil << endl;
  }
};

int main() {
  Program p;
  p.proses();

  return 0;
}