#ifndef COLOUR_H_INCLUDED
#define COLOUR_H_INCLUDED

void foreColour(int colour);
void foreColourDefault();
void foreColourNum(int value);

void backColour(int colour);
void backColourDefault();
void backColourNum(int value);

void posXY(int x, int y);
void clrscr();


#define BLACK       0
#define RED         1
#define GREEN       2
#define YELLOW      3
#define BLUE        4
#define MAGENTA     5
#define CYAN        6
#define WHITE       7


#endif // COLOUR_H_INCLUDED
