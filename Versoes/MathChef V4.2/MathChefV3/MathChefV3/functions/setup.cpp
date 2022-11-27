#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <queue>

#include "../headers/setup.h"
#include "../headers/manipularEntrada.h"
#include "../headers/event.h"

setup* configSetup(setup* config, int op) {
    config = (setup*)malloc(sizeof(setup));

    if (op == 1) {
        config->fundo = al_load_bitmap("img/fundo_menu.png");
        //strcpy(config->highscore, "");
        
        /*

        if (!config->concluido)
        {
            manipularEntrada(evento, config->highscore);

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                config->concluido = true;
            }
        } */

    }

    if (op == 2) {
        config->fundo = al_load_bitmap("img/fundo_sub.png");
    }

    if (op == 3) {
        config->fundo = al_load_bitmap("img/fundo_div.png");
    }

    return config;
}