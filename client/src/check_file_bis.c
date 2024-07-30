/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** check_file_bis
*/

#include "../../include/client.h"
#include "../../include/define_value.h"
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

char *convert_twodim_to_onedim(char **tab, char *str, int i)
{
    int j = 0;
    int k = 0;

    for (; tab[i] != NULL; i++) {
        for (j = 0; tab[i][j] != '\0'; j++) {
            if (tab[i][j] != '\n') {
                str[k] = tab[i][j];
                k++;
            }
        }
        str[k] = ' ';
        k++;
    }
    str[k] = '\0';
    return remove_space(str);
}

char *replace_token_by_new_token(char *str, char token, char new_token)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == token)
            str[i] = new_token;
    }
    return str;
}