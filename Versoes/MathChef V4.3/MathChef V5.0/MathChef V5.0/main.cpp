// Bibliotecas do allegro
#include <allegro5\allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <queue>

// Funções
#include "headers/setup.h"
#include "headers/event.h"
#include "headers/criarBotao.h"
#include "headers/botaoSelecionado.h"
#include "headers/drawButtons.h"
#include "headers/manipularEntrada.h"
#include "headers/lista.h"
#include "headers/highscore.h"

// Structs
#include "structs/setup.h"
#include "structs/buttons.h"
#include "structs/lista.h"
#include "structs/highscoreConfig.h"

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
    bool botaoMusica = false;
    bool botaoMusicaOff = false;

    bool musicaTocando;

    int mouseX = 0, mouseY = 0;
    int QTD_INGREDIENTE = 5;
    int TIPO_OPERACAO = 1;

    bool concluido = false;
    char nome[30];
    int posicao_vetor = 0;
    int tecla = 0;

    //-------------------------------CRIANDO OS OBJETOS---------------------------------//

    botao* comecar = NULL;
    botao* highscore = NULL;
    botao* musica = NULL;
    botao* musicaoff = NULL;
    botao* voltar = NULL;

    setup* config = NULL;
    lista* list = NULL;
    highscoreconfig* hs = NULL;

    //-------------------------------DISPLAY---------------------------------//

    al_init(); //Inicia o Allegro e os seus Addons
    al_init_image_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(10);

    //-------------------------------VARIÁVEIS DO ALLEGRO---------------------------------//

    ALLEGRO_DISPLAY* display = al_create_display(WIDTH_TELA, HEIGHT_TELA); //Dimensões do Display
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE* eventos = al_create_event_queue(); //Cria uma fila de eventos

    ALLEGRO_SAMPLE* musica_de_fundo = NULL;
    ALLEGRO_SAMPLE_INSTANCE* inst_musica_de_fundo = NULL;

    ALLEGRO_BITMAP* fundo = NULL;
    ALLEGRO_BITMAP* logo = NULL;

    ALLEGRO_FONT* font = al_load_ttf_font("font/font-principal.ttf", 50, 0);
    ALLEGRO_FONT* fontN = al_load_ttf_font("font/font-numero.ttf", 20, 0);

    int displayX = al_get_display_width(display);
    int displayY = al_get_display_height(display);

    musica_de_fundo = al_load_sample("music/intro-theme.wav");
    inst_musica_de_fundo = al_create_sample_instance(musica_de_fundo);

    al_attach_sample_instance_to_mixer(inst_musica_de_fundo, al_get_default_mixer());

    al_set_sample_instance_playmode(inst_musica_de_fundo, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(inst_musica_de_fundo, 0.5);

    //-------------------------------FILA DE EVENTOS---------------------------------//
    registerEvents(eventos, display, timer);
    al_register_event_source(eventos, al_get_keyboard_event_source());
    al_register_event_source(eventos, al_get_mouse_event_source());
    //al_hide_mouse_cursor(display);
    al_set_window_title(display, "Math Chef");

    assert(display != NULL);
    al_start_timer(timer);

    al_play_sample_instance(inst_musica_de_fundo);
    musicaTocando = true;

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
                highscore = criarBotao(highscore, 2);
                musica = criarBotao(musica, 3);
                musicaoff = criarBotao(musicaoff, 4);

                drawButtons(comecar, display);
                drawButtons(highscore, display);
                drawButtons(musica, display);

                if (botaoMusica) {
                    al_destroy_bitmap(musica->obj);
                    drawButtons(musicaoff, display);
                    al_stop_sample_instance(inst_musica_de_fundo);
                    musicaTocando = false;
                }
                
                if (botaoMusicaOff) {
                    al_play_sample_instance(inst_musica_de_fundo);
                    musicaTocando = true;
                }
            }
            else {
                if (TIPO_OPERACAO == 1) {
                    al_draw_bitmap(config->fundo, 0, 0, 0);

                    drawButtons(musica, display);
                    drawButtons(highscore, display);

                    if (musicaTocando) {
                        al_play_sample_instance(inst_musica_de_fundo);
                    }
                    else {
                        al_stop_sample_instance(inst_musica_de_fundo);
                    }
                }
                if (TIPO_OPERACAO == 2) {
                    al_draw_bitmap(hs->img, 10, 5, 0);

                    al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH_TELA / 2) + 3, 460, ALLEGRO_ALIGN_CENTRE, "Pressione espaco");
                    al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH_TELA / 2) + 3, 498, ALLEGRO_ALIGN_CENTRE, "para voltar");
                    
                    if (!(al_stop_sample_instance(inst_musica_de_fundo))) {
                        al_play_sample_instance(inst_musica_de_fundo);
                    }
                    else {
                        al_stop_sample_instance(inst_musica_de_fundo);
                    }
                }
                if (botaoMusica) {
                    al_destroy_bitmap(musica->obj);
                    drawButtons(musicaoff, display);
                    al_stop_sample_instance(inst_musica_de_fundo);
                    musicaTocando = false;
                }

                if (botaoMusicaOff) {
                    al_destroy_bitmap(musicaoff->obj); 
                    al_play_sample_instance(inst_musica_de_fundo); 
                    musicaTocando = true;
                }
            }

            al_flip_display();
        }

        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (evento.keyboard.keycode == ALLEGRO_KEY_SPACE && start) {
                tecla = 1;
            }
        }

        if (tecla) {
            start = false;
            tecla = 0;
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

            if (comecar->tipo && highscore->tipo && musica->tipo && musicaoff->tipo) {
                if (start = botaoSelecionado(comecar, evento)) {
                    TIPO_OPERACAO = 1;
                    /*strcpy_s(highscore, sizeof highscore, "");
                    if (!concluido)
                    {
                        al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH_TELA / 2, 200, ALLEGRO_ALIGN_CENTRE, "Digite o seu nome:");

                        manipularEntrada(evento, highscore);

                        if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
                        {
                            concluido = true;
                        }
                    }  */
                }
                else if (start = botaoSelecionado(highscore, evento)) {
                    hs = highscores(hs);
                    TIPO_OPERACAO = 2;
                }
                else if (botaoMusica = botaoSelecionado(musica, evento)) {
                    TIPO_OPERACAO = 3;
                }
                else if (botaoMusicaOff = botaoSelecionado(musicaoff, evento)) {
                    TIPO_OPERACAO = 4;
                }
                            

                if (start) {
                    config = configSetup(config, TIPO_OPERACAO, musicaoff, display, hs);

                    comecar->tipo = false;
                    highscore->tipo = false;
                    musica->tipo = false;
                }

                al_draw_bitmap(fundo, 0, 0, 0);
            }
        }

        /*if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
            strcpy_s(nome, sizeof nome, "");
            if (!concluido)
            {
                al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH_TELA / 2, 200, ALLEGRO_ALIGN_CENTRE, "Digite o seu nome:");

                manipularEntrada(evento, nome);

                if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
                {
                    concluido = true;
                }
            }
        }*/
    }
 
    al_destroy_sample(musica_de_fundo);
    al_destroy_sample_instance(inst_musica_de_fundo);
    al_destroy_timer(timer);
    al_destroy_event_queue(eventos);
    al_destroy_display(display);
    return 0;
}