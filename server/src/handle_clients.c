/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** handle_clients
*/

#include "../../include/server.h"

void create_clients(int fd, server_t *serv)
{
    client_t *client;

    if (serv->client == NULL) {
        serv->client = malloc(sizeof(client_t));
        serv->client->is_connected = false;
        serv->client->sock = fd;
        serv->client->uuid = NULL;
        serv->client->username = NULL;
        serv->client->next = NULL;
        return;
    }
    client = serv->client;
    for (;client->next != NULL; client = client->next);
    client->next = malloc(sizeof(client_t));
    client->next->is_connected = false;
    client->next->sock = fd;
    client->next->uuid = NULL;
    client->next->username = NULL;
    client->next->next = NULL;
}

client_t *handle_clients(server_t *serv)
{
    for (client_t *client = serv->client; client != NULL;
        client = client->next) {
        if (FD_ISSET(client->sock, &serv->fd_selected)) {
            return (client);
        }
    }
    return NULL;
}
