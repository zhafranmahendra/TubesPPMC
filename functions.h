/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020  
* MODUL 9 – TUGAS BESAR  
* Kelompok   : 5  
* Hari dan Tanggal : Senin, 13 April 2018 
* Asisten (NIM)  : Meinanto Tri Yuriawan (13217021) 
* Nama File   : functions.h  
* Deskripsi   : Implementasi fungsi Tick dan count_neighbor  */ 
 
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

void Tick (int jumlah_baris, int jumlah_kolom, char *Curr_Matriks){
 char *Next_Matriks = malloc(sizeod(char)*jumlah_kolom*jumlah_baris);
 int i,j;
 for(i=0;i<jumlah_baris;i++){
  for(j=0;j<jumlah_kolom;j++){
   if(*(Curr_Matriks+(i*jumlah_kolom)+j) == 'X'){
    if(count_neighbor(jumlah_baris,jumlah_kolom,i,j,Curr_Matriks)<2){
     *(Next_Matriks+(i*jumlah_kolom)+j) = '-';
    }
    else{
      if(count_neighbor(jumlah_baris,jumlah_kolom,i,j,Curr_Matriks)>3){
       *(Next_Matriks+(i*jumlah_kolom)+j) = '-';
      }
      else{
       *(Next_Matriks+(i*jumlah_kolom)+j) = *(Curr_Matriks+(i*jumlah_kolom)+j);
      };
     };
    }
    else{
     if(count_neighbor(jumlah_baris,jumlah_kolom,i,j,Curr_Matriks)==3){
      *(Next_Matriks+(i*jumlah_kolom)+j) = 'X';
     }
     else{
      *(Next_Matriks+(i*jumlah_kolom)+j) = *(Curr_Matriks+(i*jumlah_kolom)+j);
     };
    };
  };
 };
 for(i=0;i<jumlah_baris;i++){
  for(j=0;j<jumlah_kolom;j++){
   *(Curr_Matriks+(i*jumlah_kolom)+j) = *(Next_Matriks+(i*jumlah_kolom)+j);
   free(Next_Matriks+(i*jumlah_kolom)+j);
  };
 };
};
    
 
