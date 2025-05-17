#include "simulasyon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Yardımcı fonksiyonlar (ekran temizleme, gezegen bulma vb.)

void ekranTemizle() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

Gezegen* GezegenBul(Gezegen** gezegenler, int gezegenSayisi, const char* ad) {
    for (int i = 0; i < gezegenSayisi; i++) {
        if (gezegenler[i] && gezegenler[i]->ad && strcmp(gezegenler[i]->ad, ad) == 0) {
            return gezegenler[i];
        }
    }
    return NULL;
}

void UzayAraciVarisKontrol(UzayAraci* a, Gezegen** gezegenler, int gezegenSayisi) {
    if (!a || a->vardi || a->imha || !a->varisTarihi) return;
    Gezegen* varisGezegeni = GezegenBul(gezegenler, gezegenSayisi, a->varis);
    if (!varisGezegeni || !varisGezegeni->tarih) return;
    if (ZamanKarsilastir(varisGezegeni->tarih, a->varisTarihi) >= 0) {
        a->vardi = 1;
        a->kalanSaat = 0;
        // DEBUG
        printf("[DEBUG] %s aracı %s gezegenine vardı.\n", a->ad, a->varis);
    }
}

// Yardımcı fonksiyonlar (tarih işlemleri, nüfus güncelleme vb.)

void UzayAraciVarisTarihiHesapla(UzayAraci* arac, Gezegen** gezegenler, int gezegenSayisi) {
    if (!arac || !arac->kalkti || arac->varisTarihi != NULL) return;

    Gezegen* varisGezegeni = GezegenBul(gezegenler, gezegenSayisi, arac->varis);
    if (!varisGezegeni || !varisGezegeni->tarih) return;

    // Varış tarihini hesapla
    arac->varisTarihi = ZamanOlustur(
        varisGezegeni->tarih->gun,
        varisGezegeni->tarih->ay,
        varisGezegeni->tarih->yil
    );
    if (arac->varisTarihi) {
        ZamanIlerle(arac->varisTarihi, arac->kalanSaat, varisGezegeni->gunSaatSayisi);
    }
}


void GezegenNufusGuncelle(Gezegen** gezegenler, int gezegenSayisi, UzayAraci** araclar, int aracSayisi) {
    for (int i = 0; i < gezegenSayisi; i++) {
        Gezegen* g = gezegenler[i];
        if (!g || !g->GezegenNufusSifirla || !g->GezegenNufusArttir) continue;
        g->GezegenNufusSifirla(g); // Önce sıfırla
        for (int j = 0; j < aracSayisi; j++) {
            UzayAraci* a = araclar[j];
            if (!a || !a->vardi || !a->varis || !g->ad) continue;
            if (strcmp(a->varis, g->ad) != 0) continue;
            for (int k = 0; k < a->yolcuSayisi; k++) {
                if (!a->yolcular) continue;
                Kisi* yolcu = a->yolcular[k];
                printf("[DEBUG] Kontrol: %s aracı, %s gezegeni, yolcu %p\n", a->ad, g->ad, (void*)yolcu);
                if (yolcu) {
                    printf("[DEBUG] Yolcu hayatta mı? %d\n", KisiHayattaMi(yolcu));
                    if (KisiHayattaMi(yolcu)) {
                        printf("[DEBUG] %s gezegenine %s aracı ile yolcu eklendi.\n", g->ad, a->ad);
                        g->GezegenNufusArttir(g);
                    }
                }
            }
        }
    }
}

// Simülasyon durumunu yazdırma fonksiyonu
void simulasyonDurumunuYazdir(Gezegen** gezegenler, int gezegenSayisi, UzayAraci** araclar, int aracSayisi, int saatSayaci) {
    ekranTemizle();
    printf("Simülasyon Saati: %d\n\n", saatSayaci);

    printf("Gezegenler:\n");
    for (int i = 0; i < gezegenSayisi; i++) {
        if (gezegenler[i]) {
            char buf[64];
            ZamanToString(gezegenler[i]->tarih, buf);
            printf("%-10s - %s   Nüfus: %d\n", gezegenler[i]->ad, buf, gezegenler[i]->nufus);
        }
    }

    printf("\nUzay Araçları:\n");
    for (int i = 0; i < aracSayisi; i++) {
        UzayAraci* a = araclar[i];
        if (!a) continue;
        char varisTarihi[64] = "--";
        if (a->varisTarihi) { // Sadece vardi değil, varisTarihi varsa yaz
            ZamanToString(a->varisTarihi, varisTarihi);
        }
        const char* durum = a->imha ? "IMHA" : (a->vardi ? "Vardi" : (a->kalkti ? "Yolda" : "Bekliyor"));
        printf("%-10s %-8s Cikis: %s   Varis: %s   Kalan: %d   Varis Tarihi: %s\n",
               a->ad, durum, a->cikis, a->varis,
               a->imha ? -1 : a->kalanSaat, varisTarihi);
    }
}

// Simülasyonun bitip bitmediğini kontrol et
int simulasyonBittiMi(UzayAraci** araclar, int aracSayisi) {
    for (int i = 0; i < aracSayisi; i++) {
        if (araclar[i] && !araclar[i]->vardi && !araclar[i]->imha) {
            return 0; // Simülasyon bitmedi
        }
    }
    return 1; // Simülasyon bitti
}

// Ana simülasyon fonksiyonu
void SimulasyonBaslat(Kisi** kisiler, int kisiSayisi,
                     UzayAraci** araclar, int aracSayisi,
                     Gezegen** gezegenler, int gezegenSayisi) {
    int saatSayaci = 0;
    int tamamlandi = 0;

    // Kişileri araçlara ekle
    for (int i = 0; i < kisiSayisi; i++) {
        Kisi* k = kisiler[i];
        for (int j = 0; j < aracSayisi; j++) {
            UzayAraci* a = araclar[j];
            if (a && k && a->ad && k->uzayAraci && strcmp(k->uzayAraci, a->ad) == 0) {
                a->YolcuEkle(a, k);
            }
        }
    }

    // Başlangıçta varış tarihlerini hesapla (sadece kalkış yapmış araçlar için)
    for (int i = 0; i < aracSayisi; i++) {
        UzayAraci* a = araclar[i];
        if (a && a->kalkti) {
            UzayAraciVarisTarihiHesapla(a, gezegenler, gezegenSayisi);
        }
    }

    while (!tamamlandi) {
        // Kalkış kontrolü
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

        // Zaman ilerletme
        for (int i = 0; i < gezegenSayisi; i++) {
            if (gezegenler[i] && gezegenler[i]->tarih) {
                ZamanIlerle(gezegenler[i]->tarih, 1, gezegenler[i]->gunSaatSayisi);
            }
        }

        // Nüfus güncelleme
        GezegenNufusGuncelle(gezegenler, gezegenSayisi, araclar, aracSayisi);

        // Araç işlemleri ve varış tarihi hesaplama
        for (int i = 0; i < aracSayisi; i++) {
    UzayAraci* a = araclar[i];
    if (!a) continue;

    if (a->kalkti && !a->vardi && !a->imha) {
        a->SaatIlerle(a);
        UzayAraciVarisTarihiHesapla(a, gezegenler, gezegenSayisi);
        UzayAraciVarisKontrol(a, gezegenler, gezegenSayisi); // <-- buraya ekle
        UzayAraciDurumGuncelle(a);
    }

    a->DurumGuncelle(a);
}

        // Ekran yazdırma
        simulasyonDurumunuYazdir(gezegenler, gezegenSayisi, araclar, aracSayisi, saatSayaci);

        // Bitiş kontrolü
        tamamlandi = simulasyonBittiMi(araclar, aracSayisi);

        saatSayaci++;
        #ifdef _WIN32
            Sleep(30);
        #else
            usleep(30000);
        #endif
    }

    // Döngü bittiğinde
    GezegenNufusGuncelle(gezegenler, gezegenSayisi, araclar, aracSayisi);
    simulasyonDurumunuYazdir(gezegenler, gezegenSayisi, araclar, aracSayisi, saatSayaci);
    printf("\nSimülasyon tamamlandı. Toplam süre: %d saat.\n", saatSayaci);
}