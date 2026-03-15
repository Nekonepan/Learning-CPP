#include <iostream>
using namespace std;

int main() {
    int arr[] = {12, 7, 3};

    cout << "Bilangan prima dalam array: ";

    for (int i = 0; i < 3; i++) {
        int counter = 0;
        for (int j = 1; j <= arr[i]; j++) {
            if (arr[i] % j == 0) {
                counter++;
            }
        }
        if (counter == 2) { // prima = hanya habis dibagi 1 dan dirinya sendiri
            cout << "Bilangan prima : " << arr[i] << " ";
        }
    }

    cout << endl;
    return 0;
}