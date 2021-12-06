#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    "Pintu Stasiun"
};

char last; char *tptr; char temp_data[MAXB] = ""; char ticket_data[MAXF] = "";
char ticket[MAXD] = ""; char error[MAXM] = ""; char success[MAXM] = ""; char selection[MAXB];

void inputTicket(); void validateCheckIn(char *tic, size_t len); void createCheckInData();
void validateCheckOut(char *tic, size_t len); void createCheckOutData(int st, int de);
void validateSelection(char *slc, char *page); void selectReader(); void selectGate();

void successMessage(char *suc); void errorMessage(char *err, char last); void fileError(); 

int reader, destination, gate, i, j;

int main() {
    system("clear || cls"); // Menghapus screen
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
    size_t ticket_len;
    printf("+=======================[[ INPUT TIKET ]]======================+\n");
    printf("|                                                              |\n");
    printf("+--- Silakan masukan kode tiket Anda : ");
    fgets(ticket_code, sizeof ticket_code, stdin);
    ticket_code[strlen(ticket_code) - 1] = 0;    
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    printf("+==( LOADING )=================================================+\n");
    printf("|                                                              |\n");
    printf("|               Sedang memvalidasi tiket Anda...               |\n");
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    sprintf(ticket, " '%s'", ticket_code);
    ticket_len = strlen(ticket);
    sleep(10); // ceritanya nunggu 10 detik sampe tiket berhasil dicek
    if (gate)
        validateCheckOut(ticket, ticket_len);
    else
        validateCheckIn(ticket, ticket_len);
}

void validateSelection(char *slc, char *page) {
    size_t slc_len = strlen(slc);
    if (strcmp(page, pages[0]) == 0) {
        last = 'r';
        if (slc_len > 3 || (*slc < '1' || *slc > '9') || *(slc + 1) > '3')
            strcpy(error, "|             Input yang Anda masukan tidak sesuai!            |\n|                     Silakan coba kembali.                    |\n");
    }
    if (strcmp(page, pages[1]) == 0) {
        last = 'g';
        if (slc_len > 2 || (*slc < '1' || *slc > '2'))
            strcpy(error, "|             Input yang Anda masukan tidak sesuai!            |\n|                     Silakan coba kembali.                    |\n");
    }
    if (*slc == '\n')
        strcpy(error, "|                   Input tidak boleh kosong!                  |\n|                     Silakan coba kembali.                    |\n");

    if (error[0])
        errorMessage(error, last);
}

void validateCheckIn(char *tic, size_t len) {
    char arr[4][MAXA];
    char st[MAXA] = "";
    char de[MAXA] = "";
    int x = 0;
    j = 0;
    for (i = 2; i < len - 1; i++)
        if (tic[i] == ' ') {
            x = 1;
            break;
        }

    if (len != 23 || x) {
        strcpy(error, "|                   Kode tiket tidak sesuai!                   |\n|            Kode tiket tidak boleh mengandung spasi           |\n|                              dan                             |\n|     memiliki panjang kurang atau lebih dari 20 karakter.     |\n");
        errorMessage(error, 't');
    }

    FILE *rfptr;
    rfptr = fopen("./data/ticket_data.txt", "r");
    if (rfptr == NULL)
        fileError();

    while (fgets(temp_data, sizeof temp_data, rfptr) != NULL) { // cek file kosong atau tidak dan cek kode tiket
        tptr = strtok(temp_data, ",{}:\n\t");
        if (tptr != NULL) {
            tptr = strtok(NULL, ",{}:\n\t");
            strcpy(arr[j], tptr);
            if (strcmp(tic, tptr) != 0)
                strcpy(error, "|                    Tiket tidak ditemukan!                    |\n|               Silakan coba kembali lain waktu.               |\n");
            else {
                error[0] = 0;
                break;
            }
            if (j == 3)
                j = 0;
            else
                j++;
            
        }
    }
    sprintf(st, " '%s'", stations[reader]);
    if (strcmp(st, arr[1]) != 0)
        strcpy(error, "|                  Stasiun awal tidak sesuai!                  |\n|          Silakan menuju stasiun awal yang Anda pilih         |\n|                     ketika membeli tiket.                    |\n");
    for (i = 0; i < stations_len; i++) {
        sprintf(de, " '%s'", stations[i]);
        if (strcmp(arr[2], de) == 0) {
            destination = i;
            break;
        }
        de[0] = 0;
    }
    fclose(rfptr);
    if (error[0])
        errorMessage(error, 't');
    temp_data[0] = 0;
    createCheckInData();
}

void createCheckInData() {
    FILE *rfptr;
    rfptr = fopen("./data/checkin_data.txt", "r");
    if (rfptr == NULL)
        fileError();

    while (fgets(temp_data, sizeof temp_data, rfptr) != NULL)
        strcat(ticket_data, temp_data);
    fclose(rfptr);

    FILE *wfptr;
    wfptr = fopen("./data/checkin_data.txt", "w");
    if (wfptr == NULL)
        fileError();

    if (strcmp(temp_data, "") == 0) {
        sprintf(ticket_data, "{\n\t{\n\t\t'start_code': '%d',\n\t\t'destination_code': '%d',\n\t\t'ticket_code':%s,\n\t\t'already_used': 'FALSE'\n\t}\n}", reader, destination, ticket);
        fprintf(wfptr, "%s", ticket_data);
    }
    else {
        ticket_data[strlen(ticket_data) - 1] = ticket_data[strlen(ticket_data) - 2] = 0;
        sprintf(temp_data, "%s},\n\t{\n\t\t'start_code': '%d',\n\t\t'destination_code': '%d',\n\t\t'ticket_code':%s,\n\t\t'already_used': 'FALSE'\n\t}\n}", ticket_data, reader, destination, ticket);
        fprintf(wfptr, "%s", temp_data);
    }
    fclose(wfptr);
    strcpy(success, "|                   Validasi tiket berhasil!                   |\n|         Selamat menikmati perjalanan menggunakan MRT!        |\n");
    successMessage(success);
}

void validateCheckOut(char *tic, size_t len) {
    char ar[4][MAXA];
    int s, d;
    int x = 0;
    j = 0;
    for (i = 2; i < len - 1; i++)
        if (tic[i] == ' ') {
            x = 1;
            break;
        }

    if (len != 23 || x) {
        strcpy(error, "|                   Kode tiket tidak sesuai!                   |\n|            Kode tiket tidak boleh mengandung spasi           |\n|                              dan                             |\n|     memiliki panjang kurang atau lebih dari 20 karakter.     |\n");
        errorMessage(error, 't');
    }

    FILE *rfptr;
    rfptr = fopen("./data/checkin_data.txt", "r");
    if (rfptr == NULL)
        fileError();

    if (fgets(temp_data, sizeof temp_data, rfptr) == NULL) {
        strcpy(error, "|                    Tiket tidak ditemukan!                    |\n|               Silakan coba kembali lain waktu.               |\n");
        fclose(rfptr);
        errorMessage(error, 't');
    }

    while (fgets(temp_data, sizeof temp_data, rfptr) != NULL) { // cek file kosong atau tidak dan cek kode tiket
        tptr = strtok(temp_data, ",{}:\n\t");
        if (tptr != NULL) {
            tptr = strtok(NULL, ",{}:\n\t");
            strcpy(ar[j], tptr);
            if (strcmp(tic, tptr) != 0)
                strcpy(error, "|                    Tiket tidak ditemukan!                    |\n|               Silakan coba kembali lain waktu.               |\n");
            else {
                error[0] = 0;
                break;
            }
            if (j == 3)
                j = 0;
            else
                j++;
            
        }
    }
    tptr = strtok(ar[0], " '");
    s = atoi(tptr);
    tptr = strtok(ar[1], " '");
    d = atoi(tptr);
    tptr = strtok(NULL, " '");
    if (d < reader || s > reader) {
        strcpy(error, "|                     Akses keluar ditolak!                    |\n|            Anda hanya diperbolehkan keluar melalui           |\n|               pintu stasiun awal hingga tujuan.              |\n|               Tidak boleh mundur atau terlewat.              |\n");
    }

    fclose(rfptr);
    if (error[0])
        errorMessage(error, 't');
    temp_data[0] = 0;
    createCheckOutData(s, d);
}

void createCheckOutData(int s, int d) {
    FILE *rfptr;
    rfptr = fopen("./data/checkout_data.txt", "r");
    if (rfptr == NULL)
        fileError();

    while (fgets(temp_data, sizeof temp_data, rfptr) != NULL)
        strcat(ticket_data, temp_data);
    fclose(rfptr);

    FILE *wfptr;
    wfptr = fopen("./data/checkout_data.txt", "w");
    if (wfptr == NULL)
        fileError();

    if (strcmp(temp_data, "") == 0) {
        sprintf(ticket_data, "{\n\t{\n\t\t'start_code': '%d',\n\t\t'destination_code': '%d',\n\t\t'ticket_code':%s,\n\t\t'already_used': 'TRUE'\n\t}\n}", s, d, ticket);
        fprintf(wfptr, "%s", ticket_data);
    }
    else {
        ticket_data[strlen(ticket_data) - 1] = ticket_data[strlen(ticket_data) - 2] = 0;
        sprintf(temp_data, "%s},\n\t{\n\t\t'start_code': '%d',\n\t\t'destination_code': '%d',\n\t\t'ticket_code':%s,\n\t\t'already_used': 'TRUE'\n\t}\n}", ticket_data, s, d, ticket);
        fprintf(wfptr, "%s", temp_data);
    }
    fclose(wfptr);
    strcpy(success, "|                   Validasi tiket berhasil!                   |\n|                     Selamat beraktivitas!                    |\n");
    successMessage(success);
}

void successMessage(char *suc) {
    system("clear || cls"); // Menghapus screen
    printf("+==( PESAN SUKSES )============================================+\n");
    printf("|                                                              |\n");
    printf("%s", suc);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    suc[0] = 0;
    temp_data[0] = 0;
}

void errorMessage(char *err, char last) {
    system("clear || cls"); // Menghapus screen
    printf("+==( PESAN ERROR )=============================================+\n");
    printf("|                                                              |\n");
    printf("%s", err);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    err[0] = 0;
    if (last == 't') // error saat kode tiket tidak sesuai
        exit(1);
    if (last == 'r') // error saat pilihan reader tidak sesuai
        selectReader();
    if (last == 'g') // error saat pilihan gates tidak sesuai
        selectGate();
}

void fileError() {
    system("clear || cls"); // Menghapus screen
    printf("+==( PESAN ERROR )=============================================+\n");
    printf("|                                                              |\n");
    printf("|                        404 Not Found!                        |\n");
    printf("|        Tidak ada berkas atau direktori yang dimaksud.        |\n");
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    exit(0);
}