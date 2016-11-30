#include <stdio.h>
#include <stdlib.h>
#include "types.h"

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

VOITURE* allocate_cars(int nb_cars){
	VOITURE *voitures;
	voitures = malloc(sizeof(VOITURE)*nb_cars);

	return voitures;
}

VOITURE** allocate_road_matrix(int nb_line, int nb_col){
	VOITURE **voitures;
	voitures = malloc(sizeof(VOITURE*)*nb_line);
	int i =0;
	for(i=0;i<nb_line; i++){
		voitures[i] = malloc(sizeof(VOITURE)*nb_col);
	}
	return voitures;
}