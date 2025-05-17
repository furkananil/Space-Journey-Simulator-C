#include "GazDeviGezegen.h"

GazDeviGezegen* GazDeviGezegenOlustur(char* ad, int gunSaat, Zaman* tarih) {
    GazDeviGezegen* g = (GazDeviGezegen*)malloc(sizeof(GazDeviGezegen));
    g->base.ad = strdup(ad);
    g->base.tur = 1;
    g->base.gunSaatSayisi = gunSaat;
    g->base.tarih = tarih;
    g->base.yaslanmaKatsayisi = GazDeviYaslanma;
    g->base.GezegenNufusSifirla = &GezegenNufusSifirla;
    g->base.GezegenNufusArttir = GezegenNufusArttir;

    return g;
}


double GazDeviYaslanma(Gezegen* g) {
    return 0.1;
}

void GazDeviGezegenYokEt(GazDeviGezegen* g) {
    if (!g) return;
    if (g->base.tarih) ZamanYokEt(g->base.tarih);
    if (g->base.ad) free(g->base.ad);
    free(g);
}
