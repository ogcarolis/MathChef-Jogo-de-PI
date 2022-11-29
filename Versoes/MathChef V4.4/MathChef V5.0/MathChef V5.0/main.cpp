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
#include "headers/looseimg.h"
#include "headers/highscore.h"

// Structs
#include "structs/setup.h"
#include "structs/buttons.h"
#include "structs/lista.h"
#include "structs/looseimg.h"
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
    bool afterStart = false;  
    bool botaoMusica = false;    
    bool highscoreScreen = false;

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
    botao* sair = NULL;
    //botao* musicaoff = NULL;
    //botao* voltar = NULL;

    setup* config = NULL;
    lista* list = NULL;
    looseimg* fundo = NULL;
    looseimg* logo = NULL;
    looseimg* tutorial = NULL;
    looseimg* popup_highscore = NULL;

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
        
    ALLEGRO_FONT* font = al_load_ttf_font("font/font-principal.ttf", 50, 0);
    ALLEGRO_FONT* fontN = al_load_ttf_font("font/font-numero.ttf", 20, 0);
    ALLEGRO_FONT* fontHighscore = al_load_ttf_font("font/font-principal.ttf", 30, 0);

    int displayX = al_get_display_width(display);
    int displayY = al_get_display_height(display);

    //------------------------CONFIGURAÇOES DA MUSICA DE FUNDO------------------------//
    musica_de_fundo = al_load_sample("music/intro-theme.wav");
    inst_musica_de_fundo = al_create_sample_instance(musica_de_fundo);

    al_attach_sample_instance_to_mixer(inst_musica_de_fundo, al_get_default_mixer());

    al_set_sample_instance_playmode(inst_musica_de_fundo, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(inst_musica_de_fundo, 0.5);

    //-----------------------------INICIALIZAÇÃO DE BOTÕES-----------------------------//

    comecar = criarBotao(comecar, 1); 
    highscore = criarBotao(highscore, 2); 
    musica = criarBotao(musica, 3);
    sair = criarBotao(sair, 4);
    //musicaoff = criarBotao(musicaoff, 4); 

    //-------------------------------FILA DE EVENTOS---------------------------------//
    registerEvents(eventos, display, timer);
    al_register_event_source(eventos, al_get_keyboard_event_source());
    al_register_event_source(eventos, al_get_mouse_event_source());
    //al_hide_mouse_cursor(display);
    al_set_window_title(display, "Math Chef");

    assert(display != NULL);
    al_start_timer(timer);

    //play na música
    al_play_sample_instance(inst_musica_de_fundo);

    while (gaming) {

        ALLEGRO_EVENT evento; //Gera os Eventos
        al_wait_for_event(eventos, &evento);
        
        //----------------------DIGITAR O NOME-----------------------------//
        strcpy_s(nome, sizeof nome, "");

        if (!concluido)
        {   
            manipularEntrada(evento, nome);
            
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                concluido = true;
            }
        }

        if (!concluido) {
            al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH_TELA / 2,
                200, ALLEGRO_ALIGN_CENTRE, "Digite o seu nome:");
        }
        else {
            al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH_TELA / 2,
                200, ALLEGRO_ALIGN_CENTRE, "1º Lugar");
        }

        //exibir_texto_centralizado();

        //----------------------------------------------------------------//

        if (evento.type == ALLEGRO_EVENT_TIMER) {
            
            if (!start) {
                
                fundo = loose_img(fundo, 1); 
                logo = loose_img(logo, 2); 

                al_draw_bitmap(fundo->img, 0, 0, 0);
                al_draw_bitmap(logo->img, 150, 130, 0);
                
                drawButtons(comecar, display);
                drawButtons(highscore, display);
                drawButtons(musica, display);                

                if (botaoMusica) {
                    //rodando o código abaixo da um erro que não fui capaz de consertar nem 
                    //com pesquisas

                    /*free(musica);

                    musica->obj = al_load_bitmap("img/btn-musicaoff.png");
                    musica->x = 97;
                    musica->y = 2;

                    musica->width = al_get_bitmap_width(musica->obj); 
                    musica->height = al_get_bitmap_height(musica->obj);*/ 
                    
                    //unica coisa funcional no botao de musica:

                    al_stop_sample_instance(inst_musica_de_fundo);  
                }
                else
                {
                    al_play_sample_instance(inst_musica_de_fundo);
                }
                               
            }
            else { //QUANDO QUALQUER BOTAO É ATIVADO O START VIRA TRUE CAUSANDO ISSO:
                if (TIPO_OPERACAO == 1) {
                    tutorial = loose_img(tutorial, 3);

                    al_draw_bitmap(config->fundo, 0, 0, 0);

                    if (!afterStart) {                         
                        al_draw_bitmap(tutorial->img, 0, 0, 0); 
                        drawButtons(sair, display); 
                    }
                    else {
                        musica->x = 700;
                        drawButtons(musica, display);                        
                    }
                }
                if (TIPO_OPERACAO == 2) {
                    al_draw_bitmap(popup_highscore->img, 70, 40, 0);

                    al_draw_text(fontHighscore, al_map_rgb(145, 84, 3), (WIDTH_TELA / 2) + 2, 460, ALLEGRO_ALIGN_CENTRE, "Pressione ESC para voltar");
                    
                }                
            }

            if (start && afterStart) {
                if (TIPO_OPERACAO == 2) {
                    al_draw_bitmap(popup_highscore->img, 70, 40, 0);

                    al_draw_text(fontHighscore, al_map_rgb(145, 84, 3), (WIDTH_TELA / 2) + 2, 460, ALLEGRO_ALIGN_CENTRE, "Pressione ESC para voltar");

                }                
            }

            al_flip_display();
        }

        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE && start 
                    && highscoreScreen && !afterStart) {
                tecla = 1;
            }
        }

        if (tecla) {
            start = false;
            highscoreScreen = false;
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

            if (start) {
                if (evento.mouse.x >= sair->x && evento.mouse.x <= sair->x + sair->width &&
                    evento.mouse.y >= sair->y && evento.mouse.y <= sair->y + sair->height) {
                    afterStart = true;
                }                
                if (evento.mouse.x >= musica->x && evento.mouse.x <= musica->x + musica->width &&
                    evento.mouse.y >= musica->y && evento.mouse.y <= musica->y + musica->height) {
                    botaoMusica = true;
                }
            }

            if (comecar->tipo && highscore->tipo && musica->tipo) {
                if (start = botaoSelecionado(comecar, evento)) {
                    TIPO_OPERACAO = 1;
                }
                else if (start = botaoSelecionado(highscore, evento)) {
                    highscoreScreen = true;
                    popup_highscore = loose_img(popup_highscore, 4); 
                    TIPO_OPERACAO = 2;
                }
                else if (botaoMusica = botaoSelecionado(musica, evento)) {
                        al_stop_sample_instance(inst_musica_de_fundo);
                }

                if (start) {
                    config = configSetup(config, TIPO_OPERACAO);

                    comecar->tipo = false;
                    highscore->tipo = false;
                    musica->tipo = false;
                }
                               
            }
        }        
                
    }
    
    //-------------------------DESTRUIÇÃO DE TUDO-------------------------//
    free(comecar);
    free(musica);
    //free(musicaoff);
    free(highscore);
    al_destroy_sample(musica_de_fundo); 
    al_destroy_sample_instance(inst_musica_de_fundo);
    al_destroy_timer(timer);
    al_destroy_event_queue(eventos);
    al_destroy_bitmap(fundo->img);
    al_destroy_bitmap(logo->img);
    al_destroy_bitmap(comecar->obj);
    al_destroy_bitmap(musica->obj);
    al_destroy_bitmap(highscore->obj);
    al_destroy_display(display); 
    //----------------------------------------------------------//
    
    return 0;
}
