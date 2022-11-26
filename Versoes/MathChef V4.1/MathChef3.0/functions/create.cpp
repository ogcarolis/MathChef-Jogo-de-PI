#include <allegro5/allegro5.h>
#include <queue>

#include "../headers/create.h"

food* createFoods(food* foods[7], int tipo, int width, int wh_food) {
    int x = 0;

    for (int i = 0; i < 8; i++) {
        foods[i] = (food*) malloc(sizeof(food));
        foods[i]->x = x;
        foods[i]->y = width / 1.95;
        foods[i]->atived = true;
        foods[i]->selected = false;
        foods[i]->placa = al_load_bitmap("img/base-num.png");

        x += wh_food + 47;
    }
    

    if (tipo == 1) {
        foods[0]->obj = al_load_bitmap("img/comida-soma1.png");
        foods[1]->obj = al_load_bitmap("img/comida-soma2.png");
        foods[2]->obj = al_load_bitmap("img/comida-soma3.png");
        foods[3]->obj = al_load_bitmap("img/comida-soma4.png");
        foods[4]->obj = al_load_bitmap("img/comida-soma5.png");
        foods[5]->obj = al_load_bitmap("img/comida-soma6.png");
        foods[6]->obj = al_load_bitmap("img/comida-soma7.png");
    }

    if (tipo == 2) {
        foods[0]->obj = al_load_bitmap("img/comida-sub1.png");
        foods[1]->obj = al_load_bitmap("img/comida-sub2.png");
        foods[2]->obj = al_load_bitmap("img/comida-sub3.png");
        foods[3]->obj = al_load_bitmap("img/comida-sub4.png");
        foods[4]->obj = al_load_bitmap("img/comida-sub5.png");
        foods[5]->obj = al_load_bitmap("img/comida-sub6.png");
        foods[6]->obj = al_load_bitmap("img/comida-sub7.png");
    }

    if (tipo == 3) {
        foods[0]->obj = al_load_bitmap("img/comida-div1.png");
        foods[1]->obj = al_load_bitmap("img/comida-div2.png");
        foods[2]->obj = al_load_bitmap("img/comida-div3.png");
        foods[3]->obj = al_load_bitmap("img/comida-div4.png");
        foods[4]->obj = al_load_bitmap("img/comida-div5.png");
        foods[5]->obj = al_load_bitmap("img/comida-div6.png");
        foods[6]->obj = al_load_bitmap("img/comida-div7.png");
    }

    if (tipo == 4) {
        foods[0]->obj = al_load_bitmap("img/comida-mult1.png");
        foods[1]->obj = al_load_bitmap("img/comida-mult2.png");
        foods[2]->obj = al_load_bitmap("img/comida-mult3.png");
        foods[3]->obj = al_load_bitmap("img/comida-mult4.png");
        foods[4]->obj = al_load_bitmap("img/comida-mult5.png");
        foods[5]->obj = al_load_bitmap("img/comida-mult6.png");
        foods[6]->obj = al_load_bitmap("img/comida-mult7.png");
    }
   
    return foods[7];
}

button* createBottonsOp(button* btn, int tipo) {
    btn = (button*) malloc(sizeof(button));

    if (tipo == 1) {
        btn->obj = al_load_bitmap("img/op-soma.png");
        btn->width = 199;
        btn->height = 236;
        btn->x = 130;
        btn->y = 50;
    }

    if (tipo == 2) {
        btn->obj = al_load_bitmap("img/op-sub.png");
        btn->width = 243;
        btn->height = 234;
        btn->x = 115;
        btn->y = 320;
    }

    if (tipo == 3) {
        btn->obj = al_load_bitmap("img/op-div.png");
        btn->width = 199;
        btn->height = 243;
        btn->x = 425;
        btn->y = 310;
    }

    if (tipo == 4) {
        btn->obj = al_load_bitmap("img/op-mult.png");
        btn->width = 304;
        btn->height = 236;
        btn->x = 370;
        btn->y = 50;
    }

    return btn;
}

