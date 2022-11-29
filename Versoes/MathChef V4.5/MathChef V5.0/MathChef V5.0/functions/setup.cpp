#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <queue>

#include "../headers/setup.h"

setup* configSetup(setup* config, int op) {
    config = (setup*)malloc(sizeof(setup));
    
    if (op == 1) {
        config->fundo = al_load_bitmap("img/fundo_menu.png");        
    }

    return config;
}