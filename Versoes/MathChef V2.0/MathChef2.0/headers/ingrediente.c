#include <stdlib.h>
#include <allegro5/allegro5.h>

typedef struct NUMERO{
	int x, y;
	int numero;
	char* valorC;
	ALLEGRO_BITMAP* valor;
}NUMERO;

typedef struct INGREDIENTE{
	int x, y;
	bool ativo, selecionado;
	ALLEGRO_BITMAP* comida;
	NUMERO** numero;
}INGREDIENTE;


INGREDIENTE** criarIngrediente(INGREDIENTE** ing, NUMERO** num);
void exibirIngrediente(INGREDIENTE** ing, ALLEGRO_DISPLAY* janela);
//void verificarIngrediente(INGREDIENTE** ing);
