/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** use
*/

#include "../../include/server.h"
#include "../../include/define_value.h"
#include "../../include/shared_include.h"

void use_three_arg(client_t *client, server_t *server, char **buffer,
users_t *user)
{
    for (server->users; server->users != NULL;
        server->users = server->users->next) {
        if (strcmp(user->uuid, server->users->uuid) == 0) {
            server->users->team_use = strdup(buffer[1]);
            server->users->channel_use = strdup(buffer[3]);
            server->users->thread_use = strdup(buffer[5]);
            break;
        }
    }
}

void use_two_arg(client_t *client, server_t *server, char **buffer,
users_t *user)
{
    for (server->users; server->users != NULL;
        server->users = server->users->next) {
        if (strcmp(user->uuid, server->users->uuid) == 0) {
            server->users->team_use = strdup(buffer[1]);
            server->users->channel_use = strdup(buffer[3]);
            server->users->thread_use = strdup("");
            break;
        }
    }
}

void use_one_arg(client_t *client, server_t *server, char **buffer,
users_t *user)
{
    for (server->users; server->users != NULL;
        server->users = server->users->next) {
        if (strcmp(user->uuid, server->users->uuid) == 0) {
            server->users->team_use = strdup(buffer[1]);
            server->users->channel_use = strdup("");
            server->users->thread_use = strdup("");
            break;
        }
    }
}

void use_bis(client_t *client, server_t *server, char **buffer,
users_t *user)
{
    if (buffer[0] != NULL && buffer[1] != NULL && buffer[2] == NULL) {
        use_one_arg(client, server, buffer, user);
        dprintf(client->sock, ACTION_SUCCESS);
        fflush(stdout);
        return;
    }
    if (buffer[0] != NULL && buffer[1] != NULL && buffer[3] != NULL
        && buffer[4] == NULL) {
        use_two_arg(client, server, buffer, user);
        dprintf(client->sock, ACTION_SUCCESS);
        fflush(stdout);
        return;
    }
    if (buffer[0] != NULL && buffer[1] != NULL && buffer[3] != NULL
        && buffer[5] != NULL) {
        use_three_arg(client, server, buffer, user);
        dprintf(client->sock, ACTION_SUCCESS);
        fflush(stdout);
        return;
    }
}

void use(client_t *client, server_t *server, char **buffer)
{
    users_t *user;

    if (client->uuid == NULL) {
        dprintf(client->sock, ERROR_COMMAND);
        return;
    }
    for (user = server->users; user != NULL; user = user->next) {
        if (strcmp(client->uuid, user->uuid) == 0)
            break;
    }
    for (server->users; server->users != NULL;
        server->users = server->users->next) {
        if (strcmp(user->uuid, server->users->uuid) == 0)
            server->users->team_use = strdup("");
            server->users->channel_use = strdup("");
            server->users->thread_use = strdup("");
    }
    use_bis(client, server, buffer, user);
    dprintf(client->sock, ACTION_SUCCESS);
    fflush(stdout);
}