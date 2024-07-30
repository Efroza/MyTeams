/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** command
*/

#include "../../include/client.h"
#include "../../include/define_value.h"
#include "../../include/shared_include.h"

void login(client_t *client, char **tab)
{
    char buffer[1024];
    int nb_read = 0;
    char **login_tab = NULL;

    if (client->uuid == NULL && tab[0] != NULL && strcmp(tab[0], "") != 0
        && tab[1] != NULL) {
        nb_read = read(client->sockfd, buffer, sizeof(buffer));
        buffer[nb_read] = '\0';
        login_tab = get_arguments(buffer, ' ');
        client->username = malloc(sizeof(char) * (strlen(login_tab[0]) + 1));
        strcpy(client->username, login_tab[0]);
        client->uuid = malloc(sizeof(char) * (strlen(login_tab[1]) + 1));
        strcpy(client->uuid, login_tab[1]);
        client_event_logged_in(client->uuid, client->username);
    } else
        client_error_unauthorized();
    return;
}

void logout(client_t *client, char **tab)
{
    if (client->uuid == NULL) {
        client_event_logged_out("", "");
        return;
    }
    client_event_logged_out(client->uuid, client->username);
    if (client->uuid != NULL)
        free(client->uuid);
    if (client->username != NULL)
        free(client->username);
    client->uuid = NULL;
}