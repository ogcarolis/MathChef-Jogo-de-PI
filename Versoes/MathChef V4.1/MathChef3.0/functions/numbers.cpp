#include <allegro5/allegro5.h>
#include <queue>

#include "../headers/numbers.h"


operation* createOperation(food* foods[7], int tipo) {
    operation* op;
    op = (operation*) malloc(sizeof(operation));

    bool correto = false;
    int s1 = 0, s2 = 0, l = 1;

    do {
        for (int i = 0; i < l; i++) {
            int i1 = rand() % 5;
            int i2 = rand() % 5;

            if (i1 != i2) {
                s1 = foods[i1]->number;
                s2 = foods[i2]->number;
                l = 1;
            }else {
                l++;
            }
        }

        switch (tipo) {
        case 1:
            op->number = s1 + s2;
            if (op->number < 100) {
                correto = true;
            }
            break;

        case 2:
            op->number = s1 - s2;
            if (op->number > 1) {
                correto = true;
            }
            break;

        case 3:
            op->number = s1 / s2;

            if (op->number > 0) {
                correto = true;
            }
            break;

        case 4:
            op->number = s1 * s2;

            if (op->number > 0) {
                correto = true;
            }
            break;
        }

    } while (correto == false);

    op->value1 = s1;
    op->value2 = s2;
    op->type = tipo;
    return op;
}

food* createNumbers(food* foods[7]) {
    int cont = 0, i = 0, l = 1, valorVetor = 0, valida = 0;

    do {
        valorVetor = rand() % 20 + 1;

        for (int j = 0; j < i; j++) {
            if (foods[j]->number == valorVetor) {
                valida = 1;
                break;
            }
        }

        if (valida == 0) {
            foods[i]->number = valorVetor;
            i++;
        }

    } while (i < 7);

    return foods[7];
}