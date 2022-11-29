#ifndef CLICK
#define CLICK
#include "../structs/foods.h"
#include "../structs/button.h"

bool clickButton(button* btn, ALLEGRO_EVENT evento);
bool clickFood(food food, ALLEGRO_EVENT evento, int wh_food);

#endif
