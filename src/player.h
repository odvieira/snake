/***
PROJETO PRATICO DE ESTRUTURA DE DADOS I
UNIVERSIDADE TECNOLOGICA FEDERAL DO PARANA

    SNAKE GAME
AUTHORS:    Daniel E. Vieira    1366424
            Lucas S. Takahashi  1937553
***/
#ifndef player_h
#define player_h

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct player{
    char* name;
    int pts;
    struct player* prev;
    struct player* next;
}Player;

Player* createPlayer();
Player* addPlayer(Player* p, char* name, int pts);
Player* readPlayer(Player* p, char* name, int pts);

void freePlayer(Player* p);

#endif // player_h
