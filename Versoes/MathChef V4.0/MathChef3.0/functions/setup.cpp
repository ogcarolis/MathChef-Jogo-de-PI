#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <queue>

#include "../headers/setup.h"

setup* configSetup(setup* config, int op) {
    config = (setup*) malloc(sizeof(setup));

    if (op == 0) {
        config->fundo = al_load_bitmap("img/fundo_op.png");
    }

    if (op == 1) {
        config->fundo = al_load_bitmap("img/fundo_soma.png");
        config->p = al_load_bitmap("img/p-soma.png");
        config->color = al_map_rgb(244, 206, 0);

        config->xp = -68;
        config->yp = -170;
    }

    if (op == 2) {
        config->fundo = al_load_bitmap("img/fundo_sub.png");
        config->p = al_load_bitmap("img/p-sub.png");
        config->color = al_map_rgb(255, 0, 237);

        config->xp = -20;
        config->yp = -170;
    }

    if (op == 3) {
        config->fundo = al_load_bitmap("img/fundo_div.png");
        config->p = al_load_bitmap("img/p-div.png");
        config->color = al_map_rgb(255, 57, 67);

        config->xp = 230;
        config->yp = 10;
    }

    if (op == 4) {
        config->fundo = al_load_bitmap("img/fundo_mult.png");
        config->p = al_load_bitmap("img/p-mult.png");
        config->color = al_map_rgb(0, 244, 165);

        config->xp = 170;
        config->yp = 10;
    }

    return config;
}