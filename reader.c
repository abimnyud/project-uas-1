#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

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
int stasions_len = sizeof(stations) / sizeof(stations[0]);
char gate[][20] = {"Pintu Masuk", "Pintu Keluar"};

char last;
char *tptr;
char temp_data[MAXB] = "";
char ticket_data[MAXF] = "";
char ticket[MAXD] = "";
char error[MAXM] = "";
char success[MAXM] = "";

// void cekTicket(char *ticket_id);
void validateTicket(char *tic, int len, char *st);
void createCheckInData(int str, int des);
int validateSelection(int selection, char *position);
void selectStation(); void selectGate();

void successMessage(char *suc);
void errorMessage(char *err, char last);
void fileError(); 

int stasiun, pintu, i;
char tmp;

int main() {
    char ticket_code[40];
    int ticket_length;

    selectStation();
    selectGate();

    printf("+==============================================================+\n");
    printf("|                                                              |\n");
    printf("+--- Silakan masukan kode tiket Anda : ");
    fgets(ticket_code, sizeof ticket_code, stdin);
    ticket_code[strlen(ticket_code) - 1] = 0;    
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");

    system("clear || cls"); // Menghapus screen
    printf("+==( LOADING )=================================================+\n");
    printf("|                                                              |\n");
    printf("|               Sedang memvalidasi tiket Anda...               |\n");
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    sprintf(ticket, " '%s'", ticket_code);
    ticket_length = strlen(ticket);
    sleep(5); // ceritanya nunggu 5 detik sampe tiket berhasil dicek
    validateTicket(ticket, ticket_length, stations[stasiun]);
    // createCheckInData(pintu, stasiun);
    return 0;
}

int validateSelection(int selection, char *position) {
    if (strcmp(position, "Stasiun") == 0) {
        if (selection < 1 || selection > stasions_len) {
            return 0;
        }
    }
    
    if (strcmp(position, "Pintu") == 0) {
        if (selection < 1 || selection > 2) {
            return 0;
        }
    }

    return 1;
}

void selectStation() {
    printf("+======================[[ MESIN READER ]]======================+\n");
    printf("|                                                              |\n");
    printf("|                     Daftar Mesin Reader                      |\n");
    printf("|                                                              |\n");
    for (i = 0; i < stasions_len; i++)
        if(i < 9)
            printf("|    %d.  %-54s|\n", i + 1, stations[i]);
        else
            printf("|    %d. %-54s|\n", i + 1, stations[i]);
    printf("|                                                              |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("|                                                              |\n");
    printf("+--- Pilih Kode Mesin di Salah Satu Stasiun  : ");
    while(scanf("%d", &stasiun) != 1) {
        printf("\n+--- Pilih Kode Mesin di Salah Satu Stasiun  : ");
        while(getchar() != '\n');
    }
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");

    if(validateSelection(stasiun, "Stasiun") == 0) {
        system("clear || cls"); // Menghapus screen
        strcpy(error, "|             Input yang Anda masukkan tidak sesuai!           |\n|                     Silakan coba kembali.                    |\n");
        errorMessage(error, 's');
    }

    stasiun = stasiun - 1;
}

void selectGate() {
    printf("+==============================================================+\n");
    printf("|                                                              |\n");
    printf("+--- Daftar Pintu di Stasiun %-34s|\n", stations[stasiun]);
    for(i = 0; i < 2; i++) {
        printf("|    %d. %-55s|\n", i + 1, gate[i]);
    }
    printf("|                                                              |\n");
    printf("+--- Pilih Kode Pintu  : ");
    
    while(scanf("%d", &pintu) != 1) {
        printf("\n+--- Pilih Kode Pintu  : ");
        while(getchar() != '\n');
    };

    scanf("%c", &tmp); // skip enter
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    if(validateSelection(pintu, "Pintu") == 0) {
        system("clear || cls"); // Menghapus screen
        strcpy(error, "|             Input yang Anda masukan tidak sesuai!            |\n|                     Silakan coba kembali.                    |\n");
        errorMessage(error, 'g');
    }

    pintu = pintu - 1;
}

void validateTicket(char *tic, int len, char *st) {
    int x = 0; 
    i = 0;
    char st_temp[20];
    int true = 0;
    sprintf(st_temp, " '%s'", st);
    for (i = 2; i < len - 1; i++)
        if (tic[i] == ' ') {
            x = 1;
            break;
        }

    if (len != 23 || x) {
        strcpy(error, "|                   Kode tiket tidak sesuai!                   |\n|            Kode tiket TIDAK BOLEH mengandung SPASI           |\n|                              dan                             |\n|     memiliki panjang kurang atau lebih dari 20 karakter.     |\n");
        errorMessage(error, 'i');
        return;
    }

    FILE *rfptr;
    rfptr = fopen("./data/ticket_data.txt", "r");
    if (rfptr == NULL)
        fileError();

    while (fgets(temp_data, sizeof temp_data, rfptr) != NULL) { // cek file kosong atau tidak dan cek kode tiket
        strcat(ticket_data, temp_data); // simpan data terakhir yang ada di file
        tptr = strtok(temp_data, ",{}:\n\t");
        /* if (i % 4 == 0) {
            true = 0;
        } 
        
        if (strcmp(tptr, "'start'") == 0) {
            tptr = strtok(NULL, ",{}:\n\t");
            if (strcmp(tptr, st_temp) == 0) {
                true = 1;
            }
        }
        
        if (strcmp(tptr, "'ticket_code'") == 0) {
            tptr = strtok(NULL, ",{}:\n\t");
            if (strcmp(tic, tptr) == 0 && true) {
                strcpy(success, "|                   Validasi tiket berhasil!                   |\n|         Selamat menikmati perjalanan menggunakan MRT!        |\n");
                createCheckInData(pintu, stasiun);
                fclose(rfptr);  
                return;
            }
        }
        i++; */
        if (tptr != NULL) {
            tptr = strtok(NULL, ",{}:\n\t");
            if (strcmp(tic, tptr) == 0) {
                if (pintu == 1) {
                    strcpy(success, "|                   Checkout tiket berhasil!                   |\n");
                } else {
                    strcpy(success, "|                   Validasi tiket berhasil!                   |\n|         Selamat menikmati perjalanan menggunakan MRT!        |\n");
                }
                createCheckInData(pintu, stasiun);
                fclose(rfptr);  
                return;
            }
        }
    }
    fclose(rfptr); 

    strcpy(error, "|                    Tiket tidak ditemukan!                    |\n|               Silakan coba kembali lain waktu.               |\n");
    errorMessage(error, 'i');
}

void createCheckInData(int str, int des) {


    FILE *wfptr;
    wfptr = fopen("./data/checkin_data.txt", "w");
    if (wfptr == NULL)
        fileError();

    while (fgets(temp_data, sizeof temp_data, wfptr) != NULL)
        strcat(ticket_data, temp_data);
 
    if (strcmp(temp_data, "") == 0) {
        sprintf(ticket_data, "{\n\t{\n\t\t'start_code': '%d',\n\t\t'destination_code': '%d',\n\t\t'ticket_code':%s\n\t}\n}", pintu, stasiun, ticket);
        fprintf(wfptr, "%s", ticket_data);
    }
    else {
        ticket_data[strlen(ticket_data) - 1] = ticket_data[strlen(ticket_data) - 2] = 0;
        sprintf(temp_data, "%s},\n\t{\n\t\t'start_code': '%d',\n\t\t'destination_code': '%d',\n\t\t'ticket_code':%s\n\t}\n}", ticket_data, pintu, stasiun, ticket);
        fprintf(wfptr, "%s", temp_data);
    }
    fclose(wfptr);
    successMessage(success);
}

void successMessage(char *suc) {
    // system("clear || cls"); // Menghapus screen
    printf("+==( PESAN SUKSES )============================================+\n");
    printf("|                                                              |\n");
    printf("%s", suc);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    *suc = 0;
    *temp_data = 0;
}

void errorMessage(char *err, char last) {
    system("clear || cls"); // Menghapus screen
    printf("+==( PESAN ERROR )=============================================+\n");
    printf("|                                                              |\n");
    printf("%s", err);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    *err = 0;
    if (last == 'i') // error saat kode tiket tidak sesuai
        // main();
        exit(1);
    if (last == 's') // error saat pilihan stasiun tidak sesuai
        selectStation();
    if (last == 'g') // error saat pilihan gate tidak sesuai
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