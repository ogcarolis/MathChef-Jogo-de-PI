#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <queue>

#include "../headers/highscore.h"

highscoreconfig* highscores(highscoreconfig* hs) {
	hs = (highscoreconfig*)malloc(sizeof(highscoreconfig)); 

	hs->img = al_load_bitmap("img/popup-highscore.png");
	 
	return hs;
}