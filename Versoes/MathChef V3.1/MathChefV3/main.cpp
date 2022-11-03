// Bibliotecas do allegro
#include <allegro5\allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <queue>

// Funções
#include "headers/event.h"
#include "headers/criarBotao.h"
#include "headers/botaoSelecionado.h" 

// Structs
#include "structs/buttons.h"

// Bibliotecas padrões do C
#include "stdlib.h"
#include "time.h"
#include <string.h>
#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    //-------------------------------VARIÁVEIS---------------------------------//

    const int WIDTH_TELA = 780;
    const int HEIGHT_TELA = 600;

    const int WH_INGREDIENTE = 64;
    const int WH_NUMERO = 24;

    const float FPS = 60.0;
    bool gaming = true;

    int mouseX = 0, mouseY = 0;
    int QTD_INGREDIENTE = 5;
    int TIPO_OPERACAO = 1;

    float x_botao, y_botao;

    //-------------------------------CRIANDO OS OBJETOS---------------------------------//

    botao* comecar = NULL; 
    botao* opcoes = NULL; 
    botao* musica = NULL; 

    //-------------------------------DISPLAY---------------------------------//

    al_init(); //Inicia o Allegro e os seus Addons
    al_init_image_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    //-------------------------------VARIÁVEIS DO ALLEGRO---------------------------------//

    ALLEGRO_DISPLAY* display = al_create_display(WIDTH_TELA, HEIGHT_TELA); //Dimensões do Display
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE* eventos = al_create_event_queue(); //Cria uma fila de eventos
    ALLEGRO_BITMAP* fundo = NULL;
    ALLEGRO_BITMAP* logo = NULL;

    int displayX = al_get_display_width(display);
    int displayY = al_get_display_height(display);

    //-------------------------------FILA DE EVENTOS---------------------------------//
    registerEvents(eventos, display, timer);
    //al_hide_mouse_cursor(display);
    al_set_window_title(display, "Math Chef");

    assert(display != NULL);
    al_start_timer(timer);

    while (gaming) {

        ALLEGRO_EVENT evento; //Gera os Eventos
        al_wait_for_event(eventos, &evento);

        if (evento.type == ALLEGRO_EVENT_TIMER) {
            fundo = al_load_bitmap("img/fundo_inicio.png");
            logo = al_load_bitmap("img/logo-mathchef.png");

            al_draw_bitmap(fundo, 0, 0, 0);
            al_draw_bitmap(logo, 75, 50, 0);
           
            comecar = criarBotao(comecar, 230, 380, 1);
            opcoes = criarBotao(opcoes, 0, -10, 2);
            musica = criarBotao(musica, 90, -10, 3);

            al_draw_bitmap(comecar->obj, comecar->x, comecar->y, 0);
            al_draw_bitmap(opcoes->obj, opcoes->x, opcoes->y, 0); 
            al_draw_bitmap(musica->obj, musica->x, musica->y, 0); 

            al_flip_display();

        }

        //-------------------------------LOCALIZAÇÃO DO MOUSE---------------------------------//

        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseX = evento.mouse.x;
            mouseY = evento.mouse.y;
        }

        // Exemplo de ação ao clicar:
        // DOWN: Clicou no botão
        // UP: Soltou o botão

        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

            comecar = botaoSelecionado(comecar, evento);
            opcoes = botaoSelecionado(opcoes, evento);
            musica = botaoSelecionado(musica, evento);

            if (comecar->tipo) {
                al_destroy_bitmap(fundo);
                fundo = al_load_bitmap("img/fundo_soma.png");
            }
            
            if (opcoes->tipo) {
                al_destroy_bitmap(fundo);
                fundo = al_load_bitmap("img/fundo_sub.png");
            }

            if (musica->tipo) {
                al_destroy_bitmap(fundo);
                fundo = al_load_bitmap("img/fundo_mult.png");
            }

            al_draw_bitmap(fundo, 0, 0, 0);
        }



        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { gaming = false; }
    }

    return 0;
}