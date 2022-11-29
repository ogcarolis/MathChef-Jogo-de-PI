#ifndef NUMBEBRS
#define NUMBEBRS
#include "../structs/foods.h"
#include "../structs/operation.h"

int calculateScore(int temp, int score);
int* fillNumbers(int vInicial, int vFinal);
operation* createOperation(int tipo, int valor, int jogadas);
food* createNumbers(food* foods, operation* op);

#endif