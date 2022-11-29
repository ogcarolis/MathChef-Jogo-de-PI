#include <allegro5/allegro5.h>
#include <queue>
#include "../headers/criarBotao.h"

botao* criarBotao(botao* b, int tipo) {
	b = (botao*)malloc(sizeof(botao));

	if (tipo == 1) {
		b->x = 280;
		b->y = 410;
		b->obj = al_load_bitmap("img/btn-comecar.png");

		b->width = al_get_bitmap_width(b->obj);
		b->height = al_get_bitmap_height(b->obj);

	}
	if (tipo == 2) {
		b->x = 10;
		b->y = 5;
		b->obj = al_load_bitmap("img/btn-highscore.png");

		b->width = al_get_bitmap_width(b->obj);
		b->height = al_get_bitmap_height(b->obj);
	}
	if (tipo == 3) {
		b->x = 100;
		b->y = 10;
		b->obj = al_load_bitmap("img/btn-musica.png");

		b->width = al_get_bitmap_width(b->obj);
		b->height = al_get_bitmap_height(b->obj);
	}
	if (tipo == 4) {
		b->x = 70;
		b->y = 30;

		b->obj = al_load_bitmap("img/btn-sair.png");

		b->width = 199;
		b->height = 236;

		/*b->x = 97;
		b->y = 2;
		b->obj = al_load_bitmap("img/btn-musicaoff.png");

		b->width = al_get_bitmap_width(b->obj);
		b->height = al_get_bitmap_height(b->obj);*/
	}
	if (tipo == 5) {
		b->x = 355;
		b->y = 470;
		b->obj = al_load_bitmap("img/btn-home.png");

		b->width = al_get_bitmap_width(b->obj);
		b->height = al_get_bitmap_height(b->obj);
	}

	return b;
}