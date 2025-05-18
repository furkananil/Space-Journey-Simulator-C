#include "simulasyon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void ekranTemizle() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void UzayAraciVarisTarihiHesapla(UzayAraci* arac, Gezegen** gezegenler, int gezegenSayisi) {
    if (!arac || !arac->kalkti || arac->varisTarihi != NULL) return;

    Gezegen* varisGezegeni = GezegenBul(gezegenler, gezegenSayisi, arac->varis);
    if (!varisGezegeni || !varisGezegeni->tarih) return;

    arac->varisTarihi = ZamanKopyala(varisGezegeni->tarih);
    ZamanIlerle(arac->varisTarihi, arac->kalanSaat, varisGezegeni->gunSaatSayisi);
}

void GezegenNufusGuncelle(Gezegen** gezegenler, int gezegenSayisi, UzayAraci** araclar, int aracSayisi) {
    for (int i = 0; i < gezegenSayisi; i++) {
        Gezegen* g = gezegenler[i];
        if (!g || !g->GezegenNufusSifirla || !g->GezegenNufusArttir) continue;
        g->GezegenNufusSifirla(g);
    }

    for (int j = 0; j < aracSayisi; j++) {
        UzayAraci* a = araclar[j];
        if (!a || a->imha) continue;

        const char* aktifGezegen = NULL;
        if (!a->kalkti) {
            aktifGezegen = a->cikis;
        } else if (a->vardi) {
            aktifGezegen = a->varis;
        }
        if (!aktifGezegen) continue;

        Gezegen* g = GezegenBul(gezegenler, gezegenSayisi, aktifGezegen);
        if (!g) continue;

        for (int k = 0; k < a->yolcuSayisi; k++) {
            if (!a->yolcular[k]) continue;
            if (KisiHayattaMi(a->yolcular[k])) {
                g->GezegenNufusArttir(g);
            }
        }
    }
}

void simulasyonDurumunuYazdir(Gezegen** gezegenler, int gezegenSayisi, UzayAraci** araclar, int aracSayisi, int saatSayaci) {
    ekranTemizle();
    printf("Simulasyon Saati: %d\n\n", saatSayaci);
    printf("Gezegenler:\n");
    // Gezegen başlıkları
    printf("%-17s", "");
    for (int i = 0; i < gezegenSayisi; i++) {
        printf("--- %s ---           ", gezegenler[i]->ad);
    }
    printf("\n");

    // Gezegen tarihleri
    printf("%-17s", "Tarih");
    for (int i = 0; i < gezegenSayisi; i++) {
        char buf[32] = "--";
        if (gezegenler[i]->tarih)
            ZamanToString(gezegenler[i]->tarih, buf);
        printf("%-20s", buf);
    }
    printf("\n");

    // Gezegen nüfusları
    printf("%-17s", "Nufus");
    for (int i = 0; i < gezegenSayisi; i++) {
        printf("%-20d", gezegenler[i]->nufus);
    }
    printf("\n\n");

    // Uzay araçları başlık
    printf("Uzay Araclari:\n");
    printf("%-18s %-12s %-10s %-12s %-22s %-25s\n",
           "Arac Adi", "Durum", "Cikis", "Varis", "Hedefe Kalan Saat", "Hedefe Varacagi Tarih");

    // Uzay araçları bilgileri 
    for (int i = 0; i < aracSayisi; i++) {
        UzayAraci* a = araclar[i];
        if (!a) continue;
        const char* durum = a->imha ? "IMHA" : (a->vardi ? "Vardi" : (a->kalkti ? "Yolda" : "Bekliyor"));

        char kalan_saat_buffer[10] = "--";
        char varis_tarih[32] = "--";
        if (!a->imha && a->kalkti) {
            sprintf(kalan_saat_buffer, "%d", a->kalanSaat);
            if (a->varisTarihi)
                ZamanToString(a->varisTarihi, varis_tarih);
        }

        printf("%-18s %-12s %-10s %-12s %-22s %-25s\n",
               a->ad, durum, a->cikis, a->varis, kalan_saat_buffer, varis_tarih);
    }
}

int simulasyonBittiMi(UzayAraci** araclar, int aracSayisi) {
    for (int i = 0; i < aracSayisi; i++) {
        if (araclar[i] && !araclar[i]->vardi && !araclar[i]->imha) {
            return 0;
        }
    }
    return 1;
}

void SimulasyonBaslat(Kisi** kisiler, int kisiSayisi,
                     UzayAraci** araclar, int aracSayisi,
                     Gezegen** gezegenler, int gezegenSayisi) {
    int saatSayaci = 0;
    int tamamlandi = 0;

    for (int i = 0; i < kisiSayisi; i++) {
        Kisi* k = kisiler[i];
        for (int j = 0; j < aracSayisi; j++) {
            UzayAraci* a = araclar[j];
            if (a && k && a->ad && k->uzayAraci && strcmp(k->uzayAraci, a->ad) == 0) {
                a->YolcuEkle(a, k);
                break;
            }
        }
    }

    while (!tamamlandi) {
        for (int i = 0; i < aracSayisi; i++) {
            UzayAraci* a = araclar[i];
            if (a && !a->kalkti) {
                Gezegen* g = GezegenBul(gezegenler, gezegenSayisi, a->cikis);
                if (g && g->tarih && a->cikisTarihi &&
                    g->tarih->gun == a->cikisTarihi->gun &&
                    g->tarih->ay == a->cikisTarihi->ay &&
                    g->tarih->yil == a->cikisTarihi->yil &&
                    g->tarih->saat == a->cikisTarihi->saat) {
                    a->kalkti = true;
                }
            }
        }

        for (int i = 0; i < gezegenSayisi; i++) {
            if (gezegenler[i] && gezegenler[i]->tarih) {
                ZamanIlerle(gezegenler[i]->tarih, 1, gezegenler[i]->gunSaatSayisi);
            }
        }

        GezegenNufusGuncelle(gezegenler, gezegenSayisi, araclar, aracSayisi);

        
        for (int i = 0; i < aracSayisi; i++) {
            UzayAraci* a = araclar[i];
            if (!a) continue;

            
            for (int k = 0; k < a->yolcuSayisi; ) {
                Kisi* yolcu = a->yolcular[k];
                if (!KisiHayattaMi(yolcu)) {
                    for (int j = k; j < a->yolcuSayisi - 1; j++) {
                        a->yolcular[j] = a->yolcular[j + 1];
                    }
                    a->yolcuSayisi--;
                } else {
                    k++;
                }
            }
            a->SaatIlerle(a, gezegenler, gezegenSayisi);
            if (a->kalkti && !a->vardi && !a->imha) {

                UzayAraciVarisTarihiHesapla(a, gezegenler, gezegenSayisi);
                UzayAraciVarisKontrol(a, gezegenler, gezegenSayisi);
                UzayAraciDurumGuncelle(a);
            }
            a->DurumGuncelle(a);
        }

        simulasyonDurumunuYazdir(gezegenler, gezegenSayisi, araclar, aracSayisi, saatSayaci);
        tamamlandi = simulasyonBittiMi(araclar, aracSayisi);

        saatSayaci++;
        #ifdef _WIN32
            Sleep(30);
        #else
            usleep(30000);
        #endif
    }

    GezegenNufusGuncelle(gezegenler, gezegenSayisi, araclar, aracSayisi);
    simulasyonDurumunuYazdir(gezegenler, gezegenSayisi, araclar, aracSayisi, saatSayaci);
    printf("\nSimülasyon tamamlandı. Toplam süre: %d saat.\n", saatSayaci);
}
