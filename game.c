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
#include "game.h"
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

void addCars(VOITURE* voitures){
	if(rand()%2 == 1){
		int i = rand()%2 +1;
		int cmpt = 0, j=0;
		for(j=0; j<NB_CARS; j++){
			if(voitures[j].etat =='p'){
				cmpt++;
				voitures[j].etat = 'a';
				voitures[j].posy = 0;
				voitures[j].posx = rand()%3;
				voitures[j].couleur = rand()%8;
				voitures[j].vitesse = rand()%7;
				int tmp = rand()%2;
				if(tmp == 1){
					voitures[j].type ='c';
				}else{
					voitures[j].type = 'v';
				}
			}
			if(cmpt == i){
				break;
			}
		}
	}

}


void resetMatrix(VOITURE **road){
	int n, m;
	for(n=0; n<NB_LINE; n++){
		for(m=0; m<NB_COL; m++){
			road[n][m].posx = 0;
			road[n][m].posy = 0;
			road[n][m].couleur = 0;
			road[n][m].type ='c';
			road[n][m].etat = 'p';
			road[n][m].vitesse = 0;

		}
	}

}

void putCarsIntoRoad(VOITURE **matrix, VOITURE *liste){
	int i=0; 
	for(i=0;i<NB_CARS; i++){
		if(liste[i].etat == 'a' && liste[i].posy>=0){
			matrix[liste[i].posx][liste[i].posy] = liste[i];
		}
	}
}

void updateMatrixRoad(VOITURE **matrix, VOITURE *liste){
	resetMatrix(matrix);
	putCarsIntoRoad(matrix, liste);
}

void runGame(){
	char c;
	

	int **matrix = create_matrix(NB_LINE, NB_COL);
	fill_matrix(matrix, NB_LINE, NB_COL, GRID_ELEMENT_EMPTY);

	VOITURE *voitures = allocate_cars(NB_CARS);
	VOITURE **road = allocate_road_matrix(NB_LINE, NB_COL);

	// X Y
	VOITURE voiture = {1, 28, 'v', 10, 'a', 7};


	//INIT THE LIST OF CARS
	int i = 0;
	for(i=0; i<NB_CARS; i++){
		voitures[i].posy = 0;
		voitures[i].posx = 0;
		voitures[i].couleur = 0;
		voitures[i].type ='c';
		voitures[i].etat = 'p';
		voitures[i].vitesse = 0;
	}

//INIT THE MATRIX ROAD with empty cars
	resetMatrix(road);

//AFFICHE LA GRILLE
	clrscr();
	displaySpaceInvader();
	displayRoad(matrix);
	displayScore(0, 0, 0);

//AFFICHE LES VOITURES DESSUS
	addCars(voitures);
	int j=0;
	for(j=0; j<NB_CARS; j++){
		updateCarDisplay(voitures[j]);
	}

//AFFICHE LA VOITURE DU PLAYER
	updateCarDisplay(voiture);

	int current=0, last = 0;
	int speed = 200;

	while((c=key_pressed()) != 'c'){
		current = SDL_GetTicks();

		//TOUTES LES 200ms
		if(current > last + speed){
			//
			
            for(i=0; i<NB_CARS; i++){
                if(voitures[i].posy > 28){
                	//Si la voiture est passée
                	removeCarDisplay(voitures[i]); 
                    voitures[i].etat = 'p';
                    voitures[i].posy = 0;
                }
            }
			removeCarsDisplay(voitures);
			updateCarsPosition(voiture, voitures);
			updateCarsDisplay(voitures);
			addCars(voitures);
			updateMatrixRoad(road, voitures);
			//CRASH
			if(voiture.posx == road[voiture.posx][voiture.posy].posx && voiture.posy == road[voiture.posx][voiture.posy].posy){
				exit(0);
			}
			//générer une voiture ou pas./
			last = current;
		}
		
		//PLAYER

		switch(c){
			case 'z': 
					speed -= 30; voiture.vitesse ++;
				break;
			case 's': speed +=30; voiture.vitesse --; 
				break;
			case 'd': 
				if(!(voiture.posx +1 > 2)){
					removeCarDisplay(voiture); 
					voiture.posx += 1; 
					updateCarDisplay(voiture); 
				}
				break;
			case 'q': 
				if(!(voiture.posx -1 < 0)){
					removeCarDisplay(voiture); 
					voiture.posx -= 1; 
					updateCarDisplay(voiture); 
				}
				break;
		}
		
		gotoxy(1, 45);
		// TEST IF DEAD
		// UPDATE MATRIX THEN DISPLAY

	}
}

/********************************************************************************/

void updateCarsPosition(VOITURE vPlayer, VOITURE* voitures){
	int i=0;
	for(i=0; i<NB_CARS; i++){
		updateCarPosition(vPlayer, &voitures[i]);
	}
}

void updateCarsDisplay(VOITURE* voitures){
	int i=0;
	for(i=0;i<NB_CARS; i++){
		updateCarDisplay(voitures[i]);
	}
}

void removeCarsDisplay(VOITURE* voitures){
	int n=0;
	for(n=0; n<NB_CARS; n++){
		removeCarDisplay(voitures[n]);
	}
}


/*****************************************************************************/

void removeCarDisplay(VOITURE voiture){
	if(voiture.posy >= 0){
		gotoxy(ZERO_ROAD_LINE+ (voiture.posx*5)+1, ZERO_ROAD_COL+voiture.posy+1);
		backColour(BLACK);
		printf("   ");
		backColourDefault();
	}
}


// X COL / Y LIN
void updateCarDisplay(VOITURE voiture){
    if(voiture.etat == 'a' && voiture.posy >=0){
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
}

void updateCarPosition(VOITURE vPlayer, VOITURE* v2){
	//v2->posy = v2->posy + 1;
	//gotoxy(1, 45);
	//printf("%3d %3d",v2->posx, v2->posy);
    if(v2->etat == 'a'){
    	if(vPlayer.vitesse < v2->vitesse){
	    	v2->posy -= 1;
    	}else if(vPlayer.vitesse > v2->vitesse){
	    	v2->posy += 1;
    	}
    }
}