#include "../headers/insereLista.h"
#include "../structs/lista.h"

lista* insereLista(lista* l, char highscore[], int size) {
    lista* novo = (lista*)malloc(sizeof(lista));
    int i;
    for (i = 0; i < size; i++) {
        novo->highscore[i] = highscore[i];
    }
    novo->highscore[size] = '\0';
    novo->prox = l;
    return novo;
}