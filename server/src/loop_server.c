/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** loop_server
*/

#include "../../include/server.h"
#include "../../include/define_value.h"

int change_fd_max(int fd_max, client_t *client)
{
    for (client_t *parse = client; parse != NULL; parse = parse->next) {
        if (parse->sock > fd_max)
            return parse->sock;
    }
    return fd_max;
}

void set_client(client_t *client, fd_set *fd_selected)
{
    for (client_t *parse = client; parse != NULL; parse = parse->next)
        FD_SET(parse->sock, fd_selected);
}

int accept_clients(server_t *serv, int client_sock, socklen_t client_len)
{
    if (FD_ISSET(serv->sock, &serv->fd_selected)) {
        client_sock = accept(serv->sock,
        (struct sockaddr *)&serv->server, &client_len);
        if (client_sock == -1) {
            printf("%s\n", "Problem with accept");
            return ERROR;
        }
        WRITE_MESSAGE(client_sock, "Connection Ready !");
        create_clients(client_sock, serv);
        print_connection(client_sock);
        return SUCCESS;
    }
    return ERROR;
}

void create_all_users(server_t *server)
{
    int fd = open("all_users.txt", O_RDWR | O_CREAT, 0666);
    char connected;

    if (fd < 0)
        return;
    lseek(fd, 0, SEEK_SET);
    for (users_t *user = server->users; user != NULL; user = user->next) {
        write(fd, user->name, strlen(user->name));
        write(fd, " : ", 3);
        write(fd, user->uuid, strlen(user->uuid));
        write(fd, " : ", 3);
        connected = user->connected + '0';
        write(fd, &connected, 1);
        write(fd, " |", 2);
        if (user->next != NULL)
            write(fd, "\n", 1);
    }
    close(fd);
}

int loop_server(server_t *serv)
{
    serv->client = NULL;
    socklen_t client_len = sizeof(serv->server);
    int client_sock = 0;
    int fd_max = 0;
    fd_max = serv->sock;

    while (1) {
        create_all_users(serv);
        fd_max = change_fd_max(fd_max, serv->client);
        FD_ZERO(&serv->fd_selected);
        FD_SET(serv->sock, &serv->fd_selected);
        set_client(serv->client, &serv->fd_selected);
        if (select(fd_max + 1, &serv->fd_selected, NULL, NULL, NULL) < 0)
            return ERROR;
        if (accept_clients(serv, client_sock, client_len) == SUCCESS)
            continue;
        chat(handle_clients(serv), serv);
    }
}