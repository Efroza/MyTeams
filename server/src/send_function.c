/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** send_function
*/

#include "../../include/server.h"
#include "../../include/define_value.h"
#include "../../include/shared_include.h"

void loop_send(server_t *server, client_t *client, char **buffer)
{
    char *tmp = malloc(sizeof(char *) * strlen(buffer[3]) + 1);

    sprintf(tmp, "%s", buffer[3]);
    for (users_t *users = server->users; users != NULL;
            users = users->next) {
        if (strcmp(users->uuid, buffer[1]) == 0) {
            write(client->sock, ACTION_SUCCESS, strlen(ACTION_SUCCESS));
            write_uuid_and_message_generic(buffer[1], buffer[3],
                MESSAGE_FILE, client->uuid);
            server_event_private_message_sended(client->uuid,
                                            buffer[1], tmp);
            free(tmp);
            return;
        }
    }
    write(client->sock, ACTION_FAILED, strlen(ACTION_FAILED));
    free(tmp);
}

void do_send(client_t *client, server_t *server, char **buffer)
{
    if (client->uuid == NULL) {
        dprintf(client->sock, ERROR_COMMAND);
        return;
    }
    if (buffer[0] != NULL && strcmp(buffer[0], "") != 0 && buffer[1] != NULL
        && buffer[2] != NULL && buffer[3] != NULL) {
        loop_send(server, client, buffer);
    } else
        write(client->sock, ACTION_FAILED, strlen(ACTION_FAILED));
    fflush(stdout);
}