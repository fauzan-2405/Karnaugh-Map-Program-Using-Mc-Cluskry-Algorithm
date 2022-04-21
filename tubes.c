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

//
struct lnode {
}

//
void list_init(lnodeT **root, unsigned int id) {
}

//
void list_insert(lnodeT *root, unsigned int id) {
}

//
lnodeT * list_find(lnodeT *root, unsigned int id) {
}

//
void list_merge(lnodeT **newRoot, lnodeT *firstRoot, lnodeT *secondRoot ){
}

//
bool list_equal(lnodeT *firstRoot, lnodeT *secondRoot){
}

//
void list_print(lnodeT *root){
}


/*
	============================================================= 
	*						GRUP STUKTUR MINTERM
	============================================================= 
*/

//
//Membuat struktur data untuk grup minterm
struct mintermGroup{
	char *repr; //pointer untuk repr field
	lnodeT* root; //pointer root
	unsigned int cPosBits;
};
typedef struct mintermGroup mintermGroupT;


/*
	============================================================= 
	*					FUNGSI PEMBANTU
	============================================================= 
*/ 

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
	*					FUNGSI PEMBANDING
	============================================================= 
*/ 

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

//
void CountTerms(char *exp, int *cTerms){
}

void ReadInput(int *cMinterms,char *exp_minterms){
}

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



int main(int argc, char *argv[]){
}
