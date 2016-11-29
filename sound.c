#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char * sound= "./sounds/sound1.mp3";

void playSound(const char * name){
	char * res = malloc(100*sizeof(char));
	char * play = "play -q ";
	char * esperluette="&";

	strcat(res, play);
	strcat(res, name);
	strcat(res, esperluette);

	system(res);
}

void killSound(const char * name){
	char * res = malloc(100*sizeof(char));
	char * script ="./sound_script.sh ";

	strcat(res, script);
	strcat(res, name);

	system(res);
}