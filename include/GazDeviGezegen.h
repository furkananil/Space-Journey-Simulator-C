#ifndef GAZDEVIGEZEGEN_H
#define GAZDEVIGEZEGEN_H

#include "gezegen.h"
#include <stdlib.h>
#include <string.h>

// Her tür için yapılar ve oluşturucular

typedef struct GazDeviGezegen {
    Gezegen base;


} GazDeviGezegen;


GazDeviGezegen* GazDeviGezegenOlustur(char* ad, int gunSaat, Zaman* tarih);
double GazDeviYaslanma(Gezegen* g);
void GazDeviGezegenYokEt(GazDeviGezegen* g);

#endif
