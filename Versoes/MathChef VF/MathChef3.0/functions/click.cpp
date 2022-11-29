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

bool clickFood(food food, ALLEGRO_EVENT evento, int wh_food) {
    if (evento.mouse.x >= food.x && evento.mouse.x <= food.x + wh_food &&
        evento.mouse.y >= food.y - 25 && evento.mouse.y <= food.y + wh_food) {
        return true;
    }

    return false;
}
