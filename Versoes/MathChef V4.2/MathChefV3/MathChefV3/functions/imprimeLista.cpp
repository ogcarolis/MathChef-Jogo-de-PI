#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <queue>

#include "../headers/imprimeLista.h"
#include "../structs/lista.h"

void imprimeLista(lista* l, int WIDTH_TELA, int HEIGHT_TELA, ALLEGRO_FONT* font) {
    //algo como printf escrito "HIGHSCORE"

    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH_TELA / 2,
        (HEIGHT_TELA / 2 - al_get_font_ascent(font)) / 2,
        ALLEGRO_ALIGN_CENTRE, "HIGHSCORES");
    do {
        //printf("%s\n", l->highscore);
        l = l->prox;
    } while (l != NULL);
}
