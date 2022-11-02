#include <allegro5/allegro.h>
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

const int WIDTH_TELA = 780;
const int HEIGHT_TELA = 500;

const int WH_INGREDIENTE = 64;
int QTD_INGREDIENTE = 6;

typedef struct ingrediente ingrediente;

struct ingrediente {
    ALLEGRO_BITMAP* img;
    float x, y;
    bool ativo;
};

void criarIngredientes(ingrediente* ing[]);
void exibirIngredientes(ingrediente* ing[], ALLEGRO_DISPLAY* janela);

void criarIngredientes(ingrediente* ing[]) {
    int x = 0;

    for (int i = 0; i < QTD_INGREDIENTE; i++) {
        ing[i] = malloc(sizeof(ingrediente));

        ing[i]->x = x;
        ing[i]->y = WIDTH_TELA / 1.5;
        ing[i]->img = al_load_bitmap("img/salada.png");
        ing[i]->ativo = true;

        x += WH_INGREDIENTE + 20;
    }
}

void exibirIngredientes(ingrediente* ing[], ALLEGRO_DISPLAY* janela) {
    int i;
    bool value = true;

    while (value) {
        for (i = 0; i < 6; i++) {
            if (ing[i]->x >= -1 && ing[i]->x <= HEIGHT_TELA * (i + 1)) {
                ing[i]->ativo = true;
                ing[i]->x += 0.3;
            }

            if (ing[i]->x >= HEIGHT_TELA) {
                ing[i]->x = -1;
            }

            if (ing[i]->ativo) {
                al_set_target_bitmap(ing[i]->img);

                al_set_target_bitmap(al_get_backbuffer(janela));
                al_draw_bitmap(ing[i]->img, ing[i]->x, ing[i]->y, 0);
            }
            else {
                value = false;
            }
        }

        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
    }
}