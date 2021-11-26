# project-uas-1
Project Mata Kuliah Algoritma Semester 1 Kelompok Enjoy


belitiket()
    struct tiket
    char stasiun awal
    char stasiun akhir

generateTicket()
    char randomChar[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnoprstuvwxyz1234567890"
    char ticketCode[10];

    for(int i = 0; i < 10; i++) {
        ticketCode[i] = randomChar[rand() % (sizeof(abc) - 1)]
        printf("%s", ticketCode[i]);
    }
    ticketCode[10] = 0;


