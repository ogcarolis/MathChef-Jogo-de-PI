#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <queue>

#include "../headers/drawButtons.h" 

void drawButtons(botao* b, ALLEGRO_DISPLAY* display) {
    al_draw_bitmap(b->obj, b->x, b->y, 0);
}