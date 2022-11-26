#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <queue>

#include "../headers/setup.h"

setup* configSetup(setup* config, int op) {
    config = (setup*) malloc(sizeof(setup));
    config->base = al_load_bitmap("img/base-foods.png");

    if (op == 0) {
        config->fundo = al_load_bitmap("img/fundo_op.png");
    }

    if (op == 1) {
        config->fundo = al_load_bitmap("img/fundo_soma.png");
        config->p = al_load_bitmap("img/p-soma.png");
        config->color = al_map_rgb(201, 130, 0);
    }

    if (op == 2) {
        config->fundo = al_load_bitmap("img/fundo_sub.png");
        config->p = al_load_bitmap("img/p-sub.png");
        config->color = al_map_rgb(159, 0, 103);
    }

    if (op == 3) {
        config->fundo = al_load_bitmap("img/fundo_div.png");
        config->p = al_load_bitmap("img/p-div.png");
        config->color = al_map_rgb(148, 0, 4);
    }

    if (op == 4) {
        config->fundo = al_load_bitmap("img/fundo_mult.png");
        config->p = al_load_bitmap("img/p-mult.png");
        config->color = al_map_rgb(0, 102, 116);
    }

    config->xp = 218;
    config->yp = 175;

    return config;
}