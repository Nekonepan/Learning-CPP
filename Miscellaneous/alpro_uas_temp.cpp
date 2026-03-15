char kalimat[100];
cin.getline(kalimat, 100);

bool awalKata = true;

for (int i = 0; kalimat[i] != '\0'; i++) {
    if (kalimat[i] == ' ') {
        awalKata = true;
    } else if (awalKata && kalimat[i] >= 'a' && kalimat[i] <= 'z') {
        kalimat[i] = kalimat[i] - 32;  // ubah huruf kecil jadi kapital
        awalKata = false;
    } else {
        awalKata = false;
    }
}
cout << "Output: " << kalimat;