#include <iostream>
using namespace std;

string kalimat;
const int angka[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

void input_kalimat() {
  cout << "Masukkan kalimat :";
  getline(cin, kalimat);
}

bool is_vokal(char huruf) {
  if (huruf=='a'||huruf=='i'||huruf=='u'||huruf=='e'||huruf=='o'|| huruf=='A'||huruf=='I'||huruf=='U'||huruf=='E'||huruf=='O') {
    return true;
  }

  return false;
}

void proses() {
  int index = 0;
  string hasil = "";

  for (int i = 0; kalimat[i] != '\0'; i++) {
    char c = kalimat[i];

    if (is_vokal(c)) {
      hasil += char(angka[index] + '0');
      index = (index + 1) % 9;
    } else {
      hasil += c;
    }
  }

  cout << hasil << endl;
}

int main() {
  input_kalimat();
  proses();
}