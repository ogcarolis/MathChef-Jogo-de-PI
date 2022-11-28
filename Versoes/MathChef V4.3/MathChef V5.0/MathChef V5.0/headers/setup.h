#ifndef SETUP
#define SETUP
#include "../structs/setup.h"
#include "../structs/lista.h"
#include "../structs/buttons.h"
#include "../structs/highscoreConfig.h"

setup* configSetup(setup* config, int op, botao* b, ALLEGRO_DISPLAY* display, highscoreconfig* hs);

#endif