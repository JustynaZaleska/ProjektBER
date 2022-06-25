#pragma once
#include <fstream>
#include <time.h>
#include <iostream>
#include <iomanip> 

using namespace std;

// porownujemy bit o okre�lonym numerze w 2 bajtach
bool porownaj_bit(unsigned char b1, unsigned char  b2, int n) {
    unsigned char mask, tmp;

    mask = 1 << (n - 1);
    tmp = b1 ^ b2;

    if ((tmp & mask) == 0)
        return true;
    else
        return false;
}

// sprawdzamy iloma bitami r�ni� si� 2 bajty
int bit_diff(unsigned char b1, unsigned char  b2) {

    int diff = 0;
    for (int i = 0; i < 8; i++)
    {
        if (!porownaj_bit(b1, b2, i))
            diff++;
    }

    return diff;
}

// obliczamy BER pomi�dzy dwoma plikami

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

    // przechodzimy przez poszczegolne bajty i sprawdzamy o ile bitow si� roznia
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

