#ifndef STATISTICS_H
#define STATISTICS_H

#include "kvadrat.h"
#include "map.h"
#include <math.h>

/**
Egy bizonyos faj száma egy csapdában.
*/
int numFajInCsapda(const char* faj, Csapda *csapda)
{
    int i, count = 0;
    for(i=0; i<MAX_MONTHS; ++i)
		if(csapda->fajok[i].fogasszam>0)
			count += !strcmp(csapda->fajok[i].name, faj);
    return count;
}
/**
Egy bizonyos faj száma egy kvadrátban.
*/
int numFajInKvadrat(const char* faj, Kvadrat *kvadrat)
{
    int i, count = 0;
    CsapdaNode *it = kvadrat->csapdaList->next;
    for(i=0; i<kvadrat->size; ++i)
    {
        while(it)
        {
            count += numFajInCsapda(faj, &(it->csapda));
            it = it->next;
        }
    }
    return count;
}
/**
Egy bizonyos faj összes száma az egész területen
*/
int numFaj(const char* faj, KvadratNode *list)
{
    int count = 0;
    KvadratNode *it = list->next;
    while(it)
    {
        count += numFajInKvadrat(faj, &(it->kvadrat));
        it = it->next;
    }
    return count;
}

/**
Mely fajok fordultak elő egy kvadráton belül.
*/
char *fajElofordulasInKvadrat(Kvadrat *kvadrat)
{
    char buffer[5];
	char occerrence[2048];
    int i;
    CsapdaNode *it = kvadrat->csapdaList->next;
	memset(occerrence, 0, sizeof(occerrence));
    while(it)
    {
        for(i=0; i<MAX_MONTHS; ++i)
        {
			if(it->csapda.hiba==SUCCESS && it->csapda.fajok[i].fogasszam>0)
			{
				strcpy(buffer, it->csapda.fajok[i].name);
				strcat(buffer, " ");
				 if(!strstr(occerrence, buffer)) //occerrence not has fajok.name
					strncat(occerrence, buffer, 5);
			}				
        }
        it = it->next;
    }
    //occerrence[strlen(occerrence)+1] = '\0';
	
    return occerrence;
}

/** 
The occerrence of a char in a string
*/
/*int charOccerrence(const char *str, char c)
{
    char *it=str;
    int occ = 0;

    if(!str)
        return 0;

    while(*(it))
    {
        occ += ((*it)==c);
        it++;
    }

    return occ;
}*/

/**
Legtöbbször megfogott faj megkeresése adott kvadrátban
*/
char* maxFajInKvadrat(Kvadrat *kvadrat, int *max)
{
    int i;
    char *fajok = fajElofordulasInKvadrat(kvadrat);
    char *faj = strtok(fajok, " ");
    char *maxFaj;
	//int numberOfFajok = (strlen(fajok)-charOccerrence(fajok, ' '))/3; //How many faj in fajok
	//int *sumOfFajok = (int*)malloc(sizeof(int)*numberOfFajok); //We store here the fogasszam for max search maps faj to int
    CsapdaNode *it = kvadrat->csapdaList->next;
	Map *fajMap  = createMap();	
    
	while(faj)
    {
        fajMap = setMap(fajMap, faj, 0);
        faj = strtok(NULL, " ");
    }
	    
    while(it)
    {
        for(i=0; i<MAX_MONTHS; ++i)
        {
			if(it->csapda.fajok[i].fogasszam>0)
				fajMap = setMap(fajMap, it->csapda.fajok[i].name, getMapValue(fajMap, it->csapda.fajok[i].name)+1);
        }
        it = it->next;
    }

	printf("Number of occurrences by fajs: ");
	printMap(fajMap);
	printf("\n");

    maxFaj = getMapMaxValue(fajMap, max);
	destroyMap(fajMap);
    
	return maxFaj;
}
/**
Adott kvadrátban legtöbbször megfogott faj kiírása
*/
void printMostCapturedFajs(KvadratNode *kvadratList)
{
	KvadratNode *it = kvadratList->next;
	int max;
	while(it)
	{
		char *maxFaj = maxFajInKvadrat(&(it->kvadrat), &max);
		printf("In kvadrat: %c, the most occurrected faj is: %s with %d captures.\n\n", it->kvadrat.kvadratkod, maxFaj, max);
		it = it->next;
	}
}

/**
Az összes fogás meghatározása a kvadrátban
*/
int getNumCaptures(Kvadrat *kvadrat)
{
	int count = 0, i;
	CsapdaNode *it = kvadrat->csapdaList->next;
	while(it)
	{
		for(i=0; i<MAX_MONTHS; ++i)
			count += it->csapda.fajok[i].fogasszam;
		it = it->next;
	}
	/*char *fajok = fajElofordulasInKvadrat(kvadrat);
	char *faj = strtok(fajok, " ");
	while(faj)
	{
		count += numFajInKvadrat(faj, kvadrat);
		faj = strtok(NULL, " ");
	}*/
	
	return count;
}
/**
Az összes fogás meghatározása a területen
*/
int getNumAllCaptures(KvadratNode *kvadratList)
{
	int count = 0;
	KvadratNode *it = kvadratList->next;
	while(it)
	{
		count += getNumCaptures(&(it->kvadrat));
		it = it->next;
	}
	
	return count;
}
void printNumCaptures(KvadratNode *kvadratList)
{
	KvadratNode *it = kvadratList->next;
	while(it)
	{
		printf("In kvadrat: %c, we captured %d animals.\n\n", it->kvadrat.kvadratkod, getNumCaptures(&(it->kvadrat)));
		it = it->next;
	}
}
/**
Aktív csapdák száma a kvadrátban
*/
int getActiveCsapdak(Kvadrat *kvadrat)
{
	int count = 0;
	CsapdaNode *it = kvadrat->csapdaList->next;
	while(it)
	{
		count += (it->csapda.hiba==SUCCESS);
		it = it->next;
	}
	
	return count;
}
/**
Inaktív csapdák száma a kvadrátban
*/
int getInactiveCsapdak(Kvadrat *kvadrat)
{
	int count = 0;
	CsapdaNode *it = kvadrat->csapdaList->next;
	while(it)
	{
		count += (it->csapda.hiba!=SUCCESS);
		it = it->next;
	}
	
	return count;
}
/**
Állatot fogott csapdák száma
*/
int getCapturedCsapdak(Kvadrat *kvadrat)
{
	int count = 0, i;
	CsapdaNode *it = kvadrat->csapdaList->next;
	while(it)
	{
		for(i=0; i<MAX_MONTHS; ++i)
			count += ((it->csapda.fajok[i].fogasszam>0) && (it->csapda.hiba==SUCCESS));
		it = it->next;
	}
	
	return count;
}

/**
Csapdák arányai a teröleten
*/
void csapdaAranyok(KvadratNode *kvadratList)
{
	KvadratNode *it = kvadratList->next;
	while(it)
	{
		printf("In kvadrat %c, there was %d csapdas, %d captures, %d active and  %d inactive csapda\n", it->kvadrat.kvadratkod, 
			getCsapdaListSize(it->kvadrat.csapdaList), getCapturedCsapdak(&(it->kvadrat)), getActiveCsapdak(&(it->kvadrat)), getInactiveCsapdak(&(it->kvadrat))); 
		it = it->next;
	}
}
/**
Csapdánkénti átlagos denzitás
*/
float csapdaDensity(Kvadrat *kvadrat)
{
	return getCsapdaListSize(kvadrat->csapdaList)/(float)getNumCaptures(kvadrat);
}

/**
Egy faj csapdánkénti előfordulásának aránya a kvadrátban
*/
float fajOccerrenceNum(char* faj, Kvadrat *kvadrat)
{
	int captures = numFajInKvadrat(faj, kvadrat);
	return (float)captures/getCsapdaListSize(kvadrat->csapdaList)*MAX_MONTHS*100.0f;
}

/**
A fajok előfordulásainaka arányai
*/
void fajAranyok(KvadratNode *list)
{
	KvadratNode *it = list->next;
	char *fajok, *faj, *tmp;
	float tmpVal;
	Map *fajMap = createMap();
	while(it)
	{
		fajok = fajElofordulasInKvadrat(&(it->kvadrat));
		faj = strtok(fajok, " ");
		while(faj)
		{
			tmp = faj;
			tmpVal = fajOccerrenceNum(faj, &(it->kvadrat));
			fajMap = setMap(fajMap, tmp, tmpVal);
			printf("A %c kvadratban a(z) %s elofordulasi aranya: %.2f%%\n", it->kvadrat.kvadratkod, tmp, tmpVal);
			faj = strtok(NULL, " ");
		}
		it = it->next;
	}
}

/**
Faj Lloyd index
*/
float lloydPatchiness(char *faj, Kvadrat *kvadrat)
{
	float m = 1/(fajOccerrenceNum(faj, kvadrat)/100.0f);
	int captures = numFajInKvadrat(faj, kvadrat);
	float szamlalo = 0;
	CsapdaNode *it = kvadrat->csapdaList->next;
	while(it)
	{
		int captureXj = numFajInCsapda(faj, &(it->csapda));
		szamlalo += captureXj*(captureXj-1);
		it = it->next;
	}

	return szamlalo/(float)captures * m;	
}

/**
Egész területre vonatkozó Llyod index
*/
void lloydAll(KvadratNode *kvadratList)
{
	KvadratNode *it = kvadratList->next;
	while(it)
	{
		char *fajok = fajElofordulasInKvadrat(&(it->kvadrat));
		char *faj = strtok(fajok, " ");
		while(faj)
		{
			printf("In kvadrat %c a(z) %s Llyod-index: %.2f\n", it->kvadrat.kvadratkod, faj, lloydPatchiness(faj, &(it->kvadrat)));
			faj = strtok(NULL, " ");
		}
		it = it->next;
	}
}

/**
Intraspecifikus átfedés
*/
void intraAtfedes(KvadratNode *kvadratList)
{
	int i, numOfCaptures = 0;
	float ns = 0.0f, ov= 0.0f;
	KvadratNode *it = kvadratList->next;
	while(it)
	{
		CsapdaNode* csapdaIt = it->kvadrat.csapdaList->next;
		ns = 0.0f;
		numOfCaptures = 0;
		while(csapdaIt)
		{
			for(i=0;i<MAX_MONTHS; ++i)
				numOfCaptures += csapdaIt->csapda.fajok[i].fogasszam;
			ns += (numOfCaptures>=2);
			csapdaIt = csapdaIt->next;
		}
		csapdaIt = it->kvadrat.csapdaList->next;
		ov = ns/(float)getCsapdaListSize(csapdaIt)*MAX_MONTHS*100.0f;
		printf("In kvadrat %c, intraspecific atfedes was: %.2f%%\n", it->kvadrat.kvadratkod, ov);
		it = it->next;
	}
}
#endif // STATISTICS_H
