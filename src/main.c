/***
PROJETO PRATICO DE ESTRUTURA DE DADOS I
UNIVERSIDADE TECNOLOGICA FEDERAL DO PARANA

    SNAKE GAME
AUTHORS:    Daniel E. Vieira    1366424
            Lucas S. Takahashi  1937553

For more info about C:
            http://tutorialspoint.com/ansi_c/c_using_constants.htm

For more info about ncurses.h:
            http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/
            http://facom.ufu.br/~albertini/prossiga/index.php/NCURSES
            https://linux.die.net/man/3/timeout
            https://linux.die.net/man/3/ncurses
***/

#include "snakeGame.h"

int main(int argc, char* argv[])
{
	initscr(); //Start curses mode in the stdscr (which usually is the terminal)
	raw(); //Blocks the terminal commands from keyboard
	noecho(); //Disable the visual return from terminal
	keypad(stdscr, TRUE); // It enables the reading of function keys
	curs_set(0); // makes cursor invisible
	timeout(90); //Sets a input time limit for stdscr, if time's up it returns ERR

	Status s = STARTING_SCREEN;
	int height, width;
	getmaxyx(stdscr, height, width); //getting the window's size

	while(s != EXIT)
	{
		if(s == NEWGAME)
			s = gameOver(height, width, newGame(height, width));
		else if(s == RECORDS)
			s = showRecords(height, width);
        else if(s == STARTING_SCREEN)
            s = starting_screen(height, width);
        else if(s == MAINMENU)
            s = mainMenu(height, width);
		else
			s = EXIT;
	}

	endwin();
	return 0;
}
