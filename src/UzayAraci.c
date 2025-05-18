#include "UzayAraci.h"


#define ILK_KAPASITE 10

UzayAraci* UzayAraciOlustur(char* ad, char* cikis, char* varis, Zaman* cikisTarihi, int kalanSaat) {
    UzayAraci* a = (UzayAraci*)malloc(sizeof(UzayAraci));
    a->ad = strdup(ad);
    a->cikis = strdup(cikis);
    a->varis = strdup(varis);
    a->cikisTarihi = cikisTarihi;
    a->varisTarihi = NULL; // Başlangıçta NULL
    a->kalanSaat = kalanSaat;

    a->kalkti = false;
    a->vardi = false;
    a->imha = false;

    a->kapasite = ILK_KAPASITE;
    a->yolcuSayisi = 0;
    a->yolcular = (Kisi**)malloc(sizeof(Kisi*) * a->kapasite);


    a->YolcuEkle = &UzayAraciYolcuEkle;
    a->SaatIlerle = &UzayAraciSaatIlerle;
    a->DurumGuncelle = &UzayAraciDurumGuncelle;
    a->BosMu = &UzayAraciBosMu;
    a->YokEt = &UzayAraciYokEt;
    a->UzayAraciVarisKontrol = &UzayAraciVarisKontrol;

    return a;
}

void UzayAraciYolcuEkle(UzayAraci* a, Kisi* k) {
    if (!a || !k) return;

    if (a->yolcuSayisi >= a->kapasite) {
        a->kapasite *= 2;
        Kisi** yeniDizi = (Kisi**)realloc(a->yolcular, sizeof(Kisi*) * a->kapasite);
        if (!yeniDizi) return; // realloc başarısızsa ekleme yapma
        a->yolcular = yeniDizi;
    }

    a->yolcular[a->yolcuSayisi++] = k;
}

void UzayAraciSaatIlerle(UzayAraci* a, Gezegen** gezegenler, int gezegenSayisi) {
    if (a->kalkti && !a->vardi && !a->imha && a->kalanSaat > 0) {
        a->kalanSaat--;
    }

    for (int i = 0; i < a->yolcuSayisi; ) {
        Kisi* yolcu = a->yolcular[i];
        if (!yolcu) {
            i++;
            continue;
        }

        double katsayi = 1.0;
        if (!a->kalkti) {
            // Kalkmadıysa çıkış gezegeninin katsayısı
            Gezegen* cikisGezegeni = GezegenBul(gezegenler, gezegenSayisi, a->cikis);
            if (cikisGezegeni && cikisGezegeni->yaslanmaKatsayisi)
                katsayi = cikisGezegeni->yaslanmaKatsayisi(cikisGezegeni);
        } else if (a->vardi) {
            // Sadece varış yaptıysa varış gezegeninin katsayısı
            Gezegen* varisGezegeni = GezegenBul(gezegenler, gezegenSayisi, a->varis);
            if (varisGezegeni && varisGezegeni->yaslanmaKatsayisi)
                katsayi = varisGezegeni->yaslanmaKatsayisi(varisGezegeni);
        }
        // Yoldayken (kalktı ve henüz varmadıysa) katsayi = 1.0

        KisiYaslandir(yolcu, katsayi);

        if (!KisiHayattaMi(yolcu)) {
            for (int j = i; j < a->yolcuSayisi - 1; j++) {
                a->yolcular[j] = a->yolcular[j + 1];
            }
            a->yolcuSayisi--;
            a->yolcular[a->yolcuSayisi] = NULL;
        } else {
            i++;
        }
    }

    if (a->kalkti && !a->imha && a->yolcuSayisi == 0) {
        a->imha = 1;
    }

    if (a->kalanSaat <= 0 && !a->vardi) {
        a->kalanSaat = 0;
        a->vardi = 1;
    }
}

void UzayAraciDurumGuncelle(UzayAraci* a) {
    if (!a || a->imha) return;
    bool herkesOlmus = true;
    for (int i = 0; i < a->yolcuSayisi; i++) {
        if (a->yolcular[i] && a->yolcular[i]->hayatta) {
            herkesOlmus = false;
            break;
        }
    }
    // Yolda veya varış yaptıktan sonra herkes ölmüşse imha et
    if (herkesOlmus) {
        a->imha = true;
        //a->vardi = false; // Artık varmış sayılmasın
    }
}

void UzayAraciVarisKontrol(UzayAraci* a, Gezegen** gezegenler, int gezegenSayisi) {
    if (!a || a->vardi || a->imha || !a->varisTarihi) return;
    Gezegen* varisGezegeni = GezegenBul(gezegenler, gezegenSayisi, a->varis);
    if (!varisGezegeni || !varisGezegeni->tarih) return;
    if (ZamanKarsilastir(varisGezegeni->tarih, a->varisTarihi) >= 0) {
        a->vardi = 1;
        a->kalanSaat = 0;
    }
}

bool UzayAraciBosMu(UzayAraci* a) {
    for (int i = 0; i < a->yolcuSayisi; i++) {
        if (a->yolcular[i] && a->yolcular[i]->hayatta) return false;
    }
    return true;
}

void UzayAraciYokEt(UzayAraci* a) {
    if (!a) return;
    for (int i = 0; i < a->yolcuSayisi; i++) {
        KisiYokEt(a->yolcular[i]);
        a->yolcular[i] = NULL;
    }
    free(a->yolcular);
    free(a->ad);
    free(a->cikis);
    free(a->varis);
    free(a);
}

