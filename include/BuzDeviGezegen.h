#ifndef BUZDEVIGEZEGEN_H
#define BUZDEVIGEZEGEN_H

#include "gezegen.h"
#include <stdlib.h>
#include <string.h>

// Her tür için yapılar ve oluşturucular

typedef struct BuzDeviGezegen {
    Gezegen base;


} BuzDeviGezegen;


BuzDeviGezegen* BuzDeviGezegenOlustur(char* ad, int gunSaat, Zaman* tarih);
double BuzDeviYaslanma(Gezegen* g);
void BuzDeviGezegenYokEt(BuzDeviGezegen* g);
#endif
