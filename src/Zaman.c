#include "Zaman.h"



Zaman* ZamanOlustur(int gun, int ay, int yil) {
    Zaman* z = (Zaman*)malloc(sizeof(Zaman));
    z->saat = 0;
    z->gun = gun;
    z->ay = ay;
    z->yil = yil;

    z->ZamanIlerle = &ZamanIlerle;
    z->ZamanToString = &ZamanToString;
    z->ZamanYokEt = &ZamanYokEt;

    return z;
}

// Ay gün sayıları
int AyGunSayisi(int ay) {
    switch (ay) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return 28;
        default:
            return 30;
    }
}

// Saat ilerletme
void ZamanIlerle(Zaman* z, int saatArtis, int gunSaatSayisi) {
    z->saat += saatArtis;
    while (z->saat >= gunSaatSayisi) {
        z->saat -= gunSaatSayisi;
        z->gun++;
        if (z->gun > AyGunSayisi(z->ay)) {
            z->gun = 1;
            z->ay++;
            if (z->ay > 12) {
                z->ay = 1;
                z->yil++;
            }
        }
    }
}

void ZamanToString(Zaman* z, char* buffer) {
    sprintf(buffer, "%02d.%02d.%04d", z->gun, z->ay, z->yil);
}

void ZamanYokEt(Zaman* z) {
    free(z);
}

int ZamanKarsilastir(Zaman* z1, Zaman* z2) {
    if (!z1 || !z2) return 0;
    if (z1->yil != z2->yil) return z1->yil - z2->yil;
    if (z1->ay != z2->ay) return z1->ay - z2->ay;
    if (z1->gun != z2->gun) return z1->gun - z2->gun;
    if (z1->saat != z2->saat) return z1->saat - z2->saat;
    return 0;
}

Zaman* ZamanKopyala(Zaman* z) {
    if (!z) return NULL;
    Zaman* yeni = (Zaman*)malloc(sizeof(Zaman));
    yeni->saat = z->saat;
    yeni->gun = z->gun;
    yeni->ay = z->ay;
    yeni->yil = z->yil;
    yeni->ZamanIlerle = z->ZamanIlerle;
    yeni->ZamanToString = z->ZamanToString;
    yeni->ZamanYokEt = z->ZamanYokEt;
    return yeni;
}

