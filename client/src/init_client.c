/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** init_client
*/

#include "../../include/client.h"
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

void loop_chat(int sock, client_t *client, char *buff)
{
    void (*func)(client_t *, char **);
    char *test = "";

    bzero(buff, MAX_BODY_LENGTH);
    fgets(buff, MAX_BODY_LENGTH, stdin);
    write(sock, buff, strlen(buff));
    for (int i = 0; i < 7; i++) {
        if (strncmp(buff, command[i], strlen(command[i])) == 0
            && check_users(buff, command[i]) == 0) {
            func = function[i];
            func(client, check_buffer(buff, command[i]));
            fflush(stdout);
            return;
        }
    }
    client_error_unauthorized();
}

void chat(int sock, client_t *client)
{
    char buff[MAX_BODY_LENGTH];
    int nb = 0;
    char *tmp;

    bzero(buff, MAX_BODY_LENGTH);
    nb = read(sock, buff, MAX_BODY_LENGTH);
    if (nb == 0) {
        client->sockfd = -1;
        close(client->sockfd);
        return;
    }
    buff[nb] = '\0';
    printf("%s\n", buff);
    printf("> ");
    if (client->uuid != NULL) {
        tmp = copy_string(client->uuid);
        get_last_message(client, tmp);
        free(tmp);
    }
    loop_chat(sock, client, buff);
    fflush(stdout);
}

int loop_connection(client_t *client, fd_set read_serv)
{
    while (client->sockfd != -1) {
        FD_ZERO(&read_serv);
        FD_SET(0, &read_serv);
        FD_SET(client->sockfd, &read_serv);
        if (select(client->sockfd + 1, &read_serv, NULL, NULL, NULL) == -1)
            return ERROR;
        for (int i = 0; i < client->sockfd + 1; i++) {
            if (FD_ISSET(i, &read_serv))
                chat(i, client);
        }
    }
}

int connect_client_to_server(client_t *client, char *ip, int port)
{
    fd_set read_serv;

    client->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->sockfd == -1) {
        return ERROR;
    }
    bzero(&client->server, sizeof(client->server));
    client->server.sin_addr.s_addr = inet_addr(ip);
    client->server.sin_family = AF_INET;
    client->server.sin_port = htons(port);
    if (connect(client->sockfd, (struct sockaddr *)&client->server,
        sizeof(client->server)) != 0) {
        return ERROR;
    }
    printf("Successfully connected to server\n");
    loop_connection(client, read_serv);
    return SUCCESS;
}