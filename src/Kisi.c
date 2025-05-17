#include "Kisi.h"



Kisi* KisiOlustur(char* ad, int yas, double kalanOmar, char* uzayAraci) {
    Kisi* k = (Kisi*)malloc(sizeof(Kisi));
    k->ad = strdup(ad);
    k->yas = yas;
    k->kalanOmar = kalanOmar;
    k->hayatta = true;
    k->uzayAraci = strdup(uzayAraci);

    k->KisiYaslandir = &KisiYaslandir;
    k->KisiYokEt = &KisiYokEt;
    k->KisiHayattaMi = &KisiHayattaMi;

    return k;
}

void KisiYaslandir(Kisi* k, double oran) {
    if (!k->hayatta) return;
    k->kalanOmar -= oran;
    if (k->kalanOmar <= 0) {
        k->hayatta = false;
        k->kalanOmar = 0;
    }
}

void KisiYokEt(Kisi* k) {
    if (!k) return;
    free(k->ad);
    free(k->uzayAraci);
    free(k);
}

bool KisiHayattaMi(Kisi* k) {
    return k && k->hayatta;
}
