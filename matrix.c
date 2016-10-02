#include <stdio.h>
#include <stdlib.h>

int** create_matrix(int nb_line, int nb_col){
	int i;
	int **matrix;
	matrix = malloc(sizeof(int*)*nb_line);
	for(i=0; i<nb_line; i++){
		matrix[i] = malloc(sizeof(int)*nb_col);
	}
	return matrix;
}

void fill_matrix(int **matrix, int nb_line, int nb_col, int value){
	int i, j;
	for(i=0; i<nb_line; i++){
		for(j=0; j<nb_col; j++){
			matrix[i][j] = value;
		}
	}
}