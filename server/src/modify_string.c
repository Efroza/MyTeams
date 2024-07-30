/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** str_remove
*/

#include "../include/server.h"
#include "../include/shared_include.h"

char *str_remove(char *str, const char *sub)
{
    size_t len = strlen(sub);

    if (len > 0) {
        char *new_str = str;
        for (; (new_str = strstr(new_str, sub));
        memmove(new_str, new_str + len, strlen(new_str + len) + 1));
    }
    return str;
}

char *remove_space(char *str)
{
    char *new_str = str;
    int i = 0;

    while (str[i] == ' ' || str[i] == '\n')
        i++;
    new_str = str + i;
    i = strlen(str) - 1;
    while (str[i] == ' ' || str[i] == '\n')
        i--;
    str[i + 1] = '\0';
    return new_str;
}

int nbr_of_token(char *str, char delim)
{
    int i = 0;
    int nbr = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == delim)
            nbr++;
    }
    return nbr;
}

char **get_arguments(char *str, char token)
{
    int i = 0;
    char **arguments = NULL;
    char *new_str = NULL;

    if (str == NULL)
        return NULL;
    arguments = malloc (sizeof(char *) * nbr_of_token(str, token) + 1);
    new_str = strdup(str);
    new_str = strtok(str, &token);
    do {
        arguments[i] = new_str;
        i++;
        new_str = strtok(NULL, &token);
    } while (new_str != NULL);
    arguments[i] = NULL;
    return arguments;
}

char **check_buffer(char *buffer, const char *command)
{
    return check_tab(get_arguments(remove_space(buffer), '"'), command);
}