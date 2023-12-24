#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Maksimum jumlah Kontak yang dapat disimpan
#define MAX_CONTACTS 100

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct infoKontak {
    char nama[50];
    char nomorHP[15];
    bool Favorit; // boolean digunakan untuk mencari benar atau salah
};

// untuk menghapus tulisan sebelumnya yang tidak terpakai, agar lebih mudah dibaca
void clearScreen() { 
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf(ANSI_COLOR_RED "\n X -                              \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW"=================================================="ANSI_COLOR_RESET); // dekorasi
    printf(ANSI_COLOR_GREEN "\n                   BUKU TELEPON\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW"==================================================\n"ANSI_COLOR_RESET); // dekorasi
    printf(ANSI_COLOR_CYAN "            Information Technology 23\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW"--------------------------------------------------\n"ANSI_COLOR_RESET);
}

// fungsi untuk mencari nama kontak
void cariNama(struct infoKontak kontak[], int nomorKontak, char namaCari[]) { 
    int count = 0;

    printf("Hasil pencarian untuk nama '%s':\n", namaCari);
    printf("%-5s%-30s%-15s\n", "NO", "NAMA", "NOMOR HP");

    for (int i = 0; i < nomorKontak; i++) {
        // Menggunakan strcasestr untuk mencari substring dalam nama
        if (strcasestr(kontak[i].nama, namaCari) != NULL) {
            printf("%-5d%-30s%-15s\n", i + 1, kontak[i].nama, kontak[i].nomorHP);
            count++;
        }
    }

    if (count == 0) {
        printf("Tidak ada hasil pencarian untuk nama '%s'.\n", namaCari);
    }
}

// membuat fungsi menukar variable
void swap(struct infoKontak *a, struct infoKontak *b) { 
    struct infoKontak t = *a;
    *a = *b;
    *b = t;
}

// fungsi untuk membagi array
int partition(struct infoKontak kontak[], int low, int high) { 
    char pivot[50];
    strcpy(pivot, kontak[high].nama);

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (strcasecmp(kontak[j].nama, pivot) < 0) {
            i++;
            swap(&kontak[i], &kontak[j]);
        }
    }
    swap(&kontak[i + 1], &kontak[high]);
    return (i + 1);
}

// Algoritma Quick Sort, menggunakan rekursi untuk membagi array menjadi bagian yang lebih kecil kemudian baru di sort
void quickSortByFirstChar(struct infoKontak kontak[], int low, int high) { 
    if (low < high) {
        int pi = partition(kontak, low, high);

        quickSortByFirstChar(kontak, low, pi - 1);
        quickSortByFirstChar(kontak, pi + 1, high);
    }
}

// boolean untuk mengecek apakah char atau bukan
bool cariChar(char foundLetters[], char ch) { 
    for (size_t i = 0; i < strlen(foundLetters); i++) {
        if (foundLetters[i] == ch) {
            return true;
        }
    }
    return false;
}

// Algoritma Bubble Sort
void bubbleSortByFirstChar(struct infoKontak kontak[], int nomorKontak) {
    for (int i = 0; i < nomorKontak - 1; i++) {
        for (int j = 0; j < nomorKontak - i - 1; j++) {
            if (strcasecmp(kontak[j].nama, kontak[j + 1].nama) > 0) {
                struct infoKontak temp = kontak[j];
                kontak[j] = kontak[j + 1];
                kontak[j + 1] = temp;
            }
        }
    }
}

// fungsi yang digunakan untuk menambah kontak
void tambahKontak(struct infoKontak kontak[], int* nomorKontak) {
    clearScreen();
    if (*nomorKontak < MAX_CONTACTS) {
        printf("Masukkan nama: ");
        getchar();
        fgets(kontak[*nomorKontak].nama, sizeof(kontak[*nomorKontak].nama), stdin);

        size_t len = strlen(kontak[*nomorKontak].nama);
        if (len > 0 && kontak[*nomorKontak].nama[len - 1] == '\n') {
            kontak[*nomorKontak].nama[len - 1] = '\0';
        }

        printf("Masukkan nomor handphone: ");
        scanf("%s", kontak[*nomorKontak].nomorHP);

    // agar setiap kontak yang kita masukkan tidak langsung terkategori sebagai favorit
        kontak[*nomorKontak].Favorit = false;

        (*nomorKontak)++;
        printf("Kontak berhasil ditambahkan.\n");
    } else {
        printf("Buku telepon sudah penuh.\n");
    }
}

// fungsi yang akan digunakan untuk menampilkan kontak
void displayKontak(struct infoKontak kontak[], int nomorKontak) {
    clearScreen();
    printf("Pilihan tampilan:\n");
    printf("1. Tampilan Biasa\n");
    printf("2. Tampilan Sorted by First Character (Bubble Sort)\n");
    printf("3. Tampilan Sorted by Quick Sort\n");
    printf("Pilih opsi (1-3): ");

    int opsiTampilan;
    scanf("%d", &opsiTampilan);

    printf("%-5s%-30s%-15s\n", "NO", "NAMA", "NOMOR HP");

    if (opsiTampilan == 1) {
        for (int i = 0; i < nomorKontak; i++) {
            printf("%-5d%-30s%-15s\n", i + 1, kontak[i].nama, kontak[i].nomorHP);
        }
    }
    else if (opsiTampilan == 2) {
        bubbleSortByFirstChar(kontak, nomorKontak);
        for (int i = 0; i < nomorKontak; i++) {
            printf("%-5d%-30s%-15s\n", i + 1, kontak[i].nama, kontak[i].nomorHP);
        }
    }
    else if (opsiTampilan == 3) {
        quickSortByFirstChar(kontak, 0, nomorKontak - 1);
        for (int i = 0; i < nomorKontak; i++) {
            printf("%-5d%-30s%-15s\n", i + 1, kontak[i].nama, kontak[i].nomorHP);
        }
    }
    else {
        printf(ANSI_COLOR_RED"Opsi tidak valid.\n"ANSI_COLOR_RESET);
    }
}

// fungsi untuk menampilkan kontak berdasarkan abjad
void listKontak(struct infoKontak kontak[], int nomorKontak) {
    clearScreen();
    char foundLetters[52] = "";

    quickSortByFirstChar(kontak, 0, nomorKontak - 1);

    printf("%-5s    %-5s    %-30s%-15s\n", "HURUF", "NOMOR", "NAMA", "NOMOR HP");
    printf("=========================================================\n"); // dekorasi

    for (int i = 0; i < nomorKontak; i++) {
        char firstChar = kontak[i].nama[0];
        char firstCharUpper = toupper(firstChar);

        if (!cariChar(foundLetters, firstCharUpper)) {
            strcat(foundLetters, &firstCharUpper);

            printf("%-5c", firstCharUpper);
            printf("    ");

            printf("%-5d", i + 1);

            printf("    ");

            printf("%-30s%-15s\n", kontak[i].nama, kontak[i].nomorHP);

            for (int j = i + 1; j < nomorKontak; j++) {
                if (toupper(kontak[j].nama[0]) == firstCharUpper) {
                    printf("%-5s    %-5d    %-30s%-15s\n", "", j + 1, kontak[j].nama, kontak[j].nomorHP);
                }
            }
        }
    }
}

// fungsi yang digunakan untuk edit kontak
void editKontak(struct infoKontak kontak[], int *nomorKontak) {
    clearScreen();
    if (*nomorKontak == 0) {
        printf(ANSI_COLOR_RED"Buku telepon kosong. Tidak ada Kontak untuk diedit.\n"ANSI_COLOR_RED"\n");
        return;
    }

    listKontak(kontak, *nomorKontak);

    int opsi;
    printf("Masukkan nomor Kontak yang ingin diedit (1-%d): ", *nomorKontak);
    scanf("%d", &opsi);

    if (opsi >= 1 && opsi <= *nomorKontak) {
        printf("Masukkan nama baru: ");
        getchar();
        fgets(kontak[opsi - 1].nama, sizeof(kontak[opsi - 1].nama), stdin);

        size_t len = strlen(kontak[opsi - 1].nama);
        if (len > 0 && kontak[opsi - 1].nama[len - 1] == '\n') {
            kontak[opsi - 1].nama[len - 1] = '\0';
        }

        printf("Masukkan nomor handphone baru: ");
        scanf("%s", kontak[opsi - 1].nomorHP);

        printf(ANSI_COLOR_GREEN"Kontak berhasil diedit.\n"ANSI_COLOR_GREEN"\n");
    }
    else {
        printf(ANSI_COLOR_RED"Nomor Kontak tidak valid.\n"ANSI_COLOR_RED"\n");
    }
}

// fungsi yang digunakan untuk menghapus kontak
void hapusKontak(struct infoKontak kontak[], int *nomorKontak) {
    clearScreen();
    if (*nomorKontak == 0) {
        printf(ANSI_COLOR_RED"Buku telepon kosong. Tidak ada Kontak untuk dihapus.\n"ANSI_COLOR_RED"\n");
        return;
    }

    listKontak(kontak, *nomorKontak);

    int opsi;
    printf("Masukkan nomor Kontak yang ingin dihapus (1-%d): ", *nomorKontak);
    scanf("%d", &opsi);

    if (opsi >= 1 && opsi <= *nomorKontak) {
        for (int i = opsi - 1; i < *nomorKontak - 1; i++) {
            kontak[i] = kontak[i + 1];
        }
        (*nomorKontak)--;
        printf(ANSI_COLOR_GREEN"Kontak berhasil dihapus.\n"ANSI_COLOR_GREEN"\n");
    }
    else {
        printf(ANSI_COLOR_RED"Nomor Kontak tidak valid.\n"ANSI_COLOR_RED"\n");
    }
}

// fungsi yang dapat digunakan untuk menambahkan kontak yang ada ke kontak favorit
void tambahFavorit(struct infoKontak kontak[], int nomorKontak) {
    clearScreen();
    if (nomorKontak == 0) {
        printf(ANSI_COLOR_RED"Buku telepon kosong. Tidak ada Kontak untuk dijadikan favorit.\n"ANSI_COLOR_RED"\n");
        return;
    }

    listKontak(kontak, nomorKontak);

    int opsi;
    printf("Masukkan nomor Kontak yang ingin dijadikan favorit (1-%d): ", nomorKontak);
    scanf("%d", &opsi);

// untuk mengubah status favorit kontak yang awalnya false menjadi true
    if (opsi >= 1 && opsi <= nomorKontak) {
        kontak[opsi - 1].Favorit = true;
        printf(ANSI_COLOR_GREEN"Kontak berhasil dijadikan favorit.\n"ANSI_COLOR_GREEN"\n");
    }
    else {
        printf("Nomor Kontak tidak valid.\n");
    }
}

// fungsi untuk mendisplay kontak yang telah dimasukkan ke kontak favorit
void displayFavorit(struct infoKontak kontak[], int nomorKontak) {
    clearScreen();
    printf("%-5s%-30s%-15s\n", "NO", "NAMA", "NOMOR HP");

    int count = 0;

    // mengecek semua yang ada dalam kontak, jika kontak tersebut masuk pada .favorit maka tampilkan.
    for (int i = 0; i < nomorKontak; i++) {
        if (kontak[i].Favorit) {
            printf("%-5d%-30s%-15s\n", count + 1, kontak[i].nama, kontak[i].nomorHP);
            count++;
        }
    }

    if (count == 0) {
        printf("Tidak ada Kontak favorit.\n");
    }
}

int main() {
    struct infoKontak kontak[MAX_CONTACTS];
    int nomorKontak = 0;
    char namaCari[50];
    int opsi;
    
    do {
        clearScreen();
        printf(ANSI_COLOR_GREEN "\nMenu:\n" ANSI_COLOR_RESET);
        printf("1. Tambah Kontak\n");
        printf("2. Edit Kontak\n");
        printf("3. Tampilkan Semua Kontak\n");
        printf("4. Hapus Kontak\n");
        printf("5. List Kontak Berdasarkan Abjad\n");
        printf("6. Jadikan Kontak Favorit\n");
        printf("7. Tampilkan Kontak Favorit\n");
        printf("8. Cari Nama Kontak\n");
        printf("0. Keluar\n");

        printf("Pilih opsi (0-8): ");
        scanf("%d", &opsi);

        switch (opsi) {
        case 1:
            tambahKontak(kontak, &nomorKontak);
            break;
        case 2:
            editKontak(kontak, &nomorKontak);
            break;
        case 3:
            displayKontak(kontak, nomorKontak);
            break;
        case 4:
            hapusKontak(kontak, &nomorKontak);
            break;
        case 5:
            listKontak(kontak, nomorKontak);
            break;
        case 6:
            tambahFavorit(kontak, nomorKontak);
            break;
        case 7:
            displayFavorit(kontak, nomorKontak);
            break;
        case 8:
            printf("Masukkan nama yang ingin dicari: ");
            getchar();
            fgets(namaCari, sizeof(namaCari), stdin);
            
            
                size_t lenCari = strlen(namaCari);
                if (lenCari > 0 && namaCari[lenCari - 1] == '\n') {
                    namaCari[lenCari - 1] = '\0';
                }

                cariNama(kontak, nomorKontak, namaCari);
                break;
            
                printf(ANSI_COLOR_GREEN"Program selesai.\n"ANSI_COLOR_GREEN"\n");
                break;
            
                printf(ANSI_COLOR_RED"Opsi tidak valid.\n"ANSI_COLOR_RED"\n");
        }

        if (opsi != 0) {
            printf(ANSI_COLOR_BLUE"\nKetik ENTER untuk melanjutkan..."ANSI_COLOR_BLUE"\n");
            getchar();
            getchar();
        }

    } while (opsi != 0);

    return 0;
}
