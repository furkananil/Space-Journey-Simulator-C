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

void UzayAraciSaatIlerle(UzayAraci* a) {
    if (a->kalkti && !a->vardi && !a->imha && a->kalanSaat > 0) {
        a->kalanSaat--;
    }

    // Yolcuları yaşlandır, ölenleri çıkar
    for (int i = 0; i < a->yolcuSayisi; ) {
        Kisi* yolcu = a->yolcular[i];
        if (!yolcu) {
            i++;
            continue;
        }

        KisiYaslandir(yolcu, 1.0);

        if (!KisiHayattaMi(yolcu)) {
            // Hafızayı temizleme (isteğe bağlı)
            // KisiYokEt(yolcu);  // Eğer yok edeceksen burada yap
            for (int j = i; j < a->yolcuSayisi - 1; j++) {
                a->yolcular[j] = a->yolcular[j + 1];
            }
            a->yolcuSayisi--;
            a->yolcular[a->yolcuSayisi] = NULL; // Sonu NULL yap
        } else {
            i++;
        }
    }

    // Sadece kalktıysa ve boşsa imha et
    if (a->kalkti && !a->imha && a->yolcuSayisi == 0) {
        a->imha = 1;
    }

    // Hedefe ulaştıysa
    if (a->kalanSaat <= 0 && !a->vardi) {
        a->kalanSaat = 0;
        a->vardi = 1;
    }
}

void UzayAraciDurumGuncelle(UzayAraci* a) {
    if (!a || a->vardi || a->imha) return;
    bool herkesOlmus = true;
    for (int i = 0; i < a->yolcuSayisi; i++) {
        if (a->yolcular[i] && a->yolcular[i]->hayatta) {
            herkesOlmus = false;
            break;
        }
    }
    if (herkesOlmus) {
        a->imha = true;
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

