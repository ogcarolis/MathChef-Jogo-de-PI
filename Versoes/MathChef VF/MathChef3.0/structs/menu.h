#pragma once
#include <allegro5/allegro.h>
#include "../structs/button.h"

typedef struct menu menu;
struct menu {
    ALLEGRO_BITMAP* fundo;
    ALLEGRO_BITMAP* logo;
    ALLEGRO_BITMAP* highScore;
    ALLEGRO_BITMAP* tutorial;
};