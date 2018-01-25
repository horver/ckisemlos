/*******
*   A map datastruct for a short hand.
*   needed for some calculations.
*   This is associate a string to a int
*   string => int
********/
#ifndef MAP_H_
#define MAP_H_

typedef struct Map{
    char *key;
    int value;
    struct Map *next;
}Map;

Map *createMap(void);

void destroyMap(Map* map);

Map *setMap(Map* map, const char *key, int value);

int getMapValue(Map *map, const char *key);

char* getMapMaxValue(Map *map, int *max);

void printMap(Map *map);

#endif // MAP_H_
