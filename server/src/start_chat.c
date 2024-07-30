/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** start_chat
*/

#include "../../include/server.h"
#include "../../include/define_value.h"
#include "../../include/shared_include.h"

int check_users(char *buffer, const char *command)
{
    if (strcmp(command, "/user") == 0) {
        if (strncmp(buffer, "/users", strlen("/users")) == 0)
            return 1;
    }
    return 0;
}

int check_nb_read(int nb_read, client_t *client, server_t *server)
{
    if (nb_read == 0) {
        if (client->uuid != NULL)
            logout(client, server, NULL);
        client->sock = -1;
        close(client->sock);
        FD_CLR(client->sock, &server->fd_selected);
        return ERROR;
    }
    return 0;
}

void read_message(client_t *client, server_t *server)
{
    char buffer[1024];
    int nb_read = 0;
    void (*func)(client_t *, server_t *, char **);

    fflush(stdout);
    nb_read = read(client->sock, buffer, sizeof(buffer));
    buffer[nb_read] = '\0';
    if (check_nb_read(nb_read, client, server) == ERROR)
        return;
    for (int i = 0; i < 7; i++)
        if (strncmp(buffer, command[i], strlen(command[i])) == 0
            && check_users(buffer, command[i]) == 0) {
            func = function[i];
            func(client, server,check_buffer(buffer, command[i]));
            return;
        }
    dprintf(client->sock, ERROR_COMMAND);
    fflush(stdout);
}

void chat(client_t *client, server_t *server)
{
    read_message(client, server);
}