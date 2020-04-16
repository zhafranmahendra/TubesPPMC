#include "functions.h" //memasukkan library file functions untuk digunakan

int main(void){
	int jumlah_baris; //variabel untuk menyimpan jumlah baris dari matriks
	int jumlah_kolom; //variabel untuk menyimpan jumlah kolom dari matriks
	int done = 0; //variabel untuk status apakah pengguna sudah selesai menggunakan program atau belum, deklarasi awal 0 menunjukkan belum mulai menggunakan program
	int ulang = 1; //variabel untuk status apakah ingin input file baru atau tidak (kondisi awal dinyatakan 1 sebagai ingin input file baru)
	int gen = 0; //variabel untuk menandakan posisi iterasi dari matriks saat ini
	char namafile[100];//array penyimpan inputan nama file user
	char *Curr_Matriks = malloc(sizeof(char)*1*1);
  
  //tampilan awal permainan
	printf("\n");
	printf("~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'\n");
    printf("         ______                                _   _____                               __   _     _  __     \n");
    printf("        /  __ \\                              ( )     |  __ \\                             / _| | |   (_)/ _|         \n");
    printf("        | /  \\/ ___  _ ____      ____ _ _   _|/ ___  | |  \\/ __ _ _ __ ___   ___    ___ | |_  | |    _| |_ ___      \n");
    printf("        | |    / _ \\| '_ \\ \\ /\\ / / _` | | | | / __| | | __ / _` | '_ ` _ \\ / _ \\  / _ \\|  _| | |   | |  _/ _ \\     \n");
    printf("        | \\__/\\ (_) | | | \\ V  V / (_| | |_| | \\__ \\ | |_\\ \\ (_| | | | | | |  __/ | (_) | |   | |___| | ||  __/     \n");
    printf("        \\_____/\\___/|_| |_|\\_/\\_/ \\__,_|\\__, | |___/  \\____/\\__,_|_| |_| |_|\\___|  \\___/|_|   \\_____/_|_| \\___|     \n");
    printf("                                         __/ |                                                                      \n");
    printf("                                        |___/                                                                       \n");
    printf("\n");
    printf("~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'~'\n");
    program_nyala();

	while(done == 0){//selama done masih bernilai 0(tidak quit) artinya program akan terus berjalan
		if(ulang == 1){
			printf("Masukkan nama file : ");
			scanf(" %s",namafile);//inout nama file
			FILE *file;
			file = fopen(namafile,"r");//membaca file yang diinput oleh user
			while (file == NULL )//proses validasi apabila file tidak ditemukan
			{
				printf("File tidak ada, Ulangi input file!\n");//pesan kesalahan bahwa file tidak ditemukan
				printf("Masukkan nama file : ");
				scanf(" %s",namafile);//input ulang nama file
				file = fopen(namafile,"r");
			}
			char buf[MAX];
			jumlah_baris = atoi(fgets(buf,MAX,file));//membaca jumlah baris dari file eksternal kemudian merubah ke integer hasil tersebut
      			//dan disipan didalam variabel jumlah_baris. pembacaan digunakan dengan fungsi fgets yang mana akan membaca jumlah 
      			//baris yang ditulis pada seed file
			jumlah_kolom = atoi(fgets(buf,MAX,file));//membaca jumlah kolom dari file eksternal kemudian merubah ke integer hasil tersebut
     			 //dan disipan didalam variabel jumlah_kolom. pembacaan digunakan dengan fungsi fgets yang mana akan membaca jumlah kolom
      			//yang ditulis pada seed file
			free(Curr_Matriks);
			Curr_Matriks = malloc(sizeof(char)*jumlah_baris*jumlah_kolom);//memesan mempori untuk array curr_matriks sebesar jumlah baris 
      			//dan jumlah kolom
			Matriks_Input(jumlah_baris,jumlah_kolom,Curr_Matriks,file);//memanggil prosedur matriks_input
			printMatriks(jumlah_baris,jumlah_kolom,Curr_Matriks);//memanggil prosedur printMatriks
			fclose(file);//menutup file
			ulang = 0;
		};
		menu(&done,&ulang,jumlah_baris,jumlah_kolom,Curr_Matriks,&gen,namafile);//memanggil prosedur menu 
		printf("\n");
	};
	printf("Terima Kasih\n");//jika menu Quit dipilih dan tidak ingin menginput file baru
	return(0);
};
