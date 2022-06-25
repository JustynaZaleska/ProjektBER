#pragma once
#include <fstream>
#include <time.h>
#include <iostream>
#include <iomanip> 

using namespace std;

// porownujemy bit o okreœlonym numerze w 2 bajtach
bool porownaj_bit(unsigned char b1, unsigned char  b2, int n) {
    unsigned char mask, tmp;

    mask = 1 << (n - 1);
    tmp = b1 ^ b2;

    if ((tmp & mask) == 0)
        return true;
    else
        return false;
}

// sprawdzamy iloma bitami ró¿ni¹ siê 2 bajty
int bit_diff(unsigned char b1, unsigned char  b2) {

    int diff = 0;
    for (int i = 0; i < 8; i++)
    {
        if (!porownaj_bit(b1, b2, i))
            diff++;
    }

    return diff;
}

// obliczamy BER pomiêdzy dwoma plikami

void BER(char* path1, char* path2) {
    clock_t czas_poczatkowy = clock();

    // wczytujemy plik 1
    std::ifstream f1;
    int len1;
    f1.open(path1);
    f1.seekg(0, std::ios::end);
    len1 = f1.tellg();
    f1.seekg(0, std::ios::beg);
    char* buffer1 = new char[len1];
    f1.read(buffer1, len1);
    f1.close();

    // wczytujemy plik 2
    std::ifstream f2;
    int len2;
    f2.open(path2);
    f2.seekg(0, std::ios::end);
    len2 = f2.tellg();
    f2.seekg(0, std::ios::beg);
    char* buffer2 = new char[len2];
    f2.read(buffer2, len2);
    f2.close();

    // przechodzimy przez poszczegolne bajty i sprawdzamy o ile bitow siê roznia
    // wynik dodajemy do zmiennej errors
    int errors = 0;
    for (int i = 0; i < len1; i++)
    {
        unsigned char b1 = (unsigned char)buffer1[i];
        unsigned char b2 = (unsigned char)buffer2[i];

        if (b1 != b2)
        {
            errors += bit_diff(b1, b2);
        }

    }
    // obliczmy BER
    double ber = (double)errors / (double)(len1 * 8);

    clock_t czas_koncowy = clock();
    double czas = (double)(czas_koncowy - czas_poczatkowy) / CLOCKS_PER_SEC;

    fstream log("log.txt", ios::out);

    // Wynik obliczen drukowany jest w konsoli (Jako wynik podajemy: Ilosc porownanych bitow, ilosc roznych bitow, wynik BER, czas obliczen)
    cout << time(NULL) << endl;
    cout << "Ilosc porownanych bitow: " << len1 * 8 << endl;
    cout << "ilosc roznych bitow: " << errors << endl;
    cout << "BER: " << setprecision(5) << ber << endl;
    cout << "Czas obliczen (sek): " << czas << endl;

    log << time(NULL) << endl;
    log << "Ilosc porownanych bitow: " << len1 * 8 << endl;
    log << "ilosc roznych bitow: " << errors << endl;
    log << "BER: " << setprecision(5) << ber << endl;
    log << "Czas obliczen (sek): " << czas << endl;


    log.close();

    delete buffer1;
    delete buffer2;
}

int main(int argc, char** argv)
{

    if (argc != 3)
    {
        cout << " Nieprawidlowe parametry";
        return 0;
    }



    BER(argv[1], argv[2]);


}