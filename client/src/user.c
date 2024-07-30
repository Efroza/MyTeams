/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** user
*/

#include "../../include/client.h"
#include "../../include/define_value.h"
#include "../../include/shared_include.h"

void user(client_t *client, char **tab)
{
    char buffer[1024];
    int nb_read = 0;
    char **user_tab = NULL;

    if (client->uuid == NULL) {
        client_error_unauthorized();
        return;
    }
    if (tab[0] != NULL && strcmp(tab[0], "") != 0 && tab[1] != NULL) {
        bzero(buffer, 1024);
        nb_read = read(client->sockfd, buffer, sizeof(buffer));
        if (nb_read == -1)
            return;
        buffer[nb_read] = '\0';
        user_tab = get_arguments(buffer, ' ');
        strcmp(user_tab[0], "NULL") == 0 ? client_error_unknown_user(tab[1])
        : client_print_user(tab[1], user_tab[0], atoi(user_tab[1]));
        bzero(buffer, 1024);
    } else
        client_error_unauthorized();
}

void _send(client_t *client, char **tab)
{
    if (client->uuid == NULL) {
        client_error_unauthorized();
        return;
    }
    if (tab[0] != NULL && strcmp(tab[0], "") != 0 && tab[1] != NULL &&
        tab[2] != NULL) {
        return;
    } else
        client_error_unauthorized();
}

void load_users(char *usernames)
{
    char **user = NULL;
    char *username = NULL;
    char *uuid = NULL;
    int connected = 0;
 
    user = get_arguments(usernames, ':');
    username = strdup(remove_space(user[0]));
    uuid = strdup(remove_space(user[1]));
    connected = atoi(remove_space(user[2]));
    client_print_users(uuid, username, connected);
}

void get_users(char *buffer)
{
    char **usernames = get_arguments(buffer, '\n');

    for (int i = 0; usernames[i] != NULL; i++)
        load_users(usernames[i]);
}

int open_file_users(char *filename)
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
    get_users(buffer);
    close(fd);
    return SUCCESS;
}

void users(client_t *client, char **tab)
{
    char buffer[1024];
    int nb_read = 0;
    char **send_tab = NULL;

    if (client->uuid == NULL) {
        client_error_unauthorized();
        return;
    }
    open_file_users("all_users.txt");
    return;
}