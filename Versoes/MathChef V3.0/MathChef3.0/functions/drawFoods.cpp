#include <allegro5/allegro5.h>
#include <queue>

#include "../headers/drawFoods.h"

void drawFoods(food food, ALLEGRO_DISPLAY* display) {
    al_draw_bitmap(food.obj, food.x, food.y, 0);
}