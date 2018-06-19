/***
PROJETO PRATICO DE ESTRUTURA DE DADOS I
UNIVERSIDADE TECNOLOGICA FEDERAL DO PARANA

    SNAKE GAME
AUTHORS:    Daniel E. Vieira    1366424
            Lucas S. Takahashi  1937553
***/
#ifndef snakeGame_h
#define snakeGame_h

#include "player.h"
#include "elements.h"

typedef enum status{
    SUCCESS,
    FAILURE,
    EXIT,
    RECORDS,
    NEWGAME,
    MAINMENU,
    STARTING_SCREEN,
    INCREASED
}Status;

typedef enum direction{
    UP,
    DOWN,
    RIGHT,
    LEFT,
}Direction;

Status mainMenu(int height, int width);
Status starting_screen(int height, int width);
Status showRecords(int height, int width);
Status gameOver(int height, int width, int pts);
Status moveSnake(Board* snake, Direction d);

int newGame(int height, int width);
int snakeCanGo(Board* board, int y, int x);

Direction getNextMove(Direction d);


#endif // snakeGame_h
