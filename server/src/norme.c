/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** norme
*/

#include "../../include/server.h"
#include "../../include/define_value.h"

void add_new_user_to_struct_users(server_t *serv, char *username, char *uuid)
{
    users_t *new_user = malloc(sizeof(users_t));

    new_user->name = malloc(sizeof(char) * (strlen(username) + 1));
    strcpy(new_user->name, username);
    new_user->uuid = malloc(sizeof(char) * (strlen(uuid) + 1));
    strcpy(new_user->uuid, uuid);
    new_user->next = serv->users;
    new_user->connected = 1;
    serv->users = new_user;
}

void print_connection(int sock)
{
    struct sockaddr_in client;
    socklen_t client_size = sizeof(client);

    if (getpeername(sock, (struct sockaddr *)&client, &client_size) == -1)
        return;
    printf("New connection from %s:%d\n", inet_ntoa(client.sin_addr),
        ntohs(client.sin_port));
}