#pragma once
#include <allegro5/allegro.h>

typedef struct button button;
struct button {
    ALLEGRO_BITMAP* obj;
    bool atived;
    float x, y;
    int width, height;
};


