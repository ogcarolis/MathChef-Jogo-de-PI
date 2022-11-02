#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>
#include <time.h>

typedef struct numero numero;
struct numero {
    int valor;
    int valorI[5];
};

typedef struct ingrediente ingrediente;
struct ingrediente {
    numero* numero;
    ALLEGRO_BITMAP* img;
    float x, y;
    bool ativo, selecionado;
};

const int WIDTH_TELA = 780;
const int HEIGHT_TELA = 600;
const int WH_INGREDIENTE = 64;
const int WH_NUMERO = 24;
const float FPS = 60.0;

int QTD_INGREDIENTE = 5;
int TIPO_OPERACAO = 1;

ALLEGRO_DISPLAY* janela = NULL;
ALLEGRO_TIMER* tempo = NULL;
ALLEGRO_EVENT_QUEUE* eventos = NULL;
ALLEGRO_EVENT evento;

ingrediente* ingredientes[5];
numero* numeros[5];
numero* numeroOperacao;

void criarIngredientes(ingrediente* ing[]);
void moverIngredientes(ingrediente* ing[]);
void exibirIngrediente(ingrediente* ing, ALLEGRO_DISPLAY* janela);
ingrediente* selecionarIngrediente(ingrediente* ing[], ALLEGRO_EVENT* evento);

numero* atualizarNumero(numero* n);
void exibirNumero(numero* n, int x, int y);
void sortearNumeros(numero* n[], int tipo);

numero* atualizarNumero(numero* n) {
    int i = 0, fim = 5;
    int vet[5];
    int numero = n->valor;

    for (i = 0; i < fim; i++) {
        vet[i] = numero % 10;

        if (numero == 0) {
            vet[i] = -1;
        }
        numero = numero / 10;
    }

    for (i = 0; i < fim; i++) {
        n->valorI[i] = vet[fim - i - 1]; 
    }
   
    return n;
}

void sortearNumeros(numero* n[], int tipo) {
    bool correto = false;
    int cont = 0, i = 0, l = 1;
    int s1, s2;

    srand(time(NULL));
    numeroOperacao = malloc(sizeof(numero));

    do {
        s1 = rand() % 100 + 1;
        s2 = rand() % 100 + 1;

        switch (tipo) {
        case 1:
            if ((s1 > 1 && s2 > 1) && (s1 != s2)) {
                numeroOperacao->valor = s1 + s2;
                if (numeroOperacao->valor > 1) {
                    correto = true;
                }
            }
            break;

        case 2:
            if ((s1 > 1 && s2 > 1) && (s1 != s2)) {
                if (s1 - s2 > 1) {
                    numeroOperacao->valor = s1 - s2;
                    correto = true;
                }else {
                    numeroOperacao->valor = s2 - s1;
                    correto = true;
                }
            }
            break;

        case 3:
            if ((s1 > 1 && s2 > 1) && (s1 != s2)) {
                numeroOperacao->valor = s1 * s2;
                if (numeroOperacao <= 1000) {
                    correto = true;
                }
            }
            break;

        case 4:
            if ((s1 > 1 && s2 > 1) && (s1 != s2)) {
                if (s1 / s2 > 1) {
                    numeroOperacao->valor = s1 / s2;
                    correto = true;
                }else {
                    numeroOperacao->valor = s2 / s1;
                    correto = true;
                }
            }
            break;
        }
    } while (correto == false);

    numeroOperacao = atualizarNumero(numeroOperacao);

    do {
        int valorVetor = rand() % numeroOperacao->valor + 1;

        n[i] = malloc(sizeof(numero));
        if ((valorVetor > 1) && (valorVetor != numeroOperacao) && (valorVetor != s1) && (valorVetor != s2)) {
            n[i]->valor = valorVetor;
            n[i] = atualizarNumero(n[i]);
            i++;
        }

    } while (i < 6);


    for (int i = 0; i < l; i++) {
        int i1 = rand() % 5;
        int i2 = rand() % 5;

        n[i1] = malloc(sizeof(numero));
        n[i2] = malloc(sizeof(numero));

        if (i1 != i2) {
            n[i1]->valor = s1;
            n[i2]->valor = s2;

            n[i1] = atualizarNumero(n[i1]);
            n[i2] = atualizarNumero(n[i2]);
        }else {
            l++;
        }
    }
}


void criarIngredientes(ingrediente* ing[]) {
    sortearNumeros(numeros, TIPO_OPERACAO);
    int x = 0;

    for (int i = 0; i < QTD_INGREDIENTE; i++) {
        ing[i] = malloc(sizeof(ingrediente));

        ing[i]->x = x;
        ing[i]->y = HEIGHT_TELA / 1.5;
        ing[i]->img = al_load_bitmap("img/salada.png");
        ing[i]->numero = numeros[i];
        ing[i]->ativo = true;
        ing[i]->selecionado = false;

        x += WH_INGREDIENTE + 80;
    }
}

void exibirNumero(numero* numero, int x, int y) {
    ALLEGRO_BITMAP* img;

    for (int i = 0; i < 5; i++) {
        if (numero->valorI[i] > 0) {

            if (i > 0) {
                x += 13;
            }

            switch (numero->valorI[i]) {
            case 0:
                img = al_load_bitmap("img/zero.png");
                al_set_target_bitmap(img);

                al_set_target_bitmap(al_get_backbuffer(janela));
                al_draw_bitmap(img, x, y, 0);
                break;

            case 1:
                img = al_load_bitmap("img/um.png");
                al_set_target_bitmap(img);

                al_set_target_bitmap(al_get_backbuffer(janela));
                al_draw_bitmap(img, x, y, 0);
                break;

            case 2:
                img = al_load_bitmap("img/dois.png");
                al_set_target_bitmap(img);

                al_set_target_bitmap(al_get_backbuffer(janela));
                al_draw_bitmap(img, x, y, 0);
                break;

            case 3:
                img = al_load_bitmap("img/tres.png");
                al_set_target_bitmap(img);

                al_set_target_bitmap(al_get_backbuffer(janela));
                al_draw_bitmap(img, x, y, 0);
                break;

            case 4:
                img = al_load_bitmap("img/quatro.png");
                al_set_target_bitmap(img);

                al_set_target_bitmap(al_get_backbuffer(janela));
                al_draw_bitmap(img, x, y, 0);
                break;

            case 5:
                img = al_load_bitmap("img/cinco.png");
                al_set_target_bitmap(img);

                al_set_target_bitmap(al_get_backbuffer(janela));
                al_draw_bitmap(img, x, y, 0);
                break;

            case 6:
                img = al_load_bitmap("img/seis.png");
                al_set_target_bitmap(img);

                al_set_target_bitmap(al_get_backbuffer(janela));
                al_draw_bitmap(img, x, y, 0);
                break;

            case 7:
                img = al_load_bitmap("img/sete.png");
                al_set_target_bitmap(img);

                al_set_target_bitmap(al_get_backbuffer(janela));
                al_draw_bitmap(img, x, y, 0);
                break;

            case 8:
                img = al_load_bitmap("img/oito.png");
                al_set_target_bitmap(img);

                al_set_target_bitmap(al_get_backbuffer(janela));
                al_draw_bitmap(img, x, y, 0);
                break;

            case 9:
                img = al_load_bitmap("img/nove.png");
                al_set_target_bitmap(img);

                al_set_target_bitmap(al_get_backbuffer(janela));
                al_draw_bitmap(img, x, y, 0);
                break;

            default:
                break;
            }
        }
    }
}

void exibirIngrediente(ingrediente* ing, ALLEGRO_DISPLAY* janela) {
    al_set_target_bitmap(ing->img);

    al_set_target_bitmap(al_get_backbuffer(janela));
    al_draw_bitmap(ing->img, ing->x, ing->y, 0);
}

ingrediente* selecionarIngrediente(ingrediente* ing[], ALLEGRO_EVENT evento) {
    int i;

    for (i = 0; i < QTD_INGREDIENTE; i++) {
        if (evento.mouse.x >= ing[i]->x && evento.mouse.x <= ing[i]->x + WH_INGREDIENTE &&
            evento.mouse.y >= ing[i]->y && evento.mouse.y <= ing[i]->y + WH_INGREDIENTE) {
            ing[i]->selecionado = true;
            return ing[i];
        }
    }

    return NULL;
  
}


void moverIngredientes(ingrediente* ing[]) {
    int i = 0;
    int xn, yn;
    ingrediente* itemSelecionado = NULL;
    bool controle = true;
    float xF = WIDTH_TELA / 2 - WH_INGREDIENTE;
    float yF = HEIGHT_TELA / 2 - WH_INGREDIENTE;
    bool value = true, clique = false;
    
    while (value) {
        for (i = 0; i < QTD_INGREDIENTE; i++) {
            al_wait_for_event(eventos, &evento);

            if (ing[i]->x >= -1 && ing[i]->x <= WIDTH_TELA * (i + 1) && !ing[i]->selecionado) {
                ing[i]->x += 1.0;
            }

            if (ing[i]->x >= WIDTH_TELA) {
                ing[i]->x = -1;
            }
  
            if (ing[i]->ativo) {   
                xn = (ing[i]->x + WH_INGREDIENTE) - 20;
                yn = (ing[i]->y + WH_INGREDIENTE) - 8;

                exibirIngrediente(ing[i], janela);
                exibirNumero(ing[i]->numero, xn, yn);     
            }

            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                itemSelecionado = selecionarIngrediente(ing, evento);
            }
        }

        if (itemSelecionado != NULL) {
            if (itemSelecionado->y == yF) {
                itemSelecionado = NULL;
            }
            else {
                if (itemSelecionado->x < xF) {
                    itemSelecionado->x += 4;
                    itemSelecionado->y -= 4;
                }

                if (itemSelecionado->x > xF) {
                    itemSelecionado->x -= 4;
                    itemSelecionado->y -= 4;
                }

                if (itemSelecionado->x == xF) {
                    itemSelecionado->y -= 4;
                }

                int xn = (itemSelecionado->x + WH_INGREDIENTE) - 20;
                int yn = (itemSelecionado->y + WH_INGREDIENTE) - 8;
            }
        }

        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
        exibirNumero(numeroOperacao, 680, 100);
    }
}


void destroy() {
    al_destroy_display(janela);
}


int main(void) {
    al_set_window_title(janela, "MathChef");

    if (!al_init()) {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return -1;
    }

    if (!al_init_image_addon()) {
        fprintf(stderr, "Falha ao inicializar a Imagem.\n");
        return -1;
    }

    janela = al_create_display(WIDTH_TELA, HEIGHT_TELA);
    if (!janela) {
        fprintf(stderr, "Falha ao criar janela.\n");
        return -1;
    }

    if (!al_install_mouse()){
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    tempo = al_create_timer(1.0 / FPS);
    eventos = al_create_event_queue();
    if (!eventos) {
        fprintf(stderr, "Falha ao inicializar o fila de eventos.\n");
        al_destroy_display(janela);
        return -1;
    }
    al_register_event_source(eventos, al_get_mouse_event_source());
    al_register_event_source(eventos, al_get_display_event_source(janela));
    al_register_event_source(eventos, al_get_timer_event_source(tempo));

    al_start_timer(tempo);

    criarIngredientes(ingredientes);
    moverIngredientes(ingredientes, janela);
    al_flip_display();
   

    destroy();
    return 0;
}
