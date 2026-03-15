#include <iostream>
using namespace std;

int main(){
  int bilangan;
  cout << "Masukkan bilangan : ";
  cin >> bilangan;

  int check = 0;
  for (int i = 1; i <= bilangan; i++){
    if (bilangan % i == 0){
      check++;
    }
  }

  if (check < 3){
    cout << bilangan << " merupakan bilangan prima" << endl;
  } else {
    cout << bilangan << " bukan bilangan prima";
  }
}