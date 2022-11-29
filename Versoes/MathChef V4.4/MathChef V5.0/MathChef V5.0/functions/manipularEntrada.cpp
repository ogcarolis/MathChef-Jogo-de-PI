#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <queue>

#include "../headers/manipularEntrada.h"

void manipularEntrada(ALLEGRO_EVENT evento, char *nome)
{
    if (evento.type == ALLEGRO_EVENT_KEY_CHAR)
    {
        if (strlen(nome) <= 29)
        {
            char temp[] = { evento.keyboard.unichar, '\0' };
            if (evento.keyboard.unichar == ' ')
            {
                strcat_s(nome, sizeof nome, temp);
            }
            else if (evento.keyboard.unichar >= '0' && evento.keyboard.unichar <= '9')
            {
                strcat_s(nome, sizeof nome, temp);
            }
            else if (evento.keyboard.unichar >= 'A' && evento.keyboard.unichar <= 'Z')
            {
                strcat_s(nome, sizeof nome, temp);
            }
            else if (evento.keyboard.unichar >= 'a' && evento.keyboard.unichar <= 'z')
            {
                strcat_s(nome, sizeof nome, temp); 
            }
        }

        if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(nome) != 0)
        {
            nome[strlen(nome) - 1] = '\0';
        }
    }
}