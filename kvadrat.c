#include "kvadrat.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Kvadrat *createEmptyKvadrat(void)
{
    Kvadrat *newKvadrat = (Kvadrat*)malloc(sizeof(Kvadrat));
    newKvadrat->csapdaList = createCsapdaNode(NULL);
    return newKvadrat;
}

KvadratNode *createKvadratNode(Kvadrat *kvadrat)
{
    KvadratNode *newKvadratNode = (KvadratNode*)malloc(sizeof(KvadratNode));
    if(kvadrat)
        newKvadratNode->kvadrat = *(kvadrat);
    newKvadratNode->next = NULL;
    return newKvadratNode;
}

void destroyKvadratList(KvadratNode *list)
{
	if(list->next)
	{
		destroyCsapdaList(list->next->kvadrat.csapdaList);
		destroyKvadratList(list->next);
	}
	free(list);
}

KvadratNode *insertKvadrat(KvadratNode *list, Kvadrat *kvadrat)
{
    KvadratNode *newKvadratNode;

    if(!list)
        return NULL;

    newKvadratNode = createKvadratNode(kvadrat);

    if(list->next==NULL)
        list->next = newKvadratNode;
    else{
        KvadratNode *it = list;
        while(it->next)
            it = it->next;
        it->next = newKvadratNode;
    }

    return list;
}

int getKvadratListSize(KvadratNode *list)
{
    int count = 0;
    KvadratNode *it = list->next;
    while(it)
    {
        count++;
        it = it->next;
    }
    return count;
}

KvadratNode *readKvadratok(KvadratNode *list, FILE *fp, MODES mode)
{
    char buffer[255], nameBuffer[4];

    if(!fp)
        return NULL;

    while(fgets(buffer, 255, fp))
    {
		if(strcmp(buffer, "\n") && strcmp(buffer, "\t"))
		{
			Kvadrat *tmpKvadrat = createEmptyKvadrat();
			sscanf(buffer, "%c%d%s", &(tmpKvadrat->kvadratkod),  &(tmpKvadrat->size), nameBuffer);
			//printf("Readed kvadrat char: %c and size: %d\n", tmpKvadrat->kvadratkod, tmpKvadrat->size);
			if(mode == FAJ)
				tmpKvadrat->csapdaList = readCsapdakFajok(tmpKvadrat->csapdaList, tmpKvadrat->size, fp);
			else
				tmpKvadrat->csapdaList = readCsapdakFogasok(tmpKvadrat->csapdaList, tmpKvadrat->size, fp, nameBuffer);
			list = insertKvadrat(list, tmpKvadrat);
		}
    }
    return list;
}

void printKvadrat(Kvadrat *kvadrat, MODES mode)
{
    printCsapdaList(kvadrat->csapdaList, mode);
    printf("\n");
}

void printKvadratList(KvadratNode *list, MODES mode)
{
    KvadratNode *it = list->next;
    while(it)
    {
        printKvadrat(&(it->kvadrat), mode);
        it = it->next;
    }
}
