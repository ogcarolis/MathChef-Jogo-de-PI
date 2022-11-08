#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <queue>

#include "../headers/draw.h"

void drawFoods(food food, ALLEGRO_DISPLAY* display, ALLEGRO_COLOR color, ALLEGRO_FONT* font) {
    al_draw_bitmap(food.obj, food.x, food.y, 0);
    al_draw_textf(font, color, food.x + 66, food.y + 38, 0, "%d", food.number);
}

void drawButtons(button* btn, ALLEGRO_DISPLAY* display) {
    al_draw_bitmap(btn->obj, btn->x, btn->y, 0);
}