#include "map.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Map *createMap(void)
{
    Map *newMap = (Map*)malloc(sizeof(Map));
    if(!newMap)
        return NULL;
    newMap->next = NULL;
    return newMap;
}

void destroyMap(Map* map)
{
	if(map->next)
		destroyMap(map->next);
	free(map);
}

Map *setMap(Map* map, const char *key, int value)
{
    Map *newMap;

    if(!map)
        return NULL;

    newMap = createMap();
    newMap->key = (char*)malloc(sizeof(char)*strlen(key)+1);
    strcpy(newMap->key, key);
    newMap->value = value;
    if(!(map->next))
        map->next = newMap;
    else{
        Map *it = map->next;
        while(it->next)
        {
            if(!strcmp(key, it->key))
            {
                it->value = value;
                return map;
            }
            it = it->next;
        }
         it->next = newMap;
    }

    return map;
}

int getMapValue(Map *map, const char *key)
{
    Map *it = map->next;
    if(!map)
        return 0;

    while(it)
    {
        if(!strcmp(it->key, key))
            return it->value;
        it = it->next;
    }

    return 0;
}

char* getMapMaxValue(Map *map, int *max)
{
    Map *it = map->next;
	char *key = (char*)malloc(sizeof(char)*4);
    (*max) = it->value;
    strcpy(key, it->key);
    if(!map)
        return NULL;
    while(it)
    {
        if((*max)<it->value)
        {
            (*max) = it->value;
            strcpy(key, it->key);
        }

        it = it->next;
    }

    return key;
}

void printMap(Map *map)
{
	Map *it = map->next;
	while(it)
	{
		printf("%s (%d) ", it->key, it->value);
		it = it->next;
	}
}