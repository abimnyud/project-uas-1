#include <stdio.h>
#include <stdlib.h>
/* #d// eUNEMNfine5 MUE  */


// Pernyataan Kondisi (Wajib) **
// Pernyataan Looping (Wajib) **
// Fungsi (Wajib) **
// Array 1D (Optional) **
// Array 2D (Optional) *
// Pointer (Optional) **
// Karakter & String (Optional) **
// Struct (optional) **

char stasiun_mrt[][20] = {
    " ",
    "Lebak Bulus",
    "Fatmawati",
    "Cipete Raya",
    "Haji Nawi",
    "Blok A",
    "Blok M",
    "Sisingamangaraja",
    "Senayan",
    "Istora",
    "Benhil",
    "Setiabudi",
    "Dukuh Atas",
    "Bundaran HI" 
};

void menuUtama(int *pilihan);
void exit(int status);
char *generateTicket(char *kodeTiket);
void beliTiket();

int main() {

    int pilihan;
    menuUtama(&pilihan);

    switch(pilihan) {
        case 1:
            beliTiket();
            break;
        case 2:
            printf("Anda memilih menu Lihat Riwayat\n");
            break;
        case 3:
            printf("Anda memilih menu Jadwal\n");
            break;
        case 4:
            printf("Anda memilih menu Rute MRT\n");
            break;
        case 5:
            printf("Anda memilih menu Keluar\n");
            exit(0);
            break;
        default:
            printf("Anda memilih menu yang salah\n");
            break;
    }

    return 0;
}

void menuUtama(int *pilihan) {
    char menu_utama[5][20] = {
        "Beli Tiket",
        "Lihat Riwayat",
        "Jadwal",
        "Rute MRT",
        "Keluar"
    };

    for (int i = 0; i < 48; i++) {
        printf("=");
    }
    printf("\nSelamat Datang di MRT Ticketing System\n");    
    for (int i = 0; i < 48; i++) {
        printf("=");
    }
    printf("\nPilihan Menu:\n\n");    
    for(int i = 0; i < 5; i++) {
        printf("%d. %s\n", i+1, menu_utama[i]);
    }
    
    printf("\nSilahkan pilih menu: ");    
    scanf("%d", &(*pilihan));
}

char *generateTiket(char *kodeTiket) {
    char randomChar[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnoprstuvwxyz1234567890";

    for(int i = 0; i < 20; i++) {
        kodeTiket[i] = randomChar[rand() % (sizeof(randomChar) - 1)];
    }

    return kodeTiket;
}

void beliTiket() {
    
    struct tiket{
        int st_awal; 
        int st_akhir;
        char kode_tiket[20];
    } tiket;

    printf("\nAnda memilih menu Beli Tiket\n");
    printf("\nDaftar Stasiun Awal:\n");
    for(int i = 1; i <= 13; i++) {
        printf("%d. %s\n", i, stasiun_mrt[i]);
    }
    printf("\nSilahkan masukkan kode stasiun awal: ");
    scanf("%d", &tiket.st_awal);
    printf("Anda memilih stasiun awal : %s", stasiun_mrt[tiket.st_awal]);

    printf("\n\nDaftar Stasiun Tujuan:\n");
    for(int i = 1; i <= 13; i++) {
        if(stasiun_mrt[i] != stasiun_mrt[tiket.st_awal]) {
            printf("%d. %s\n", i, stasiun_mrt[i]);
        }
    }
    printf("\nSilahkan masukkan kode stasiun tujuan anda: ");
    do {
        scanf("%d", &tiket.st_akhir);
        if(tiket.st_akhir == tiket.st_awal) {
            printf("\nStasiun tujuan tidak boleh sama dengan stasiun awal\n");
            printf("Silahkan masukkan kode stasiun tujuan anda: ");
        }
    } while (tiket.st_awal == tiket.st_akhir);

    generateTiket(tiket.kode_tiket);
    printf("Anda memilih stasiun akhir : %s", stasiun_mrt[tiket.st_akhir]);

    printf("\n\nSedang membuat tiket anda.....\n\n");
    
    printf("Stasiun Awal: %s", stasiun_mrt[tiket.st_awal]);
    printf("\nStasiun Akhir: %s", stasiun_mrt[tiket.st_akhir]);
    printf("\nKode Tiket Anda: %s\n\n", tiket.kode_tiket);
    printf("Tiket anda telah dibuat\n\n");

    //printf("");
    

    
}