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
#include "headers/event.h"
#include "headers/draw.h"
#include "headers/numbers.h"
#include "headers/setup.h"
#include "headers/create.h"
#include "headers/click.h"
#include "headers/players.h"

// Bibliotecas padrões do C
#include "stdlib.h"
#include "time.h"
#include <string.h>
#include <stdio.h>
#include <locale.h>


int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    char nome[17];
    memset(nome, 0, sizeof(nome));

    char nomeV[17];
    memset(nomeV, 0, sizeof(nomeV));

    const int FPS = 30;

    const int WIDTH_TELA = 780;
    const int HEIGHT_TELA = 600;

    const int WH_FOOD = 65;
    const int QTD_FOOD = 7;

    int TIPO_OPERACAO = 0;

    int foodsSelected = 0;
    int jogadas = 0;
    int valueOp = 0;
    int score = 0;

    bool gaming = true;
    bool start = false;
    bool startM = true;
    bool tutorial = false;
    bool highScore = false;
    bool close = false;
    bool iniciarSegOp = false;

    int mouseX = 0, mouseY = 0;

    int segOp = 0;
    int seg = 0, min = 0;

    al_init(); 
    al_init_image_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    ALLEGRO_DISPLAY* display = al_create_display(WIDTH_TELA, HEIGHT_TELA); 
    ALLEGRO_EVENT_QUEUE* eventos = al_create_event_queue(); 

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    ALLEGRO_TIMER* temp = al_create_timer(1.0);

    ALLEGRO_FONT* font = al_load_ttf_font("font/font-principal.ttf", 50, 0);
    ALLEGRO_FONT* fontT = al_load_ttf_font("font/font-principal.ttf", 25, 0);
    ALLEGRO_FONT* fontS = al_load_ttf_font("font/font-principal.ttf", 30, 0);
    ALLEGRO_FONT* fontN = al_load_ttf_font("font/font-numero.ttf", 20, 0);

    ALLEGRO_BITMAP* cursor = al_load_bitmap("img/cursor.png");
    ALLEGRO_BITMAP* end = al_load_bitmap("img/fim-jogo.png");
    ALLEGRO_COLOR colorTemp;

    food* foods = NULL;
    operation* operacao = NULL;
    players* users = NULL;

    setup* config = NULL;
    config = configSetup(config, TIPO_OPERACAO);

    menu* configMenu = NULL;
    configMenu = createMenu(configMenu);

    button* btnSair = NULL;
    button* btnSoma = NULL;
    button* btnSub = NULL;
    button* btnDiv = NULL;
    button* btnMult = NULL;

    button* btnComecar = NULL;
    button* btnHighScore = NULL;
    button* btnMusica = NULL;
    button* btnCloseT = NULL;

    btnComecar = createButtonsMenu(btnComecar, 1);
    btnHighScore = createButtonsMenu(btnHighScore, 2);
    btnMusica = createButtonsMenu(btnMusica, 3);
    btnCloseT = createButtonsMenu(btnCloseT, 4);

    btnSoma = createButtonsOp(btnSoma, 1);
    btnSub = createButtonsOp(btnSub, 2);
    btnDiv = createButtonsOp(btnDiv, 3);
    btnMult = createButtonsOp(btnSoma, 4);
    btnSair = createButtonsOp(btnSair, 5);

    registerEvents(eventos, display, timer, temp);
    al_hide_mouse_cursor(display);
    al_set_window_title(display, "MathChef");

    assert(display != NULL);
    al_start_timer(timer);
    al_start_timer(temp);

    while (gaming) {
        ALLEGRO_EVENT evento; //Gera os Eventos
        al_wait_for_event(eventos, &evento);

        if (evento.type == ALLEGRO_EVENT_TIMER) {
            if (evento.timer.source == timer) {
                if (!start) {
                    if (startM) {
                        if (highScore) {
                            al_draw_bitmap(configMenu->fundo, 0, 0, 0);
                            al_draw_bitmap(configMenu->highScore, 70, 40, 0);
                            drawPlayers(users);
                            al_draw_text(fontS, al_map_rgb(145, 84, 3), (WIDTH_TELA / 2) + 2, 460, ALLEGRO_ALIGN_CENTRE, "Pressione ESC para voltar");    
                        }
                        else {
                            al_draw_bitmap(configMenu->fundo, 0, 0, 0);
                            al_draw_bitmap(configMenu->logo, 150, 130, 0);

                            drawButtons(btnComecar);
                            drawButtons(btnHighScore);
                            drawButtons(btnMusica);

                            btnComecar->atived = true;
                            btnHighScore->atived = true;
                            btnMusica->atived = true;
                        }
                    }else { 
                        if (tutorial) {
                            al_draw_bitmap(configMenu->fundo, 0, 0, 0);
                            al_draw_bitmap(configMenu->tutorial, 0, 0, 0);
                            drawButtons(btnCloseT);
                        }
                        else {
                            if (close) {
                                drawEndGame(config, end, fontS, fontT, score, nome);
                            }
                            else {
                                al_draw_bitmap(config->fundo, 0, 0, 0);
                                drawButtons(btnSoma);
                                drawButtons(btnSub);
                                drawButtons(btnDiv);
                                drawButtons(btnMult);
                            }
                        }            
                    } 
                }else {
                    al_draw_bitmap(config->fundo, 0, 0, 0);
                    al_draw_bitmap(config->base, 80, 515, 0);
                    al_draw_bitmap(config->p, config->xp, config->yp, 0);
                    al_draw_bitmap(config->timer, 650, 7, 0);

                    drawTitleOP(TIPO_OPERACAO, fontT, config->color);
                    drawNumberOP(operacao->number, font, config->color);
                    drawTimer(min, seg, fontT, colorTemp);
                    drawButtons(btnSair);
                    drawScore(score, fontT, config->color);
                    
                    for (int i = 0; i < QTD_FOOD; i++) {
                        if (foods[i].selected) {
                            if (foodsSelected == 1 && foods[i].y != 490) {
                                foods[i].y = 490;
                                foods[i].x = (WIDTH_TELA / 2) - (WH_FOOD + 20);
                            }

                            if (foodsSelected == 2 && foods[i].y != 490) {
                                foods[i].y = 490;
                                foods[i].x = WIDTH_TELA / 2;
                            }

                        }

                        if (foods[i].x >= -1 && foods[i].x <= WIDTH_TELA * (i + 1) && !foods[i].selected) {
                            foods[i].x += 1.0;
                        }

                        if (foods[i].x >= WIDTH_TELA) {
                            foods[i].x = -1;
                        }

                        if (foods[i].atived) {
                            drawFoods(foods[i], config->color, fontN);
                        }
                    }
                    
                    if (foodsSelected == 2) {
                        if (valueOp == operacao->number) {
                            score = calculateScore(segOp, score);
                            jogadas++;

                            free(foods);
                            foods = createFoods(foods, TIPO_OPERACAO, WIDTH_TELA, WH_FOOD);
                            operacao = createOperation(TIPO_OPERACAO, operacao->number, jogadas);
                            foods = createNumbers(foods, operacao);

                            segOp = 0;
                            foodsSelected = 0;
                            valueOp = 0;
                        }
                        else {
                            close = true;
                            start = false;

                            btnSair->atived = false;
                            btnSoma->atived = false;
                            btnSub->atived = false;
                            btnDiv->atived = false;
                            btnMult->atived = false;
                        }
                    }   
                }
            }
            else if (evento.timer.source == temp) {
                seg--;
                if (min == 0 && seg == 0 && start) {
                    close = true;
                    start = false;

                    btnSair->atived = false;
                    btnSoma->atived = false;
                    btnSub->atived = false;
                    btnDiv->atived = false;
                    btnMult->atived = false;
                }

                if (seg == 0) {
                    min--;
                    seg = 59;
                }

                if (min == 0 && seg <= 45) {
                    colorTemp = al_map_rgb(255, 0, 0);
                }

                if (iniciarSegOp) {
                    segOp++;
                }
            }
         
            al_draw_bitmap(cursor, mouseX, mouseY, 0);
            al_flip_display();
        }

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { gaming = false; }


        if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseX = evento.mouse.x;
            mouseY = evento.mouse.y;
        }

        if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
            if (close) {
                if (strlen(nome) <= 17) {
                    char temp[] = { evento.keyboard.unichar, '\0' };

                    if (evento.keyboard.unichar == ' ') {
                        strcat_s(nome, temp);
                    }
                    else if (evento.keyboard.unichar >= '0' && evento.keyboard.unichar <= '9') {
                        strcat_s(nome, temp);
                    }
                    else if (evento.keyboard.unichar >= 'A' && evento.keyboard.unichar <= 'Z') {
                        strcat_s(nome, temp);
                    }
                    else if (evento.keyboard.unichar >= 'a' && evento.keyboard.unichar <= 'z') {
                        strcat_s(nome, temp);
                    }
                }

                if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(nome) != 0) {
                    nome[strlen(nome) - 1] = '\0';
                }
            }
        }

        if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            if (highScore) {
                highScore = false;
            }else {
                highScore = true;
            }
        }

        if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER){
            if (close) {
                users = insertPlayers(users, nome, score, strlen(nome), TIPO_OPERACAO);

                free(foods);
                free(operacao);
                free(config);
                free(configMenu);

                strcpy_s(nome, nomeV);

                foodsSelected = 0;
                valueOp = 0;
                score = 0;
                jogadas = 0;
                
                segOp = 0;
                min = 1;
                seg = 30;

                config = configSetup(config, 0);
                configMenu = createMenu(configMenu);

                startM = true;
                tutorial = false;
                close = false;
                start = false;

                btnSair->atived = false;
                btnCloseT->atived = false;

                btnSoma->atived = false;
                btnSub->atived = false;
                btnDiv->atived = false;
                btnMult->atived = false;

                btnComecar->atived = true;
                btnHighScore->atived = true;
                btnMusica->atived = true;
            }
        }

        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            if (start) {
                for (int i = 0; i < 7; i++) {
                    if (clickFood(foods[i], evento, WH_FOOD)) {
                        if (!foods[i].selected && foodsSelected < 2) {
                            foodsSelected++;
                            foods[i].selected = true;

                            if (TIPO_OPERACAO == 1) {
                                valueOp += foods[i].number;
                            }

                            if (TIPO_OPERACAO == 2) {
                                if (foodsSelected == 1) {
                                    valueOp = foods[i].number;
                                }
                                else {
                                    valueOp -= foods[i].number;
                                }

                            }

                            if (TIPO_OPERACAO == 3) {
                                if (foodsSelected == 1) {
                                    valueOp = foods[i].number;
                                }
                                else {
                                    valueOp /= foods[i].number;
                                }
                            }

                            if (TIPO_OPERACAO == 4) {
                                if (foodsSelected == 1) {
                                    valueOp = foods[i].number;
                                }
                                else {
                                    valueOp *= foods[i].number;
                                }
                            }
                        }
                    }
                }
            }

            if (startM) {
                if (btnComecar->atived) {
                    if (clickButton(btnComecar, evento)) {
                        startM = false;

                        tutorial = true;
                        btnCloseT->atived = true;

                        btnMusica->atived = false;
                        btnComecar->atived = false;
                        btnHighScore->atived = false;
                    }
                } 

                if (btnHighScore->atived) {
                    if (clickButton(btnHighScore, evento)) {
                        highScore = true;
            
                        btnMusica->atived = false;
                        btnComecar->atived = false;
                        btnHighScore->atived = false;
                    }
                }
            }

            if (tutorial) {
                if (btnCloseT->atived) {
                    if (clickButton(btnCloseT, evento)) {
                        tutorial = false;
                        btnCloseT->atived = false;

                        configMenu = NULL;
                        config = configSetup(config, 0);

                        btnSair->atived = false;
                        btnSoma->atived = true;
                        btnSub->atived = true;
                        btnDiv->atived = true;
                        btnMult->atived = true;
                    }
                }
            }

            if (btnSair->atived) {
                if (close = clickButton(btnSair, evento)) {
                    start = false;

                    btnSair->atived = false;
                    btnSoma->atived = false;
                    btnSub->atived = false;
                    btnDiv->atived = false;
                    btnMult->atived = false;
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
                    iniciarSegOp = true;
                    min = 1;
                    seg = 30;

                    config = configSetup(config, TIPO_OPERACAO);
                    colorTemp = config->color;

                    operacao = createOperation(TIPO_OPERACAO, 0, jogadas);
                    foods = createFoods(foods, TIPO_OPERACAO, WIDTH_TELA, WH_FOOD);
                    foods = createNumbers(foods, operacao);
                    
                    btnSoma->atived = false;
                    btnSub->atived = false;
                    btnDiv->atived = false;
                    btnMult->atived = false;
                    btnSair->atived = true;
                }
            }
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(eventos);
    al_destroy_display(display);
    return 0;
}