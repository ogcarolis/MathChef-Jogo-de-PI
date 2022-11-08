#include <allegro5/allegro5.h>
#include <queue>

#include "../headers/numbers.h"

operation* createOperation(int tipo) {
    operation* op;
    op = (operation*) malloc(sizeof(operation));

    bool correto = false;
    int s1, s2;

    srand(time(NULL));
    do {
        s1 = rand() % 100 + 2;
        s2 = rand() % 100 + 2;

        switch (tipo) {
        case 1:
            if ((s1 != s2)) {
                op->number = s1 + s2;
                correto = true;
            }
            break;

        case 2:
            if (s1 != s2) {
                if (s1 - s2 > 0) {
                    op->number = s1 - s2;
                    correto = true;
                }else if (s2 - s1 > 0) {
                    op->number = s2 - s1;
                    correto = true;
                }
            }
            break;

        case 3:
            if (s1 != s2) {
                if (s1 / s2 > 0) {
                    op->number = s1 / s2;
                    correto = true;
                }
                else if (s2 / s1 > 0) {
                    op->number = s2 / s1;
                    correto = true;
                }
            }
            break;

        case 4:
            if ((s1 != s2)) {
                op->number = s1 * s2;

                if(op->number < 100) {
                    correto = true;
                }
            }
            break;
        }
    } while (correto == false);

    op->type = tipo;
    op->value1 = s1;
    op->value2 = s2;

    return op;
}

food createNumbers(food foods[7], operation* op ) {
    int cont = 0, i = 0, l = 1;
    int ant = 0, valorVetor = 0;

    do {
        valorVetor = rand() % op->number + 2;

        if ((valorVetor != op->number) && (valorVetor != op->value1) && (valorVetor != op->value2) && (valorVetor != ant)) {
            foods[i].number = valorVetor;
            ant = valorVetor;
            i++;
        }

    } while (i < 7);


    for (int i = 0; i < l; i++) {
        int i1 = rand() % 5;
        int i2 = rand() % 5;

        if (i1!= i2) {
            foods[i1].number = op->value1;
            foods[i2].number = op->value2;
        }else {
            l++;
        }
    }

    return foods[7];
}