#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <queue>

#include "../headers/players.h"

players* insertPlayers(players* l, char nome[], int score, int size, int tipo) {
    players* novo = (players*)malloc(sizeof(players));
    int i;
    for (i = 0; i < size; i++) {
        novo->nome[i] = nome[i];
    }
    novo->nome[size] = '\0';
    novo->score = score;
    novo->tipo = tipo;
    novo->prox = l;
    return novo;
}


