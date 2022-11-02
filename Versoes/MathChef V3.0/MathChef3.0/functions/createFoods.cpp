#include <allegro5/allegro5.h>
#include <queue>

#include "../headers/createFoods.h"

food createFoods(food foods[9], int tipo, int width_tela, int wh_food) {
    int x = 0;

    for (int i = 0; i < 9; i++) {
        foods[i].x = x;
        foods[i].y = width_tela / 1.5;
        foods[i].atived = true;
        foods[i].selected = false;

        x += wh_food + 30;
    }

    return foods[9];
}

