// dosyaokuma.h
#ifndef DOSYAOKUMA_H
#define DOSYAOKUMA_H



#include "kayacgezegen.h"
#include "kisi.h"
#include "gezegen.h"
#include "uzayaraci.h"
#include "zaman.h"
#include "buzdevigezegen.h"
#include "gazdevigezegen.h"
#include "cucegezegen.h"
#include "kayacgezegen.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define AYIRICI "#"

char* dosyaIcerik(const char* dosyaAdi);
Kisi** KisileriYukle(const char* dosyaAdi, int* kisiSayisi);
UzayAraci** AraclariYukle(const char* dosyaAdi, int* aracSayisi);
Gezegen** GezegenleriYukle(const char* dosyaAdi, int* gezegenSayisi);

#endif