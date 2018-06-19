/***
PROJETO PRATICO DE ESTRUTURA DE DADOS I
UNIVERSIDADE TECNOLOGICA FEDERAL DO PARANA

    SNAKE GAME
AUTHORS:    Daniel E. Vieira    1366424
            Lucas S. Takahashi  1937553
***/
#include "elements.h"

#define N_FOOD 5
#define SNK_STRTNG_SIZE 3

Coord* createCoord()
{
    return NULL;
}

Coord* addFood(Board* board, int height, int width)
{
    Coord* f = (Coord*)malloc(sizeof(Coord));
    int y = 3 + (rand()%(height - 6)),
        x = 3 + (rand()%(width - 6));

    while(contains(board->snake, y, x) ||
            contains(board->food, y, x) ||
            contains(board->bonus, y, x))//Guarantees food on a good position
    {
        y = 3 + (rand()%(height - 6));
        x = 3 + (rand()%(width - 6));
    }

    f->y = y;
    f->x = x;
    f->prev = NULL;
    f->next = board->food;

    if(board->food)
        board->food->prev = f;

    return f;
}

Coord* addBonus(Board* board, int height, int width)
{
    Coord* f = (Coord*)malloc(sizeof(Coord));
    int y = 3 + (rand()%(height - 6)),
        x = 3 + (rand()%(width - 6));

    while(contains(board->snake, y, x) ||
            contains(board->food, y, x) ||
            contains(board->bonus, y, x))//Guarantees food on a good position
    {
        y = 3 + (rand()%(height - 6));
        x = 3 + (rand()%(width - 6));
    }

    f->y = y;
    f->x = x;
    f->prev = NULL;
    f->next = NULL;

    return f;
}

void bonusAdjust(Coord* snake)
{
    if(!snake){
        mvaddstr(0,0,"bonusAdjust(Coord* snake): ERROR");
        exit(1);
    }

    Coord* aux = snake;
    int nodes = 1, i;

    while(aux->next)
    {
        aux = aux->next;
        nodes++;
    }

    for(i = 0; i < nodes / 4; i++)
        decreaseSnake(snake);
}

Coord* removeFood(Coord* food, int y, int x)
{
    if(!food)
        return NULL;

    Coord* currentAux = food;

    while(!(currentAux->y == y && currentAux->x == x))
        currentAux = currentAux->next;

    if(!currentAux->prev) //case head
    {
        currentAux = currentAux->next;
        free(currentAux->prev);
        currentAux->prev = NULL;

        return currentAux;
    }
    else if(currentAux->prev && currentAux->next) //case body
    {
        currentAux->prev->next = currentAux->next;
        currentAux->next->prev = currentAux->prev;

        free(currentAux);

        return food;
    }
    else if(!currentAux->next) //case butthole
    {
        currentAux->prev->next = NULL;

        free(currentAux);

        return food;
    }
}

Coord* removeBonus(Coord* bonus, int y, int x)
{
    if(bonus)
        free(bonus);

    return NULL;
}

Coord* increaseSnake(Coord* snake, int y, int x)
{
    Coord* newSnake = (Coord*)malloc(sizeof(Coord));
    newSnake->y = y;
    newSnake->x = x;
    newSnake->prev = NULL;
    newSnake->next = snake;

    if(snake)
        snake->prev = newSnake;

    return newSnake;
}

void decreaseSnake(Coord* snake)
{
    Coord* aux = snake;

    while(aux->next != NULL)
        aux = aux->next;

    aux->prev->next = NULL;

    free(aux);
}

Board* createBoard(int height, int width)
{
    int i;

    Board* board = (Board*)malloc(sizeof(Board));

    board->height = height;
    board->width = width;

    board->snake = createCoord();
    for(i = 0; i < SNK_STRTNG_SIZE; i++)
        board->snake = increaseSnake(board->snake, height/2,
                                     (width/2) + i - 10);

    board->food = createCoord();
    for(i = 0; i < N_FOOD; i++)
        board->food = addFood(board, height, width);

    board->bonus = createCoord();

    return board;
}

void displayCoord(Coord* c, const char* symbol)
{
    while(c)
    {
        mvaddstr(c->y, c->x, symbol);
        c = c->next;
    }
}

void displayCoord_chtype(Coord* c, const chtype symbol)
{
    while(c)
    {
        mvaddch(c->y, c->x, symbol);
        c = c->next;
    }
}

void freeBoard(Board *b)
{
    Coord* aux;
    while(b->snake)
    {
        aux = b->snake->next;
        free(b->snake);
        b->snake = aux;
    }
    while(b->food)
    {
        aux = b->food->next;
        free(b->food);
        b->food = aux;
    }
    free(b);
}

int contains(Coord* snake, int y, int x)
{
    Coord* aux = snake;
    while(aux)
    {
        if(aux->y == y && aux->x == x)
            return TRUE;

        aux = aux->next;
    }

    return FALSE;
}
