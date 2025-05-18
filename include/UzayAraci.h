// uzayaraci.h
#ifndef UZAYARACI_H
#define UZAYARACI_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "kisi.h"
#include "gezegen.h"

typedef struct UzayAraci {
    char* ad;
    char* cikis;
    char* varis;
    int kalanSaat;
    Zaman* cikisTarihi;
    Zaman* varisTarihi;

    bool kalkti;
    bool vardi;
    bool imha;

    Kisi** yolcular;
    int yolcuSayisi;
    int kapasite;

    void (*YolcuEkle)(struct UzayAraci* a, Kisi* k);
    void (*SaatIlerle)(struct UzayAraci* a, Gezegen** gezegenler, int gezegenSayisi);
    void (*DurumGuncelle)(struct UzayAraci* a);
    bool (*BosMu)(struct UzayAraci* a);
    void (*YokEt)(struct UzayAraci* a);
    void (*UzayAraciVarisKontrol)(struct UzayAraci* a, Gezegen** gezegenler, int gezegenSayisi);
} UzayAraci;

UzayAraci* UzayAraciOlustur(char* ad, char* cikis, char* varis, Zaman* cikisTarihi, int kalanSaat);
void UzayAraciYolcuEkle(UzayAraci* a, Kisi* k);
void UzayAraciSaatIlerle(UzayAraci* a, Gezegen** gezegenler, int gezegenSayisi);
void UzayAraciDurumGuncelle(UzayAraci* a);
bool UzayAraciBosMu(UzayAraci* a);
void UzayAraciYokEt(UzayAraci* a);
void UzayAraciVarisKontrol(UzayAraci* a, Gezegen** gezegenler, int gezegenSayisi);

#endif