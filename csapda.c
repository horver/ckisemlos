#include "csapda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Faj *createEmptyFaj(void)
{
    Faj *newFaj = (Faj*)malloc(sizeof(Faj));
    return newFaj;
}

Csapda *createEmptyCsapda(void)
{
    Csapda *newCsapda = (Csapda*)malloc(sizeof(Csapda));
    newCsapda->hiba = SUCCESS;
    return newCsapda;
}

CsapdaNode *createCsapdaNode(Csapda *csapda)
{
    CsapdaNode *newCsapdaNode = (CsapdaNode*)malloc(sizeof(CsapdaNode));
    if(csapda)
        newCsapdaNode->csapda = *(csapda);
    newCsapdaNode->next = NULL;
    return newCsapdaNode;
}

void destroyCsapdaList(CsapdaNode *list)
{
	if(list->next)
		destroyCsapdaList(list->next);
    free(list);
}


CsapdaNode *insertCsapda(CsapdaNode *list, Csapda *csapda)
{
    CsapdaNode *newCsapdaNode;

    if(!list)
        return NULL;

    newCsapdaNode = createCsapdaNode(csapda);

    if(list->next==NULL)
        list->next = newCsapdaNode;
    else{
        CsapdaNode *it = list;
        while(it->next)
            it = it->next;
        it->next = newCsapdaNode;
    }

    return list;
}

int getCsapdaListSize(CsapdaNode *list)
{
    int count = 0;
    CsapdaNode *it = list->next;
    while(it)
    {
        count++;
        it = it->next;
    }
    return count;
}

CsapdaNode *readCsapdakFajok(CsapdaNode *list, const int csapdaNum, FILE *fp)
{
    int i, j; //I for fajs, j for csapdas
	char buffer[255], nameBuffer[4];

    if(!fp)
        return NULL;

    for(j=0; j<csapdaNum; ++j)
    {
        Csapda *tmpCsapda = createEmptyCsapda();
		//fgets(buffer, 255, fp);
		fscanf(fp, "%d", &(tmpCsapda->id));
        for(i=0; i<MAX_MONTHS; ++i)
        {
            Faj *tmpFaj = createEmptyFaj();
			tmpFaj->fogasszam = 1;
            fscanf(fp, "%s", nameBuffer);
			if(strcmp(nameBuffer, "0"))
				strcpy(tmpFaj->name, nameBuffer);
			if(!strcmp(nameBuffer, "0"))
			{
				tmpFaj->fogasszam = 0;
				strcpy(tmpFaj->name, "NON");
			}				
            //Handle for error codes
            if (!strcmp(tmpFaj->name, "CSH"))
                tmpCsapda->hiba = CSH;
            if (!strcmp(tmpFaj->name, "LCS"))
                tmpCsapda->hiba = LCS;
            if (!strcmp(tmpFaj->name, "KSZ"))
                tmpCsapda->hiba = KSZ;
            if (!strcmp(tmpFaj->name, "R"))
                tmpCsapda->hiba = R;
            tmpCsapda->fajok[i] = *(tmpFaj);
        }
        list = insertCsapda(list, tmpCsapda);
    }

    return list;
}

CsapdaNode *readCsapdakFogasok(CsapdaNode *list, const int csapdaNum, FILE *fp, char nameBuffer[4])
{
    int i, j; //I for fajs, j for csapdas

    if(!fp)
        return NULL;

	for(j=0; j<csapdaNum; ++j)
    {
        Csapda *tmpCsapda = createEmptyCsapda();
		fscanf(fp, "%d", &(tmpCsapda->id));
        for(i=0; i<MAX_MONTHS; ++i)
        {
            Faj *tmpFaj = createEmptyFaj();
			strcpy(tmpFaj->name, nameBuffer);
			fscanf(fp, "%d", &(tmpFaj->fogasszam));
			if(tmpFaj->fogasszam==-1)
				tmpCsapda->hiba = CSH;
			if(tmpFaj->fogasszam==-2)
				tmpCsapda->hiba = LCS;
			if(tmpFaj->fogasszam==-3)
				tmpCsapda->hiba = KSZ;
			if(tmpFaj->fogasszam==-4)
				tmpCsapda->hiba = R;
            tmpCsapda->fajok[i] = *(tmpFaj);
        }
        list = insertCsapda(list, tmpCsapda);
    }

    return list;
}

void printCsapda(Csapda *csapda)
{
    int i;
    printf("%d ", csapda->id);
    for(i=0; i<MAX_MONTHS; ++i)
        printf("%s ", csapda->fajok[i].name);
    printf("\n");
}

void printCsapdaSzam(Csapda *csapda)
{
	int i;
    printf("%d %s ", csapda->id, csapda->fajok[0].name);
    for(i=0; i<MAX_MONTHS; ++i)
        printf("%d ", csapda->fajok[i].fogasszam);
    printf("\n");
}

void printCsapdaList(CsapdaNode *list, MODES mode)
{
    CsapdaNode *it = list->next;
    while(it)
    {
		mode?printCsapdaSzam(&(it->csapda)):printCsapda(&(it->csapda));
        it = it->next;
    }
}
