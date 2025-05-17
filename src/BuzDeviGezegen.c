#include "BuzDeviGezegen.h"

BuzDeviGezegen* BuzDeviGezegenOlustur(char* ad, int gunSaat, Zaman* tarih) {
    BuzDeviGezegen* g = (BuzDeviGezegen*)malloc(sizeof(BuzDeviGezegen));
    g->base.ad = strdup(ad);
    g->base.tur = 2;
    g->base.gunSaatSayisi = gunSaat;
    g->base.tarih = tarih;
    g->base.yaslanmaKatsayisi = BuzDeviYaslanma;
    g->base.GezegenNufusSifirla = &GezegenNufusSifirla;
    g->base.GezegenNufusArttir = GezegenNufusArttir;
    
    return g;
}

double BuzDeviYaslanma(Gezegen* g) {
    return 0.5;
}

void BuzDeviGezegenYokEt(BuzDeviGezegen* g) {
    if (!g) return;
    if (g->base.tarih) ZamanYokEt(g->base.tarih);
    if (g->base.ad) free(g->base.ad);
    free(g);
}