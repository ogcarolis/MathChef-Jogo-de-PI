#include <allegro5/allegro5.h>
#include <queue>

#include "../headers/numbers.h"

int calculateScore(int temp, int score) {
    if (temp <= 5) {
        score += 1500;
    }

    if (temp > 5 && temp <= 10) {
        score += 750;
    }

    if (temp > 10) {
        score += 300;
    }

    return score;
}

int* fillNumbers(int vInicial, int vFinal) {
    int tamanho = 0;
    int* numeros;

    tamanho = vFinal - vInicial;
    numeros = (int*)malloc(tamanho * sizeof(int));

    for (int i = 0; i < tamanho; i++) {
        numeros[i] = vInicial + i;
    }

    return numeros;
}

operation* createOperation(int tipo, int valor, int acertos) {
    operation* op;
    op = (operation*)malloc(sizeof(operation));
    op->type = tipo;

    bool correto = false;

    int* s1 = NULL;
    int* s2 = NULL;

    int valorInicial = 0, valorFinal = 0;
    int l = 1, i1 = 0, i2 = 0, qtd = 0, qN = 0;

    if (acertos <= 2) {
        if (tipo == 2 || tipo == 3) {
            valorInicial = 7;
            valorFinal = 30;
        }
        else {
            valorInicial = 7;
            valorFinal = 13;
        }
    }

    if (acertos > 2 && acertos <= 4) {
        if (tipo == 2 || tipo == 3) {
            valorInicial = 30;
            valorFinal = 60;
        }else {
            valorInicial = 13;
            valorFinal = 27;
        }
    }

    if (acertos > 4 && acertos <= 6) {
        if (tipo == 2 || tipo == 3) {
            valorInicial = 60;
            valorFinal = 90;
        }
        else {
            valorInicial = 27;
            valorFinal = 33;
        }
    }

    if (acertos > 6) {
        if (tipo == 2 || tipo == 3) {
            valorInicial = 90;
            valorFinal = 120;
        }
        else {
            valorInicial = 33;
            valorFinal = 57;
        }
    }

    qtd = valorFinal - valorInicial;

    do {
        for (int i = 0; i < l; i++) {
            i1 = rand() % qtd;
            i2 = rand() % qtd;

            if (i1 != i2) {
                l = 1;
            }
            else {
                l++;
            }
        }

        switch (tipo) {
        case 1:
            s1 = fillNumbers(valorInicial, valorFinal);
            s2 = fillNumbers(valorInicial, valorFinal);

            op->value1 = s1[i1];
            op->value2 = s2[i2];

            if (op->value1 + op->value2 > valor) {
                op->number = op->value1 + op->value2;
                correto = true;
            }

            free(s1);
            free(s2);
            break;

        case 2:
            s1 = fillNumbers(valorInicial, valorFinal);
            op->value1 = s1[i1];

            s2 = (int*)malloc(op->value1 * sizeof(int));
            for (int i = 0; i <= (op->value1 - 1); i++) {
                op->number = op->value1 - (i + 1);

                if (((op->value1 - (i + 1)) / 1) == op->number) {
                    if (op->value1 - (i + 1) > 7) {
                        s2[qN] = i + 1;
                        qN++;
                        op->number = 0;
                    }else {
                        break;
                    }
                }
            }

            if (qN == 0) {
                correto = false;
                free(s1);
                free(s2);
            }else {
                i2 = rand() % qN;
                if (i1 != i2) {
                    op->value2 = s2[i2];

                    if (op->value1 - op->value2 > valor) {
                        op->number = op->value1 - op->value2;
                        correto = true;
                    }
                }
                else {
                    correto = false;
                }
            }
            break;

        case 3:
            s1 = fillNumbers(valorInicial, valorFinal);
            op->value1 = s1[i1];

            s2 = (int*)malloc(op->value1 * sizeof(int));
            for (int i = 0; i <= (op->value1 - 1); i++) {
                op->number = op->value1 / (i + 1);

                if ((op->value1 / (i + 1) / 1) == op->number) {
                    if ((op->value1 / (i + 1) > 7) && i != 0) {
                        s2[qN] = i + 1;
                        qN++;
                    }
                }
            }

            if (qN == 0) {
                correto = false;

                free(s1);
                free(s2);
            }else {
                i2 = rand() % qN;
                if (i1 != i2) {
                    op->value2 = s2[i2];

                    if (op->value1 / op->value2 > valor) {
                        op->number = op->value1 / op->value2;
                        correto = true;
                    }
                }
                else {
                    correto = false;
                }
            }
            break;

        case 4:
            s1 = fillNumbers(valorInicial, valorFinal);
            s2 = fillNumbers(2, 8);

            op->value1 = s1[i1];
            op->value2 = s2[i2];

            if (op->value1 * op->value2 > valor) {
                op->number = op->value1 * op->value2;
                correto = true;
            }

            free(s1);
            free(s2);
            break;
        }

    } while (correto == false);

    return op;
}

food* createNumbers(food* foods, operation* op) {
    int i = 0, j = 0, q = 0, l = 1;
    int vInicial = 0, vFinal = 0;
    int tamanho = 0;
    int* numeros;

    vInicial = 2;
    vFinal = op->number - 1;
    tamanho = vFinal - vInicial;
    numeros = fillNumbers(vInicial, vFinal);

    for (i = 0; i < tamanho; i++) {
        j = tamanho - (rand() % (tamanho - i)) - 1;                                      
        int tmp = numeros[j];
        numeros[j] = numeros[i];
        numeros[i] = tmp;
    }

    i = 0;
    do {
        if ((numeros[i] != op->value1) && (numeros[i] != op->value2)) {
            foods[q].number = numeros[i];
            i++;
            q++;
        }else {
            i++;
        }
    } while (q < 7);


    for (i = 0; i < l; i++) {
        int i1 = rand() % 7;
        int i2 = rand() % 7;

        if (i1 != i2) {
            foods[i1].number = op->value1;
            foods[i2].number = op->value2;
        }else {
            l++;
        }
    }

    free(numeros);
    return foods;
}