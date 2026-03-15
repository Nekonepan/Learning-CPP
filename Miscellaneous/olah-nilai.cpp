// Diketahui N mahasiswa dengan nilai [0 - 100] bilagnan real. Hitung rata-rata nilai, nilai tertinggi dan terkecil, hitung berapa
// mahasiswa yang memiliki nilai > 70

#include <iostream>
using namespace std;

int main() {
  int n;
  float jumlah = 0;
  float rata_rata = 0;

  cout << "Masukkan jumlah mahasiswa : ";
  cin >> n;

  float* arr = new float[n];

  for (int i = 0; i < n; i++) {
    cout << "Masukkan nilai mahasiswa ke-" << i << " : ";
    cin >> arr[i];
  }

  for (int i = 0; i < n; i++) {
    jumlah += arr[i];
    rata_rata = jumlah / n;
  }

  float min = arr[0];
  float max = arr[0];

  for (int i = 0; i < n; i++) {
    if (arr[i] < min) {
      min = arr[i];
    }
    if (arr[i] > max) {
      max = arr[i];
    }
  }

  int counter = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i] > 70) {
      counter++;
    }
  }

  cout << "Nilai rata-rata mahasiswa = " << rata_rata << endl;
  cout << "Nilai terkecil mahasiswa = " << min << endl;
  cout << "Nilai terbesar mahasiswa = " << max << endl;
  cout << "Jumlah mahasiswa yang mendapat nilai lebih dari 70 = " << counter << endl;
  
}