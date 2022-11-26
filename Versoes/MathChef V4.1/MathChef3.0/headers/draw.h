#ifndef DRAW_FOODS
#define DRAW_FOODS
#include "../structs/foods.h"
#include "../structs/button.h"

void drawFoods(food* food, ALLEGRO_DISPLAY* display, ALLEGRO_COLOR color, ALLEGRO_FONT* font);
void drawButtons(button* btn, ALLEGRO_DISPLAY* display);
#endif