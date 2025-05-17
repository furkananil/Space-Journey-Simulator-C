// zaman.h
#ifndef ZAMAN_H
#define ZAMAN_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

// Zaman yapısı: saat, gün, ay, yıl
typedef struct Zaman {
    int saat;
    int gun;
    int ay;
    int yil;

    void (*ZamanIlerle)(struct Zaman* z, int saatArtis, int gunSaatSayisi);
    void (*ZamanToString)(struct Zaman* z, char* buffer);
    void (*ZamanYokEt)(struct Zaman* z);
} Zaman;

Zaman* ZamanOlustur(int gun, int ay, int yil);
void ZamanIlerle(Zaman* z, int saatArtis, int gunSaatSayisi);
void ZamanYokEt(Zaman* z);
void ZamanToString(Zaman* z, char* buffer);
int ZamanKarsilastir(Zaman* z1, Zaman* z2);


#endif