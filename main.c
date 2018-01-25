#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "statistics.h"

int main(int argc, char **argv)
{
	FILE *fileFaj, *fileFogas;
	KvadratNode *kvadratFajList = createKvadratNode(NULL);
	KvadratNode *kvadratFogasszamList = createKvadratNode(NULL);
	/*if(argc>1)
	{
		fileFaj = fopen(argv[1], "r");
		fileFogas = fopen(argv[2], "r");
	}else{*/
		fileFaj = fopen("fajs.txt", "r");
		fileFogas = fopen("fogasszams.txt", "r");
	//}
	if(!fileFaj || !fileFogas)
		fprintf(stderr, "Couldn't open the files.\n");
	else{
		//Reading from files...
		kvadratFajList = readKvadratok(kvadratFajList, fileFaj, FAJ);
		kvadratFogasszamList = readKvadratok(kvadratFogasszamList, fileFogas, FOGAS);
		fclose(fileFaj);
		fclose(fileFogas);
		//Do your job!!!!
		printKvadratList(kvadratFajList, FAJ);
		printf("\nFogasszamos:\n");
		printKvadratList(kvadratFogasszamList, FOGAS);
		printMostCapturedFajs(kvadratFajList);
		printNumCaptures(kvadratFajList);
		fajAranyok(kvadratFajList);
		csapdaAranyok(kvadratFajList);
		lloydAll(kvadratFajList);
		intraAtfedes(kvadratFajList);
		destroyKvadratList(kvadratFajList);
		destroyKvadratList(kvadratFogasszamList);
	}
    printf("Hello world!\n");
    return 0;
}
