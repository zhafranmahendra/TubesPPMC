#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h> 
  
void delay(int milli_seconds) 
{ 
	int time = 0;
	int time_delay;
    // Storing start time 
    clock_t start_time = clock(); 
    // looping till required time is not achieved
    time_delay = start_time + milli_seconds;
    while (time < time_delay){
		time = clock();
	};  
} ;

int const MAX = 100;

void Matriks_Input(int jumlah_baris, int jumlah_kolom, char *MatriksInput, FILE *file){
	int i,j;
	char buf[jumlah_kolom];
	for(i=0;i<jumlah_baris;i++){
		fgets(buf,(jumlah_kolom+2),file);
		for(j=0;j<jumlah_kolom;j++){
			*((MatriksInput+(i*jumlah_kolom))+j) = buf[j];
		};
	};
};

void printMatriks(int jumlah_baris, int jumlah_kolom, char *matriks){
	int i,j;
	printf("\nTampilan Matriks\n\n");
	for(i=0;i<jumlah_baris;i++){
		for(j=0;j<jumlah_kolom;j++){
			printf("%c ",*((matriks+(i*jumlah_kolom))+j));
		};
		printf("\n");
	};
};

int count_neighbor(int jumlah_baris, int jumlah_kolom, int posisi_baris, int posisi_kolom, char *matriks){
	int count = 0;
	int i,j;
	char x;
	for (i=(posisi_baris-1);i<(posisi_baris+2);i++){
		
		for(j=(posisi_kolom-1);j<(posisi_kolom+2);j++){
			if(i == -1){
				if(j == -1){
					x = *((matriks+((jumlah_baris-1)*jumlah_kolom))+(jumlah_kolom-1));
				}
				else{
					x = *((matriks+((jumlah_baris-1)*jumlah_kolom))+(j%jumlah_kolom));
				};
			}
			else{
				if(j == -1){
					x = *((matriks+((i%jumlah_baris)*jumlah_kolom))+(jumlah_kolom-1));
				}
				else{
					x = *(matriks+(((i%jumlah_baris)*jumlah_kolom))+(j%jumlah_kolom));
				};
			};
			if(x == 'X'){
				if((i != posisi_baris) || (j != posisi_kolom)){
					count++;
				};
			};
		};
	};
	return(count);
};
		
void Tick(int jumlah_baris, int jumlah_kolom, char *Curr_Matriks){
	char *Next_Matriks = malloc(sizeof(char)*jumlah_baris*jumlah_kolom);
	int i,j;
	for(i=0;i<jumlah_baris;i++){
		for(j=0;j<jumlah_kolom;j++){
			if(*(Curr_Matriks+(i*jumlah_kolom)+j) == 'X'){
				if(count_neighbor(jumlah_baris,jumlah_kolom,i,j,Curr_Matriks) < 2){
					*((Next_Matriks+(i*jumlah_kolom))+j) = '-';
				}
				else{
					if(count_neighbor(jumlah_baris,jumlah_kolom,i,j,Curr_Matriks) > 3){
						*((Next_Matriks+(i*jumlah_kolom))+j) = '-';
					}
					else{
						*((Next_Matriks+(i*jumlah_kolom))+j) = *((Curr_Matriks+(i*jumlah_kolom))+j);
					};
				};
			}
			else{
				if(count_neighbor(jumlah_baris,jumlah_kolom,i,j,Curr_Matriks) == 3){
					*((Next_Matriks+(i*jumlah_kolom))+j) = 'X';
				}
				else{
					*((Next_Matriks+(i*jumlah_kolom))+j) = *((Curr_Matriks+(i*jumlah_kolom))+j);
				};
			};
		};
	};
	for(i=0;i<jumlah_baris;i++){
		for(j=0;j<jumlah_kolom;j++){
			*((Curr_Matriks+(i*jumlah_kolom))+j) = *((Next_Matriks+(i*jumlah_kolom))+j);
		};
	};
	free(Next_Matriks);
};

void Animate(int jumlah_baris, int jumlah_kolom,char *Curr_Matriks, int iterasi){
	int count = 0;
	system("cls"); 
	printMatriks(jumlah_baris,jumlah_kolom,Curr_Matriks);
	while(count<iterasi){
		delay(500);
		system("cls"); 
		Tick(jumlah_baris,jumlah_kolom,Curr_Matriks);
		printMatriks(jumlah_baris,jumlah_kolom,Curr_Matriks);
		count++;
	};
};

void menu (int *done, int *ulang, int jumlah_baris, int jumlah_kolom, char *Curr_Matriks){
	int pilihan,iterasi;
	char jawab[5];
	printf("\nPILIHAN MENU\n");
	printf("1. Animate\n");
	printf("2. Tick\n");
	printf("3. Quit\n");
	printf("\nMasukkan pilihan menu : ");
	scanf("%d",&pilihan);
	if(pilihan == 1){
		printf("\nMasukkan banyak iterasi : ");
		scanf("%d",&iterasi);
		Animate(jumlah_baris,jumlah_kolom,Curr_Matriks,iterasi);
	}
	else{
		if(pilihan == 2){
			Tick(jumlah_baris,jumlah_kolom,Curr_Matriks);
			printMatriks(jumlah_baris,jumlah_kolom,Curr_Matriks);
		}
		else{
			if(pilihan == 3){
				printf("\nApakah ingin memasukkan file baru ? Ya/Tidak\n");
				printf("Jawaban : ");
				scanf(" %s",jawab);
				if(strcmp(jawab,"Ya")==0){
					//free(Curr_Matriks);
					*ulang = 1;
				}
				else{
					*done = 1;
				}
			}
			else{
				printf("Masukkan pilihan menu salah, ulangi\n");
			};
		};
	};
};
	
int main(void){
	int jumlah_baris;
	int jumlah_kolom;
	int done = 0;
	int ulang = 1;
	char *Curr_Matriks = malloc(sizeof(char)*1*1);
	
	while(done == 0){
		if(ulang == 1){
			char namafile[100];
			printf("Masukkan nama file : ");
			scanf(" %s",namafile);
			FILE *file;
			file = fopen(namafile,"r");
			char buf[MAX];
			jumlah_baris = atoi(fgets(buf,MAX,file));
			jumlah_kolom = atoi(fgets(buf,MAX,file));
			free(Curr_Matriks);
			Curr_Matriks = malloc(sizeof(char)*jumlah_baris*jumlah_kolom);
			Matriks_Input(jumlah_baris,jumlah_kolom,Curr_Matriks,file);
			printMatriks(jumlah_baris,jumlah_kolom,Curr_Matriks);
			fclose(file);
			ulang = 0;
		};
		menu(&done,&ulang,jumlah_baris,jumlah_kolom,Curr_Matriks);
		printf("\n");
	};
	printf("Terima Kasih\n");
	return(0);
};
