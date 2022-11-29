#ifndef CREATE
#define CREATE

#include "../structs/foods.h"
#include "../structs/button.h"
#include "../structs/menu.h"

food* createFoods(food* foods, int tipo, int width_tela, int wh_food);
menu* createMenu(menu* menuG);
button* createButtonsMenu(button* b, int tipo);
button* createButtonsOp(button* btn, int tipo);


#endif