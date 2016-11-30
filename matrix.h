#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include "types.h"
int** create_matrix(int nb_line, int nb_col);
void fill_matrix(int **matrix, int nb_line, int nb_col, int value);
VOITURE* allocate_cars(int nb_cars);
VOITURE** allocate_road_matrix(int nb_line, int nb_col);

#endif