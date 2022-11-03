#include <allegro5/allegro5.h>
#include <queue>
#include "../headers/botaoSelecionado.h"

botao* botaoSelecionado(botao* b, ALLEGRO_EVENT evento) {
    if (evento.mouse.x >= b->x && evento.mouse.x <= b->x + b->width &&
        evento.mouse.y >= b->y && evento.mouse.y <= b->y + b->height) {
        b->tipo = true;
        return b;
    }
    else {
        b->tipo = false;
        return b;
    }
}