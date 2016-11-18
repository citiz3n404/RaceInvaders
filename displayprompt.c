#include <stdio.h>
#include <stdlib.h>
#include "colour.h"
#include "constants.h"
#include "types.h"

void displayScore(int speed, int score, int bestScore){
	posXY(0,1);
	printf("╔════════════════════════╗\n");
	printf("║ SPEED:     %6d km/h ║\n", speed);
	printf("╠════════════════════════╣\n");
	printf("║ SCORE:      %6d pts ║\n", score);
	printf("╠════════════════════════╣\n");
	printf("║ BEST SCORE: %6d pts ║\n", bestScore);
	printf("╚════════════════════════╝\n");
	posXY(1,50);
}

void displaySpaceInvader (){
    int i, j;
    int spaceInvader[8][11]={{0,0,1,0,0,0,0,0,1,0,0},
                            {0,0,0,1,0,0,0,1,0,0,0},
                            {0,0,1,1,1,1,1,1,1,0,0},
                            {0,1,1,0,1,1,1,0,1,1,0},
                            {1,1,1,1,1,1,1,1,1,1,1},
                            {1,0,1,1,1,1,1,1,1,0,1},
                            {1,0,1,0,0,0,0,0,1,0,1},
                            {0,0,0,1,1,0,1,1,0,0,0}};
    printf("\n");

    for (i=0; i<8; i++){
        printf("\t\t\t\t     ");
        for (j=0; j<11; j++){
            if(spaceInvader[i][j]==1){
                backColour(RED);
                printf("  ");
                backColourDefault();
            }else {printf("  ");}

        }
        printf("\n");
    }
    printf("\n");
}





void displayRoad(int **matrix){
	int i, j;
	for(i=0; i<NB_LINE; i++){
		backColourDefault();
		printf("\t\t\t\t\t║");
		backColourNum(0);
		for(j=0; j<NB_COL; j++){


			switch(matrix[i][j]){
				case GRID_ELEMENT_CAR: 
					foreColour(YELLOW);
					printf(" 🚘 ");
					foreColourDefault();
					break;
				case GRID_ELEMENT_SHOOT:
					printf(" ");
					foreColour(RED);
					printf("|");
					foreColourDefault();
					printf(" ");
					break;
				case GRID_ELEMENT_EMPTY:
					printf("   ");
					break;
				case GRID_ELEMENT_BUS:
					foreColour(CYAN);
					printf(" 🚍 ");
					foreColourDefault();
					break;
				case GRID_ELEMENT_EXPLOSION:
					foreColour(RED);
					printf(" 💥 ");
					foreColourDefault();
					break;
				default:
					printf("   ");
					break;
			}

			if(j!=NB_COL-1){
				foreColour(WHITE);
				printf(" |");
				foreColourDefault();
			}else{
				printf(" ");
			}
			

		}
		backColourDefault();
		printf("║ \n");
	}
}

void displayColours(){
	int i;

	for(i=0; i<255; i++){
		foreColourNum(i);
		printf("%d \n", i);
		foreColourDefault();
	}
}