/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** check_file
*/

#include "../../include/client.h"
#include "../../include/define_value.h"
#include "../../include/shared_include.h"

time_t convert_string(char *str)
{
    struct tm tm;
    char *tmp = malloc(sizeof(char) * (strlen(str) + 1));
    char **tab = malloc(sizeof(char *) * (strlen(str) + 1));

    strcpy(tmp, str);
    tab = get_arguments(replace_token_by_new_token(tmp, ':', ' '), ' ');
    tm.tm_year = atoi(tab[6]) - 1900;
    tm.tm_mon = atoi(tab[1]) - 1;
    tm.tm_mday = atoi(tab[2]);
    tm.tm_hour = atoi(tab[3]);
    tm.tm_min = atoi(tab[4]);
    tm.tm_sec = atoi(tab[5]);
    tm.tm_isdst = -1;
    free(tmp);
    free(tab);
    return mktime(&tm);
}

char *convert_time_t_to_char(time_t t)
{
    char *time = NULL;
    struct tm *tm = localtime(&t);

    time = malloc(sizeof(char) * 20);
    sprintf(time, "%d-%02d-%02d %02d:%02d:%02d", tm->tm_year + 1900,
    tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    return time;
}

void print_file(char *user_id, char *tmp, char **tab)
{
    char **message = get_arguments(tmp, '"');

    client_private_message_print_messages(tab[1],
    convert_string(message[2]), message[0]);
}

void loop_file(FILE *fd, char *user_id, client_t *client)
{
    char line[MAX_BODY_LENGTH];
    char **tab;
    char *tmp_str;

    while (fgets(line, sizeof(line), fd)) {
        tab = get_arguments(line, ' ');
        if (tab == NULL)
            return;
        tmp_str = malloc(sizeof(char) * (strlen(tab[0]) + strlen(tab[1])));
        if (tmp_str == NULL)
            return;
        tmp_str = convert_twodim_to_onedim(tab, tmp_str, 2);
        if (strcmp(user_id, tab[0]) == 0 || strcmp(user_id, tab[1]) == 0)
            print_file(user_id, tmp_str, tab);
        free(tab);
        free(tmp_str);
    }
}

void message(client_t *client, char **tab)
{
    FILE *fd;

    if (client->uuid == NULL) {
        client_error_unauthorized();
        return;
    }
    if (access(MESSAGE_FILE, F_OK) == -1)
        return;
    fd = fopen(MESSAGE_FILE, "a+");
    if (fd == NULL)
        return;
    if (tab[0] != NULL && tab[1] != NULL && strcmp(tab[0], "") != 0) {
        loop_file(fd, tab[1], client);
    } else {
        client_error_unauthorized();
    }
}