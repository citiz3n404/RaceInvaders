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
#define gotoxy(y,x) printf("\033[%d;%dH", (x), (y))

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
	displaySpaceInvader();

	int **matrix = create_matrix(NB_LINE, NB_COL);
	fill_matrix(matrix, NB_LINE, NB_COL, GRID_ELEMENT_EMPTY);

	// X Y
	VOITURE voiture = {5, 29, 'v', 10, 'a'};
	VOITURE voiture2 = {5, 28, 'c', RED, 'a'};

	VOITURE *voitures = allocate_cars(30);


	matrix[5][1] = GRID_ELEMENT_SHOOT;

	displayRoad(matrix);
	displayScore(0, 0, 0);


	while((c=key_pressed()) != 'c'){

		removeCarDisplay(voiture);
		switch(c){
			case 'z': voiture.posy -= 1; break;
			case 's': voiture.posy += 1; break;
			case 'd': voiture.posx += 5; break;
			case 'q': voiture.posx -= 5; break;
		}
		updateCarDisplay(voiture);
		updateCarDisplay(voiture2);
		// UPDATE ALL CARS IN FUNCTION OF SPEED
		// TEST IF DEAD
		// UPDATE MATRIX THEN DISPLAY
	}
}

void removeCarDisplay(VOITURE voiture){
	gotoxy(ZERO_ROAD_LINE+ voiture.posx+1, ZERO_ROAD_COL+voiture.posy+1);
	//gotoxy(x, y);
	backColour(BLACK);
	printf("   ");
	backColourDefault();
	gotoxy(20, 1);
}

// X COL / Y LIN
void updateCarDisplay(VOITURE voiture){
	gotoxy(ZERO_ROAD_LINE+ voiture.posx+1, ZERO_ROAD_COL+voiture.posy+1);
	backColour(BLACK);
	foreColour(voiture.couleur);
	if(voiture.type == 'v'){
		printf(" 🚘 ");
	}else if(voiture.type == 'c'){
		printf(" 🚍 ");
	}
	foreColourDefault();
	backColourDefault();
	gotoxy(1, 45);
}
