#ifndef CREATE
#define CREATE
#include "../structs/foods.h"
#include "../structs/button.h"

food* createFoods(food* foods[7], int tipo, int width_tela, int wh_food);
button* createBottonsOp(button* btn, int tipo);

#endif