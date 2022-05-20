/*
	TUGAS BESAR EL2008
	Kelompok 13:
	1. Bayu Aji Nugroho 
	2. Deovie Lentera
	3. Muhammad Fauzan
	4. Muhammad Rafli Fadilah Yusmar
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DELIMITER ','
#define PARSE_DELIMETERS " ,"

#define EXPRESSION_MAX_LENGTH 1001

#define VARIABLES_MAX 20

typedef char bool;

// LIST FUNGSI DAN PROSEDUR YANG AKAN DIGUNAKAN

/*	
	============================================================= 
	*			IMPLEMENTASI LIST/TABEL YANG DIURUT
	============================================================= 
*/

// Rafli
// Membuat Struktur data untuk lnode
struct lnode {
	unsigned int id;
	struct lnode * next;
	struct lnode * prev;
};
typedef struct lnode lnodeT;    // Nama baru untuk tipe data struct lnod


// Rafli
// Memasukkan minterms ke dalam list
void list_init(lnodeT **root, unsigned int id) {
	 // Alokasi dan inisialisasi node baru
    	lnodeT *newElement = (lnodeT *)malloc( sizeof(lnodeT) );
	newElement->id = id;
	newElement->next = newElement->prev = NULL;

	*root = newElement;
}

// Rafli
void list_insert(lnodeT *root, unsigned int id) {
	// Alokasi dan inisialisasi node baru
	lnodeT *newElement = (lnodeT *)malloc( sizeof(lnodeT) );
	newElement->id = id;
	newElement->next = newElement->prev = NULL;

	// Temukan posisi yang sesuai untuk menyisipkan newElement
	lnodeT * curr = root;
	while(curr->next != NULL)
		if(curr->next->id > newElement->id)
			break;

		curr = curr->next;  // Jika keadaan di atas belum dipenuhi
}

// Rafli
lnodeT * list_find(lnodeT *root, unsigned int id) {
	lnodeT * curr = root;

	while( curr != NULL ){
		// Jika nod id yang sekarang sama dengan id yang kita cari, maka:
		if( curr->id == id ){
			return curr;
		}
		curr = curr->next;
	}

	return NULL;
}

// Rafli
void list_merge(lnodeT **newRoot, lnodeT *firstRoot, lnodeT *secondRoot ){
	list_init(newRoot, firstRoot->id );

	// Sisipkan semua nod dari list pertama
	lnodeT *curr = firstRoot->next;
	while( curr != NULL ){
		list_insert( *newRoot, curr->id );
		curr = curr->next;
	}

	// Sisipkan semua nod dari list kedua
	curr = secondRoot;
	while( curr != NULL ){
		list_insert( *newRoot, curr->id );
		curr = curr->next;
	}
}

// Rafli
bool list_equal(lnodeT *firstRoot, lnodeT *secondRoot){
	lnodeT *fNode = firstRoot;
	lnodeT *sNode = secondRoot;
	while( fNode != NULL ){
		// Jika list tidak sama
		if(fNode->id != sNode->id)
			return 0;

		fNode = fNode->next;
		sNode = sNode->next;
	}
	// Jika list sama
	return 1;
}

// Rafli
void list_print(lnodeT *root){
	lnodeT *curr = root;
	while(curr != NULL){
		printf("%2d ",curr->id);
		curr = curr->next;
	}
}


/*
	============================================================= 
	*			GRUP STUKTUR MINTERM
	============================================================= 
*/

// Mas Bayu
//Membuat struktur data untuk grup minterm
struct mintermGroup{
	char *repr; //pointer untuk repr field
	lnodeT* root; //pointer root
	unsigned int cPosBits;
};
typedef struct mintermGroup mintermGroupT;


/*
	============================================================= 
	*			FUNGSI PEMBANTU
	============================================================= 
*/ 

// Mas Bayu
//Menentukan nilai mana yang lebih besar (a atau b)
int max(int a,int b){
	if (a>b) //jika a lebih besar dari b
        return a; //kembali ke a
    else //jika a lebih kecil dari b
        return b; //kembali ke b
}

//Mengubah nilai biner pada Kmap
void StrReverse(char *s){
	int low = 0; //nilai awal 0
	int high = strlen(s) - 1; //menentukan nilai high dari panjang karakter s dikurangi 1
	while(low < high){ //fungsi akan berulang ketika low lebih kecil dari high
		char c = s[low];
		s[low] = s[high];
		s[high] = c;
        //ketika low > high, maka:
		low++;high--; 
	}
}


/*
	============================================================= 
	*		FUNGSI PEMBANDING UNTUK QSORT
	============================================================= 
*/ 

// Mas Bayu
//Fungsi CompareMintermByRepr
int CompareMintermsByRepr( const void *a , const void * b){
    //mengisi nilai mintermGroupT 1 dan 2 ke a dan b
	mintermGroupT *first  = (mintermGroupT *)a;
	mintermGroupT *second = (mintermGroupT *)b;

	if( first->cPosBits == second->cPosBits ){ //jika nilai 1 dan 2 cPosbits sama
        //maka kembali ke:
		return strcmp( first->repr, second->repr ); 
	}
    //jika tidak sama maka kembali ke:
	return (first->cPosBits - second->cPosBits);
}

//Fungsi CompareMintermById
int CompareMintermsById( const void * a, const void * b){
    //mengisi nilai 1 dan 2 mintermgrup ke a dan b
	mintermGroupT * first  = (mintermGroupT *)a;
	mintermGroupT * second = (mintermGroupT *)b;
    //setelah isi kembali ke:
	return ( first->root->id - second->root->id);
}

/*
	============================================================= 
	*					FUNGSI FUNDAMENTAL
	============================================================= 
*/

// Rafli
void CountTerms(char *exp, int *cTerms){
	 *cTerms = 1;

	char *ptr = strchr(exp,DELIMITER);
	while(ptr != NULL){
		(*cTerms)++;    // Inkremen cTerms

		ptr = strchr(ptr + 1, DELIMITER);
	}
}

// Rafli
void ReadInput(int *cMinterms,char *exp_minterms){

	char printfFormat[15];
	sprintf(printfFormat,"%%%d[^\n]s",EXPRESSION_MAX_LENGTH - 1);

	printf("Masukkan minterm yang akan diminimisasi:\n\t>> ");    // Masukkan minterms yang ingin diproses
	scanf(printfFormat, exp_minterms);

	// Hitung terms yang dimasukkan oleh user
	CountTerms(exp_minterms, cMinterms);
}

// Deovie
void ParseInput(char *exp, mintermGroupT *mt, int cTerms, int *cVariables){
	int i,j;			//inisialisasi variable untuk for loop
	int maxMinterm = 0;		//inisialisasi untuk mencari minterm terbesar
	
	char * pch = strtok(exp, PARSE_DELIMETERS);
	for(i = 0; i < cTerms; i++){

		mt[i].cPosBits = 0;		//inisialisasi ke 0
		
		mt[i].root = NULL;		
		int id = atoi(pch);
		list_init(&mt[i].root, id);		//memasukkan minterm ke dalam list
		
		maxMinterm = max(maxMinterm, id );		//untuk mencari minterm max
		
		char *binaryRepr = (char *)malloc( (VARIABLES_MAX + 1) * sizeof(char) );	//mengubah minterm dari angka ke binary
		for(j = 0; j < VARIABLES_MAX; j++){		//binary yang dibuat akan terkonstruksi secara terbalik
			if( (id & (1 << j) ) != 0){
				binaryRepr[j] = '1';
				mt[i].cPosBits++;
			}
			else{
				binaryRepr[j] = '0';
			}
		}
		binaryRepr[VARIABLES_MAX] = '\0';		//untuk menandakan akhir dari str
		
		mt[i].repr = (char *)malloc( (VARIABLES_MAX + 1) * sizeof(char) );	//malloc biasa utk membuat tempat utk variable
		strcpy(mt[i].repr, binaryRepr);		//meng-copy nilai binary dari minterm ke repr
		
		if(i < cTerms - 1){		//lanjut mencari minterm selanjutnya
			pch = strtok(NULL, PARSE_DELIMETERS);
		}
	}
	
	(*cVariables) = 0;
	int binary = 1;
	while( maxMinterm > (binary - 1) ){		//untuk menghitung jumlah variable yang ada
		binary = binary * 2;
		(*cVariables)++;
	}
	
	for(i = 0; i < cTerms; i++){		//digunakan realloc untuk menghemat memory, kalau bisa
		mt[i].repr = (char *)realloc( mt[i].repr , (*cVariables + 1) * sizeof(char) );
		mt[i].repr[ *cVariables ] = '\0';
		StrReverse( mt[i].repr );
	}
}

bool CanFormGroup(mintermGroupT firstGroup, mintermGroupT secondGroup, int cVariables){		//digunakan untuk membuat group minterm
	int i, bitsDiffer = 0;
	for(i = 0; i < cVariables; i++){	//for loop biasa untuk mengiterasi isi dari group
		if( (firstGroup.repr[i] == '-' && secondGroup.repr[i] != '-') ||	//apabila kedua group memiliki posisi '-' yang berbeda
			(firstGroup.repr[i] != '-' && secondGroup.repr[i] == '-') ){	//maka fungsi selesai
				return 0;
		}
	
		if( firstGroup.repr[i] != secondGroup.repr[i] ){	//apabila kedua group punya bit yang berbeda (kecuali '-') di posisi yang sama
			bitsDiffer++;									//maka variable bitsDiffer akan ditambah 1
		}
	}
	
	return (bitsDiffer == 1) ? 1 : 0;	//apabila hanya terdapat 1 bit yang berbeda, return 1, klo tidak return 0
}

void CreateNewGroupRepr(char *newGroupRepr, char *firstGroupRepr, char *secondGroupRepr, int cVariables){	//digunakan untuk membuat group representative baru
	int i;
	for(i = 0; i < cVariables; i++){
		if( firstGroupRepr[i] == secondGroupRepr[i] ){	//apabila kedua bit dari group repr pertama dan kedua sama,
			newGroupRepr[i] = firstGroupRepr[i];		//maka element group baru pada index i akan memiliki nilai yang sama juga
		}
		else{
			newGroupRepr[i] = '-';						//kalau tidak, maka element dari group baru pada index i akan berupa '-'
		}
	}
	newGroupRepr[cVariables] = '\0';	//untuk menandakan akhir dari str
}

void GetPrimeImplicants( mintermGroupT **table, bool ** termsUsed, 
						mintermGroupT *primeImplicants, int *lenCol, int cColumns){	//untuk mendapatkan array prime implicant dari tabel
	int index = 0;
	int i,j;
	
	for( i = 0; i <= cColumns; i++){		//nested for loop biasa untuk mendapatkan prime implicant dari tabel
		for( j = 0; j < lenCol[i]; j++){
			if( !termsUsed[i][j] ){
				primeImplicants[index] = table[i][j]; 	//mengisi array prime implicant dengan nilai dari tabel
				index++;
			}
		}
	}
}

void CreatePrimeChart(bool ** primeChart, mintermGroupT* minterms, int cMinterms,
					mintermGroupT * primeImplicants, int cPrimeImplicants){			//untuk membuat chart dari prime implicant
	int i,j, mintermId;
	lnodeT * curr;
	for(i = 0; i < cPrimeImplicants; i++){
		j = 0;
		
		curr = primeImplicants[i].root;
		while(curr != NULL){
			
			/* Find the appropriate cell */
			mintermId = minterms[j].root->id;
			while( mintermId < (curr->id) ){
				j++;
				mintermId = minterms[j].root->id;
			}
			
			/* The i-th primeImplicant covers the j-th minterm */
			primeChart[i][j] = 1;
			
			curr = curr->next;
		}
	}
}

void GetEssentialImplicants(bool ** primeChart, int cPrimeImplicants, int cMinterms, bool * isEssential ){		//fungsi untuk mengambil implicants2 yang penting saja (prime implicant yg tidak dibuang)
	int i,j;
	int nextEssential;
	
	for(j = 0; j < cMinterms; j++){ 	//loop semua kolom dari minterm
		nextEssential = -1;
		for(i = 0; i < cPrimeImplicants; i++){ 		//loop semua prime implicant yang ada
			if( primeChart[i][j] == 1 ){
				if(nextEssential == -1){
					nextEssential = i;		//menukar nilai nextEssensial dengan nilai i dari loop
				}
				else{						//fungsi akan selesai apabila variable nextEssensial tidak bernilai -1
					nextEssential = -1;		//nextEssensial akan diset nilainya ke -1 terlebih dahulu lalu fungsi di-break
					break;
				}
			}
		}
		
		if(nextEssential != -1){	
			isEssential[nextEssential] = 1;
		}
	}
}


// Ojan
int main(int argc, char *argv[]){
	// Inisiasi Variabel
	mintermGroupT *table[VARIABLES_MAX + 1]; // Array dari kolom
	mintermGroupT *primeImplicants;
	mintermGroupT *minterms;	// Array dari minterms yang sudah diurut

	bool *termsUsed[VARIABLES_MAX + 1];  // Array 2d boolean yg berisi minterm yang sudah dipakai
	bool **primeChart; 	// Array 2d boolean yang memegang di [i,j] jika prime implicant
						// implicant ke-i dapat meng-cover minterm ke-j
	bool *isEssential;	// Array boolean yang memegang di [i] apakah prime implicant
						// ke -i merupakan essential prime implicant atau tidak
	bool *mintermsCovered;	// Array boolean yang menyimpan nilai 1 di [i] jika 
							// minterm ke-i harus di-cover oleh selain essential prime implicant


	int lenCol[VARIABLES_MAX]; // Ukuran kolom
	int cVariables; // Jumlah variabel dari minterm yang dimasukkan
	int cMinterms; // Jumlah minterm
	int cColumns; // Jumlah kolom
	int cPrimeImplicants; // Jumlah prime implicant 

	printf("===================================================================\n");
	printf("SELAMAT DATANG DI PROGRAM LOGIC MINIMIZATION DENGAN ALGORITMA QMC\n");
	printf("Contoh masukan: 0,1,2,5,7,9\n");

	// Input string
	char exp_minterms[EXPRESSION_MAX_LENGTH];

	ReadInput(&cMinterms, exp_minterms);

	// Alokasikan memori untuk array minterms dan table
	table[0] = (mintermGroupT *) malloc( cMinterms * sizeof(mintermGroupT));
	lenCol[0] = cMinterms;
	minterms = (mintermGroupT *)  malloc( cMinterms * sizeof(mintermGroupT));

	// Parse input minterms dari tanda koma ","
	ParseInput(exp_minterms, minterms, cMinterms, &cVariables);

	// Urutkan minterm
	qsort(minterms, cMinterms, sizeof(mintermGroupT), CompareMintermsById);
	
	// Copy isi minterms ke table[0] dan sort table[0]
	memcpy( table[0], minterms, lenCol[0] * sizeof(mintermGroupT));
	qsort( table[0], cMinterms, sizeof(mintermGroupT), CompareMintermsByRepr);

	cPrimeImplicants = 0;

	// Alokasikan memori dan inisialisasi nilai 0 pada kolom array  boolean
	termsUsed[0] = (bool*) calloc(lenCol[0], sizeof(bool));

	int i,j;
	for (i = 0; i <=cVariables; i++) {
		// Alokasikan memori untuk kolom slenajutnya
		mintermGroupT *nextCol = (mintermGroupT*) malloc(lenCol[i] * lenCol[i] * sizeof(mintermGroupT));

		int nextColPos = 0;
		for (j = 0; j < lenCol[i]; j++) {
			int k = j + 1;

			// Jika ada minterm yang memiliki jumlah "1" yang sama pada bentuk binary
			// nya, maka akan dilewatkan
			while (k < lenCol[i] && table[i][k].cPosBits == table[i][j].cPosBits) {
				k++;
			}

			while (k < lenCol[i] && (table[i][k].cPosBits - table[i][j].cPosBits) == 1) {
				// Cek apakah 2 grup dapat digabung menjadi grup yang lebih besar
				if (CanFormGroup( table[i][k], table[i][j], cVariables)) {

					// Cek apakah grup baru tersebut sebenarnya telah dibuat
					lnodeT * newGroupRoot;
					list_merge(&newGroupRoot, table[i][j].root, table [i][k].root);
					bool alreadyInColumn = 0;
					int c;

					for ( c = 0; c< nextColPos; c++) {
						if (list_equal(nextCol[c].root, newGroupRoot) != 0) {
							alreadyInColumn = 1;
							break;
						}
					}

					if (! alreadyInColumn) {
						// Update
						nextCol[nextColPos].root = newGroupRoot;
						nextCol[nextColPos].cPosBits = table[i][j].cPosBits;

						nextCol[nextColPos].repr = (char*) malloc((cVariables + 1) * sizeof(char));
						CreateNewGroupRepr (nextCol[nextColPos].repr, table[i][j].repr, table[i][k].repr, cVariables);

						nextColPos++;
					}

					// Tandai grup yang telah digunakan
					termsUsed[i][j] = termsUsed[i][k] = 1;
				}
				k++;
			}
		}

		lenCol[i+1] = nextColPos;

		// Hitung terms yang tidak digunakan (berarti prime Implicant)
		for (j = 0; j < lenCol[i]; j++) {
			if (!termsUsed[i][j]) {
				cPrimeImplicants++;
			}
		}
		
		// Grup yang tidak dapat digabung ke grup yang lebih besar
		if (lenCol[i+1] == 0){
			break;
		}

		// Alokasikan memori ke kolom selanjutnya dan copy terms
		table[i+1] = (mintermGroupT*) malloc(lenCol[i+1] * sizeof(mintermGroupT));
		for (j =0; j <lenCol[i+1]; j++) {
			table[i+1][j] = nextCol[j];
		}

		//Alokasikan memori dan inisialisasi nilai 0 ke kolom-i array boolean
		termsUsed[i+1] = (bool* ) calloc( lenCol[i+1], sizeof(bool));

		free(nextCol);
	}

	cColumns = i;

	// Alokasikan memori untuk array primeImplicants dan simpan nilai Prime Implicants
	primeImplicants = (mintermGroupT *) malloc(cPrimeImplicants * sizeof(mintermGroupT));
	GetPrimeImplicants (table, termsUsed, primeImplicants, lenCol, cColumns);

	// Alokasikan memori untuk array primeChart dan bentuk chart
	primeChart = (bool**) malloc (cPrimeImplicants * sizeof(bool*));
	for (i=0; i < cPrimeImplicants; i++) {
		primeChart[i] = (bool*) calloc(cMinterms, sizeof(bool));
	}
	CreatePrimeChart(primeChart, minterms, cMinterms, primeImplicants, cPrimeImplicants);

	// Alokasikan memori untuk array isEssential dan simpan nilai essential prime implicant
	isEssential = (bool*) calloc(cPrimeImplicants, sizeof(bool));
	GetEssentialImplicants (primeChart, cPrimeImplicants, cMinterms, isEssential);

	// Alokasikan memori untuk array mintermsToCover dan isi array tersebut
	mintermsCovered = (bool *)calloc( cMinterms, sizeof(bool) );
	for( i = 0; i < cPrimeImplicants; i++){
		if( isEssential[i] ){
			for( j = 0; j < cMinterms; j++)
				if( primeChart[i][j] )
					mintermsCovered[j] = 1;
		}
	} 


	// Print Hasil yang didapatkan
	// Print Tabel sesuai langkah QMC algorithm
	printf("\n\n");
	for(j = 0; j <= cColumns; j++){
		printf("############### TABEL %d ###############\n",j+1);
		for(i = 0; i < lenCol[j]; i++){
			printf("[ ");
			list_print( table[j][i].root );
			printf("]  %s  %s\n", table[j][i].repr, (termsUsed[j][i] ? "OK" : " *") );
		}
		printf("\n\n");
	}
	
	// Print prime implicant
	printf("############### PRIME IMPLICANT ###############\n\n");
	for(i = 0; i < cPrimeImplicants; i++){
		printf("[P%2d]: %s  [ ", i, primeImplicants[i].repr);
		list_print( primeImplicants[i].root );
		printf(" ]\n");
	}
	
	// Print Prime Implicant chart
	printf("\n\n############### PRIME CHART ###############\n\n");
	printf("        ");
	for(j = 0; j < cMinterms; j++){
		printf("| %2d", minterms[j].root->id );
	}
	printf("|\n---------");
	for(j = 0; j < cMinterms; j++){
		printf("----");
	}
	printf("\n");
	
	for(i = 0; i < cPrimeImplicants; i++){
		printf("[P%2d]:  ", i);
		for(j = 0; j < cMinterms; j++){
			printf("|  %c", ( primeChart[i][j] ) ? 'X' : ' ');
		}
		printf("|\n");
	}
	
	// Print essential prime implicant
	printf("\n\n############### ESSENTIAL PRIME IMPLICANT ###############\n\n");
	for(i = 0; i < cPrimeImplicants; i++){
		if( isEssential[i] ){
			printf("[P%2d]: %s  [ ", i, primeImplicants[i].repr);
			list_print( primeImplicants[i].root );
			printf(" ]\n");
		}
	}

	printf("\nHasil = ");
	for(i = 0; i < cPrimeImplicants; i++){
		if( isEssential[i] ){
			for (int k = 0; k < strlen(primeImplicants[i].repr); k++) {
				if  (primeImplicants[i].repr[k] == '1') {
					printf("x[%d]", k);
				}
				else if  (primeImplicants[i].repr[k] == '0') {
					printf("x'[%d]", k);
				}

				else {
					printf("");
				}	
			}
			if (i < cPrimeImplicants - 1) {
				printf(" + ");
			}
			
			
		}
		
	}

	return 0;
}
