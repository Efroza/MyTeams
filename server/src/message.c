/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** message
*/

#include "../../include/server.h"
#include "../../include/define_value.h"

void message(client_t *client, server_t *server, char **buffer)
{
    if (client->uuid == NULL) {
        dprintf(client->sock, ERROR_COMMAND);
        return;
    }
    if (buffer[0] != NULL && buffer[1] != NULL && strcmp(buffer[0], "") != 0){
        for (users_t *users = server->users; users != NULL;
            users = users->next) {
            if (strcmp(users->uuid, buffer[1]) == 0) {
                dprintf(client->sock, ACTION_SUCCESS);
                fflush(stdout);
                return;
            }
        }
        dprintf(client->sock, ERROR_COMMAND);
        fflush(stdout);
    } else
        dprintf(client->sock, ERROR_COMMAND);
    fflush(stdout);
}