/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** modify_string_bis
*/

#include "../../include/server.h"
#include "../../include/shared_include.h"

char *remove_token(char *str, char token)
{
    char *new_str = str;
    int i = 0;

    while (str[i] == token)
        i++;
    new_str = str + i;
    i = strlen(str) - 1;
    while (str[i] == token)
        i--;
    str[i + 1] = '\0';
    return new_str;
}

void free_tab(char **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

void write_two_strings_to_sock(char *username, char *uid, int clientsock)
{
    char tmp[strlen(username) + strlen(uid) + 1];

    sprintf(tmp, "%s %s", username, uid);
    write(clientsock, tmp, strlen(tmp));
    fflush(stdout);
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