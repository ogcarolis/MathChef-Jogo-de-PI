#include <allegro5/allegro5.h>
#include <queue>
#include "../headers/manipularEntrada.h"

void manipular_entrada(ALLEGRO_EVENT evento, char highscore[])
{
    if (evento.type == ALLEGRO_EVENT_KEY_CHAR)
    {
        if (strlen(highscore) <= 29)
        {
            char temp[] = { evento.keyboard.unichar, '\0' };
            if (evento.keyboard.unichar == ' ')
            {
                strcat_s(highscore, sizeof highscore, temp);
            }
            else if (evento.keyboard.unichar >= '0' &&
                evento.keyboard.unichar <= '9')
            {
                strcat_s(highscore, sizeof highscore, temp);
            }
            else if (evento.keyboard.unichar >= 'A' &&
                evento.keyboard.unichar <= 'Z')
            {
                strcat_s(highscore, sizeof highscore, temp);
            }
            else if (evento.keyboard.unichar >= 'a' &&
                evento.keyboard.unichar <= 'z')
            {
                strcat_s(highscore, sizeof highscore, temp);
            }
        }

        if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(highscore) != 0)
        {
            highscore[strlen(highscore) - 1] = '\0';
        }
    }
}