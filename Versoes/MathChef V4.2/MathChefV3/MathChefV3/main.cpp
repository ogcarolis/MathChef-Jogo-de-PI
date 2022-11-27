// Bibliotecas do allegro
#include <allegro5\allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <queue>

// Funções
#include "headers/setup.h"
#include "headers/event.h"
#include "headers/criarBotao.h"
#include "headers/botaoSelecionado.h"
#include "headers/drawButtons.h"
#include "headers/manipularEntrada.h"
#include "headers/insereLista.h"
#include "headers/imprimeLista.h"

// Structs
#include "structs/setup.h"
#include "structs/buttons.h"
#include "structs/lista.h"

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

    const int FPS = 30;
    bool gaming = true;
    bool start = false;

    int mouseX = 0, mouseY = 0;
    int QTD_INGREDIENTE = 5;
    int TIPO_OPERACAO = 1;
    
    bool concluido = false;
    char highscore[30];
    //-------------------------------CRIANDO OS OBJETOS---------------------------------//

    botao* comecar = NULL;
    botao* opcoes = NULL;
    botao* musica = NULL;

    setup* config = NULL;

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

    ALLEGRO_FONT* font = al_load_ttf_font("font/font-principal.ttf", 50, 0); 
    ALLEGRO_FONT* fontN = al_load_ttf_font("font/font-numero.ttf", 20, 0); 

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

            if (!start) {
                fundo = al_load_bitmap("img/fundo_inicio.png");
                logo = al_load_bitmap("img/logo-mathchef.png");

                al_draw_bitmap(fundo, 0, 0, 0);
                al_draw_bitmap(logo, 150, 130, 0);

                comecar = criarBotao(comecar, 1);
                opcoes = criarBotao(opcoes, 2);
                musica = criarBotao(musica, 3);

                drawButtons(comecar, display);
                drawButtons(opcoes, display);
                drawButtons(musica, display);

                al_flip_display();
            }
            else {
                al_draw_bitmap(config->fundo, 0, 0, 0);
                al_flip_display();
            }
        }

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { gaming = false; }

        //-------------------------------LOCALIZAÇÃO DO MOUSE---------------------------------//

        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseX = evento.mouse.x;
            mouseY = evento.mouse.y;
        }

        // Exemplo de ação ao clicar:
        // DOWN: Clicou no botão
        // UP: Soltou o botão

        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

            if (comecar->tipo && opcoes->tipo && musica->tipo) {
                if (start = botaoSelecionado(comecar, evento)) {
                    TIPO_OPERACAO = 1;
                    strcpy_s(highscore, sizeof highscore, "");

                    if (!concluido)
                    {
                        al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH_TELA / 2, 200, ALLEGRO_ALIGN_CENTRE, "Digite o seu nome:");

                        manipularEntrada(evento, highscore);

                        if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
                        {
                            concluido = true;
                        }
                    }
                }
                else if (start = botaoSelecionado(opcoes, evento)) {
                    TIPO_OPERACAO = 2;
                }
                else if (start = botaoSelecionado(musica, evento)) {
                    TIPO_OPERACAO = 3;
                }

                if (start) {
                    config = configSetup(config, TIPO_OPERACAO);

                    comecar->tipo = false;
                    opcoes->tipo = false;
                    musica->tipo = false;
                }

                al_draw_bitmap(fundo, 0, 0, 0);
            }
        }

        if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {}
    }

    return 0;
}