/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** user
*/

#include "../../include/server.h"
#include "../../include/define_value.h"
#include "../../include/shared_include.h"

int check_if_uid_is_connected(server_t *server, char *uid, int sock)
{
    char number[2];

    for (users_t *users = server->users; users != NULL; users = users->next)
        if (strcmp(users->uuid, uid) == 0) {
            sprintf(number, "%d", users->connected);
            write_two_strings_to_sock(users->name, number, sock);
            return 1;
        }
    return 0;
}

void user(client_t *client, server_t *server, char **buffer)
{
    int connected = 0;

    if (client->uuid == NULL) {
        dprintf(client->sock, ERROR_COMMAND);
        return;
    }
    if (buffer[0] != NULL && strcmp(buffer[0], "") != 0 && buffer[1] != NULL){
        if (check_if_uid_is_connected(server, buffer[1], client->sock) != 1) {
            write_two_strings_to_sock("NULL", "0", client->sock);
            dprintf(client->sock, ACTION_FAILED);
        } else
            dprintf(client->sock, ACTION_SUCCESS);
    } else
        dprintf(client->sock, ACTION_FAILED);
    fflush(stdout);
}

void users(client_t *client, server_t *server, char **buffer)
{
    if (client->uuid == NULL) {
        dprintf(client->sock, ERROR_COMMAND);
        return;
    }
    dprintf(client->sock, ACTION_SUCCESS);
    fflush(stdout);
}