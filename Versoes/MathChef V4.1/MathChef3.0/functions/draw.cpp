#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <queue>

#include "../headers/draw.h"

void drawFoods(food* food, ALLEGRO_DISPLAY* display, ALLEGRO_COLOR color, ALLEGRO_FONT* font) {
    al_draw_bitmap(food->placa, food->x + 12, food->y - 25, 0);
    
    if (food->number < 10) {
        al_draw_textf(font, color, food->x + 26, food->y - 17, 0, "0%d", food->number);
    }else {
        al_draw_textf(font, color, food->x + 26, food->y - 17, 0, "%d", food->number);
    }
    
    al_draw_bitmap(food->obj, food->x, food->y, 0);
}

void drawButtons(button* btn, ALLEGRO_DISPLAY* display) {
    al_draw_bitmap(btn->obj, btn->x, btn->y, 0);
}