/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020  
* MODUL 9 – TUGAS BESAR  
* Kelompok   : 5  
* Hari dan Tanggal : Senin, 13 April 2018 
* Asisten (NIM)  : Meinanto Tri Yuriawan (13217021) 
* Nama File   : functions.h  
* Deskripsi   : Implementasi fungsi Tick dan count_neighbor  */ 
 
//file ini digunakan sebagai library untuk fungsi-fungsi yang akan digunakan pada program utama

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h> 

//fungsi untuk menghitung jumlah tetangga yang hidup pada suatu sel
int count_neighbor (int jumlah_baris, int jumlah_kolom, int posisi_baris, int posisi_kolom, char *matriks){
 /*
 *fungsi memiliki paramter input berupa jumlah baris dan jumlah kolom dari matriks, indeks posisi elemen saat ini dari matriks, 
 *dan pointer menuju ke elemen pertama dari matriks
 *fungsi memiliki keluaran berupa bilangan bulat jumlah tetangga yang hidup, alias jumlah tetangga pada matriks yang 
 *memiliki character 'X', pengecekan tetangga dilakukan secara diagonal, vertikal, dan horizontal.
 */
 //*kamus
 int count = 0; //variabel untuk menghitung jumlah tetangga
 int i,j; //indeks pada matriks dan digunakan untuk loop
 char c; //variabel untuk menyimpan character sementara pada matriks
 
 //*algoritma
 //looping untuk baris dari matriks, dari posisi elemen secara vertikal kurang satu hingga posisi elemen secara vertikal tambah 1
 for(i=(posisi_baris-1);i<(posisi_baris+2);i++){
   //looping untuk kolom dari matriks, dari posisi elemen secara horizontal kurang satu hingga posisi elemen secara horizontal tambah 1
  for(j=(posisi_kolom-1);j<(posisi_kolom+2);i++){
   /*
   *jika setelah pengurangan ternyata indeks baris adalah -1, karena matriks toroidal maka -1 menandakan baris paling akhir
   *merupakan atas dari baris elemen saat ini.
   */
   if(i==-1){ 
    /*
   *jika setelah pengurangan ternyata indeks kolom adalah -1, karena matriks toroidal maka -1 menandakan kolom paling akhir
   *merupakan seblah kiri dari baris elemen saat ini.
   */
    if(j==-1){
     //mengassign c sesuai dengan character pada posisi matriks[i][j], dalam kasus ini berarti j adalah kolom paling akhir dan i adalah 
     //baris paling akhir
     c = *((matriks+((jumlah_baris-1)*jumlah_kolom))+(jumlah_kolom-1)); 
    }
    //jika indeks j bukan -1
    else{
     //mengassign c sesuai dengan character pada posisi matriks[i][j], dalam hal ini berarti i adalah baris paling akhir. j mod jumlah_kolom
     //digunakan agar, ketika j sudah lebih dari jumlah kolom maka akan kembali ke kolom pertama (toroidal)
     c = *((matriks+((jumlah_baris-1)*jumlah_kolom))+(j%jumlah_kolom));
    };
   }
   //jika indeks i bukan -1
   else{ 
    /*
    *jika setelah pengurangan ternyata indeks kolom adalah -1, karena matriks toroidal maka -1 menandakan kolom paling akhir
    *merupakan seblah kiri dari baris elemen saat ini.
    */
    if(j==-1){
     //mengassign c sesuai dengan character pada posisi matriks[i][j], dalam hal ini berarti j adalah kolom paling akhir.
     //i mod jumlah_baris digunakan agar, ketika i sudah lebih dari jumlah baris maka akan kembali ke baris pertama (toroidal)
     c = *((matriks+((i%jumlah_baris)*jumlah_kolom))+(jumlah_kolom-1));
    }
    //jika indeks j bukan -1
    else{
     //mengassign c sesuai dengan character pada posisi matriks[i][j], i mod jumlah_baris dan j mod jumlah_kolom digunakan agar,
     //ketika i dan j sudah lebih dari jumlah baris dan jumlah kolom maka akan kembali ke baris dan kolom pertama (toroidal)
     c = *((matriks+((i%jumlah_baris)*jumlah_kolom))+(j%jumlah_kolom));
    };
   };
   //jika tetangga elemen tersebut ternyata hidup, alias 'X'
   if(c == 'X'){
    //jika elemen yang dianggap tetangga itu bukan kondisi (hidup atau mati) dari elemen itu sendiri (karena yang dicek tetangga)
    if((i != posisi_baris) || (j != posisi_kolom)){
     //menambahkan jumlah tetangga yang hidup
     count++;
    };
   };
  };
 };
 //mengembalikan nilai jumlah tetangga yang hidup
 return(count);
};

//prosedur Tick dari matriks saat ini
void Tick (int jumlah_baris, int jumlah_kolom, char *Curr_Matriks){
 //prosedur ini memiliki paramter input jumlah baris, jumlah kolom, dan pointer ke elemen pertama matriks saat ini
 //prosedur akan menghasilkan matriks hasil tick (iterasi sesuai ketentuan) dari matriks saat ini.
 //mengassign Next_Matriks sebagai matriks sementara hasil tick dari Curr_Matriks dengan besar yang sama dengan Curr_Matriks
 char *Next_Matriks = malloc(sizeod(char)*jumlah_kolom*jumlah_baris);
 //indeks untuk looping dan posisi elemen pada matriks
 int i,j;
 //looping untuk baris dari Curr_Matriks, dari baris pertama hingga baris akhir
 for(i=0;i<jumlah_baris;i++){
  //looping untuk kolom dari Curr_Matriks, dari kolom pertama hingga kolom akhir
  for(j=0;j<jumlah_kolom;j++){
   //jika elemen pada posisi Curr_Matriks[i][j] berstatus hidup, alias 'X'
   if(*(Curr_Matriks+(i*jumlah_kolom)+j) == 'X'){
    //jika hasil perhitungan fungsi count_neighbor kurang dari 2
    if(count_neighbor(jumlah_baris,jumlah_kolom,i,j,Curr_Matriks)<2){
     //mengassign bahwa kondisi berikutnya elemen ini akan mati, alias '-', karena under population
     *(Next_Matriks+(i*jumlah_kolom)+j) = '-';
    }
    //jika hasil perhitungan fungsi count_neighbor tidak kurang dari 2
    else{
      //jika hasil perhitungan fungsi count_neighbor lebih dari 3
      if(count_neighbor(jumlah_baris,jumlah_kolom,i,j,Curr_Matriks)>3){
       //mengassign bahwa kondisi berikutnya elemen ini akan mati, alias '-', karena over population
       *(Next_Matriks+(i*jumlah_kolom)+j) = '-';
      }
      //jika hasil perhitungan fungsi count_neighbor tidak lebih dari 3
      else{
       //mengassign bahwa kondisi berikutnya elemen ini tidak berubah (tetap hidup)
       *(Next_Matriks+(i*jumlah_kolom)+j) = *(Curr_Matriks+(i*jumlah_kolom)+j);
      };
     };
    }
   //jika elemen pada posisi Curr_Matriks[i][j] berstatus mati, alias '-'
    else{
     //jika hasil perhitungan fungsi count_neighbor tepat sama dengan 3
     if(count_neighbor(jumlah_baris,jumlah_kolom,i,j,Curr_Matriks)==3){
      //mengassign bahwa kondisi berikutnya elemen menjadi hidup (seperti memiliki anak)
      *(Next_Matriks+(i*jumlah_kolom)+j) = 'X';
     }
     //jika hasil perhitungan fungsi count_neighbor tidak tepat sama dengan 3
     else{
      //mengassign bahwa kondisi berikutnya elemen ini tidak berubah (tetap mati)
      *(Next_Matriks+(i*jumlah_kolom)+j) = *(Curr_Matriks+(i*jumlah_kolom)+j);
     };
    };
  };
 };
 //looping untuk baris dari Curr_Matriks, dari baris pertama hingga baris akhir
 for(i=0;i<jumlah_baris;i++){
  //looping untuk kolom dari Curr_Matriks, dari kolom pertama hingga kolom akhir
  for(j=0;j<jumlah_kolom;j++){
   //mengassign elemen-elemen pada Curr_Matriks menjadi Next_Matriks
   *(Curr_Matriks+(i*jumlah_kolom)+j) = *(Next_Matriks+(i*jumlah_kolom)+j);
  };
 };
 //membebaskan memori dari Next_Matriks
 free(Next_Matriks);
};
//prosedur menu untuk tampilan user

// Prosedur printmatriks
void printMatriks(int jumlah_baris, int jumlah_kolom, char *matriks){
	// Prosedur ini memiliki parameter input jumlah baris dan jumlah kolom matriks, dan pointer elemen pertama matriks
	// Prosedur ini menampilkan matriks pada layar
	
	// Kamus lokal

	int i,j;
	// Variabel untuk indeks matriks yang digunakan pada looping
	
	// Algoritma
	printf("\nTampilan Matriks\n\n");

	// Mencetak matriks
	for(i=0;i<jumlah_baris;i++){
		for(j=0;j<jumlah_kolom;j++){
			printf("%c ",*((matriks+(i*jumlah_kolom))+j));
		};
		printf("\n");
	};
};

// Prosedur Delay 
void delay(int milli_seconds) 
{ 	
	// Prosedur delay memiliki parameter input waktu delay yang diinginkan dalam milisecond(ms)
	
	// Kamus lokal

	int time = 0;

	// Variabel utk menyimpan nilai delay yang diingkinkan
	int time_delay;
	
	// Algoritma 

   	 // Menyimpan start time
    	clock_t start_time = clock();

    	// nilai delay yang diinginkan ditambahkan dengan nilai start time
   	 time_delay = start_time + milli_seconds;

	// Melakukan looping sampai delay yang dibutuhkan/diinginkan
    	while (time < time_delay){
		time = clock();
	};  
} ;

// Prosedur Animate Matriks saat ini
void Animate(int jumlah_baris, int jumlah_kolom,char *Curr_Matriks, int iterasi){
	// Prosedur ini memiliki paramter input jumlah baris, jumlah kolom, pointer ke elemen pertama matriks saat ini, dan jumlah iterasi yang akan dilakukan
	// Prosedur akan menghasilkan matriks hasil tick dan menampilkannya, proses ini dilakukan sebanyak iterasi yang telah ditentukan
	// Prosedur ini menggunakan prosedur lain(dari luar) yaitu diantaranya :
	// printMatriks untuk mencetak matriks
	// Tick untuk melakukan 1 proses iterasi
	// Delay untuk memberikan jeda(delay) antar iterasi

	// Kamus lokal
	int count = 0;
	// Variabel count sebagai counter untuk menentukan proses iterasi sudah selesai atau belum
	
	// Algoritma
	system("cls");
	// Membersihkan layar program 

	// Mencetak matriks saat ini
	printMatriks(jumlah_baris,jumlah_kolom,Curr_Matriks);
	
	// melakukan looping sampai nilai count sama dengan iterasi
	while(count<iterasi){
		// Melakukan proses tick dan mencetak hasil sebanyak iterasi sesuai dengan input prosedur
		delay(500);
		// Memberikan delay antar iterasi

		system("cls");
		// Membersihkan layar program

		// Melakukan proses tick dan mencetak matriks hasik tick
		Tick(jumlah_baris,jumlah_kolom,Curr_Matriks);
		printMatriks(jumlah_baris,jumlah_kolom,Curr_Matriks);
		
		count++;
		// Proses iterasi pertama selesai dan dilanjutkan dengan iterasi kedua ditandai dengan nilai count bertambah 1
	};
};


void menu (int *done, int *ulang, int jumlah_baris, int jumlah_kolom, char *Curr_Matriks){
	int pilihan,iterasi;
	char jawab[5];
 //setelah memasukkan nama file, maka akan ditampilkan berbagai menu seperti berikut.
	printf("\nPILIHAN MENU\n");
	printf("1. Animate\n");//pilihan ini akan menjalankan prosedur animate dengan meminta input berapa kali iterasi
	printf("2. Tick\n");//pilihan ini akan hanya menjalankan prosedur tick kemudian dikeluarkan hasilnya(1 iterasi)
	printf("3. Quit\n");//Pilihan ini akan selanjutnya dimintai file eksternal yang baru kemudian akan keluar jika tidak ingin melanjutkan
	printf("\nMasukkan pilihan menu : ");
	scanf("%d",&pilihan);
	if(pilihan == 1){//menjalankan prosedur animate
		printf("\nMasukkan banyak iterasi : ");
		scanf("%d",&iterasi);//input jumlah iterasi yang diinginkan
		Animate(jumlah_baris,jumlah_kolom,Curr_Matriks,iterasi);//memanggil fungsi animate
	}
	else{
		if(pilihan == 2){//menjalankan prosedur tick
			Tick(jumlah_baris,jumlah_kolom,Curr_Matriks);//memanggil fungsi tick
			printMatriks(jumlah_baris,jumlah_kolom,Curr_Matriks);//melakukan pencetakan
		}
		else{
			if(pilihan == 3){//akan diminta file eksternal yang baru
				printf("\nApakah ingin memasukkan file baru ? Ya/Tidak\n");//diminta apakah ingin memasukkan file baru atau tidak
				printf("Jawaban : ");
				scanf(" %s",jawab);
				while (strcmp(jawab,"Ya") != 0 && strcmp(jawab,"Tidak") != 0)//melakukan validasi input
                {
                    printf("Pilihan salah, Ulangi! \n");
                    printf("\nApakah ingin memasukkan file baru ? Ya/Tidak\n");//diminta apakah ingin memasukkan file baru atau tidak
                    printf("Jawaban : ");
                    scanf(" %s",jawab);
                }
				if(strcmp(jawab,"Ya")==0 ){//jika ingin kembali memasukkan file baru
					//free(Curr_Matriks);
					*ulang = 1;//variabel ulang tetap 1 yang artinya program akan meminta kembali file baru
				}
				else if(strcmp(jawab,"Tidak")==0)//jika tidak ingin memasukkan file baru
                {
                	*done = 1;//variabel done akan menjadi 1 yang tandanya program akan berakhir
				}
			}
			else{//apabila inputan menu salah
				printf("Masukkan pilihan menu salah, ulangi\n");
			};
		};
	};
};


