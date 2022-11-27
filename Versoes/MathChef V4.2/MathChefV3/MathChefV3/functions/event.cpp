#include <allegro5/allegro5.h>
#include <queue>
#include "../headers/event.h"

void registerEvents(ALLEGRO_EVENT_QUEUE* evento, ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer) {
    al_install_mouse();
    al_register_event_source(evento, al_get_mouse_event_source());
    al_register_event_source(evento, al_get_display_event_source(display));
    al_register_event_source(evento, al_get_timer_event_source(timer));
}