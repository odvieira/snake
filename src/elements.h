/***
PROJETO PRATICO DE ESTRUTURA DE DADOS I
UNIVERSIDADE TECNOLOGICA FEDERAL DO PARANA

    SNAKE GAME
AUTHORS:    Daniel E. Vieira    1366424
            Lucas S. Takahashi  1937553
***/
#ifndef elements_h
#define elements_h

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct coord{
    int x;
    int y;
    struct coord* prev;
    struct coord* next;
}Coord;

typedef struct board{
    int width;
    int height;
    Coord* snake;
    Coord* food;
    Coord* bonus;
}Board;

Board* createBoard(int height, int width);

Coord* createCoord();
Coord* increaseSnake(Coord* snake, int y, int x);
Coord* addFood(Board* board, int height, int width);
Coord* removeFood(Coord* food, int y, int x);
Coord* addBonus(Board* board, int height, int width);
Coord* removeBonus(Coord* bonus, int y, int x);

int contains(Coord* snake, int y, int x);

void bonusAdjust(Coord* snake);
void decreaseSnake(Coord* snake);
void displayCoord(Coord* c, const char* symbol);
void displayCoord_chtype(Coord* c, const chtype symbol);
void freeBoard(Board *b);

#endif // elements_h
