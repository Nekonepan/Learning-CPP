// dua bilangan interger A dan B kemudian tukarkan bilangan tersebut dan tampilkan hasil penukarannya

#include <iostream>
using namespace std;

int main() {
  int a, b;

  cout << "Masukkan bilangan pertama : ";
  cin >> a;
  cout << "Masukkan bilangan kedua : ";
  cin >> b;

  swap(a, b);
  cout << "a : " << a << endl;
  cout << "b : " << b << endl;
}