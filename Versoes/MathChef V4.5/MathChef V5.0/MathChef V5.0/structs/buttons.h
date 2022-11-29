#ifndef BUTTONS
#define BUTTONS

#include <allegro5/allegro5.h>
#include <queue>

//Inicio da struct de botao do menu
typedef struct botao botao;
struct botao {
	bool tipo;
	float x, y;
	ALLEGRO_BITMAP* obj;
	int width, height;
};

#endif