#include <allegro5/allegro5.h>
#include <queue>
#include "../headers/botaoSelecionado.h"

bool botaoSelecionado(botao* b, ALLEGRO_EVENT evento) {
    if (evento.mouse.x >= b->x && evento.mouse.x <= b->x + b->width &&
        evento.mouse.y >= b->y && evento.mouse.y <= b->y + b->height) {

        if (b->obj == al_load_bitmap("img/btn-home.png")) {
            return false;
        }
        else
            return true;
    }
    return false;
}