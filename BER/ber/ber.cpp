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