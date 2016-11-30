#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "types.h"

char key_pressed();
void runGame();
void updateCarsDisplay(VOITURE* voitures);
void updateCarsPosition(VOITURE vPlayer, VOITURE* voitures);
void updateCarsPosition(VOITURE vPlayer, VOITURE* voitures);
void removeCarDisplay(VOITURE voiture);
void updateCarDisplay(VOITURE voiture);
void updateCarPosition(VOITURE vPlayer, VOITURE* v2);
void removeCarsDisplay(VOITURE* voitures);
void printScore(int score);
void printSpeed(int speed);
void playSound(const char * name);
void killSound(const char * name);

#endif
