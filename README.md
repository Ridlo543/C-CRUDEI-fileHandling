# C-CRUDEI-fileHandling
Create, Read, Update, Delete, Export, Import in C file-handling program

Ini merupakan Program C dalam file processing untuk membuat data dalam file berbentuk txt atau format lain.<br>
Program ini dapat Create, Read, Update, Delete, Export, Import Data <br>
Input data dapat berupa NIM, Nama, Gender, dan IPK

buka file [CRUDEI.c](https://github.com/Ridlo543/C-CRUDEI-fileHandling/blob/main/CRUDEI.c)

```C
// Ridlo L0122138
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct
typedef struct
{
  int NIM;
  char Nama[100];
  char gender[100];
  float IPK;
} Mahasiswa;

// prototype fungsi
int menuUtama();
Mahasiswa inputDataMahasiswa();
void tambahMahasiswa(Mahasiswa mhs);
void ubahMahasiswa(int NIM, Mahasiswa mhs);
void hapusMahasiswa(int NIM);
void cetakDataMahasiswa();
void importDataMahasiswa(char *filename);
void exportDataMahasiswa(char *filename);

// fungsi main
int main()
{
  int pilihan;
  char filename[50];
  Mahasiswa mhs;
  int NIM;

  // option
  do
  {
    pilihan = menuUtama();
    switch (pilihan)
    {
    case 1:
      mhs = inputDataMahasiswa();
      tambahMahasiswa(mhs);
      break;
    case 2:
      printf("Masukkan NIM mahasiswa yang ingin diubah : ");
      scanf("%d", &NIM);
      mhs = inputDataMahasiswa();
      ubahMahasiswa(NIM, mhs);
      break;
    case 3:
      printf("Masukkan NIM mahasiswa yang ingin dihapus : ");
      scanf("%d", &NIM);
      hapusMahasiswa(NIM);
      break;
    case 4:
      cetakDataMahasiswa();
      break;
    case 5:
      printf("\nMasukkan nama file dan formatnya\n>> ");
      scanf("%s", filename);
      importDataMahasiswa(filename);
      break;
    case 6:
      printf("\nMasukkan nama file dan formatnya\n>> ");
      scanf("%s", filename);
      exportDataMahasiswa(filename);
      break;
    }
  } while (pilihan != 0);

  return 0;
}

// Fungsi untuk menampilkan menu utama
int menuUtama()
{
  int pilihan;
  printf("\n\n+===============MENU UTAMA================+");
  printf("\n| 1. Tambah Data  Mahasiswa               |");
  printf("\n| 2. Ubah   Data  Mahasiswa               |");
  printf("\n| 3. Hapus  Data  Mahasiswa               |");
  printf("\n| 4. Cetak  Data  Mahasiswa               |");
  printf("\n| 5. Impor  Data  Mahasiswa               |");
  printf("\n| 6. Ekspor Data  Mahasiswa               |");
  printf("\n| 0. Keluar                               |");
  printf("\n+==========================================+");
  printf("\nPilih Menu >> ");
  scanf("%d", &pilihan);
  return pilihan;
}

// Fungsi untuk input data mahasiswa
Mahasiswa inputDataMahasiswa()
{
  Mahasiswa mhs;

  printf("\n--- INPUT DATA MAHASISWA ---\n");
  printf("Masukkan NIM : ");
  scanf("%d", &mhs.NIM);
  printf("Masukkan Nama : ");
  scanf(" %[^\n]", mhs.Nama);
  printf("Masukkan Jenis Kelamin : ");
  scanf(" %[^\n]", mhs.gender);
  /*
  Menggunakan %[^\n], karena jika user menginputkan
  Nama lengkap yang terdapat spasi
  Input itu akan dianggap inputan untuk data selanjutnya
  yang akan menyebabkan error pada program
  */
  printf("Masukkan IPK : ");
  scanf("%f", &mhs.IPK);

  return mhs;
}
// Fungsi untuk menambah data mahasiswa
void tambahMahasiswa(Mahasiswa mhs)
{
  FILE *fp;

  // Buka file mahasiswa.txt jika tidak ada, buat file baru
  fp = fopen("mahasiswa.txt", "a+");

  // Tulis data mahasiswa ke file
  fprintf(fp, "%d;%s;%s;%f\n", mhs.NIM, mhs.Nama, mhs.gender, mhs.IPK);

  // Tutup file
  fclose(fp);
}

// Fungsi untuk mengubah data mahasiswa
void ubahMahasiswa(int NIM, Mahasiswa mhs)
{
  FILE *fp;
  char tempFilename[50] = "temp-mahasiswa.txt";
  Mahasiswa tempmhs;
  int found = 0;

  // Buka file mahasiswa.txt
  fp = fopen("mahasiswa.txt", "r");

  // Buka file sementara
  FILE *temp = fopen(tempFilename, "w");

  // Cek file mahasiswa.txt
  while (fscanf(fp, "%d;%[^;];%[^;];%f\n", &tempmhs.NIM, tempmhs.Nama, tempmhs.gender, &tempmhs.IPK) != EOF)
  {
    // Cetak data lama ke file sementara
    if (NIM != tempmhs.NIM)
      fprintf(temp, "%d;%s;%s;%f\n", tempmhs.NIM, tempmhs.Nama, tempmhs.gender, tempmhs.IPK);
    // Cetak data baru ke file sementara
    else
    {
      found = 1;
      fprintf(temp, "%d;%s;%s;%f\n", mhs.NIM, mhs.Nama, mhs.gender, mhs.IPK);
    }
  }

  // Tutup file
  fclose(fp);
  fclose(temp);

  // Hapus file mahasiswa.txt
  remove("mahasiswa.txt");

  // Rename file sementara
  rename(tempFilename, "mahasiswa.txt");

  // Notifikasi jika data tidak ditemukan
  if (!found)
    printf("\nData mahasiswa dengan NIM %d tidak ditemukan\n", NIM);
}

// Fungsi untuk menghapus data mahasiswa
void hapusMahasiswa(int NIM)
{
  FILE *fp;
  char tempFilename[50] = "temp-mahasiswa.txt";
  Mahasiswa tempmhs;
  int found = 0;

  // Buka file mahasiswa.txt
  fp = fopen("mahasiswa.txt", "r");

  // Buka file sementara
  FILE *temp = fopen(tempFilename, "w");

  // Cek file mahasiswa.txt
  while (fscanf(fp, "%d;%[^;];%[^;];%f\n", &tempmhs.NIM, tempmhs.Nama, tempmhs.gender, &tempmhs.IPK) != EOF)
  {
    // Cetak data selain data yang dihapus ke file sementara
    if (NIM != tempmhs.NIM)
      fprintf(temp, "%d;%s;%s;%f\n", tempmhs.NIM, tempmhs.Nama, tempmhs.gender, tempmhs.IPK);
    else
      found = 1;
  }

  // Tutup file
  fclose(fp);
  fclose(temp);

  // Hapus file mahasiswa.txt
  remove("mahasiswa.txt");

  // Rename file sementara
  rename(tempFilename, "mahasiswa.txt");

  // Notifikasi jika data tidak ditemukan
  if (!found)
    printf("\nData mahasiswa dengan NIM %d tidak ditemukan\n", NIM);
}

// Fungsi untuk mencetak data mahasiswa
void cetakDataMahasiswa()
{
  FILE *fp;
  Mahasiswa tempmhs;

  printf("\n\n+=========================DATA MAHASISWA===========================+");
  printf("\n| %4s  | %-30s | %-13s | %-2.2f  |", "NIM", "Nama", "Jenis Kelamin", "IPK");
  printf("\n+------------------------------------------------------------------+");

  fp = fopen("mahasiswa.txt", "r");

  // Cetak data mahasiswa dari file
  while (fscanf(fp, "%d;%[^;];%[^;];%f\n", &tempmhs.NIM, tempmhs.Nama, tempmhs.gender, &tempmhs.IPK) != EOF)
  {
    printf("\n| %4d  | %-30s | %-13s | %-2.2f  |", tempmhs.NIM, tempmhs.Nama, tempmhs.gender, tempmhs.IPK);
  }

  // Tutup file
  fclose(fp);

  printf("\n+------------------------------------------------------------------+");
}

// Fungsi untuk mengimport data mahasiswa
void importDataMahasiswa(char *filename)
{
  FILE *fp;
  Mahasiswa tempmhs;

  // Buka file
  fp = fopen(filename, "r");

  // Periksa file
  if (fp == NULL)
  {
    printf("\nFile tidak ditemukan\n");
    return;
  }

  // Baca data dari file
  while (fscanf(fp, "%d;%[^;];%[^;];%f\n", &tempmhs.NIM, tempmhs.Nama, tempmhs.gender, &tempmhs.IPK) != EOF)
  {
    // Tambahkan data mahasiswa ke mahasiswa.txt
    tambahMahasiswa(tempmhs);
  }

  // Tutup file
  fclose(fp);

  printf("\nData berhasil diimpor\n");
}

// Fungsi untuk mengekspor data mahasiswa
void exportDataMahasiswa(char *filename)
{
  FILE *fp;
  Mahasiswa tempmhs;

  // Buka file
  fp = fopen(filename, "w");

  // Baca data dari mahasiswa.txt
  FILE *mhsfp = fopen("mahasiswa.txt", "r");
  while (fscanf(mhsfp, "%d;%[^;];%[^;];%f\n", &tempmhs.NIM, tempmhs.Nama, tempmhs.gender, &tempmhs.IPK) != EOF)
  {
    // Tulis data ke file
    fprintf(fp, "%d;%s;%s;%f\n", tempmhs.NIM, tempmhs.Nama, tempmhs.gender, tempmhs.IPK);
  }

  // Tutup file
  fclose(mhsfp);
  fclose(fp);

  printf("\nData berhasil diekspor\n");
}
```
