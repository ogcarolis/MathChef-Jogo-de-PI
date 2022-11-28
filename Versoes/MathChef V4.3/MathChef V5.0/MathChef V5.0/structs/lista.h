#pragma once
#include <allegro5/allegro.h>

typedef struct lista {
	char highscore[30];
	struct lista* prox;
}lista;