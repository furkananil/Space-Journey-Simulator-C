#ifndef CUCEGEZEGEN_H
#define CUCEGEZEGEN_H

#include "gezegen.h"
#include <stdlib.h>
#include <string.h>

// Her tür için yapılar ve oluşturucular

typedef struct CuceGezegen {
    Gezegen base;


} CuceGezegen;



CuceGezegen* CuceGezegenOlustur(char* ad, int gunSaat, Zaman* tarih);
double CuceYaslanma(Gezegen* g);
void CuceGezegenYokEt(CuceGezegen* g);

#endif
