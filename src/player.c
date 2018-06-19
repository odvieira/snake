/***
PROJETO PRATICO DE ESTRUTURA DE DADOS I
UNIVERSIDADE TECNOLOGICA FEDERAL DO PARANA

    SNAKE GAME
AUTHORS:    Daniel E. Vieira    1366424
            Lucas S. Takahashi  1937553
***/
#include "player.h"

#define PLAYER_NAME_SIZE 7

Player* createPlayer()
{
    return NULL;
}

Player* addPlayer(Player* p, char* name, int pts)
{
    //Creating a new element
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    newPlayer->name = (char*)malloc((PLAYER_NAME_SIZE + 1)*sizeof(char));
    strcpy(newPlayer->name, name);
    newPlayer->pts = pts;

    if(!p)
    {
        newPlayer->next = NULL;
        newPlayer->prev = NULL;
        return newPlayer;
    }

    Player* aux = p;
    // Locating the queue's tail, if isn't a new record
    while(aux != NULL)
    {
        if(newPlayer->pts > aux->pts)
        {
            newPlayer->prev = aux->prev;
            newPlayer->next = aux;
            if(aux->prev)
                aux->prev->next = newPlayer;
            aux->prev = newPlayer;

            if(!newPlayer->prev) //If a new champion rise, he's the queue's head
                return newPlayer;
            else
                return p;
        }
        else if(!aux->next)
        {
            aux->next = newPlayer;
            newPlayer->next = NULL;
            newPlayer->prev = aux;
            return p;
        }
        else
            aux = aux->next;
    }
}

Player* readPlayer(Player* p, char* name, int pts)
{
    //Creating a new element
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    newPlayer->name = (char*)malloc((PLAYER_NAME_SIZE + 1)*sizeof(char));
    strcpy(newPlayer->name, name);
    newPlayer->pts = pts;

    if(!p)
    {
        newPlayer->next = NULL;
        newPlayer->prev = NULL;
        return newPlayer;
    }
    else
    {
        Player* aux = p;

        while(aux->next)
            aux = aux->next;

        aux->next = newPlayer;
        newPlayer->prev = aux;
        newPlayer->next = NULL;

        return p;
    }

}

void freePlayer(Player* p)
{
    Player* aux;
    while(p)
    {
        aux = p->next;
        free(p->name);
        free(p);
        p = aux;
    }
}
