#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

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

char user[30], user_id[20], pilihan[8], buffer[8];
int loggedIn = 0, id, buffLen, i, opt;

void mainGate(); void menuRegister(); void mainMenu(char *user); void optionLoginRegister(); void loginRegister(char *pil);
void login(int *loggedIn); void subMenu(char *pil);
void jadwal(); void kembaliKeMenuUtama(); void ruteMRT(); void beliTiket(); void lihatRiwayat();
void menuLogin(); void exit(int status);

void mainGate()
{
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("||                                                            ||\n");
    printf("||                                                            ||\n");
    printf("||                                                            ||\n");
    printf("||    S E L A M A T   D A T A N G   D I   A P L I K A S I     ||\n");
    printf("||          M R T   T I C K E T I N G   S Y S T E M           ||\n");
    printf("||                                                            ||\n");
    printf("||                                                            ||\n");
    printf("||                                                            ||\n");
    printf("||                   developed by Algojo(y)                   ||\n");
    printf("||                           v1.0.0                           ||\n");
    printf("||                                                            ||\n");
    printf("||                                                            ||\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
    printf("+==============================================================+\n");
    printf("|                                                              |\n");
    printf("|                        Sebelum lanjut,                       |\n");
    printf("|   Silakan memilih menu login atau register terlebih dahulu.  |\n");
    printf("|                                                              |\n");
    printf("+--------------------------------------------------------------+\n");
    optionLoginRegister();
}

void menuRegister() {
    // system("clear || cls"); // Menghapus Screen /* Menurut gue lebih keren gausah di-clear */
    FILE *rfptr;
    rfptr = fopen("./data/user_data.txt", "r");
    if (rfptr == NULL)
    {
        printf("+==( PESAN ERROR )=============================================+\n");
        printf("|                                                              |\n");
        printf("|                        404 Not Found!                        |\n");
        printf("|         Tidak ada berkas atau direktori yang dimaksud.       |\n");
        printf("|              Gagal membuka berkas data pengguna.             |\n");
        printf("|                                                              |\n");
        printf("+==============================================================+\n\n");
        exit(1);
    }

    char name[30], username[20], password[20], confirmPassword[20], u[20];
    char *ptr; // pointer untuk pengecekan username yang ada di dalam file
    char temp[64] = "";
    char userData[1024] = "";

    printf("+========================[[ REGISTER ]]========================+\n");
    printf("|                                                              |\n");
    printf("+--- Nama Lengkap\t: ");
    gets(name);
    printf("|                                                              |\n");
    printf("+--- Username\t\t: ");
    scanf("%s", username);
    printf("|                                                              |\n");
    printf("+--- Password\t\t: ");
    scanf("%s", password);
    printf("|                                                              |\n");
    printf("+--- Ulangi Password\t: ");
    scanf("%s", confirmPassword);
    fgetc(stdin);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");

    sprintf(u, " '%s'", username);
    while (fgets(temp, 64, rfptr) != NULL)
    {
        strcat(userData, temp);
        ptr = strtok(temp, ",{}:\n\t");
        if (ptr != NULL)
        {
            ptr = strtok(NULL, ",{}:\n\t");
            if (strcmp(u, ptr) == 0)
            {
                printf("+==( PESAN ERROR )=============================================+\n");
                printf("|                                                              |\n");
                printf("|                   Username sudah dipakai!                    |\n");
                printf("|    Silakan registrasi kembali menggunakan data yang baru     |\n");
                printf("|                             atau                             |\n");
                printf("|            login menggunakan akun yang sudah ada.            |\n");
                printf("|                                                              |\n");
                printf("+--------------------------------------------------------------+\n");
                fclose(rfptr);
                optionLoginRegister();
            }
        }
    }

    if (strcmp(password, confirmPassword))
    {
        printf("+==( PESAN ERROR )=============================================+\n");
        printf("|                                                              |\n");
        printf("|               Konfirmasi password tidak sesuai!              |\n");
        printf("|           Silakan registrasi kembali dengan teliti           |\n");
        printf("|                             atau                             |\n");
        printf("|            login menggunakan akun yang sudah ada.            |\n");
        printf("|                                                              |\n");
        printf("+--------------------------------------------------------------+\n");
        fclose(rfptr);
        optionLoginRegister();
    }

    FILE *wfptr;
    wfptr = fopen("./data/user_data.txt", "w");
    if (wfptr == NULL)
    {
        printf("+==( PESAN ERROR )=============================================+\n");
        printf("|                                                              |\n");
        printf("|                        404 Not Found!                        |\n");
        printf("|         Tidak ada berkas atau direktori yang dimaksud.       |\n");
        printf("|              Gagal membuka berkas data pengguna.             |\n");
        printf("|                                                              |\n");
        printf("+==============================================================+\n\n");
        exit(1);
    }

    char def[] = "U0000000";
    srand(time(NULL));                   // inisialisasi nomor acak
    id = rand() % 9999999 + 1;           // id acak
    buffLen = sprintf(buffer, "%d", id); // konversi int ke string

    int n = 8 - buffLen;
    for (int i = n, j = 0; i < 8; i++, j++)
        def[i] = buffer[j];

    if (strcmp(temp, "") == 0)
    {
        fprintf(wfptr, "{\n");
        fprintf(wfptr, "\t{\n");
        fprintf(wfptr, "\t\t'id': '%s',\n", def);
        fprintf(wfptr, "\t\t'name': '%s',\n", name);
        fprintf(wfptr, "\t\t'username': '%s',\n", username);
        fprintf(wfptr, "\t\t'password': '%s'\n", password);
        fprintf(wfptr, "\t}\n");
        fprintf(wfptr, "}");
    }
    else
    {
        userData[strlen(userData) - 1] = userData[strlen(userData) - 2] = 0;
        strcat(userData, "},\n");
        strcat(userData, "\t{\n");
        strcat(userData, "\t\t'id': '");
        strcat(userData, def);
        strcat(userData, "',\n");
        strcat(userData, "\t\t'name': '");
        strcat(userData, name);
        strcat(userData, "',\n");
        strcat(userData, "\t\t'username': '");
        strcat(userData, username);
        strcat(userData, "',\n");
        strcat(userData, "\t\t'password': '");
        strcat(userData, password);
        strcat(userData, "'\n");
        strcat(userData, "\t}\n");
        strcat(userData, "}");
        fprintf(wfptr, "%s", userData);
    }
    printf("+==( PESAN SUKSES )============================================+\n");
    printf("|                                                              |\n");
    printf("|                           Selamat!                           |\n");
    printf("|                  Akun Anda berhasil dibuat.                  |\n");
    printf("|               Silakan login untuk melanjutkan.               |\n");
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    fclose(rfptr);
    fclose(wfptr);
    menuLogin();
}

int main() {
    system("clear || cls"); // Menghapus Screen
    mainGate();
}

void menuLogin() {
    FILE *rfptr;
    rfptr = fopen("./data/user_data.txt", "r");
    if (!rfptr)
    {
        printf("+==( PESAN ERROR )=============================================+\n");
        printf("|                                                              |\n");
        printf("|                        404 Not Found!                        |\n");
        printf("|         Tidak ada berkas atau direktori yang dimaksud.       |\n");
        printf("|              Gagal membuka berkas data pengguna.             |\n");
        printf("|                                                              |\n");
        printf("+==============================================================+\n\n");
        exit(1);
    }
    int key = 0;
    char *ptr;
    char username[20], password[20], temp[64], u[20], p[20];

    printf("+==========================[[ LOGIN ]]=========================+\n");
    printf("|                                                              |\n");
    printf("+--- Username\t\t: ");
    scanf("%s", username);
    printf("|                                                              |\n");
    printf("+--- Password\t\t: ");
    scanf("%s", password);
    fgetc(stdin);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");

    sprintf(u, " '%s'", username);
    sprintf(p, " '%s'", password);

    i = 0;
    while (fgets(temp, 64, rfptr) != NULL)
    {
        ptr = strtok(temp, ",{}:\n\t");
        if (ptr != NULL)
        {
            ptr = strtok(NULL, ",{}:\n\t");
            if (i % 3 == 0)
                strcpy(user, ptr);
            if (strcmp(u, ptr) == 0 || strcmp(p, ptr) == 0)
                key++;
        }
        i++;
        if (key == 2)
            break;
    }

    // Menghapus kutip
    user[0] = ',';
    user[1] = ' ';
    user[strlen(user) - 1] = '\0';

    switch (key)
    {
    case 2:
        printf("+==( PESAN SUKSES )============================================+\n");
        printf("|                                                              |\n");
        printf("|                        Login berhasil!                       |\n");
        printf("|                                                              |\n");
        printf("+==============================================================+\n\n");
        mainMenu(user);
        exit(0);
    default:
        printf("+==( PESAN ERROR )=============================================+\n");
        printf("|                                                              |\n");
        printf("|            Kombinasi username dan password salah!            |\n");
        printf("|              Silakan periksa kembali akun Anda               |\n");
        printf("|                             atau                             |\n");
        printf("|             daftar akun baru pada menu register.             |\n");
        printf("|                                                              |\n");
        printf("+--------------------------------------------------------------+\n");
        optionLoginRegister();
    }
}

void optionLoginRegister()
{
    printf("|                                                              |\n");
    printf("|    1. Login                                                  |\n");
    printf("|    2. Register                                               |\n");
    printf("|    3. Keluar                                                 |\n");
    printf("|                                                              |\n");
    printf("+--- Pilih Menu : ");
    fgets(pilihan, sizeof(pilihan), stdin);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    pilihan[strlen(pilihan) - 1] = 0;
    loginRegister(pilihan);
}

void loginRegister(char *pil)
{
    i = 0;
    while (*(pil + i))
    {
        if (!isdigit(*(pil + i)))
        {
            printf("+==( PESAN ERROR )=============================================+\n");
            printf("|                                                              |\n");
            printf("|      Input hanya boleh berupa nomor! Silakan coba lagi.      |\n");
            printf("|                                                              |\n");
            printf("+--------------------------------------------------------------+\n");
            optionLoginRegister();
        }
        opt = atoi(pil);
        i++;
    }

    switch (opt)
    {
    case 1:
        menuLogin();
    case 2:
        menuRegister();
    case 3:
        printf("+==============================================================+\n");
        printf("|                                                              |\n");
        printf("|                Terima kasih dan sampai jumpa!                |\n");
        printf("|                                                              |\n");
        printf("+==============================================================+\n");
        exit(0);
    default:
        printf("+==( PESAN ERROR )=============================================+\n");
        printf("|                                                              |\n");
        printf("|        Nomor pilihan tidak sesuai! Silakan coba lagi.        |\n");
        printf("|                                                              |\n");
        printf("+--------------------------------------------------------------+\n");
        optionLoginRegister();
    }
}

void mainMenu(char *user)
{
    printf("+==============================================================+\n");
    printf("|                                                              |\n");
    printf("|                           MAIN MENU                          |\n");
    printf("|                                                              |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("|                                                              |\n");
    printf("|    Selamat datang%s!\n", user);
    printf("|                                                              |\n");
    printf("|    1. Beli Tiket                                             |\n");
    printf("|    2. Lihat Riwayat                                          |\n");
    printf("|    3. Jadwal                                                 |\n");
    printf("|    4. Rute MRT                                               |\n");
    printf("|    5. Keluar                                                 |\n");
    printf("|                                                              |\n");
    printf("+--- Pilih Menu : ");
    fgets(pilihan, sizeof(pilihan), stdin);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    pilihan[strlen(pilihan) - 1] = 0;
    subMenu(pilihan);
}

void subMenu(char *pil)
{
    i = 0;
    while (*(pil + i))
    {
        if (!isdigit(*(pil + i)))
        {
            printf("+==( PESAN ERROR )=============================================+\n");
            printf("|                                                              |\n");
            printf("|      Input hanya boleh berupa nomor! Silakan coba lagi.      |\n");
            printf("|                                                              |\n");
            printf("+--------------------------------------------------------------+\n");
            mainMenu(user);
        }
        opt = atoi(pil);
        i++;
    }

    switch (opt)
    {
    case 1:
        menuTicket();
        break;
    case 2:
        lihatRiwayat();
        break;
    case 3:
        jadwal();
        break;
    case 4:
        ruteMRT();
        break;
    case 5:
        printf("+==============================================================+\n");
        printf("|                                                              |\n");
        printf("|                Terima kasih dan sampai jumpa!                |\n");
        printf("|                                                              |\n");
        printf("+==============================================================+\n");
        exit(0);
    default:
        printf("+==( PESAN ERROR )=============================================+\n");
        printf("|                                                              |\n");
        printf("|        Nomor pilihan tidak sesuai! Silakan coba lagi.        |\n");
        printf("|                                                              |\n");
        printf("+--------------------------------------------------------------+\n");
        mainMenu(user);
    }
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
            mainMenu(user);
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