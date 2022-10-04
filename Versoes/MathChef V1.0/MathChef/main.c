// Os arquivos de cabeçalho
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

typedef struct ingrediente {
    ALLEGRO_BITMAP* objeto;
    float x, y;
    bool ativo;
}ingrediente;

ingrediente* ing[6];

const int LARGURA_TELA = 780;
const int ALTURA_TELA = 500;

const int WIDTH_ING = 100;
const int HEIGHT_ING = 90;

ALLEGRO_DISPLAY* janela = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;

void criarIng() {
    int x = 0;

    for (int i = 0; i < 6; i++) {
        ing[i] = malloc(sizeof(ingrediente));

        ing[i]->x = x;
        ing[i]->y = ALTURA_TELA / 1.5;
        ing[i]->objeto = al_create_bitmap(WIDTH_ING, HEIGHT_ING);
        ing[i]->ativo = true;

        x += WIDTH_ING + 20;
    }
}

void moverIng() {
    criarIng();

    int i;

    bool value = true;

    while (value) {
        for (i = 0; i < 6; i++) {
            if (ing[i]->x >= 0 && ing[i]->x <= LARGURA_TELA * (i + 1)) {
                ing[i]->ativo = true;
                ing[i]->x += 0.3;
            }

            if (ing[i]->x >= LARGURA_TELA) {
                ing[i]->x = 0;
            }

            if (ing[i]->ativo) {
                al_set_target_bitmap(ing[i]->objeto);
                al_clear_to_color(al_map_rgb(255, 0, 0));

                al_set_target_bitmap(al_get_backbuffer(janela));
                al_draw_bitmap(ing[i]->objeto, ing[i]->x, ing[i]->y, 0);
            }else {
                value = false;
            }
        }

        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
    }
}

void destroy() {
    for (int i = 0; i < 6; i++) {
        al_destroy_bitmap(ing[i]->objeto);
    }

    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
}

int main(void) {
    al_set_window_title(janela, "MathChef");

    int sair = 0;

    if (!al_init()) {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return -1;
    }

    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela) {
        fprintf(stderr, "Falha ao criar janela.\n");
        return -1;
    }

    
    if (!al_install_mouse()){
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return -1;
    }

    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)) {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return -1;
    }
    
    fila_eventos = al_create_event_queue();
    if (!fila_eventos) {
        fprintf(stderr, "Falha ao inicializar o fila de eventos.\n");
        al_destroy_display(janela);
        return -1;
    }

 
    al_register_event_source(fila_eventos, al_get_mouse_event_source());

    while (!sair) {

        // Verificamos se há eventos na fila
        while (!al_is_event_queue_empty(fila_eventos)) {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            fila_eventos = al_create_event_queue();
            if (!fila_eventos) {
                fprintf(stderr, "Falha ao inicializar o fila de eventos.\n");
                al_destroy_display(janela);
                return -1;
            }

            al_register_event_source(fila_eventos, al_get_mouse_event_source());

            moverIng();
            // Atualiza a tela
            al_flip_display();
        }    
    }


    destroy();
    return 0;
}