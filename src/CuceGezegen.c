#include "CuceGezegen.h"

CuceGezegen* CuceGezegenOlustur(char* ad, int gunSaat, Zaman* tarih) {
    CuceGezegen* g = (CuceGezegen*)malloc(sizeof(CuceGezegen));
    g->base.ad = strdup(ad);
    g->base.tur = 3;
    g->base.gunSaatSayisi = gunSaat;
    g->base.tarih = tarih;
    g->base.yaslanmaKatsayisi = CuceYaslanma;
    g->base.GezegenNufusSifirla = &GezegenNufusSifirla;
    g->base.GezegenNufusArttir = GezegenNufusArttir;

    return g;
}

double CuceYaslanma(Gezegen* g) {
    return 0.01;
}

void CuceGezegenYokEt(CuceGezegen* g) {
    if (!g) return;
    if (g->base.tarih) ZamanYokEt(g->base.tarih);
    if (g->base.ad) free(g->base.ad);
    free(g);
}