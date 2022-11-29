#pragma once
#include <allegro5/allegro.h>

typedef struct food food;
struct food {
    ALLEGRO_BITMAP* obj;
    ALLEGRO_BITMAP* placa;
    int number;
    float x, y;
    bool atived, selected;
};
