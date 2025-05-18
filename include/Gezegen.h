// gezegen.h
#ifndef GEZEGEN_H
#define GEZEGEN_H

#include "zaman.h"
#include <stdlib.h>
#include <string.h>


// Soyut Gezegen yapısı (Base)
typedef struct Gezegen {
    char* ad;
    int tur; // 0: Kayaç, 1: Gaz Devi, 2: Buz Devi, 3: Cüce
    int gunSaatSayisi;
    int nufus;
    Zaman* tarih;

    // Sanal metodlar (function pointer benzetimi)
    double (*yaslanmaKatsayisi)(struct Gezegen*);
    void (*GezegenYokEt)(struct Gezegen*);
    void (*GezegenZamanIlerle)(struct Gezegen* g, int saat);
    void (*GezegenNufusSifirla)(struct Gezegen* g);
    void (*GezegenNufusArttir)(struct Gezegen* g);
    void (*GezegenYazdirTarih)(struct Gezegen* g, char* hedefBuffer, int bufferSize);
} Gezegen;

// Gezegen oluşturucu (base initializer)
Gezegen* GezegenOlustur(char* ad, int tur, int gunSaatSayisi, Zaman* tarih);
void GezegenYokEt(Gezegen*);

void GezegenZamanIlerle(Gezegen* g, int saat);
void GezegenNufusSifirla(Gezegen* g);
void GezegenNufusArttir(Gezegen* g);
void GezegenYazdirTarih(Gezegen* g, char* hedefBuffer, int bufferSize);
Gezegen* GezegenBul(Gezegen** gezegenler, int gezegenSayisi, const char* ad);
#endif