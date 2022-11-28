#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <queue>

#include "../headers/setup.h"
#include "../headers/manipularEntrada.h"
#include "../headers/event.h"

#include "../headers/criarBotao.h"
#include "../headers/drawButtons.h"

setup* configSetup(setup* config, int op, botao* b, ALLEGRO_DISPLAY* display, highscoreconfig* hs) {
    config = (setup*)malloc(sizeof(setup));
    hs = (highscoreconfig*)malloc(sizeof(highscoreconfig));   

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
        //highscore        config->fundo = al_load_bitmap("img/fundo_menu.png");
        hs->img = al_load_bitmap("img/popup-fimjogo.png");
    }

    if (op == 3) {
        //musica
        
    }

    return config;
}