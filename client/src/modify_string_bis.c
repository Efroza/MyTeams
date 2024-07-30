/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** modify_string_bis
*/

#include "../../include/client.h"
#include "../../include/shared_include.h"

void free_tab(char **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

int check_length_tab(char **tab, int x)
{
    int i = 0;

    for (; tab[i] != NULL; i++);
    if (i == x)
        return 0;
    return 1;
}

char **check_tab(char **tab, const char *command)
{
    int count = 0;

    tab[0] = str_remove(tab[0], command);
    for (int i = 0; tab[0][i]; i++) {
        if (tab[0][i] != ' ')
            count++;
    }
    if (count != 0)
        return NULL;
    return tab;
}