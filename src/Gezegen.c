#include "Gezegen.h"
#include "GazDeviGezegen.h"
#include "BuzDeviGezegen.h"
#include "CuceGezegen.h"

Gezegen* GezegenOlustur(char* ad, int tur, int gunSaatSayisi, Zaman* tarih) {
    Gezegen* g = (Gezegen*)malloc(sizeof(struct Gezegen));
    g->ad = strdup(ad);
    g->tur = tur;
    g->nufus = 0;
    g->gunSaatSayisi = gunSaatSayisi;
    g->tarih = tarih;
    g->yaslanmaKatsayisi = NULL; // Başlangıçta NULL, türüne göre atanacak

    g->GezegenYokEt = &GezegenYokEt;
    g->GezegenZamanIlerle = &GezegenZamanIlerle;
    g->GezegenNufusSifirla = &GezegenNufusSifirla;
    g->GezegenNufusArttir = &GezegenNufusArttir;
    g->GezegenYazdirTarih = &GezegenYazdirTarih;


    return g;
}

void GezegenYokEt(Gezegen* g) {
    if (!g) return;
    switch (g->tur) {
        case 0: // Kayac
            free(g->ad);
            free(g); break;
        case 1: // Gaz Devi
            GazDeviGezegenYokEt((GazDeviGezegen*)g); break;
        case 2: // Buz Devi
            BuzDeviGezegenYokEt((BuzDeviGezegen*)g); break;
        case 3: // Cuce
            CuceGezegenYokEt((CuceGezegen*)g); break;
        default:
            free(g->ad);
            free(g); break;
    }
}

void GezegenZamanIlerle(Gezegen* g, int saat) {
    if (g && g->tarih) {
        ZamanIlerle(g->tarih, saat, g->gunSaatSayisi);
    }
}

void GezegenNufusSifirla(Gezegen* g) {
    if (g) {
        printf("[DEBUG] %s gezegeninin nüfusu sıfırlandı.\n", g->ad);
        g->nufus = 0;
    }
}

void GezegenNufusArttir(Gezegen* g) {
    if (g) {
        g->nufus++;
        printf("[DEBUG] %s gezegeninin nüfusu arttı: %d\n", g->ad, g->nufus);
    }
}

void GezegenYazdirTarih(Gezegen* g, char* hedefBuffer, int bufferSize) {
    snprintf(hedefBuffer, bufferSize, "%02d.%02d.%04d %02d:00", 
        g->tarih->gun, g->tarih->ay, g->tarih->yil, g->tarih->saat);
}





