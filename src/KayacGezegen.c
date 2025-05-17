#include "KAYACGEZEGEN.h"

KayacGezegen* KayacGezegenOlustur(char* ad, int gunSaat, Zaman* tarih) {
    KayacGezegen* g = (KayacGezegen*)malloc(sizeof(KayacGezegen));
    g->base.ad = strdup(ad);
    g->base.tur = 0;
    g->base.gunSaatSayisi = gunSaat;
    g->base.tarih = tarih;
    g->base.yaslanmaKatsayisi = KayacYaslanma;
    g->base.GezegenNufusSifirla = &GezegenNufusSifirla;
    g->base.GezegenNufusArttir = GezegenNufusArttir;

    return g;
}

// Türlere özel yaşlanma oranları
double KayacYaslanma(Gezegen* g) {
    return 1.0;
}

void KayacGezegenYokEt(KayacGezegen* g) {
    if (!g) return;
    if (g->base.tarih) ZamanYokEt(g->base.tarih);
    if (g->base.ad) free(g->base.ad);
    free(g);
}