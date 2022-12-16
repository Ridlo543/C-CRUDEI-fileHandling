#include <stdio.h>
#include <math.h>

// struct
typedef struct
{
  int NIM;
  char Nama[100];
  char gender[100];
  float IPK;
} Mahasiswa;

// prototype fungsi
int menuUtama();                            // Fungsi ini akan mengembalikan nilai integer yang merupakan pilihan menu yang dipilih oleh pengguna.
Mahasiswa inputDataMahasiswa();             // Fungsi ini akan mengembalikan sebuah variabel Mahasiswa yang merupakan hasil input dari pengguna.
void tambahMahasiswa(Mahasiswa mhs);        // Fungsi ini akan menambahkan sebuah variabel Mahasiswa ke dalam suatu daftar/database
void ubahMahasiswa(int NIM, Mahasiswa mhs); // Fungsi ini akan mengubah data Mahasiswa dengan NIM tertentu sesuai dengan data Mahasiswa yang diberikan.
void hapusMahasiswa(int NIM);               // Fungsi ini akan menghapus data Mahasiswa dengan NIM tertentu dari daftar/database.
void showDataMahasiswa();                   // Fungsi ini akan mencetak seluruh data Mahasiswa yang tersimpan dalam daftar/database.
void importDataMahasiswa(char *filename);   // Fungsi ini akan mengimport data Mahasiswa dari sebuah file eksternal yang bernama sesuai dengan parameter yang diberikan.
void exportDataMahasiswa(char *filename);   // Fungsi ini akan mengekspor data Mahasiswa ke dalam sebuah file eksternal yang bernama sesuai dengan parameter yang diberikan.
void cariMahasiswa(int NIM);                // FUngsi untuk mencari data mahasiswa berdasar NIM
void sortNIMMahasiswa();                    // Fungsi untuk mengurutkan data mahasiswa berdasar NIM
void sortIPKMahasiswa();                    // Fungsi untuk mengurutkan data mahasiswa berdasar IPK
void filterIPKMahasiswa();                  // Fungsi untuk menyaring data mahasiswa berdasar IPK
void detailDataMahasiswa();                 // Fungsi untuk menampilkan detail informasi data mahasiswa

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
      showDataMahasiswa();
      break;
    case 5:
      printf("\nMasukkan nama file dan formatnya\n>> ");
      scanf("%s", filename);
      exportDataMahasiswa(filename);
      break;
    case 6:
      printf("\nMasukkan nama file dan formatnya\n>> ");
      scanf("%s", filename);
      importDataMahasiswa(filename);
      break;
    case 7:
      printf("Masukkan NIM mahasiswa yang ingin dicari : ");
      scanf("%d", &NIM);
      cariMahasiswa(NIM);
      break;
    case 8:
      sortNIMMahasiswa();
      break;
    case 9:
      sortIPKMahasiswa();
      break;
    case 10:
      filterIPKMahasiswa();
      break;
    case 11:
      detailDataMahasiswa();
      break;
    }
  } while (pilihan != 0);

  return 0;
}

// Fungsi untuk menampilkan menu utama
// Fungsi ini akan mengembalikan nilai integer yang merupakan pilihan menu yang dipilih oleh pengguna.
int menuUtama()
{
  int pilihan;
  printf("\n\n+================MENU UTAMA=================+");
  printf("\n| [1]  Add              Data Mahasiswa      |");
  printf("\n| [2]  Update           Data Mahasiswa      |");
  printf("\n| [3]  Delete           Data Mahasiswa      |");
  printf("\n| [4]  Show             Data Mahasiswa      |");
  printf("\n| [5]  Export           Data Mahasiswa      |");
  printf("\n| [6]  Import           Data Mahasiswa      |");
  printf("\n| [7]  Find             Data Mahasiswa      |");
  printf("\n| [8]  Sort      NIM    Data Mahasiswa      |");
  printf("\n| [9]  Sort      IPK    Data Mahasiswa      |");
  printf("\n| [10] Filter    IPK    Data Mahasiswa      |");
  printf("\n| [11] Detail Informasi Data Mahasiswa      |");
  printf("\n| [0]  Keluar                               |");
  printf("\n+===========================================+");
  printf("\nPilih Menu >> ");
  scanf("%d", &pilihan);
  return pilihan;
}

// Fungsi untuk input data mahasiswa
// Fungsi ini akan mengembalikan sebuah variabel Mahasiswa yang merupakan hasil input dari pengguna.
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
// Fungsi ini akan menambahkan sebuah variabel Mahasiswa ke dalam suatu daftar/database
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
// Fungsi ini akan mengubah data Mahasiswa dengan NIM tertentu sesuai dengan data Mahasiswa yang diberikan.
void ubahMahasiswa(int NIM, Mahasiswa mhs)
{
  // fp akan dibaca kemudian ditulis di temp
  // Lalu cetak data baru mengecualikan data yang dipilih ke *temp
  // Lalu fp dihapus, rename temp ke "mahasiswa.txt"
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
// Fungsi ini akan menghapus data Mahasiswa dengan NIM tertentu dari daftar/database.
void hapusMahasiswa(int NIM)
{
  // cetak data baru mengecualikan data yang dipilih ke *temp
  // Lalu fp dihapus, rename temp ke "mahasiswa.txt"
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
// Fungsi ini akan mencetak seluruh data Mahasiswa yang tersimpan dalam daftar/database.
void showDataMahasiswa()
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
// Fungsi ini akan mengimport data Mahasiswa dari sebuah file eksternal yang bernama sesuai dengan parameter yang diberikan.
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
// Fungsi ini akan mengekspor data Mahasiswa ke dalam sebuah file eksternal yang bernama sesuai dengan parameter yang diberikan.
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

// Fungsi untuk mencari data mahasiswa berdasar NIM
void cariMahasiswa(int NIM)
{
  FILE *fp;
  Mahasiswa tempmhs;

  fp = fopen("mahasiswa.txt", "r");

  printf("\n\n+=========================DATA MAHASISWA============================+");
  printf("\n| %4s  | %-30s | %-13s | %-2.2f  |", "NIM", "Nama", "Jenis Kelamin", "IPK");
  printf("\n+------------------------------------------------------------------+");

  while (fscanf(fp, "%d;%[^;];%[^;];%f\n", &tempmhs.NIM, tempmhs.Nama, tempmhs.gender, &tempmhs.IPK) != EOF)
  {
    if (NIM == tempmhs.NIM)
    {
      printf("\n| %4d  | %-30s | %-13s | %-2.2f  |", tempmhs.NIM, tempmhs.Nama, tempmhs.gender, tempmhs.IPK);
      break;
    }
  }

  fclose(fp);

  printf("\n+------------------------------------------------------------------+");
}

// Fungsi untuk mengurutkan data mahasiswa berdasarkan NIM
void sortNIMMahasiswa()
{
  int option;
  FILE *fp;
  Mahasiswa tempmhs;
  Mahasiswa mhs[100];
  int i = 0;

  fp = fopen("mahasiswa.txt", "r");
  // Menyimpan data mahasiswa dari file ke array
  while (fscanf(fp, "%d;%[^;];%[^;];%f\n", &tempmhs.NIM, tempmhs.Nama, tempmhs.gender, &tempmhs.IPK) != EOF)
  {
    mhs[i] = tempmhs;
    i++;
  }
  fclose(fp);

  printf("=======SORTING NIM========\n");
  printf("[1] Ascending\n");
  printf("[2] Descending\n");
  printf(">> ");
  scanf("%d", &option);

  // Mengurutkan data mahasiswa berdasarkan NIM
  // Option 1 mengurutkan dari NIM terkecil ke terbesar
  // Option 2 mengurutkan dari NIM terbesar ke terkecil
  if (option == 1)
  {
    for (int j = 0; j < i; j++)
    {
      for (int k = j; k < i; k++)
      {
        Mahasiswa temp;
        if (mhs[j].NIM > mhs[k].NIM)
        {
          temp = mhs[j];
          mhs[j] = mhs[k];
          mhs[k] = temp;
        }
      }
    }
  }
  else if (option == 2)
  {
    for (int j = 0; j < i; j++)
    {
      for (int k = j; k < i; k++)
      {
        Mahasiswa temp;
        if (mhs[j].NIM < mhs[k].NIM)
        {
          temp = mhs[j];
          mhs[j] = mhs[k];
          mhs[k] = temp;
        }
      }
    }
  }

  // Menuliskan data mahasiswa yang telah diurutkan ke file mahasiswa.txt
  fp = fopen("mahasiswa.txt", "w");
  for (int j = 0; j < i; j++)
  {
    fprintf(fp, "%d;%s;%s;%f\n", mhs[j].NIM, mhs[j].Nama, mhs[j].gender, mhs[j].IPK);
  }
  fclose(fp);
  printf("\nData berhasil di sort\n");
}

void sortIPKMahasiswa()
{
  int option;
  FILE *fp;
  Mahasiswa tempmhs[100], temp;
  int i, j, counter;

  fp = fopen("mahasiswa.txt", "r");

  // Copy data mahasiswa ke array
  counter = 0;
  while (fscanf(fp, "%d;%[^;];%[^;];%f\n", &tempmhs[counter].NIM, tempmhs[counter].Nama, tempmhs[counter].gender, &tempmhs[counter].IPK) != EOF)
  {
    counter++;
  }
  // Tutup file
  fclose(fp);

  printf("=======SORTING IPK========\n");
  printf("[1] Ascending\n");
  printf("[2] Descending\n");
  printf(">> ");
  scanf("%d", &option);

  // Sorting data
  for (i = 0; i < counter; i++)
  {
    for (j = 0; j < counter - 1; j++)
    {
      // Sort ascending
      if (option == 1)
      {
        if (tempmhs[j].IPK > tempmhs[j + 1].IPK)
        {
          temp = tempmhs[j];
          tempmhs[j] = tempmhs[j + 1];
          tempmhs[j + 1] = temp;
        }
      }
      // Sort descending
      else if (option == 2)
      {
        if (tempmhs[j].IPK < tempmhs[j + 1].IPK)
        {
          temp = tempmhs[j];
          tempmhs[j] = tempmhs[j + 1];
          tempmhs[j + 1] = temp;
        }
      }
    }
  }

  // Overwrite file mahasiswa.txt
  fp = fopen("mahasiswa.txt", "w");
  for (i = 0; i < counter; i++)
  {
    fprintf(fp, "%d;%s;%s;%f\n", tempmhs[i].NIM, tempmhs[i].Nama, tempmhs[i].gender, tempmhs[i].IPK);
  }
  // Tutup file
  fclose(fp);
  printf("\nData berhasil di sort\n");
}

void filterIPKMahasiswa()
{
  int option;
  FILE *fp;
  Mahasiswa tempmhs;
  float IPK, totalIPK = 0;
  int jumlahData = 0;
  printf("=======FILTER IPK========\n");
  printf("[1] Lebih dari rata-rata\n");
  printf("[2] Kurang dari rata-rata\n");
  printf(">> ");
  scanf("%d", &option);

  printf("\n\n+=========================DATA MAHASISWA===========================+");
  printf("\n| %4s  | %-30s | %-13s | %-2.2f  |", "NIM", "Nama", "Jenis Kelamin", "IPK");
  printf("\n+------------------------------------------------------------------+");

  fp = fopen("mahasiswa.txt", "r");

  // Hitung total IPK dan jumlah data
  while (fscanf(fp, "%d;%[^;];%[^;];%f\n", &tempmhs.NIM, tempmhs.Nama, tempmhs.gender, &tempmhs.IPK) != EOF)
  {
    totalIPK += tempmhs.IPK;
    jumlahData++;
  }

  // Hitung IPK rata-rata
  IPK = totalIPK / jumlahData;

  // Cetak data mahasiswa dari file
  rewind(fp);
  while (fscanf(fp, "%d;%[^;];%[^;];%f\n", &tempmhs.NIM, tempmhs.Nama, tempmhs.gender, &tempmhs.IPK) != EOF)
  {
    // Cetak data mahasiswa sesuai kondisi yang diinginkan
    if (option == 1 && tempmhs.IPK > IPK)
    {
      printf("\n| %4d  | %-30s | %-13s | %-2.2f  |", tempmhs.NIM, tempmhs.Nama, tempmhs.gender, tempmhs.IPK);
    }
    else if (option == 2 && tempmhs.IPK < IPK)
    {
      printf("\n| %4d  | %-30s | %-13s | %-2.2f  |", tempmhs.NIM, tempmhs.Nama, tempmhs.gender, tempmhs.IPK);
    }
  }

  // Tutup file
  fclose(fp);
  printf("\n+------------------------------------------------------------------+");
  printf("\nData berhasil difilter\n");
}

// Fungsi untuk menampilkan detail informasi data mahasiswa
void detailDataMahasiswa()
{
  FILE *fp;
  Mahasiswa tempmhs;
  int n = 0;
  float sum_IPK = 0;
  float mean_IPK;
  float tempIPK[100];
  float median_IPK;
  float modus_IPK;
  float max_IPK;
  float min_IPK;
  float range_IPK;
  float varian_IPK = 0;
  float standar_deviasi_IPK;

  fp = fopen("mahasiswa.txt", "r");

  // Cetak data mahasiswa dari file
  while (fscanf(fp, "%d;%[^;];%[^;];%f\n", &tempmhs.NIM, tempmhs.Nama, tempmhs.gender, &tempmhs.IPK) != EOF)
  {
    sum_IPK += tempmhs.IPK;
    tempIPK[n] = tempmhs.IPK;
    n++;
  }

  // Hitung mean
  mean_IPK = sum_IPK / n;

  // Hitung median
  if (n % 2 == 0)
  {
    median_IPK = (tempIPK[n / 2] + tempIPK[(n / 2) - 1]) / 2;
  }
  else
  {
    median_IPK = tempIPK[(n - 1) / 2];
  }

  // Hitung modus
  int frek[100];
  int max = 0;
  for (int i = 0; i < n; i++)
  {
    frek[i] = 0;
    for (int j = 0; j < n; j++)
    {
      if (tempIPK[i] == tempIPK[j])
      {
        frek[i]++;
      }
    }
    if (frek[i] > max)
    {
      max = frek[i];
      modus_IPK = tempIPK[i];
    }
  }

  // Hitung range
  max_IPK = tempIPK[0];
  min_IPK = tempIPK[0];
  for (int i = 0; i < n; i++)
  {
    if (tempIPK[i] > max_IPK)
    {
      max_IPK = tempIPK[i];
    }
    else if (tempIPK[i] < min_IPK)
    {
      min_IPK = tempIPK[i];
    }
  }
  range_IPK = max_IPK - min_IPK;

  // Hitung varian
  for (int i = 0; i < n; i++)
  {
    varian_IPK += pow(tempIPK[i] - mean_IPK, 2);
  }
  varian_IPK = varian_IPK / n;

  // Hitung standar deviasi
  standar_deviasi_IPK = sqrt(varian_IPK);

  printf("\n\n+=======================DETAIL DATA MAHASISWA=======================+");
  printf("\n| Banyak data\t\t\t\t\t\t : %d", n);
  printf("\n| Mean\t\t\t\t\t\t\t\t : %2.2f", mean_IPK);
  printf("\n| Median\t\t\t\t\t\t\t : %2.2f", median_IPK);
  printf("\n| Modus\t\t\t\t\t\t\t : %2.2f", modus_IPK);
  printf("\n| Range\t\t\t\t\t\t\t : %2.2f", range_IPK);
  printf("\n| Varian\t\t\t\t\t\t : %2.2f", varian_IPK);
  printf("\n| Standar deviasi\t\t\t\t\t : %2.2f", standar_deviasi_IPK);
  printf("\n+---------------------------------------------------------------+");

  // Tutup file
  fclose(fp);
}
