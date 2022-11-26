#include <allegro5/allegro5.h>
#include <queue>

#include "../headers/click.h"

bool clickButton(button* btn, ALLEGRO_EVENT evento) {
    if (evento.mouse.x >= btn->x && evento.mouse.x <= btn->x + btn->width &&
        evento.mouse.y >= btn->y && evento.mouse.y <= btn->y + btn->height) {
        return true;
    }
    
    return false;
}
