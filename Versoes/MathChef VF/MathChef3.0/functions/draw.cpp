#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <queue>

#include "../headers/draw.h"

void drawFoods(food food, ALLEGRO_COLOR color, ALLEGRO_FONT* font) {
    al_draw_bitmap(food.placa, food.x + 12, food.y - 25, 0);
    
    if (food.number < 10) {
        al_draw_textf(font, color, food.x + 26, food.y - 17, 0, "0%d", food.number);
    }else {
        al_draw_textf(font, color, food.x + 26, food.y - 17, 0, "%d", food.number);
    }
    
    al_draw_bitmap(food.obj, food.x, food.y, 0);
}

void drawEndGame(setup* config, ALLEGRO_BITMAP* end, ALLEGRO_FONT* font, ALLEGRO_FONT* fontT, int score, char nome[]) {
    int x = 245;
    int y = 125;

    config->color = al_map_rgb(255, 255, 255);
    al_draw_bitmap(config->fundoF, 0, 0, 0);
    al_draw_bitmap(end, x, y, 0);

    if (score == 0) {
        al_draw_textf(font, config->color, x + 138, y + 232, 0, "%d", score);
    }else if (score < 1000) {
        al_draw_textf(font, config->color, x + 120, y + 232, 0, "%d", score);
    }else if (score >= 1000) {
        al_draw_textf(font, config->color, x + 113, y + 232, 0, "%d", score);
    }else{
        al_draw_textf(font, config->color, x + 105, y + 232, 0, "%d", score);
    }

    al_draw_textf(fontT, config->color, x + 2, y + 360, 0, "Pressione Enter para Salvar");
    al_draw_textf(fontT, config->color, 390, 255, ALLEGRO_ALIGN_CENTRE, "%s", nome);
}

void drawButtons(button* btn) {
    al_draw_bitmap(btn->obj, btn->x, btn->y, 0);
}

void drawTimer(int min, int seg, ALLEGRO_FONT* fontT, ALLEGRO_COLOR colorTemp) {
    if (seg < 10) {
        al_draw_textf(fontT, colorTemp, 685, 10, 0, "0%d:0%d", min, seg);
    }
    else {
        al_draw_textf(fontT, colorTemp, 685, 10, 0, "0%d:%d", min, seg);
    }
}

void drawNumberOP(int number, ALLEGRO_FONT* font, ALLEGRO_COLOR color) {
    if (number < 10) {
        al_draw_textf(font, color, 246, 195, 0, "0%d", number);
    }
    else {
        if (number >= 100) {
            al_draw_textf(font, color, 240, 195, 0, "%d", number);
        }
        else {
            al_draw_textf(font, color, 246, 195, 0, "%d", number);
        }
    }
}

void drawTitleOP(int tipo, ALLEGRO_FONT * font, ALLEGRO_COLOR color) {
    if (tipo == 1) {
        al_draw_textf(font, color, 70, 10, 0, "Soma");
    }

    if (tipo == 2) {
        al_draw_textf(font, color, 70, 10, 0, "Subtracao");
    }

    if (tipo == 3) {
        al_draw_textf(font, color, 70, 10, 0, "Divisao");
    }

    if (tipo == 4) {
        al_draw_textf(font, color, 70, 10, 0, "Multiplicacao");
    }

}

void drawScore(int score, ALLEGRO_FONT* font, ALLEGRO_COLOR color) {
    al_draw_textf(font, color, 500, 10, 0, "Score: %d", score);
}

void drawPlayers(players* l) {
    int qtd = 0;
    do {
        if (l != NULL) {
            printf("%s\n", l->nome);
            printf("%d\n", l->score);
            printf("%d\n", l->tipo);
            printf("-----------------------------------\n");

            l = l->prox;
        }
        qtd++;
    } while (l != NULL || qtd < 5);
}

