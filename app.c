#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


// Pernyataan Kondisi (Wajib) **
// Pernyataan Looping (Wajib) **
// Fungsi (Wajib) **
// Array 1D (Optional) **
// Array 2D (Optional) *
// Pointer (Optional) **
// Karakter & String (Optional) **
// Struct (optional) **
// I/O **

char stasiun_mrt[][20] = {
    " ",
    "Lebak Bulus",
    "Fatmawati",
    "Cipete Raya",
    "Haji Nawi",
    "Blok A",
    "Blok M",
    "ASEAN",
    "Senayan",
    "Istora",
    "Benhil",
    "Setiabudi",
    "Dukuh Atas",
    "Bundaran HI" 
};

char user_id[20];
int loggedIn = 0;
int pilihan;

void login(int *loggedIn);
void menuLogin(int *pilihan);
void menuUtama(int *pilihan);
void exit(int status);
void *generateTicket(int st_awal, int st_akhir, char *kodeTiket);
void beliTiket(); void lihatRiwayat(); void ruteMRT(); void kembaliKeMenuUtama(); void jadwal();

int main() {
    system("clear || cls"); // Menghapus Screen
    menuLogin(&pilihan);

    switch(pilihan) {
        case 1:
            login(&loggedIn);
            break;
        case 2:
            /* register(); */
            printf("Anda memilih menu register\n");
            break;
        case 3:
            printf("Anda memilih menu Keluar\n");
            exit(0);
            break;
        default:
            system("clear || cls");
            return 0;
    }

    if(!loggedIn) return main();

    menuUtama(&pilihan);
}

void menuLogin(int *pilihan) {
    char menu_login[3][20] = {
        "Login",
        "Register",
        "Keluar"
    };
    for (int i = 0; i < 48; i++) {
        printf("=");
    }
    printf("\nSelamat Datang di Aplikasi MRT\n");    
    for (int i = 0; i < 48; i++) {
        printf("=");
    }

    printf("\n");
    for(int i = 0; i < 3; i++) {
        printf("\n%d. %s", i+1, menu_login[i]);
    }

    printf("\n\nSilakan pilih menu: ");    
    scanf("%d", &(*pilihan));
    system("clear || cls"); // Menghapus Screen Untuk Ke Menu Berikutnya
}

void login(int *loggedIn) {
    char username[20], password[20], tmp_user[100];
    char *sp; // pointer untuk memisahkan username dan password

    printf("Masukkan username: ");
    scanf("%s", username);
    printf("Masukkan password: ");
    scanf("%s", password);

    FILE *userdata;
    userdata = fopen("./data/user_data.csv", "r");
    if(userdata == NULL) {
        printf("Error: Tidak dapat membuka file data user\n");
        exit(1);
    }

    while(fgets(tmp_user, 100, userdata) != NULL) {
        sp = strtok(tmp_user, ",");
        if(strcmp(username, sp) == 0) {
            sp = strtok(NULL, ",");
            if(strcmp(password, sp) == 0) {
                strcpy(user_id, username);
                system("clear || cls"); // Menghapus Screen Untuk Ke Menu Berikutnya
                printf("Login berhasil!\n\n");
                *loggedIn = 1;
                break;
            }
        }
    }
    fclose(userdata);
    userdata = 0;
}

void menuUtama(int *pilihan) {
    system("clear || cls"); // Menghapus Screen Untuk Ke Menu Berikutnya
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
    printf("\nSelamat Datang Kembali, %s!\n", user_id);    
    for (int i = 0; i < 48; i++) {
        printf("=");
    }
    printf("\nPilihan Menu:\n\n");    
    for(int i = 0; i < 5; i++) {
        printf("%d. %s\n", i+1, menu_utama[i]);
    }
    
    printf("\nSilakan pilih menu: ");    
    scanf("%d", &(*pilihan));

    switch(*pilihan) {
        case 1:
            beliTiket();
            break;
        case 2:
            printf("Anda memilih menu Lihat Riwayat\n\n");
            lihatRiwayat();
            break;
        case 3:
            jadwal();
            break;
        case 4:
            ruteMRT();
            break;
        case 5:
            printf("Anda memilih untuk keluar\n");
            exit(0);
            break;
        default:
            printf("Anda memilih menu yang salah\n");
            break;
    }

}

void *generateTiket(int st_awal, int st_akhir, char *kodeTiket) {
    char randomChar[63] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";

    srand(time(0));
    for(int i = 0; i < 20; i++) {
        kodeTiket[i] = randomChar[rand() % 63];
    }

    printf("\nSedang membuat tiket anda.....\n\n");
    
    // Simpan data tiket ke ticket_data.csv
    FILE *fp;
    fp = fopen("./data/ticket_data.csv", "a+");
    if(fp == NULL) {
        printf("Error: Tidak dapat membuka file data tiket\n");
        exit(1);
    }
    fprintf(fp, "%s,%s,%s,%s\n", user_id, stasiun_mrt[st_awal], stasiun_mrt[st_akhir], kodeTiket);
    fclose(fp);
    fp = 0;

    printf("Stasiun Awal: %s", stasiun_mrt[st_awal]);
    printf("\nStasiun Akhir: %s", stasiun_mrt[st_akhir]);
    printf("\nKode Tiket Anda: %s\n\n", kodeTiket);
    printf("Tiket anda telah dibuat\n");
}

void beliTiket() {
    system("clear || cls"); // Menghapus Screen Untuk Ke Menu Berikutnya
    struct tiket{
        int st_awal; 
        int st_akhir;
        char kode_tiket[20];
    } tiket;

    printf("Anda memilih menu Beli Tiket\n");
    printf("\nDaftar Stasiun Awal:\n");
    for(int i = 1; i <= 13; i++) {
        printf("%d. %s\n", i, stasiun_mrt[i]);
    }
    printf("\nSilakan masukkan kode stasiun awal: ");
    scanf("%d", &tiket.st_awal);
    system("clear || cls"); // Menghapus Screen Untuk Ke Menu Berikutnya


    printf("Daftar Stasiun Tujuan:\n");
    for(int i = 1; i <= 13; i++) {
        if(stasiun_mrt[i] != stasiun_mrt[tiket.st_awal]) {
            printf("%d. %s\n", i, stasiun_mrt[i]);
        }
    }
    printf("\nSilakan masukkan kode stasiun tujuan anda: ");
    do {
        scanf("%d", &tiket.st_akhir);
        if(tiket.st_akhir == tiket.st_awal) {
            printf("\nStasiun tujuan tidak boleh sama dengan stasiun awal\n");
            printf("Silakan masukkan kode stasiun tujuan anda: ");
        }
    } while (tiket.st_awal == tiket.st_akhir);

    system("clear || cls"); // Menghapus Screen Untuk Ke Menu Berikutnya
    printf("Anda memilih stasiun %s sebagai stasiun awal dan stasiun %s sebagai stasiun akhir\n", stasiun_mrt[tiket.st_awal], stasiun_mrt[tiket.st_akhir]);
    generateTiket(tiket.st_awal, tiket.st_akhir, tiket.kode_tiket);

    kembaliKeMenuUtama();
}

void lihatRiwayat() {
    system("clear || cls"); // Menghapus screen
    char tmp_user[100], *sp;

    FILE *userdata;
    userdata = fopen("./data/ticket_data.csv", "r");
    if(userdata == NULL) {
        printf("Error: Tidak dapat membuka file data user\n");
        exit(1);
    }

    int i = 1;
    printf("No. Stasiun Awal\tStasiun Tujuan\t    Kode_Tiket\n");
    while(fgets(tmp_user, 100, userdata) != NULL) {
        sp = strtok(tmp_user, ",");
        if(strcmp(user_id, sp) == 0) {
            printf("%-4d", i);
            sp = strtok(NULL, ",");
            printf("%-20s", sp);
            sp = strtok(NULL, ",");
            printf("%-20s", sp);
            sp = strtok(NULL, ",");
            printf("%s\n", sp);
        i++;
        }
    }
    fclose(userdata);
    userdata = 0;
    kembaliKeMenuUtama();
}

void ruteMRT () {
    system("clear || cls"); // Menghapus screen
    printf("Rute MRT:\n\n");
    for(int i = 1; i <= 13; i++) {
        printf("%s\n", stasiun_mrt[i]);
        if (i!=13) 
        printf("   | \n");
    }

    kembaliKeMenuUtama();
}

void kembaliKeMenuUtama() {
    char yesNo[1];
    do {
        printf("\nKetik Y jika ingin kembali ke menu utama (Y) ");
        scanf("%s", &yesNo[0]);
        if(yesNo[0] == 'Y' || yesNo[0] == 'y') {
            system("clear || cls"); // Menghapus Screen Untuk Ke Menu Berikutnya
            menuUtama(&pilihan);
        } else {
            printf("Error!\n");
        }
    } while (yesNo[0] != 'Y' && yesNo[0] != 'y');
}

void jadwal() {
    system("clear || cls"); // Menghapus screen
    printf("Anda memilih menu Jadwal MRT\n\n");
    int a, id_jadwal[14] = {0, 20, 21, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
    for (int i = 1; i <= 13; i++) {
        printf("%d. %s\n", i, stasiun_mrt[i]);
    }

    do {
        printf("\nMasukkan nomor stasiun keberangkatan: ");
        scanf("%d", &a);
        if (a < 1 || a > 13) printf("\nNomor stasiun tidak valid\n");
    } while (a < 1 || a > 13);

    printf("\nAnda memilih stasiun %s sebagai stasiun keberangkatan\n", stasiun_mrt[a]);
    printf("Jadwal lengkap kedatangan kereta dapat dilihat di: https://jakartamrt.co.id/id/jadwal-keberangkatan-mrt?dari=%d\n\n", id_jadwal[a]);

    kembaliKeMenuUtama();
}