/***
PROJETO PRATICO DE ESTRUTURA DE DADOS I
UNIVERSIDADE TECNOLOGICA FEDERAL DO PARANA

    SNAKE GAME
AUTHORS:    Daniel E. Vieira    1366424
            Lucas S. Takahashi  1937553
***/
#include "snakeGame.h"

#define PLAYER_NAME_SIZE    7
#define PLAYER_PTS_SIZE     7

#define PLAYER_LIST_SIZE    10

Status mainMenu(int height, int width)
{
    const int SIZEOF_MENU = 3;
    int i, button = KEY_LEFT, yCursor, yMenList;
    const int xCursor = width/2 - 2,
              xMenList = width/2 + 1;
    const char* menuList[] =
    {
        "New Game",
        "Records",
        "Exit"
    };

    yMenList = yCursor = height/2 - 2;

    while(button != '\n')
    {
        clear();

        mvaddch(yCursor, xCursor, ACS_DIAMOND);

        for(i = 0; i < SIZEOF_MENU; i++)
            mvaddstr(yMenList + i, xMenList, menuList[i]);

        button = getch();

        if(button == KEY_DOWN &&
                yCursor >=  yMenList &&
                yCursor < yMenList + SIZEOF_MENU - 1)
            yCursor++;
        if(button == KEY_UP &&
                yCursor > yMenList &&
                yCursor <= yMenList + SIZEOF_MENU - 1)
            yCursor--;
    }

    if(yCursor == yMenList)
        return NEWGAME;
    else if(yCursor == yMenList + 1)
        return RECORDS;
    else
        return EXIT;
}

Status starting_screen(int height, int width)
{
    const short centerY = (height/2), centerX = (width/2);
    int i;
    const char* text[] =
    {
        "___@@@@@@@@__@@@@@______@@@__@@@@@@@@@__@@@__@@@__@@@@@@@@@___",
        "___@@@@@@@@__@@@@@@_____@@@__@@@@@@@@@__@@@__@@@__@@@@@@@@@___",
        "___@@@_______@@@_@@@____@@@__@@@___@@@__@@@__@@___@@@_________",
        "___@@@@@@@___@@@__@@@___@@@__@@@@@@@@@__@@@@@_____@@@@@@______",
        "___@@@@@@@___@@@___@@@__@@@__@@@@@@@@@__@@@@@@@___@@@@@@______",
        "_______@@@___@@@____@@@_@@@__@@@___@@@__@@@__@@@__@@@_________",
        "___@@@@@@@___@@@_____@@@@@@__@@@___@@@__@@@__@@@__@@@@@@@@@___",
        "___@@@@@@@___@@@______@@@@@__@@@___@@@__@@@__@@@__@@@@@@@@@___",
        "PRESS ENTER TO START!",
        "v1.5.1-Final by Daniel Vieira and Lucas Shoiti"
    };

    clear();
    for(i = 0; i < 8; i++)
        mvaddstr(centerY - 8 + i, centerX - strlen(text[1]) / 2, text[i]);

    mvaddstr(height - 8, centerX - strlen(text[9]) / 2, text[9]);
    mvaddstr(height - 2, centerX - strlen(text[8]) / 2, text[8]);

    refresh();

    while(i != '\n')
        i = getch();

    return MAINMENU;
}

Status showRecords(int height, int width)
{
    FILE* input_file = fopen("data/top_players_rec.dat", "r");
    int pts, i, nlinhas;
    const short centerX = (width / 2);
    char* name = (char*)malloc(sizeof(char)*(PLAYER_NAME_SIZE + 1)),
          straux[PLAYER_PTS_SIZE + 1];
    const char *text[] = {"POS.\tNAME\t\tSCORE", "PRESS ENTER TO GO BACK"};
    Player *p = createPlayer(), *aux = createPlayer();

//If the file is missing
    if (!input_file)
        return STARTING_SCREEN;

    fscanf(input_file, "%d", &nlinhas);

//Loading the game history
    for(i = 0; i < nlinhas; i++)
    {
        fscanf(input_file, "%s", name);
        fscanf(input_file, "%d", &pts);
        p = readPlayer(p, name, pts);
    }

    clear();
    mvaddstr(3, centerX - strlen(text[1]) / 2, text[0]);

    for(i = 0, aux = p; aux != NULL && i < PLAYER_LIST_SIZE;
            i++, aux = aux->next)
        mvprintw(5 + i, centerX - strlen(text[1]) / 2,
                 "%02d.\t%s\t\t%d", i + 1, aux->name, aux->pts);

    mvaddstr(height - 2, centerX - strlen(text[1]) / 2, text[1]);

    i = 0;
    while(i != '\n')
        i = getch();

    freePlayer(p);
    free(name);
    freePlayer(aux);
    fclose(input_file);

    return MAINMENU;
}

char* getGameTime(char** string, time_t* start, time_t* now)
{
    *now = time(now);
    sprintf(*string, "%2.2ld:%2.2ld:%2.2ld\t",((*now - *start)/3600)%60,((*now - *start)/60)%60, (*now - *start)%60);
    return *string;
}

int newGame(int height, int width)
{
    time_t start = time(&start), now;
    char *string = (char*)malloc(sizeof(char)*13);
    srand(time(NULL));
    Board* board = createBoard(height, width);
    Status s = SUCCESS;
    Direction d = RIGHT;
    int pts = 0, bonusCont = 0, bonusChkpt = 4;

    while(s != FAILURE)
    {
        clear();
        wborder(stdscr, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
                ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

        mvhline(2, 1, ACS_HLINE, width - 2);
        mvprintw(1, 3, "SCORE: %06d\t\t", pts);
        addch(ACS_DIAMOND);
        addstr(" Food\t\t");
        addch(ACS_CKBOARD);
        addstr(" Bonus\t\t");
        addstr("ooo You\t\t");
        addstr(getGameTime(&string, &start, &now));
        printw(" Next Bonus: %d/%d", bonusCont, bonusChkpt + 1);
        displayCoord(board->snake, "o");
        displayCoord_chtype(board->food, ACS_DIAMOND);
        displayCoord_chtype(board->bonus, ACS_CKBOARD);

        d = getNextMove(d);
        s = moveSnake(board, d);
        if(s == INCREASED)
        {
            pts++;
            if(bonusCont == bonusChkpt && !board->bonus)
            {
                board->bonus = addBonus(board, height, width);
                bonusChkpt += 5;
                bonusCont = 0;
            }
            else if(bonusCont < bonusChkpt)
                bonusCont++;
        }
    }
    freeBoard(board);
    return pts;
}

Direction getNextMove(Direction d)
{
    int nextDir = getch();

    if(nextDir == KEY_LEFT && d != RIGHT)
        return LEFT;
    else if(nextDir == KEY_RIGHT && d != LEFT)
        return RIGHT;
    else if (nextDir == KEY_UP && d != DOWN)
        return UP;
    else if(nextDir == KEY_DOWN && d != UP)
        return DOWN;
    else
        return d;
}

Status moveSnake(Board* board, Direction d)
{
    if(d == UP && snakeCanGo(board,
                             board->snake->y - 1, board->snake->x))
    {
        board->snake = increaseSnake(
                           board->snake,
                           board->snake->y - 1,
                           board->snake->x);

        if(!contains(board->food, board->snake->y, board->snake->x) &&
                !contains(board->bonus, board->snake->y, board->snake->x))
            decreaseSnake(board->snake);
        else if(contains(board->bonus, board->snake->y, board->snake->x))
        {
            board->bonus = removeBonus(board->bonus,
                                       board->snake->y, board->snake->x);

            bonusAdjust(board->snake);

            return SUCCESS;
        }
        else
        {
            board->food = removeFood(board->food,
                                     board->snake->y, board->snake->x);
            board->food = addFood(board, board->height, board->width);

            return INCREASED;
        }
    }
    else if(d == DOWN && snakeCanGo(board,
                                    board->snake->y + 1, board->snake->x))
    {
        board->snake = increaseSnake(
                           board->snake,
                           board->snake->y + 1,
                           board->snake->x);

        if(!contains(board->food, board->snake->y, board->snake->x) &&
                !contains(board->bonus, board->snake->y, board->snake->x))
            decreaseSnake(board->snake);
        else if(contains(board->bonus, board->snake->y, board->snake->x))
        {
            board->bonus = removeBonus(board->bonus,
                                       board->snake->y, board->snake->x);

            bonusAdjust(board->snake);

            return SUCCESS;
        }
        else
        {
            board->food = removeFood(board->food,
                                     board->snake->y, board->snake->x);
            board->food = addFood(board, board->height, board->width);

            return INCREASED;
        }
    }
    else if (d == RIGHT && snakeCanGo(board,
                                      board->snake->y, board->snake->x + 1))
    {
        board->snake = increaseSnake(
                           board->snake,
                           board->snake->y,
                           board->snake->x + 1);

        if(!contains(board->food, board->snake->y, board->snake->x) &&
                !contains(board->bonus, board->snake->y, board->snake->x))
            decreaseSnake(board->snake);
        else if(contains(board->bonus, board->snake->y, board->snake->x))
        {
            board->bonus = removeBonus(board->bonus,
                                       board->snake->y, board->snake->x);

            bonusAdjust(board->snake);

            return SUCCESS;
        }
        else
        {
            board->food = removeFood(board->food,
                                     board->snake->y, board->snake->x);
            board->food = addFood(board, board->height, board->width);

            return INCREASED;
        }
    }
    else if (d == LEFT && snakeCanGo(board,
                                     board->snake->y, board->snake->x - 1))
    {

        board->snake = increaseSnake(
                           board->snake,
                           board->snake->y,
                           board->snake->x - 1);

        if(!contains(board->food, board->snake->y, board->snake->x) &&
                !contains(board->bonus, board->snake->y, board->snake->x))
            decreaseSnake(board->snake);
        else if(contains(board->bonus, board->snake->y, board->snake->x))
        {
            board->bonus = removeBonus(board->bonus,
                                       board->snake->y, board->snake->x);

            bonusAdjust(board->snake);

            return SUCCESS;
        }
        else
        {
            board->food = removeFood(board->food,
                                     board->snake->y, board->snake->x);
            board->food = addFood(board, board->height, board->width);

            return INCREASED;
        }
    }
    else
        return FAILURE; //collision with wall

    return SUCCESS;
}

int snakeCanGo(Board* board, int y, int x)
{
    if (contains(board->snake, y, x) ||
            y == 2 || x == 2 || y == board->height - 1 || x == board->width - 1)
        return FALSE;

    return TRUE;
}

Status gameOver(int height, int width, int pts)
{
    FILE* input_file = fopen("data/top_players_rec.dat", "r");
    Player *p = createPlayer(), *auxplayer = createPlayer();
    int i = 0, ptsaux, nlinhas, aux = '_';
    const char* text[] =
    {
        "GAME OVER",
        "Insert Name:",
        "Score:",
        "PRESS ENTER TO CONFIRM",
    };
    char name[PLAYER_NAME_SIZE + 1] = {"______"}, nameaux[PLAYER_NAME_SIZE + 1];
    const int centerY = height/2, centerX = width/2,
              xName = centerX - 8 - (strlen(text[1]) + strlen(text[2]) +
                                     PLAYER_NAME_SIZE + PLAYER_PTS_SIZE) / 2;

    while (aux != '\n')
    {
        clear();
        mvaddstr(centerY, centerX - strlen(text[0])/2, text[0]);
        mvprintw(centerY + 3, xName, "%s\t\t\t%s %d", text[1], text[2], pts);
        mvaddstr(height - 3, centerX - strlen(text[3]) / 2, text[3]);
        if(i > 0 &&
                (aux == KEY_BACKSPACE || aux == 127 || aux == KEY_DC))
        {
            i--;
            name[i] = '_';
        }
        else if (((aux >= 65 && aux <= 90) || (aux >= 97 && aux<= 122)) &&
                 (i < PLAYER_NAME_SIZE - 1))
        {
            name[i] = aux;
            i++;
        }

        mvprintw(centerY + 3, xName + strlen(text[1]), "%s", name);
        aux = getch();
    }

    if(i > 0)
        name[i] = '\0';
    else
        strcpy(name, "ANON");

    //If the file is missing
    if (!input_file)
    {
        mvaddstr(0, 0, "file[player_score] not found");
        return MAINMENU;
    }

    //Loading the game history
    fscanf(input_file, "%d", &nlinhas);

    for(i = 0; i < nlinhas; i++)
    {
        fscanf(input_file, "%s", nameaux);
        fscanf(input_file, "%d", &ptsaux);
        p = readPlayer(p, nameaux, ptsaux);
    }
    fclose(input_file);

    p = addPlayer(p, name, pts);

    //Writing the new file
    FILE *output_file = fopen("data/top_players_rec.dat", "w");

    if(nlinhas < PLAYER_LIST_SIZE)
        fprintf(output_file, "%d\n", nlinhas + 1);
    else
        fprintf(output_file, "%d\n", nlinhas);

    for(auxplayer = p, i = 0;
            auxplayer != NULL && i < PLAYER_LIST_SIZE;
            auxplayer = auxplayer->next, i++)
        fprintf(output_file, "%s\t%d\n", auxplayer->name, auxplayer->pts);

    freePlayer(p);
    fclose(output_file);

    return STARTING_SCREEN;
}
