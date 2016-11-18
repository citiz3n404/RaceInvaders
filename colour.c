#include <stdio.h>
#include "colour.h"

void foreColour(int colour){
    if(colour >= BLACK && colour <= WHITE){
        printf("\e[%dm",30 + colour);
    }
}

void foreColourNum(int value){
    printf("\e[38;5;%dm", value);

}

void foreColourDefault(){
	printf("\e[39m");
}

void backColour(int colour){
    if(colour >= BLACK && colour <= WHITE){
        printf("\e[%dm",40 + colour);
    }
}

void backColourNum(int value){
	printf("\e[30;48;5;%dm",value);
}

void backColourDefault(){
	printf("\e[49m");
}

void posXY(int x, int y){
    if(x>=0 && y >=0){
        printf("\e[%d;%dH",y+1,x+1);
    }
}

void clrscr(){
    printf("\e[2J");
    printf("\e[%d;%dH",0,0);
}
