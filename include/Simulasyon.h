// simulasyon.h
#ifndef SIMULASYON_H
#define SIMULASYON_H

#include "kisi.h"
#include "gezegen.h"
#include "uzayaraci.h"

void SimulasyonBaslat(Kisi** kisiler, int kisiSayisi,
                      UzayAraci** araclar, int aracSayisi,
                      Gezegen** gezegenler, int gezegenSayisi);

#endif


