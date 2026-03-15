#include <iostream>
using namespace std;

int main() {
    char data[3][5] = {
        {'D', 'A', 'U', 'A', 'D'},
        {'U', 'D', 'A', 'U', 'U'},
        {'U', 'A', 'D', 'D', 'A'}
    };
    int counter = 0;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (data[i][j] == 'U' && data[i][j + 1] == 'A' && data[i][j + 2] == 'D') {
                counter++;
            }
        }
    }
    
    cout << "Jumlah kata UAD : " << counter;
}
