// Bibliotecas do allegro
#include <allegro5\allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <queue>

// Funções
#include "headers/event.h"
#include "headers/draw.h"
#include "headers/numbers.h"
#include "headers/setup.h"
#include "headers/create.h"
#include "headers/click.h"

// Structs
#include "structs/setup.h"
#include "structs/foods.h"
#include "structs/button.h"
#include "structs/operation.h"

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
    
    const int FPS = 30;

    const int WIDTH_TELA = 780;
    const int HEIGHT_TELA = 600;

    const int WH_FOOD = 65;
    const int QTD_FOOD = 7;

    int TIPO_OPERACAO = 0;
    int foodsSelected = 0;
    int valueOp = 0;
    int acertos = 0;

    bool gaming = true;
    bool start = false;

    int mouseX = 0, mouseY = 0;

    //-------------------------------DISPLAY---------------------------------//

    al_init(); //Inicia o Allegro e os seus Addons
    al_init_image_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    //-------------------------------VARIÁVEIS DO ALLEGRO---------------------------------//

    ALLEGRO_DISPLAY* display = al_create_display(WIDTH_TELA, HEIGHT_TELA); //Dimensões do Display
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE* eventos = al_create_event_queue(); //Cria uma fila de eventos

    ALLEGRO_FONT* font = al_load_ttf_font("font/font-principal.ttf", 50, 0);
    ALLEGRO_FONT* fontN = al_load_ttf_font("font/font-numero.ttf", 20, 0);
    ALLEGRO_BITMAP* cursor = al_load_bitmap("img/cursor.png");
    ALLEGRO_BITMAP* clique = al_load_bitmap("img/clique.png");

    //-------------------------------CRIANDO OS OBJETOS---------------------------------//
    food* foods[7];
    setup* config = NULL;
    operation* operacao = NULL;

    button* btnSoma = NULL;
    button* btnSub = NULL;
    button* btnDiv = NULL;
    button* btnMult = NULL;

    config = configSetup(config, TIPO_OPERACAO);
    btnSoma = createBottonsOp(btnSoma, 1);
    btnSub = createBottonsOp(btnSub, 2);
    btnDiv = createBottonsOp(btnDiv, 3);
    btnMult = createBottonsOp(btnSoma, 4);

    //-------------------------------FILA DE EVENTOS---------------------------------//
    registerEvents(eventos, display, timer);
    al_hide_mouse_cursor(display);
    al_set_window_title(display, "Math Chef");

    assert(display != NULL);
    al_start_timer(timer);

    while (gaming) {
        ALLEGRO_EVENT evento; //Gera os Eventos
        al_wait_for_event(eventos, &evento);

        if (evento.type == ALLEGRO_EVENT_TIMER) {
            if (!start) {
                al_draw_bitmap(config->fundo, 0, 0, 0);

                drawButtons(btnSoma, display);
                drawButtons(btnSub, display);
                drawButtons(btnDiv, display);
                drawButtons(btnMult, display);

            }
            else {
                al_draw_bitmap(config->fundo, 0, 0, 0);
                al_draw_bitmap(config->base, 80, 515, 0);
                al_draw_bitmap(config->p, config->xp, config->yp, 0);

                for (int i = 0; i < QTD_FOOD; i++) {
                    int xF = (WIDTH_TELA / 2)  - (( 2 * WH_FOOD) / 2);
                    int yF = 490;

                    if (foods[i]->selected) {
                        if (foods[i]->x < xF && foods[i]->y < yF) {
                            foods[i]->x += 4;
                            foods[i]->y += 4;
                        }

                        if (foods[i]->x > xF && foods[i]->y < yF) {
                            foods[i]->x -= 4;
                            foods[i]->y += 4;
                        }

                        if (foods[i]->x == xF && foods[i]->y < yF) {
                            foods[i]->y += 4;
                        }
                    }

                    if (foods[i]->x >= -1 && foods[i]->x <= WIDTH_TELA * (i + 1) && !foods[i]->selected) {
                        foods[i]->x += 1.0;
                    }

                    if (foods[i]->x >= WIDTH_TELA) {
                        foods[i]->x = -1;
                    }

                    if (foods[i]->atived) {
                        drawFoods(foods[i], display, config->color, fontN);
                    }
                }

                if (operacao->number < 10) {
                    al_draw_textf(font, config->color, 262, 195, 0, "0%d", operacao->number);
                }else {
                    al_draw_textf(font, config->color, 262, 195, 0, "%d", operacao->number);
                }

                al_draw_textf(font, config->color, 100, 80, 0, "%d", valueOp);

                if (foodsSelected == 2 && valueOp == operacao->number) {
                    acertos++;

                    foods[7] = NULL;
                    operacao = NULL;
                    
                    foods[7] = createFoods(foods, TIPO_OPERACAO, WIDTH_TELA, WH_FOOD);
                    foods[7] = createNumbers(foods);
                    operacao = createOperation(foods, TIPO_OPERACAO);

                    foodsSelected = 0;
                    valueOp = 0;
                }
                
            }

            al_draw_bitmap(cursor, mouseX, mouseY, 0);
            al_flip_display();
        }

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { gaming = false; }


        //-------------------------------LOCALIZAÇÃO DO MOUSE---------------------------------//
        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseX = evento.mouse.x;
            mouseY = evento.mouse.y;
        }

        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            if (start) {
                for (int i = 0; i < 7; i++) {
                    if (evento.mouse.x >= foods[i]->x && evento.mouse.x <= foods[i]->x + WH_FOOD &&
                        evento.mouse.y >= foods[i]->y - 25 && evento.mouse.y <= foods[i]->y + WH_FOOD) {
                        foodsSelected++;
                        if (foodsSelected <= 2) {
                            foods[i]->selected = true;

                            if (TIPO_OPERACAO == 1) {
                                valueOp += foods[i]->number;
                            }

                            if (TIPO_OPERACAO == 2) {
                                if (foodsSelected == 1) {
                                    valueOp = foods[i]->number;
                                }
                                else {
                                    valueOp -= foods[i]->number;
                                }
                                
                            }

                            if (TIPO_OPERACAO == 3) {
                                if (foodsSelected == 1) {
                                    valueOp = foods[i]->number;
                                }
                                else {
                                    valueOp /= foods[i]->number;
                                }
                            }

                            if (TIPO_OPERACAO == 4) {
                                if (foodsSelected == 1) {
                                    valueOp = foods[i]->number;
                                }
                                else {
                                    valueOp *= foods[i]->number;
                                }
                            } 
                        }
                    }
                }
            }

            if (btnSoma->atived && btnSub->atived && btnDiv->atived && btnMult->atived && btnDiv->atived) {
                if (start = clickButton(btnSoma, evento)) {
                    TIPO_OPERACAO = 1;
                }
                else if (start = clickButton(btnSub, evento)) {
                    TIPO_OPERACAO = 2;
                }
                else if (start = clickButton(btnDiv, evento)) {
                    TIPO_OPERACAO = 3;
                }
                else if (start = clickButton(btnMult, evento)) {
                    TIPO_OPERACAO = 4;
                }

                if (start) {
                    config = configSetup(config, TIPO_OPERACAO);
                    
                    foods[7] = createFoods(foods, TIPO_OPERACAO, WIDTH_TELA, WH_FOOD);
                    foods[7] = createNumbers(foods);
                    operacao = createOperation(foods, TIPO_OPERACAO);

                    btnSoma->atived = false;
                    btnSub->atived = false;
                    btnDiv->atived = false;
                    btnMult->atived = false;
                }
            }
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(eventos);
    al_destroy_display(display);
    return 0;
}