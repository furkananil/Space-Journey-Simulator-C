#ifndef KAYACGEZEGEN_H
#define KAYACGEZEGEN_H

#include "gezegen.h"
#include <stdlib.h>
#include <string.h>

// Her tür için yapılar ve oluşturucular

typedef struct KayacGezegen {
    Gezegen base;


} KayacGezegen;


KayacGezegen* KayacGezegenOlustur(char* ad, int gunSaat, Zaman* tarih);
double KayacYaslanma(Gezegen* g);
void KayacGezegenYokEt(KayacGezegen* g);


#endif
