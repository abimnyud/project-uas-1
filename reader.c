#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <Windows.h>
#else   
#include <unistd.h>
#endif

#define MAXA 64
#define MAXB 1024
#define MAXD 40
#define MAXF 2048
#define MAXM 512

char stations[][20] = {
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
int stations_len = sizeof(stations) / sizeof(stations[0]);

char gates[][20] = {
    "Pintu Masuk",
    "Pintu Keluar"
};
int gates_len = sizeof(gates) / sizeof(gates[0]);

char pages[][20] = {
    "Mesin Reader",
    "Pintu Stasiun",
};

char last; char *tptr; char temp_data[MAXF]; char ticket_data[MAXF] = "";
char ticket[MAXA]; char error[MAXM]; char success[MAXM]; char selection[MAXB];
int reader, destination, gate, i, j;

void inputTicket(); void validateCheckIn(char *tic, int len); void createCheckInData(char *tic);
void validateCheckOut(char *tic, int len); void createCheckOutData(char *tic);
void updateTicketData(char *src, char *sub, char *str);
void validateSelection(char *slc, char *page); void selectReader(); void selectGate();
void successMessage(char *suc); void errorMessage(char *err, char *page); void fileError();

int main() {
    system("cls || clear"); // Menghapus screen
    selectReader();
    selectGate();
    inputTicket();
    return 0;
}

void selectReader() {
    printf("+======================[[ MESIN READER ]]======================+\n");
    printf("|                                                              |\n");
    printf("|                      Daftar Mesin Reader                     |\n");
    printf("|                                                              |\n");
    for (i = 0; i < stations_len; i++)
        if(i < 9)
            printf("|    %d.  %-54s|\n", i + 1, stations[i]);
        else
            printf("|    %d. %-54s|\n", i + 1, stations[i]);
    printf("|                                                              |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("|                                                              |\n");
    printf("+--- Pilih kode mesin di salah satu stasiun : ");
    fgets(selection, sizeof selection, stdin);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    validateSelection(selection, pages[0]);
    reader = atoi(selection) - 1;
}

void selectGate() { 
    printf("+======================[[ PINTU STASIUN ]]=====================+\n");
    printf("|                                                              |\n");
    printf("|                     Daftar Pintu Stasiun                     |\n");
    printf("|                                                              |\n");
    for(i = 0; i < gates_len; i++) {
        printf("|    %d. %-55s|\n", i + 1, gates[i]);
    }
    printf("|                                                              |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("|                                                              |\n");
    printf("+--- Pilih Kode Pintu : ");
    fgets(selection, sizeof selection, stdin);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    validateSelection(selection, pages[1]);
    gate = atoi(selection) - 1;
}

void inputTicket() {
    char ticket_code[MAXD];
    int ticket_len;
    printf("+=======================[[ INPUT TIKET ]]======================+\n");
    printf("|                                                              |\n");
    printf("+--- Silakan masukan kode tiket Anda : ");
    fgets(ticket_code, sizeof ticket_code, stdin);
    ticket_code[strlen(ticket_code) - 1] = 0;    
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    sprintf(ticket, " '%s'", ticket_code); // format ticket
    ticket_len = strlen(ticket);
    if (gate) {
        printf("+==( LOADING )=================================================+\n");
        printf("|                                                              |\n");
        printf("|              Sedang mengonfirmasi tiket Anda...              |\n");
        printf("|                                                              |\n");
        printf("+==============================================================+\n\n");
        sleep(3); // ceritanya nunggu 3 detik sampe tiket berhasil dicek
        validateCheckOut(ticket, ticket_len);
        createCheckOutData(ticket);
    }
    else {
        printf("+==( LOADING )=================================================+\n");
        printf("|                                                              |\n");
        printf("|               Sedang memvalidasi tiket Anda...               |\n");
        printf("|                                                              |\n");
        printf("+==============================================================+\n\n");
        sleep(3); // ceritanya nunggu 3 detik sampe tiket berhasil dicek
        validateCheckIn(ticket, ticket_len);
        createCheckInData(ticket);
    }
}

void validateSelection(char *slc, char *page) {
    int slc_len = strlen(slc);
    if (strcmp(page, pages[0]) == 0) {
        slc_len--;
        last = '9';
    }
    if (strcmp(page, pages[1]) == 0)
        last = '2';

    if ((slc_len > 2) || (*slc < '1' || *slc > last) || (*slc > '0' && *(slc + 1) > '3'))
            strcpy(error, "|             Input yang Anda masukan tidak sesuai!            |\n|                     Silakan coba kembali.                    |\n");
    if (*slc == '\n')
        strcpy(error, "|                   Input tidak boleh kosong!                  |\n|                     Silakan coba kembali.                    |\n");

    if (error[0])
        errorMessage(error, page);
}

void validateCheckIn(char *tic, int len) {
    char arr[5][MAXA];
    char st[MAXA];
    int x = 0;
    for (i = 2; i < len - 1; i++)
        if (tic[i] == ' ') {
            x = 1;
            break;
        }

    if (len != 23 || x) {
        strcpy(error, "|                   Kode tiket tidak sesuai!                   |\n|       Kode hanya boleh berupa karakter angka atau huruf      |\n|                              dan                             |\n|                 memiliki panjang 20 karakter.                |\n");
        errorMessage(error, "0");
    }

    FILE *rfptr;
    rfptr = fopen("./data/ticket_data.txt", "r");
    if (rfptr == NULL)
        fileError();

    j = x = 0;
    while (fgets(temp_data, sizeof temp_data, rfptr) != NULL) { // ambil semua data dari file
        tptr = strtok(temp_data, ",{}:\n\t");
        if (tptr != NULL) {
            tptr = strtok(NULL, ",{}:\n\t");
            strcpy(arr[j], tptr);
            if (x)
                break;
            if (strcmp(tic, tptr) != 0)
                strcpy(error, "|                    Tiket tidak ditemukan!                    |\n|               Silakan coba kembali lain waktu.               |\n");
            else {
                error[0] = 0;
                x++;
            }

            if (j == 4)
                j = 0;
            else
                j++;
        }
    }
    sprintf(st, " '%s'", stations[reader]);
    if (strcmp(arr[1], st) != 0 && x)
        strcpy(error, "|                  Stasiun awal tidak sesuai!                  |\n|          Silakan menuju stasiun awal yang Anda pilih         |\n|                     ketika membeli tiket.                    |\n");
    if (strcmp(arr[4], " 'pending'") == 0)
        strcpy(error, "|                   Tiket sudah tervalidasi!                   |\n|       Segera gunakan tiket Anda dan lakukan konfirmasi       |\n|       di pintu keluar ketika sampai di stasiun tujuan.       |\n");
    if (strcmp(arr[4], " 'true'") == 0)
        strcpy(error, "|                    Tiket sudah digunakan!                    |\n|               Silakan untuk membeli tiket baru.              |\n");

    fclose(rfptr);
    if (error[0])
        errorMessage(error, "0");
    temp_data[0] = 0;
}

void createCheckInData(char *tic) {
    FILE *rfptr, *wfptr; // rfptr untuk membaca file, wfptr untuk menulis file
    rfptr = fopen("./data/ticket_data.txt", "r"); // read data
    if (rfptr == NULL)
        fileError();

    int x = 0;
    while (fgets(temp_data, sizeof temp_data, rfptr) != NULL) {
        strcat(ticket_data, temp_data); // menggabungkan atau menyatukan data
        tptr = strtok(temp_data, ",{}:\n\t");
        if (tptr != NULL) {
            tptr = strtok(NULL, ",{}:\n\t");
            if (x) {
                updateTicketData(ticket_data, tptr, " 'pending'");
                x--;
            }
            if (strcmp(tic, tptr) == 0) // membandingkan kode tiket
                x++;
        }
    }

    wfptr = fopen("./data/ticket_data.txt", "w"); // write data ke file
    fprintf(wfptr, "%s", ticket_data);
    fclose(rfptr);
    fclose(wfptr);
    strcpy(success, "|                   Validasi tiket berhasil!                   |\n|         Selamat menikmati perjalanan menggunakan MRT!        |\n");
    successMessage(success);
}

void validateCheckOut(char *tic, int len) {
    char arr[5][MAXA];
    int st, de;
    int x = 0;
    for (i = 2; i < len - 1; i++)
        if (!isalnum(tic[i])) { // cek apakah kode tiket merupakan karakter angka atau huruf
            x = 1;
            break;
        }

    if (len != 23 || x) {
        strcpy(error, "|                   Kode tiket tidak sesuai!                   |\n|       Kode hanya boleh berupa karakter angka atau huruf      |\n|                              dan                             |\n|                 memiliki panjang 20 karakter.                |\n");
        errorMessage(error, "0");
    }

    FILE *rfptr;
    rfptr = fopen("./data/ticket_data.txt", "r");
    if (rfptr == NULL)
        fileError();

    j = x = 0;
    while (fgets(temp_data, sizeof temp_data, rfptr) != NULL) { // ambil semua data dari file
        tptr = strtok(temp_data, ",{}:\n\t");
        if (tptr != NULL) {
            tptr = strtok(NULL, ",{}:\n\t");
            strcpy(arr[j], tptr);
            if (x)
                break;
            if (strcmp(tic, tptr) != 0)
                strcpy(error, "|                    Tiket tidak ditemukan!                    |\n|               Silakan coba kembali lain waktu.               |\n");
            else {
                error[0] = 0;
                x++;
            }

            if (j == 4)
                j = 0;
            else
                j++;
        }
    }

    for (i = 0; i < stations_len; i++)
    {
        sprintf(temp_data, " '%s'", stations[i]);
        if (strcmp(temp_data, arr[1]) == 0)
            st = i;
        if (strcmp(temp_data, arr[2]) == 0)
            de = i;
    }

    if (((st > de && (st < reader || de > reader)) || (st < de && (st > reader || de < reader))) && x) // Cek apakah stasiun sesuai dengan stasiun yang ada di tiket
        strcpy(error, "|                     Akses keluar ditolak!                    |\n|            Anda hanya diperbolehkan keluar melalui           |\n|               pintu stasiun awal hingga tujuan,              |\n|               tidak boleh mundur atau terlewat.              |\n");
    if (strcmp(arr[4], " 'false'") == 0)
        strcpy(error, "|                   Tiket belum tervalidasi!                   |\n|        Segera gunakan tiket Anda dan lakukan validasi        |\n|                 di pintu masuk stasiun awal.                 |\n");
    if (strcmp(arr[4], " 'true'") == 0)
            strcpy(error, "|                  Tiket sudah terkonfirmasi!                  |\n");

    fclose(rfptr);
    if (error[0])
        errorMessage(error, "0");
    temp_data[0] = 0;
}

void createCheckOutData(char *tic) {
    FILE *rfptr;
    rfptr = fopen("./data/ticket_data.txt", "r"); // read data
    if (rfptr == NULL)
        fileError();

    int x = 0;
    while (fgets(temp_data, sizeof temp_data, rfptr) != NULL) {
        strcat(ticket_data, temp_data);
        tptr = strtok(temp_data, ",{}:\n\t");
        if (tptr != NULL) {
            tptr = strtok(NULL, ",{}:\n\t");
            if (x) {
                updateTicketData(ticket_data, tptr, " 'true'");
                x--;
            }
            if (strcmp(tic, tptr) == 0)
                x++;
        }
    }
    fclose(rfptr);

    FILE *wfptr;
    wfptr = fopen("./data/ticket_data.txt", "w"); // write data ke file
    fprintf(wfptr, "%s", ticket_data);
    fclose(wfptr);
    strcpy(success, "|                  Konfirmasi tiket berhasil!                  |\n|                     Selamat beraktivitas!                    |\n");
    successMessage(success);
}

void updateTicketData(char *src, char *sub, char *str) { // src = ticket_data
    size_t sub_len = strlen(sub);
    size_t str_len = strlen(str);

    char *last_sub = strrchr(src, ':'); // Cari tiket paling akhir
    char *sub_source = strstr(last_sub, sub); // Ambil data status tiket
    size_t sub_source_len = strlen(sub_source); // 
    if (sub_source == NULL)
        return;

    memmove(
        sub_source + str_len,
        sub_source + sub_len,
        sub_source_len - sub_len + 1
    ); // Memindahkan string ke string satunya

    memcpy(sub_source, str, str_len); // Update status ticket_data paling terakhir (memindahkan variabel str ke variabel status di ticket_data)
}

void successMessage(char *suc) {
    system("cls || clear"); // Menghapus screen
    printf("+==( PESAN SUKSES )============================================+\n");
    printf("|                                                              |\n");
    printf("%s", suc);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    suc[0] = 0;
}

void errorMessage(char *err, char *page) {
    system("cls || clear"); // Menghapus screen
    printf("+==( PESAN ERROR )=============================================+\n");
    printf("|                                                              |\n");
    printf("%s", err);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    err[0] = 0;
    if (strcmp(page, pages[0]) == 0) // error saat pilihan reader tidak sesuai
        selectReader();
    if (strcmp(page, pages[1]) == 0) // error saat pilihan gates tidak sesuai
        selectGate();
    if (page[0] == '0') { // error saat kode tiket tidak sesuai
        sleep(3); // nunggu 3 detik sebelum terminal tutup
        exit(0);
    }
}

void fileError() {
    system("cls || clear"); // Menghapus screen
    printf("+==( PESAN ERROR )=============================================+\n");
    printf("|                                                              |\n");
    printf("|                        404 Not Found!                        |\n");
    printf("|        Tidak ada berkas atau direktori yang dimaksud.        |\n");
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    sleep(3); // nunggu 3 detik sebelum terminal tutup
    exit(0);
}