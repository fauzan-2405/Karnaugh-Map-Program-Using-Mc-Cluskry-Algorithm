/*
	TUGAS BESAR EL2008
	Kelompok 13:
	1. Bayu Aji Nugroho 
	2. Deovie Lentera
	3. Muhammad Fauzan
	4. Muhammad Rafli Bagaskara
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
struct lnode {
}

// Rafli
void list_init(lnodeT **root, unsigned int id) {
}

// Rafli
void list_insert(lnodeT *root, unsigned int id) {
}

// Rafli
lnodeT * list_find(lnodeT *root, unsigned int id) {
}

// Rafli
void list_merge(lnodeT **newRoot, lnodeT *firstRoot, lnodeT *secondRoot ){
}

// Rafli
bool list_equal(lnodeT *firstRoot, lnodeT *secondRoot){
}

// Rafli
void list_print(lnodeT *root){
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

// BY DEFAULT DEOVIE
void CountTerms(char *exp, int *cTerms){
}

//
void ReadInput(int *cMinterms,char *exp_minterms){
}

//
void ParseInput(char *exp, mintermGroupT *mt, int cTerms, int *cVariables){
}


bool CanFormGroup(mintermGroupT firstGroup, mintermGroupT secondGroup, int cVariables){
}

void CreateNewGroupRepr(char *newGroupRepr, char *firstGroupRepr, char *secondGroupRepr, int cVariables){
}

void GetPrimeImplicants( mintermGroupT **table, bool ** termsUsed, mintermGroupT *primeImplicants, int *lenCol, int cColumns){
}

void CreatePrimeChart(bool ** primeChart, mintermGroupT* minterms, int cMinterms, mintermGroupT * primeImplicants, int cPrimeImplicants){
}

void GetEssentialImplicants(bool ** primeChart, int cPrimeImplicants, int cMinterms, bool * isEssential ){
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
	printf("Masukkan minterm yang akan diminimisasi/n");
	printf("Contoh masukan: 0,1,2,5,7,9");

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

	/* // Alokasikan memori untuk array mintermsToCover dan isi array tersebut
	mintermsCovered = (bool *)calloc( cMinterms, sizeof(bool) );
	for( i = 0; i < cPrimeImplicants; i++){
		if( isEssential[i] ){
			for( j = 0; j < cMinterms; j++)
				if( primeChart[i][j] )
					mintermsCovered[j] = 1;
		}
	} */


	// Print Hasil yang didapatkan
	// Print kolom
	printf("\n\n");
	for(j = 0; j <= cColumns; j++){
		printf("############### COLUMN %d ###############\n",j);
		for(i = 0; i < lenCol[j]; i++){
			printf("[ ");
			list_print( table[j][i].root );
			printf("]  %s  %s\n", table[j][i].repr, (termsUsed[j][i] ? "OK" : " *") );
		}
		printf("\n\n");
	}
	
	// Print prime implicant
	printf("############### PRIME IMPLICANTS ###############\n\n");
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
	printf("\n\n############### ESSENTIAL PRIME IMPLICANTS ###############\n\n");
	for(i = 0; i < cPrimeImplicants; i++){
		if( isEssential[i] ){
			printf("[P%2d]: %s  [ ", i, primeImplicants[i].repr);
			list_print( primeImplicants[i].root );
			printf(" ]\n");
		}
	}


	return 0;
}
