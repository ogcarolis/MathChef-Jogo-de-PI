#include <allegro5/allegro5.h>
#include <queue>
#include "criarBotao.h"

botao* criarBotao(botao* b, float x, float y, int tipo) {
	b = (botao*)malloc(sizeof(botao)); 
	b->x = x;
	b->y = y;

	if (tipo == 1) {
		b->obj = al_load_bitmap("img/btn-comecar.png");
		
		b->width = al_get_bitmap_width(b->obj); 
		b->height = al_get_bitmap_height(b->obj); 

	}
	if (tipo == 2) {
		b->obj = al_load_bitmap("img/btn-opcoes.png");

		b->width = al_get_bitmap_width(b->obj);
		b->height = al_get_bitmap_height(b->obj);
	}
	if (tipo == 3) {
		b->obj = al_load_bitmap("img/btn-musica.png");

		b->width = al_get_bitmap_width(b->obj);
		b->height = al_get_bitmap_height(b->obj);
	}

	return b;
}