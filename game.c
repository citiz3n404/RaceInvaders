#include <string.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	

	int **matrix = create_matrix(NB_LINE, NB_COL);
	fill_matrix(matrix, NB_LINE, NB_COL, GRID_ELEMENT_EMPTY);

	// X Y
	VOITURE voiture = {1, 28, 'v', 10, 'a', 7};
	VOITURE voiture2 = {1, 0, 'c', RED, 'a', 2};

	VOITURE *voitures = allocate_cars(NB_CARS);

	int i = 0;
	for(i=0; i<2; i++){
		voitures[i].posy = 0;
		voitures[i].posx = rand()%3;
		voitures[i].couleur = rand()%8;
		int tmp = rand()%2;
		if(tmp == 1){
			voitures[i].type ='c';
		}else{
			voitures[i].type = 'v';
		}
		voitures[i].etat = 'a';
		voitures[i].vitesse = rand()%7;
	}


	matrix[5][1] = GRID_ELEMENT_SHOOT;

	clrscr();
	displaySpaceInvader();
	displayRoad(matrix);
	displayScore(0, 0, 0);

	int j=0;
	for(j=0; j<2; j++){
		//updateCarDisplay(voitures[j]);
	}
	updateCarDisplay(voiture2);
	updateCarDisplay(voiture);

	int current=0, last = 0;

	while((c=key_pressed()) != 'c'){
		current = SDL_GetTicks();

		
		if(current > last + 200){
				removeCarDisplay(voiture2);
				updateCarPosition(voiture, &voiture2);
				updateCarDisplay(voiture2);
				last = current;
		}
		

		switch(c){
			case 'z': 
				/*for(i=0; i<2; i++){
					removeCarDisplay(voitures[i]);
					updateCarPosition(voiture, voitures[i]);
					updateCarDisplay(voitures[i]);
				}*/
				
				break;
			//case 's': voiture.posy += 1; break;
			case 'd': removeCarDisplay(voiture); 
						voiture.posx += 1; 
						updateCarDisplay(voiture); 
						break;
			case 'q': removeCarDisplay(voiture); 
						voiture.posx -= 1; 
						updateCarDisplay(voiture); 
						break;
		}
		
		gotoxy(1, 45);
		// UPDATE ALL CARS IN FUNCTION OF SPEED
		// TEST IF DEAD
		// UPDATE MATRIX THEN DISPLAY

	}
}


void updateCarPosition(VOITURE vPlayer, VOITURE* v2){
	int i=0;
	v2->posy = v2->posy + 1;
	gotoxy(1, 45);
	printf("%3d %3d",v2->posx, v2->posy);
	/*for(i=0; i<NB_CARS; i++){
		if(vPlayer.vitesse < v2.vitesse){
			v2.posy -= 1;
		}else if(vPlayer.vitesse > v2.vitesse){
			v2.posy += 1;
		}
	}*/

}

void removeCarDisplay(VOITURE voiture){
	gotoxy(ZERO_ROAD_LINE+ (voiture.posx*5)+1, ZERO_ROAD_COL+voiture.posy+1);
	backColour(BLACK);
	printf("   ");
	backColourDefault();
	
}

// X COL / Y LIN
void updateCarDisplay(VOITURE voiture){
	gotoxy(ZERO_ROAD_LINE+ (voiture.posx*5)+1, ZERO_ROAD_COL+voiture.posy+1);
	backColour(BLACK);
	foreColour(voiture.couleur);
	if(voiture.type == 'v'){
		printf(" 🚘 ");
	}else if(voiture.type == 'c'){
		printf(" 🚍 ");
	}
	foreColourDefault();
	backColourDefault();
}


