// main.c
#include "dosyaokuma.h"
#include "simulasyon.h"
#include "kisi.h"
#include "gezegen.h"
#include "uzayaraci.h"
#include "zaman.h"
#include "buzdevigezegen.h"
#include "gazdevigezegen.h"
#include "cucegezegen.h"
#include "kayacgezegen.h"

int main() {
    
    int kisiSayisi = 0, aracSayisi = 0, gezegenSayisi = 0;

    Kisi** kisiler = KisileriYukle("Kisiler.txt", &kisiSayisi);
    UzayAraci** araclar = AraclariYukle("Araclar.txt", &aracSayisi);
    Gezegen** gezegenler = GezegenleriYukle("Gezegenler.txt", &gezegenSayisi);
    

    if (!kisiler || !araclar || !gezegenler) {
        printf("Veri dosyaları yüklenemedi.\n");
        return 1;
    }
    
    SimulasyonBaslat(kisiler, kisiSayisi, araclar, aracSayisi, gezegenler, gezegenSayisi);
    
    
    return 0;
}