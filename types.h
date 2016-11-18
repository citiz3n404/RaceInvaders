#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED


typedef struct voiture {
	int posx; /* Position courante x de la voiture */
	int posy; /* Position courante y de la voiture */
	char type; /* ’v’=>voiture, ’c’=>camion, etc. */
	int couleur; /* Couleur du véhicule */
	char etat; /* État du véhicule => actif ou inactif */
	/* Vous pouvez rajouter d’autres variables si nécessaire */
} VOITURE;


typedef struct spaceInvader {
	int life;

} SPACEINVADER;

#endif