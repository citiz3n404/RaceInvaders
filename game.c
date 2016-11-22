#include <string.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "constants.h"
#include "matrix.h"
#include "displayprompt.h"
#include "colour.h"
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))

// X COL / Y LINE

char key_pressed(){
	struct termios oldterm, newterm;
	int oldfd;
	char c, result = 0;
	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm;
	newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
	fcntl (STDIN_FILENO, F_SETFL, oldfd);
	if (c != EOF) {
		ungetc(c, stdin);
		result = getchar();
	}
	return result;
}

void runGame(){
	char c;
	clrscr();
	//displaySpaceInvader();

	//int **matrix = create_matrix(NB_LINE, NB_COL);
	//fill_matrix(matrix, NB_LINE, NB_COL, GRID_ELEMENT_EMPTY);

	// X Y
	//VOITURE voiture = {0, 0, 'v', 10, 'a'};


	//matrix[5][1] = GRID_ELEMENT_SHOOT;

	//displayRoad(matrix);
	//displayScore(200, 99999, 999999);
	int x=10, y=10;

	gotoxy(x, y);
	updateCarDisplay(x, y);

	gotoxy(x, y);
	removeCarDisplay(x ,y);

	x=20; y=4;

	gotoxy(x, y);
	updateCarDisplay(x, y);

	gotoxy(x, y);
	removeCarDisplay(x ,y);
	

	/*while((c=key_pressed()) != 'c'){

		removeCarDisplay(x, y);
		switch(c){
			case 'z': y -= 1; break;
			case 's': y += 1; break;
			case 'd': x += 1; break;
			case 'q': x -= 1; break;
		}
		updateCarDisplay(c, x, y);
		//clrscr();
		//displaySpaceInvader();
		//displayRoad(matrix);
		//displayScore(200, 12, 10);

		// UPDATE ALL CARS IN FUNCTION OF SPEED
		// TEST IF DEAD
		// UPDATE MATRIX THEN DISPLAY
	}*/
}

void removeCarDisplay(int x, int y){
	backColour(BLACK);
	printf("  ");
	backColourDefault();
	printf("remove %d %d", x, y);
}

// X COL / Y LIN
void updateCarDisplay(char c, int x, int y){
	//matrix[voiture.posx][voiture.posy] = GRID_ELEMENT_EMPTY;
	//posXY(ZERO_ROAD_LINE+ voiture.posx, ZERO_ROAD_COL+voiture.posy);
	//
	printf("update %d %d", x, y);
	//printf("%d, %d", voiture.posy, voiture.posx);

	//foreColour(YELLOW);
	backColour(BLACK);
	printf(" 🚘 ");
	backColourDefault();
	//foreColourDefault();

	//matrix[voiture.posx][voiture.posy] = GRID_ELEMENT_CAR;
}


