#ifndef DRAW_FOODS
#define DRAW_FOODS
#include "../structs/foods.h"
#include "../structs/button.h"
#include "../structs/setup.h"
#include "../structs/players.h"

void drawFoods(food food, ALLEGRO_COLOR color, ALLEGRO_FONT* font);
void drawEndGame(setup* config, ALLEGRO_BITMAP* end, ALLEGRO_FONT* font, ALLEGRO_FONT* fontT, int score, char nome[]);

void drawButtons(button* btn);
void drawTimer(int min, int seg, ALLEGRO_FONT* fontT, ALLEGRO_COLOR colorTemp);
void drawNumberOP(int numero, ALLEGRO_FONT* font, ALLEGRO_COLOR color);
void drawTitleOP(int tipo, ALLEGRO_FONT* font, ALLEGRO_COLOR color);
void drawScore(int score, ALLEGRO_FONT* font, ALLEGRO_COLOR color);
void drawPlayers(players* l);

#endif