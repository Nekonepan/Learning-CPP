
#include <iostream>
#include <cmath>
using namespace std;

class hitung {
  public:
  int proses();
  void input();

  private:
  int n;
  float rumus, jumlah, total;
};

void hitung::input() {
  cin >> n;
  cout << endl;
};

int hitung::proses() {
  jumlah = 0;
  total = 0;
  rumus = -1;

  for (int i = 1; i <= n; i++) {
    total = (i % 2 == 0) ? -(1.0 / i) : (1.0 / i);
    jumlah += total;

    if (i == 1) {
      cout << "(" << total << ")";
    } else {
        cout << (total > 0 ? " + " : " - ")<< "(" << abs(total) << ")";
    }
  }

  cout << endl << endl << "Hasil penjumlahan deret = " << jumlah;
  return jumlah;
};

int main() {
  hitung deret;
  cout << "Program sederhana menghitung jumlah dari rumus 1 - (1/2) + (1/3) - (1/4) + ... + (1/n)" << endl << endl;
  cout << "Tentukan nilai n: ";
  deret.input();
  deret.proses();
}