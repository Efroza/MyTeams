/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** init_server
*/

#include "../../include/server.h"
#include "../../include/define_value.h"
#include "../../include/shared_include.h"

void load_users(server_t *serv, char *username, char **user)
{
    users_t *parse;
    users_t *users = malloc(sizeof(users_t));

    if (users == NULL)
        return;
    user = get_arguments(username, '(');
    users->name = strdup(remove_space(user[0]));
    if (users->name == NULL)
        return;
    users->uuid = strdup(remove_space(user[1]));
    if (users->uuid == NULL)
        return;
    users->connected = 0;
    users->next = NULL;
    if (serv->users == NULL) {
        serv->users = users;
        return;
    }
    for (parse = serv->users; parse->next != NULL; parse = parse->next);
    parse->next = users;
}

void get_users(server_t *serv, char *buffer)
{
    char **user = NULL;
    char **usernames = get_arguments(buffer, ')');

    serv->users = NULL;
    for (int i = 0; usernames[i] != NULL; i++)
        load_users(serv, usernames[i], user);

    for (users_t *user = serv->users; user != NULL; user = user->next)
        server_event_user_loaded(user->uuid, user->name);
}

int open_file_users(server_t *serv, char *filename)
{
    struct stat file;
    size_t size = 0;
    char *buffer = NULL;
    int fd = open(filename, O_RDWR | O_CREAT, 0666);

    if (fd < 0)
        return ERROR;
    stat(filename, &file);
    size = file.st_size;
    buffer = malloc((sizeof(char) * size) + 1);
    read(fd, buffer, size);
    close(fd);
    get_users(serv, buffer);
    return SUCCESS;
}

int init_server(server_t *serv, int port)
{
    serv->sock = socket(AF_INET, SOCK_STREAM, 6);
    if (serv->sock == -1) {
        printf("%s\n", "Problem with socket");
        return ERROR;
    }
    serv->server.sin_family = AF_INET;
    serv->server.sin_port = htons(port);
    serv->server.sin_addr.s_addr = INADDR_ANY;
    if (bind(serv->sock, (struct sockaddr *)&serv->server,
        sizeof(serv->server)) == -1) {
        printf("%s\n", "Problem with bind");
        return ERROR;
    }
    if (listen(serv->sock, 3) == -1) {
        printf("%s\n", "Problem with listen");
        return ERROR;
    }
    open_file_users(serv, USERS_FILE);
    if (loop_server(serv) == ERROR)
        return ERROR;
}