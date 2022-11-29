#pragma once
#include <allegro5/allegro.h>

typedef struct players players;
typedef struct players {
	char nome[30];
	int tipo;
	int score;
	struct players* prox;
};