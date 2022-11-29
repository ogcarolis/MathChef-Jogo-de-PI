#pragma once
#include <allegro5/allegro.h>

typedef struct setup setup;
struct setup {
    ALLEGRO_BITMAP* p;
    ALLEGRO_BITMAP* base;
    ALLEGRO_BITMAP* fundo;
    ALLEGRO_BITMAP* fundoF;
    ALLEGRO_BITMAP* timer;
    ALLEGRO_COLOR color;

    float xp, yp;
};

