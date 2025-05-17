#include "dosyaokuma.h"

char* dosyaIcerik(const char* dosyaAdi) {
    FILE* fp = fopen(dosyaAdi, "r");
    if (!fp) return NULL;
    fseek(fp, 0, SEEK_END);
    long uzunluk = ftell(fp);
    rewind(fp);
    char* icerik = (char*)malloc(sizeof(char) * (uzunluk + 1));
    fread(icerik, 1, uzunluk, fp);
    icerik[uzunluk] = '\0';
    fclose(fp);
    return icerik;
}

Kisi** KisileriYukle(const char* dosyaAdi, int* kisiSayisi) {
    char* icerik = dosyaIcerik(dosyaAdi);
    if (!icerik) {
        fprintf(stderr, "Dosya okuma hatasi\n");
        return NULL;
    }

    Kisi** kisiler = NULL;
    *kisiSayisi = 0;

    char* satir = icerik;
    char* sonraki_satir;

    while (satir) {
        char ad[50]; // İsim için yeterli boyut
        int yas;
        double omur;
        char arac[50]; // Araç adı için yeterli boyut
        int okunan;

        sonraki_satir = strchr(satir, '\n');
        if (sonraki_satir) {
            *sonraki_satir = '\0'; // Satırı sonlandır
        }

        okunan = sscanf(satir, "%49[^#]#%d#%lf#%49[^\n]", ad, &yas, &omur, arac);
        if (okunan != 4) {
            fprintf(stderr, "Hatali satir: %s\n", satir);
            // Bellek temizleme (gerekirse)
            if (sonraki_satir)
                satir = sonraki_satir + 1;
            else
                break;
            continue;
        }

        Kisi* kisi = KisiOlustur(ad, yas, omur, arac);
        if (!kisi) {
            fprintf(stderr, "Kisi olusturulamadi\n");
            // Bellek temizleme (gerekirse)
            if (sonraki_satir)
                satir = sonraki_satir + 1;
            else
                break;
            continue;
        }

        kisiler = realloc(kisiler, sizeof(Kisi*) * (*kisiSayisi + 1));
        if (!kisiler) {
            fprintf(stderr, "Bellek yeniden ayirma hatasi\n");
            KisiYokEt(kisi); // Kisi'yi yok et
            if (sonraki_satir)
                satir = sonraki_satir + 1;
            else
                break;
            break; // Döngüden çık
        }

        kisiler[*kisiSayisi] = kisi;
        (*kisiSayisi)++;

        if (sonraki_satir)
            satir = sonraki_satir + 1;
        else
            break;
    }

    free(icerik);
    return kisiler;
}

UzayAraci** AraclariYukle(const char* dosyaAdi, int* aracSayisi) {
    char* icerik = dosyaIcerik(dosyaAdi);
    if (!icerik) {
        fprintf(stderr, "Araclar.txt okuma hatasi\n");
        return NULL;
    }

    UzayAraci** araclar = NULL;
    *aracSayisi = 0;

    char* satir = icerik;
    char* sonraki_satir;

    while (satir) {
        char ad[50];
        char cikis[50];
        char varis[50];
        int mesafe;
        int gun, ay, yil;
        int okunan;

        sonraki_satir = strchr(satir, '\n');
        if (sonraki_satir) {
            *sonraki_satir = '\0';
        }

        okunan = sscanf(satir, "%49[^#]#%49[^#]#%49[^#]#%d.%d.%d#%d", ad, cikis, varis, &gun, &ay, &yil, &mesafe);
        if (okunan != 7) {
            fprintf(stderr, "Hatali arac satiri: %s\n", satir);
            if (sonraki_satir)
                satir = sonraki_satir + 1;
            else
                break;
            continue;
        }

        Zaman* cikisTarihi = ZamanOlustur(gun, ay, yil);
        if (!cikisTarihi) {
            fprintf(stderr, "Cikis tarihi olusturulamadi: %s\n", satir);
            if (sonraki_satir)
                satir = sonraki_satir + 1;
            else
                break;
            continue;
        }

        UzayAraci* arac = UzayAraciOlustur(ad, cikis, varis, cikisTarihi, mesafe);
        if (!arac) {
            fprintf(stderr, "Uzay araci olusturulamadi: %s\n", satir);
            ZamanYokEt(cikisTarihi);
            if (sonraki_satir)
                satir = sonraki_satir + 1;
            else
                break;
            continue;
        }

        araclar = realloc(araclar, sizeof(UzayAraci*) * (*aracSayisi + 1));
        if (!araclar) {
            fprintf(stderr, "Bellek yeniden ayirma hatasi\n");
            UzayAraciYokEt(arac);
            ZamanYokEt(cikisTarihi);
            if (sonraki_satir)
                satir = sonraki_satir + 1;
            else
                break;
            break;
        }

        araclar[*aracSayisi] = arac;
        (*aracSayisi)++;

        if (sonraki_satir)
            satir = sonraki_satir + 1;
        else
            break;
    }

    free(icerik);
    return araclar;
}

Gezegen** GezegenleriYukle(const char* dosyaAdi, int* gezegenSayisi) {
    Gezegen** gezegenler = NULL;
    *gezegenSayisi = 0;

    char* icerik = dosyaIcerik(dosyaAdi);
    if (!icerik) {
        fprintf(stderr, "Dosya okuma hatasi\n");
        return NULL;
    }

    char* satir = icerik;
    char* sonraki_satir;
    while (satir) {
        char ad[50];
        int tur, gunSaat, gun, ay, yil;
        int okunan;

        sonraki_satir = strchr(satir, '\n');
        if (sonraki_satir) {
            *sonraki_satir = '\0'; // Satırı sonlandır
        }

        okunan = sscanf(satir, "%49[^#]#%d#%d#%d.%d.%d", ad, &tur, &gunSaat, &gun, &ay, &yil);
        if (okunan != 6) {
            fprintf(stderr, "Gecersiz satir formati: %s\n", satir);
            if (sonraki_satir)
                satir = sonraki_satir + 1;
            else
                break;
            continue;
        }

        Zaman* z = ZamanOlustur(gun, ay, yil);
        if (!z) goto hata_satir;

        Gezegen* g = NULL;
        switch (tur) {
            case 0: g = (Gezegen*)KayacGezegenOlustur(ad, gunSaat, z); break;
            case 1: g = (Gezegen*)GazDeviGezegenOlustur(ad, gunSaat, z); break;
            case 2: g = (Gezegen*)BuzDeviGezegenOlustur(ad, gunSaat, z); break;
            case 3: g = (Gezegen*)CuceGezegenOlustur(ad, gunSaat, z); break;
            default: g = (Gezegen*)KayacGezegenOlustur(ad, gunSaat, z);
        }
        if (!g) {
            ZamanYokEt(z);
            goto hata_satir;
        }

        gezegenler = realloc(gezegenler, sizeof(Gezegen*) * (*gezegenSayisi + 1));
        if (!gezegenler) {
            ZamanYokEt(z);
            GezegenYokEt(g);
            goto hata_satir;
        }
        gezegenler[*gezegenSayisi] = g;
        (*gezegenSayisi)++;

    hata_satir:
        // Bellek temizleme işlemleri (gerekirse)
        if (sonraki_satir)
            satir = sonraki_satir + 1;
        else
            break;
    }

    free(icerik);
    return gezegenler;
}
