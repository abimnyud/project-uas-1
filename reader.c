#include <stdio.h>

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

char gate[][20] = {"Pintu Masuk", "Pintu Keluar"};

int main() {
    int stasiun, pintu, i;
    
    printf("\nDaftar stasiun:\n");
    for(i = 1; i <= 13; i++) {
        printf("%d. %s\n", i, stasiun_mrt[i]);
    }
    printf("\nSilakan masukkan kode mesin di salah satu stasiun: ");
    scanf("%d", &stasiun);

    printf("\nDaftar pintu di stasiun %s\n", stasiun_mrt[stasiun]);
    for(i = 0; i < 2; i++) {
        printf("%d. %s\n", i, gate[i]);
    }
    printf("\nSilakan masukkan kode pilihan pintu: ");
    scanf("%d", &pintu);

    printf("\n%s", stasiun_mrt[stasiun]);
    printf("\n%s\n", gate[pintu]);
    return 0;
}

char *tmp_ticket;
char *ticket_id;
char *sp;

void menuRegister()
{
    FILE *ticketdata;
    ticketdata = fopen("./data/ticket_data.csv", "r");
    if(ticketdata == NULL) {
        printf("Error: Tidak dapat membuka file data user\n");
        exit(1);
    }

    int i = 1;
    printf("Username\tStasiun Awal\tStasiun Tujuan\tKode_Tiket\n");
    while(fgets(tmp_ticket, 100, ticketdata) != NULL) {
        sp = strtok(tmp_ticket, ",");
        if(strcmp(ticket_id, sp) == 0) {
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
}
