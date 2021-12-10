#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define MAXB 1024
#define MAXD 40
#define MAXF 2048
#define MAXI 12
#define MAXM 512
#define MAXT 21

// Pernyataan Kondisi (Wajib) **
// Pernyataan Looping (Wajib) **
// Fungsi (Wajib) **
// Array 1D (Optional) **
// Array 2D (Optional) *
// Pointer (Optional) **
// Karakter & String (Optional) **
// Struct (optional) **
// I/O **

char pages[][20] = {
    "Main Gate",
    "Main Menu",
    "Ticket Menu",
    "Jadwal",
};
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

int i, j;
char user_id[MAXI];
char buff_id[MAXI];
char name[MAXD], username[MAXD], password[MAXD], confirm_password[MAXD], u[MAXM], p[MAXM], user[MAXD];
char temp_data[MAXF];
char user_data[MAXF] = "";
char ticket_data[MAXF] = "";
char *tptr;
char last;
char selection[MAXB];
char success[MAXM];
char error[MAXM];

void splashScreen();
void mainGate();
void validateSelection(char *slc, char *cur);
void exitMainGate(char *slc);
void registerMenu();
void registerAttempt(char *name, char *u, char *pass, char *conf);
void createUserData(char *name, char *u, char *pass);
void loginMenu();
void loginAttempt(FILE **rfptr, char *u, char *p);
void mainMenu(char *user);
void subMenu(char *slc);
void ticketMenu();
void generateTicket(char *code);
void createTicketData(char *str, char *des, char *code);
void history();
void schedule();
void routes();
void backToMainMenu();
void logout();
void successMessage(char *suc);
void errorMessage(char *err, char *cur);
void fileError();
void exitMessage();

int main(void) {
    system("cls || clear"); // Menghapus Screen
    splashScreen();
    mainGate();
    return 0;
}

void splashScreen() {
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
    printf("+==============================================================+\n\n");
}

void mainGate() {
    printf("+========================[[ MAIN GATE ]]=======================+\n");
    printf("|                                                              |\n");
    printf("|    1. Login                                                  |\n");
    printf("|    2. Register                                               |\n");
    printf("|    0. Keluar                                                 |\n");
    printf("|                                                              |\n");
    printf("+--- Pilih Menu : ");
    fgets(selection, sizeof selection, stdin);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    validateSelection(selection, pages[0]);
    exitMainGate(selection);
}

void validateSelection(char *slc, char *cur) {
    i = 1;
    size_t len = strlen(slc);
    if (strcmp(cur, pages[0]) == 0)
        last = '2';
    if (strcmp(cur, pages[1]) == 0)
        last = '4';
    if (strcmp(cur, pages[2]) == 0 || strcmp(cur, pages[3]) == 0) {
        len--;
        last = '9';
    }
    if (*cur == 'y')
        last = 'y';
    if (*cur == 'Y' || *cur == '0')
        last = 'Y';

    if (last == 'y' || last == 'Y')
        if (*slc != 'y' && *slc != 'Y')
            strcpy(error, "|             Input yang Anda masukan tidak sesuai!            |\n|                     Silakan coba kembali.                    |\n");

    if (strcmp(cur, pages[2]) == 0 || strcmp(cur, pages[3]) == 0) {
        if (*slc == '\n' || *slc == '0') {
            printf("|                                                              |\n");
            printf("+==============================================================+\n\n");
        }
        while (slc[i - 1] != '\n') {
            if(!isdigit(slc[i - 1]) || slc[i] > '3') {
                printf("|                                                              |\n");
                printf("+==============================================================+\n\n");
                break;
            }
            i++;
        }
        i = atoi(slc);
    }

    if (len > 2 || (*slc < '0' || *slc > last) || (i < 1 || i > 13) || (*slc == '0' && *(slc + 1) >= '0'))
        strcpy(error, "|             Input yang Anda masukan tidak sesuai!            |\n|                     Silakan coba kembali.                    |\n");
    if (*slc == '\n')
        strcpy(error, "|                   Input tidak boleh kosong!                  |\n|                     Silakan coba kembali.                    |\n");

    if (error[0])
        errorMessage(error, cur);
}

void exitMainGate(char *slc) {
    system("cls || clear"); // Menghapus Screen
    switch (*slc)
    {
    case '1':
        loginMenu();
        break;
    case '2':
        registerMenu();
        break;
    default:
        exitMessage();
        break;
    }
}

void registerMenu() {
    printf("+========================[[ REGISTER ]]========================+\n");
    printf("|                                                              |\n");
    printf("+--- Nama Lengkap        : ");
    fgets(name, sizeof name, stdin);
    printf("|                                                              |\n");
    printf("+--- Username            : ");
    fgets(username, sizeof username, stdin);
    printf("|                                                              |\n");
    printf("+--- Password            : ");
    fgets(password, sizeof password, stdin);
    printf("|                                                              |\n");
    printf("+--- Konfirmasi Password : ");
    fgets(confirm_password, sizeof confirm_password, stdin);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    name[strlen(name) - 1] = username[strlen(username) - 1] = password[strlen(password) - 1] = confirm_password[strlen(confirm_password) - 1] = 0;
    sprintf(u, " '%s'", username);
    registerAttempt(name, u, password, confirm_password);
    createUserData(name, username, password);
    loginMenu();
}

void registerAttempt(char *name, char *u, char *pass, char *conf) {
    FILE *rfptr;
    rfptr = fopen("./data/user_data.txt", "r");
    if (rfptr == NULL)
        fileError();

    if (strcmp(pass, conf)) // validasi password dengan konfirmasi password
        strcpy(error, "|               Konfirmasi password tidak sesuai!              |\n|           Silakan registrasi kembali dengan teliti           |\n|                             atau                             |\n|            login menggunakan akun yang sudah ada.            |\n");

    while (fgets(temp_data, sizeof temp_data, rfptr) != NULL) { // ambil data dari file
        tptr = strtok(temp_data, ",{}:\n\t");
        if (tptr != NULL) {
            tptr = strtok(NULL, ",{}:\n\t");
            if (strcmp(u, tptr) == 0) { // unique username
                strcpy(error, "|                   Username sudah dipakai!                    |\n|    Silakan registrasi kembali menggunakan data yang baru     |\n|                             atau                             |\n|            login menggunakan akun yang sudah ada.            |\n");
            }
        }
    }

    i = 0;
    while (username[i] != '\0') {
        if ((username[i] >= '0' && username[i] <= '9') || (username[i] == '.' || username[i] == '_')) {
            i++;
            continue;
        }
        if (!isalpha(name[i]))
            strcpy(error, "|                      Username dilarang!                      |\n|      Dilarang menggunakan karakter selain huruf, angka,      |\n|                    underscore, dan titik!                    |\n");

        i++;
    }

    i = 0;
    while (name[i] != '\0') {
        if (name[i] == ' ') {
            i++;
            continue;
        }
        if (!isalpha(name[i]))
            strcpy(error, "|                        Nama dilarang!                        |\n|     Dilarang menggunakan karakter selain huruf dan spasi!    |\n");

        i++;
    }

    if (*name == '\n' || *u == '\n' || *pass == '\n' || *conf == '\n')
        strcpy(error, "|                   Input tidak boleh kosong!                  |\n|            Mohon untuk mengisi input dengan benar!           |\n");

    fclose(rfptr);
    if (error[0])
        errorMessage(error, pages[0]);
}

void createUserData(char *name, char *u, char *pass) {
    FILE *rfptr, *wfptr;
    rfptr = fopen("./data/user_data.txt", "r");
    if (rfptr == NULL)
        fileError();

    int token, n;
    strcpy(user_id, "U0000000");
    srand(time(NULL));                   // inisialisasi nomor acak
    token = rand() % 9999999 + 1;       // id acak
    n = sprintf(buff_id, "%d", token); // konversi int ke string

    for (i = 8 - n, j = 0; i < 8; i++, j++)
        user_id[i] = buff_id[j];

    while (fgets(temp_data, sizeof temp_data, rfptr) != NULL)
        strcat(user_data, temp_data);

    wfptr = fopen("./data/user_data.txt", "w");
    if (user_data[0] == 0) {
        sprintf(user_data, "{\n\t{\n\t\t'id': '%s',\n\t\t'name': '%s',\n\t\t'username': '%s',\n\t\t'password': '%s'\n\t}\n}", user_id, name, u, pass);
        fprintf(wfptr, "%s", user_data);
    } else {
        user_data[strlen(user_data) - 1] = user_data[strlen(user_data) - 2] = 0;
        sprintf(temp_data, "%s},\n\t{\n\t\t'id': '%s',\n\t\t'name': '%s',\n\t\t'username': '%s',\n\t\t'password': '%s'\n\t}\n}", user_data, user_id, name, u, pass);
        fprintf(wfptr, "%s", temp_data);
    }
    fclose(rfptr);
    fclose(wfptr);
    strcpy(success, "|                           Selamat!                           |\n|                  Akun Anda berhasil dibuat.                  |\n|               Silakan login untuk melanjutkan.               |\n");
    successMessage(success);
    user_data[0] = 0;
}

void loginMenu() {
    FILE *rfptr;
    rfptr = fopen("./data/user_data.txt", "r");
    if (rfptr == NULL)
        fileError();

    printf("+==========================[[ LOGIN ]]=========================+\n");
    printf("|                                                              |\n");
    printf("+--- Username : ");
    fgets(username, sizeof username, stdin);
    printf("|                                                              |\n");
    printf("+--- Password : ");
    fgets(password, sizeof password, stdin);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    username[strlen(username) - 1] = password[strlen(password) - 1] = 0;
    sprintf(u, " '%s'", username);
    sprintf(p, " '%s'", password);
    loginAttempt(&rfptr, u, p);
}

void loginAttempt(FILE **rfptr, char *u, char *p) {
    int key = 0;
    i = j = 0;
    while (fgets(temp_data, sizeof temp_data, *rfptr) != NULL) {
        tptr = strtok(temp_data, ",{}:\n\t");
        if (tptr != NULL) {
            tptr = strtok(NULL, ",{}:\n\t");
            if (i % 2 == 0 && (i - 2) % 6 == 0)
                strcpy(user_id, tptr);
            if (i % 3 == 0)
                strcpy(user, tptr);
            if (strcmp(u, tptr) == 0) {
                j = i + 1;
                *u = 0;
            }
            if (i == j && strcmp(p, tptr) == 0)
                key = 1;
        }
        i++;
        if (key)
            break;
    }
    // Menghapus kutip pada nama pengguna
    user[0] = ',';
    user[1] = ' ';
    user[strlen(user) - 1] = '!';
    fclose(*rfptr);

    if (key) {
        strcpy(success, "|                        Login berhasil!                       |\n");
        successMessage(success);
        mainMenu(user);
    } else {
        if (*u == '\n' || *p == '\n')
            strcpy(error, "|                   Input tidak boleh kosong!                  |\n|            Mohon untuk mengisi input dengan benar!           |\n");
        else
            strcpy(error, "|            Kombinasi username dan password salah!            |\n|              Silakan periksa kembali akun Anda               |\n|                             atau                             |\n|             daftar akun baru pada menu register.             |\n");

        errorMessage(error, pages[0]);
    }
}

void mainMenu(char *user) {
    printf("+==============================================================+\n");
    printf("|                                                              |\n");
    printf("|                           MAIN MENU                          |\n");
    printf("|                                                              |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("|                                                              |\n");
    printf("|    Selamat datang%-44s|\n", user);
    printf("|                                                              |\n");
    printf("|    1. Beli Tiket                                             |\n");
    printf("|    2. Lihat Riwayat                                          |\n");
    printf("|    3. Jadwal                                                 |\n");
    printf("|    4. Rute MRT                                               |\n");
    printf("|    0. Logout                                                 |\n");
    printf("|                                                              |\n");
    printf("+--- Pilih Menu : ");
    fgets(selection, sizeof selection, stdin);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    validateSelection(selection, pages[1]);
    subMenu(selection);
}

void subMenu(char *slc) {
    switch (*slc)
    {
    case '1':
        system("cls || clear"); // Menghapus Screen
        ticketMenu();
        break;
    case '2':
        system("cls || clear"); // Menghapus Screen
        history();
        break;
    case '3':
        system("cls || clear"); // Menghapus Screen
        schedule();
        break;
    case '4':
        system("cls || clear"); // Menghapus Screen
        routes();
        break;
    default:
        logout();
    }
}

void ticketMenu() {
    struct TICKET {
        char start[MAXD]; 
        char destination[MAXD];
        char ticket_code[MAXT];
    } ticket;
    int s, d, price;

    printf("+=======================[[ BELI TIKET ]]=======================+\n");
    printf("|                                                              |\n");
    printf("|                      Daftar Stasiun MRT                      |\n");
    printf("|                                                              |\n");
    for (i = 0; i < stations_len; i++)
        if(i < 9)
            printf("|    %d.  %-54s|\n", i + 1, stations[i]);
        else
            printf("|    %d. %-54s|\n", i + 1, stations[i]);
    printf("|                                                              |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("|                                                              |\n");
    printf("+--- Pilih Stasiun Awal   : ");
    fgets(ticket.start, sizeof ticket.start, stdin);
    // validateSelection(&(ticket.start), pages[2]);
    validateSelection(ticket.start, pages[2]);
    printf("|                                                              |\n");
    printf("+--- Pilih Stasiun Tujuan : ");
    fgets(ticket.destination, sizeof ticket.destination, stdin);
    // validateSelection(&(ticket.destination), pages[2]);
    validateSelection(ticket.destination, pages[2]);
    printf("|                                                              |\n");
    ticket.start[strlen(ticket.start) - 1] = ticket.destination[strlen(ticket.destination) - 1] = 0;

    if (strcmp(ticket.start, ticket.destination) == 0) {
        printf("+==============================================================+\n\n");
        strcpy(error, "|     Stasiun tujuan tidak boleh sama dengan stasiun awal!     |\n|                     Silakan coba kembali.                    |\n");
        errorMessage(error, pages[2]);
    }
    s = atoi(ticket.start) - 1;
    d = atoi(ticket.destination) - 1;
    if ( s > d) {
        price = ((s - d) * 1000) + 3000;
    } else {
        price = ((d - s) * 1000) + 3000;
    }
    printf("+--------------------------------------------------------------+\n");
    printf("|                                                              |\n");
    printf("|    Stasiun yang dipilih, yaitu :                             |\n");
    printf("|                                                              |\n");
    printf("|    1. Stasiun %-16s (awal) -----------------------+\n", stations[s]);
    printf("|    2. Stasiun %-16s (tujuan) ---------------------+\n", stations[d]);
    printf("|    3. Total Pembayaran : Rp%-5d ----------------------------+\n", price );
    printf("|                                                              |\n");
    printf("|        Silakan untuk melakukan pembayaran menggunakan        |\n");
    printf("|               metode pembayaran kesukaan Anda.               |\n");
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");

    j = 0;
    do {
        printf("+==( LOADING )=================================================+\n");
        printf("|                                                              |\n");
        printf("|                  Menunggu pembayaran Anda...                 |\n");
        printf("|                                                              |\n");
        printf("+==============================================================+\n\n");
        sleep(3); // nunggu 3 detik ceritanya
        printf("+==( CONFIRM PAYMENT )=========================================+\n");
        printf("|                                                              |\n");
        printf("|                  Apakah Anda sudah membayar?                 |\n");
        printf("|                                                              |\n");
        printf("+--- (Y/N) : ");
        fgets(selection, sizeof selection, stdin);
        printf("|                                                              |\n");
        printf("+==============================================================+\n\n");
        validateSelection(selection, "0");
        if (strlen(selection) < 3) {
            if (*selection == 'N') {
                j++;
                if (j == 3) {
                    strcpy(error, "|       Anda gagal melakukan pembayaran sebanyak 3 kali!       |\n|              Silakan coba kembali di lain waktu.             |\n");
                    errorMessage(error, pages[1]);
                }
                system("cls || clear"); // Menghapus Screen
                printf("+==( WARNING )=================================================+\n");
                printf("|                                                              |\n");
                printf("|          Silakan lakukan pembayaran terlebih dahulu!         |\n");
                printf("|                                                              |\n");
                printf("+==============================================================+\n\n");
            }
            if (*selection == 'Y') {
                // generateTicket(&(ticket.ticket_code));
                generateTicket(ticket.ticket_code);
                // createTicketData(stations[s], stations[d], &(ticket.ticket_code));
                createTicketData(stations[s], stations[d], ticket.ticket_code);
                backToMainMenu();
            }
        }
    } while (1);
}

void generateTicket(char *code) {
    char word_char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    size_t word_char_len = strlen(word_char);

    srand(time(NULL));
    for(i = 0; i < MAXT - 1; i++)
        code[i] = word_char[rand() % (word_char_len - 1)];

    printf("+==( LOADING )=================================================+\n");
    printf("|                                                              |\n");
    printf("|                 Sedang membuat tiket Anda...                 |\n");
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    sleep(10); // ceritanya nunggu 10 detik sampe tiket berhasil dibuat
}

void createTicketData(char *str, char *des, char *code) {
    FILE *rfptr, *wfptr;
    rfptr = fopen("./data/ticket_data.txt", "r");
    if(rfptr == NULL)
        fileError();

    while (fgets(temp_data, sizeof temp_data, rfptr) != NULL) // ambil data dari file
        strcat(ticket_data, temp_data); // simpan data terakhir yang ada di file

    wfptr = fopen("./data/ticket_data.txt", "w");
    if (ticket_data[0] == 0) { // file kosong
        sprintf(ticket_data, "{\n\t{\n\t\t'user_id':%s,\n\t\t'start': '%s',\n\t\t'destination': '%s',\n\t\t'ticket_code': '%s',\n\t\t'status': 'false'\n\t}\n}", user_id, str, des, code);
        fprintf(wfptr, "%s", ticket_data);
    } else {
        ticket_data[strlen(ticket_data) - 1] = ticket_data[strlen(ticket_data) - 2] = 0;
        sprintf(temp_data, "%s},\n\t{\n\t\t'user_id':%s,\n\t\t'start': '%s',\n\t\t'destination': '%s',\n\t\t'ticket_code': '%s',\n\t\t'status': 'false'\n\t}\n}",ticket_data, user_id, str, des, code);
        fprintf(wfptr, "%s", temp_data);
    }
    fclose(rfptr);
    fclose(wfptr);
    strcpy(success, "|                           Selamat!                           |\n|                  Tiket Anda berhasil dibuat.                 |\n");
    successMessage(success);
    ticket_data[0] = 0;
}

void history() {
    FILE *rfptr;
    rfptr = fopen("./data/ticket_data.txt", "r");
    if(rfptr == NULL)
        fileError();

    int n = 0;
    i = j = 0;
    printf("+=========================[[ RIWAYAT ]]========================+\n");
    printf("|                                                              |\n");
    while(fgets(temp_data, sizeof temp_data, rfptr) != NULL) {
        tptr = strtok(temp_data, ",{}:\n\t");
        if (tptr != NULL) {
            tptr = strtok(NULL, ",{}:\n\t");
            if (strcmp(user_id, tptr) == 0) {
                n++;
                j = i;
                printf("|    Nomor          : %-41d|\n", n);
            }
            if (j > 0) {
                if (i == j + 1)
                    printf("|    Stasiun Awal   :%-42s|\n", tptr);
                if (i == j + 2)
                    printf("|    Stasiun Tujuan :%-42s|\n", tptr);
                if (i == j + 3)
                    printf("|    Kode Tiket     :%-42s|\n", tptr);
                if (i == j + 4) {
                    printf("|    Status         :%-42s|\n", tptr);
                    printf("|                                                              |\n");
                    printf("+--------------------------------------------------------------+\n");
                    printf("|                                                              |\n");
                }
            } 
        }        
        i++;
    }
    if (n) {
        printf("|    Total Tiket : %-44d|\n", n);
        printf("|                                                              |\n");
        printf("+==============================================================+\n\n");
    } else {
        printf("|            Riwayat pembelian tiket muncul di sini.           |\n");
        printf("|                                                              |\n");
        printf("+==============================================================+\n\n");
    }
    fclose(rfptr);
    backToMainMenu();
}

void schedule() {
    int schedule_id[] = {20, 21, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
    int s;
    printf("+=========================[[ JADWAL ]]=========================+\n");
    printf("|                                                              |\n");
    printf("|                      Daftar Stasiun MRT                      |\n");
    printf("|                                                              |\n");
    for (i = 0; i < stations_len; i++)
        if(i < 9)
            printf("|    %d.  %-54s|\n", i + 1, stations[i]);
        else
            printf("|    %d. %-54s|\n", i + 1, stations[i]);
    printf("|                                                              |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("|                                                              |\n");
    printf("+--- Pilih Stasiun Keberangkatan : ");
    fgets(selection, sizeof selection, stdin);
    validateSelection(selection, pages[3]);

    s = atoi(selection) - 1;
    printf("|                                                              |\n");
    printf("|    Stasiun yang dipilih, yaitu :                             |\n");
    printf("|                                                              |\n");
    printf("|    Stasiun %-16s (keberangkatan) -----------------+\n", stations[s]);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    printf("+==( LINK )==========================================================+\n");
    printf("|                                                                    |\n");
    printf("|    Jadwal lengkap keberangkatan dapat dilihat di :                 |\n");
    printf("|                                                                    |\n");
    printf("|    https://jakartamrt.co.id/id/jadwal-keberangkatan-mrt?dari=%-6d|\n", schedule_id[s]);
    printf("|                                                                    |\n");
    printf("+====================================================================+\n\n");
    backToMainMenu();
}

void routes() {
    printf("+========================[[ RUTE MRT ]]========================+\n");
    printf("|                                                              |\n");
    for (i = 0; i < stations_len; i++) {
        printf("|    %-58s|\n", stations[i]);
        if (i < stations_len - 1)
            printf("|      |                                                       |\n");
    }
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    backToMainMenu();
}

void backToMainMenu() {
    printf("+==============================================================+\n");
    printf("|                                                              |\n");
    printf("+--- Ketik Y atau y untuk kembali ke menu utama : ");
    fgets(selection, sizeof selection, stdin);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    validateSelection(selection, "y");
    system("cls || clear"); // Menghapus Screen
    mainMenu(user);
}

void logout() {
    printf("+=========================[[ LOGOUT ]]=========================+\n");
    printf("|                                                              |\n");
    printf("+--- Apakah yakin ingin keluar akun? (Y/N) : ");
    fgets(selection, sizeof selection, stdin);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    validateSelection(selection, "Y");
    if (*selection == 'N') {
        system("cls || clear"); // Menghapus Screen
        mainMenu(user);
    }
    strcpy(success, "|                       Logout berhasil!                       |\n");
    successMessage(success);
    mainGate();
}

void successMessage(char *suc) {
    system("cls || clear"); // Menghapus Screen
    printf("+==( PESAN SUKSES )============================================+\n");
    printf("|                                                              |\n");
    printf("%s", suc);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    suc[0] = 0;
}

void errorMessage(char *err, char *cur) {
    system("cls || clear"); // Menghapus Screen
    printf("+==( PESAN ERROR )=============================================+\n");
    printf("|                                                              |\n");
    printf("%s", err);
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    err[0] = 0;
    if (strcmp(cur, pages[0]) == 0)
        mainGate();
    if (strcmp(cur, pages[1]) == 0)
        mainMenu(user);
    if (strcmp(cur, pages[2]) == 0)
        ticketMenu();
    if (strcmp(cur, pages[3]) == 0)
        schedule();
    if (*cur == 'y')
        backToMainMenu();
    if (*cur == 'Y')
        logout();
}

void fileError() {
    system("cls || clear"); // Menghapus Screen
    printf("+==( PESAN ERROR )=============================================+\n");
    printf("|                                                              |\n");
    printf("|                        404 Not Found!                        |\n");
    printf("|        Tidak ada berkas atau direktori yang dimaksud.        |\n");
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    exit(0);
}

void exitMessage() {
    printf("+==============================================================+\n");
    printf("|                                                              |\n");
    printf("|            Terima kasih dan sampai jumpa kembali!            |\n");
    printf("|                                                              |\n");
    printf("+==============================================================+\n\n");
    sleep(3); // nunggu 3 detik biar pesannya kebaca sebelum terminal tutup
    exit(0);
}
