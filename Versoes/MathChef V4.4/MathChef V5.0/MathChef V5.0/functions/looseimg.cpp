#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <queue>

#include "../headers/looseimg.h"

looseimg* loose_img(looseimg* limg, int type) {
	limg = (looseimg*)malloc(sizeof(looseimg));

	if (type == 1) {
		limg->img = al_load_bitmap("img/fundo_inicio.png");
	}
	if (type == 2) {
		limg->img = al_load_bitmap("img/logo-mathchef.png");
	}
	if (type == 3) {
		limg->img = al_load_bitmap("img/tutorial.png");
	}
	if (type == 4) {
		limg->img = al_load_bitmap("img/popup-highscore.png");
	}
	
	return limg;
}