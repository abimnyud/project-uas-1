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