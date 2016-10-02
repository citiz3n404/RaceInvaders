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
	displaySpaceInvader();

	int **matrix = create_matrix(NB_LINE, NB_COL);
	fill_matrix(matrix, NB_LINE, NB_COL, GRID_ELEMENT_EMPTY);

	VOITURE voiture = {NB_LINE-1, 2, 'v', 10, 'a'};


	matrix[5][1] = GRID_ELEMENT_SHOOT;

	displayRoad(matrix);
	displayScore(200, 99999, 999999);

	while((c=key_pressed()) != 'c'){
		//SUPPRIMER LA DERNIERE POSITION DANS MATRIX DE VOITURE
		matrix[voiture.posx][voiture.posy] = GRID_ELEMENT_EMPTY;
		switch(c){
			case 'z': voiture.posx -= 1; break;
			case 's': voiture.posx += 1; break;
			case 'd': voiture.posy += 1; break;
			case 'q': voiture.posy -= 1; break;
		}
		matrix[voiture.posx][voiture.posy] = GRID_ELEMENT_CAR;

		clrscr();
		displaySpaceInvader();
		displayRoad(matrix);
		displayScore(200, 12, 10);
		// UPDATE ALL CARS IN FUNCTION OF SPEED
		// TEST IF DEAD
		// UPDATE MATRIX THEN DISPLAY
	}
}
