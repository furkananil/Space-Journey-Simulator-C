// kisi.h
#ifndef KISI_H
#define KISI_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Kisi {
    char* ad;
    int yas;
    double kalanOmar; // saat bazında kalan ömür
    bool hayatta;
    char* uzayAraci; // hangi araca ait

    void (*KisiYaslandir)(struct Kisi* k, double oran);
    void (*KisiYokEt)(struct Kisi* k);
    bool (*KisiHayattaMi)(struct Kisi* k);
} Kisi;

Kisi* KisiOlustur(char* ad, int yas, double kalanOmar, char* uzayAraci);
void KisiYaslandir(Kisi* k, double oran); // oran: yaşlanma katsayısı
void KisiYokEt(Kisi* k);
bool KisiHayattaMi(Kisi* k);

#endif