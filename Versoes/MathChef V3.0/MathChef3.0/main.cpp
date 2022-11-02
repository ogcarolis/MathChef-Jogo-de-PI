// Bibliotecas do allegro
#include <allegro5\allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <queue>

// Fun��es
#include "headers/event.h"
#include "headers/drawFoods.h"

// Structs
#include "structs/foods.h"

// Bibliotecas padr�es do C
#include "stdlib.h"
#include "time.h"
#include <string.h>
#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    //-------------------------------VARI�VEIS---------------------------------//

    const int WIDTH_TELA = 780;
    const int HEIGHT_TELA = 600;

    const int WH_FOOD = 65;

    const int FPS = 60;
    bool gaming = true;

    int mouseX = 0, mouseY = 0;
    int QTD_FOOD = 8;
    int TIPO_OPERACAO = 1;

    //-------------------------------DISPLAY---------------------------------//

    al_init(); //Inicia o Allegro e os seus Addons
    al_init_image_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();


    //-------------------------------CRIANDO OS OBJETOS---------------------------------//
    food foods[9];
    int x = 0;

    if (TIPO_OPERACAO == 1) {
        foods[0].obj = al_load_bitmap("img/comida-soma1.png");
        foods[1].obj = al_load_bitmap("img/comida-soma2.png");
        foods[2].obj = al_load_bitmap("img/comida-soma3.png");
        foods[3].obj = al_load_bitmap("img/comida-soma4.png");
        foods[4].obj = al_load_bitmap("img/comida-soma5.png");
        foods[5].obj = al_load_bitmap("img/comida-soma6.png");
        foods[6].obj = al_load_bitmap("img/comida-soma7.png");
        foods[7].obj = al_load_bitmap("img/comida-soma8.png");
    }

    for (int i = 0; i < 9; i++) {
        foods[i].x = x;
        foods[i].y = WIDTH_TELA / 1.95;
        foods[i].atived = true;
        foods[i].selected = false;

        x += WH_FOOD + 35;
    }

    //-------------------------------VARI�VEIS DO ALLEGRO---------------------------------//

    ALLEGRO_DISPLAY* display = al_create_display(WIDTH_TELA, HEIGHT_TELA); //Dimens�es do Display
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE* eventos = al_create_event_queue(); //Cria uma fila de eventos
    ALLEGRO_BITMAP* fundo;
    ALLEGRO_BITMAP* personagem;

    int displayX = al_get_display_width(display);
    int displayY = al_get_display_height(display);

    //-------------------------------FILA DE EVENTOS---------------------------------//
    registerEvents(eventos, display, timer);
   // al_hide_mouse_cursor(display);
    al_set_window_title(display, "Math Chef");

    assert(display != NULL);
    al_start_timer(timer);

    while (gaming) {

        ALLEGRO_EVENT evento; //Gera os Eventos
        al_wait_for_event(eventos, &evento);

        if (evento.type == ALLEGRO_EVENT_TIMER) {
            fundo = al_load_bitmap("img/fundo_soma.png");
            personagem = al_load_bitmap("img/p-soma.png");
            al_draw_bitmap(fundo, 0, 0, 0);
            al_draw_bitmap(personagem, 200, 10, 0);

            for (int i = 0; i < QTD_FOOD; i++) {
                if (foods[i].x >= -1 && foods[i].x <= WIDTH_TELA * (i + 1) && !foods[i].selected) {
                    foods[i].x += 1.0;
                }

                if (foods[i].x >= WIDTH_TELA) {
                    foods[i].x = -1;
                }

                if (foods[i].atived) {
                    al_draw_bitmap(foods[i].obj, foods[i].x, foods[i].y, 0);
                }
            }

            al_flip_display();
        }

        //-------------------------------LOCALIZA��O DO MOUSE---------------------------------//

        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseX = evento.mouse.x;
            mouseY = evento.mouse.y;
        }

        // Exemplo de a��o ao clicar:
        // DOWN: Clicou no bot�o
        // UP: Soltou o bot�o

        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

            //-------------------------------DI�LOGO DE TEXTO---------------------------------//

            
        }

          

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { gaming = false; }
    }

    return 0;
}