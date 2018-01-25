/************
* csapda.h - header file of csapda struct, csapdalist and they funcs
* I like mixed angol ><
************/

#ifndef CSAPDA_H
#define CSAPDA_H

#include <stdio.h>

#define MAX_MONTHS 5 //This contains how many months we have, also this is the number of days in a sample

/*
Csapdas error codes:
SUCCESS : csapda was success
CSH: csapdahiba, a mechanical problem, etc
LCS: lecsapodódott
KSZ: kiszökött
R: predáció
*/
typedef enum ERROR {SUCCESS, CSH, LCS, KSZ, R} ERROR;

//Months of sampling, always these five:
typedef enum MONTH {JULIUS, AUGUSZTUS, SZEPTEMBER, OKTOBER, NOVEMBER} MONTH;

typedef enum MODES {FAJ, FOGAS} MODES;

/**
A faj struct
id: no reason for it.
fogasszam: num of captures+recaptures
name: 3 char
*/
typedef struct {
    int id;
    unsigned int fogasszam;
    char name[4];
}Faj;

/**
A csapda struct
id: num of csapda 1-n, n=kvadrat size
fajok: a csapda has a faj for every day/month
hiba: has the csapda any problem
*/
typedef struct {
    int id;
    Faj fajok[MAX_MONTHS];
    ERROR hiba;
}Csapda;

/**
CsapdaNode is a node of a linked list which contains csapdák
*/
typedef struct CsapdaNode {
    Csapda csapda;
    struct CsapdaNode *next;
}CsapdaNode;

/**Creates an empty faj
returns: a pointer of a new faj in da memory
*/
Faj *createEmptyFaj(void);
/**Creates an empty csapda
returns: a pointer of a new csapda in da memory
*/
Csapda *createEmptyCsapda(void);
/**
Creates an element of the linked list
returns: a pointer of a new csapda node in the memory
*/
CsapdaNode *createCsapdaNode(Csapda *csapda);
/**
Destroys the csapda list
*/

void destroyCsapdaList(CsapdaNode *list);
/**
Inserts a new csapda node with csapda to the back of the list.
returns: the pointer of the list's head
*/
CsapdaNode *insertCsapda(CsapdaNode *list, Csapda *csapda);
/**
Gets the number of elements in csapda list
returns: element number
*/
int getCsapdaListSize(CsapdaNode *list);
/**
Read a row from the file into the list
returns: the pointer of the list's head
*/
CsapdaNode *readCsapdakFajok(CsapdaNode *list, const int csapdaNum, FILE *fp);
CsapdaNode *readCsapdakFogasok(CsapdaNode *list, const int csapdaNum, FILE *fp, char nameBuffer[4]);
/**
Prints out the data fo a csapda
*/
void printCsapda(Csapda *csapda);
void printCsapdaSzam(Csapda *csapda);
/**
Prints out the list of csapdak
*/
void printCsapdaList(CsapdaNode *list, MODES mode);

#endif // CSAPDA_H
