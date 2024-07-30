/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** command
*/

#include "../../include/server.h"
#include "../../include/define_value.h"

void open_file_write_username_and_uuid(server_t *serv, char *username,
char *uuid, char *filename)
{
    int fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
    char *buffer = NULL;

    if (fd < 0)
        return;
    buffer = malloc(sizeof(char) * (strlen("\n") +
            strlen(username) + strlen(uuid) + 2));
    sprintf(buffer, "\n%s (%s)", username, uuid);
    write(fd, buffer, strlen(buffer));
    free(buffer);
    add_new_user_to_struct_users(serv, username, uuid);
}

void logout(client_t *client, server_t *server, char **buffer)
{
    dprintf(client->sock, LOGOUT_SUCCESS);
    if (client->username == NULL)
        server_event_user_logged_out("");
    else
        server_event_user_logged_out(client->uuid);
    client->is_connected = false;
    if (client->uuid == NULL)
        return;
    for (users_t *users = server->users; users != NULL; users = users->next) {
        if (strcmp(users->uuid, client->uuid) == 0) {
            users->connected = 0;
            break;
        }
    }
    client->uuid = NULL;
}

int check_if_user_already_exist(server_t *server, char *username,
                                client_t *client)
{
    for (users_t *user = server->users; user != NULL; user = user->next)
        if (strcmp(user->name, username) == 0) {
            client->uuid = strdup(user->uuid);
            user->connected = 1;
            return ONE;
        }
    return SUCCESS;
}

void check_existing_client(client_t *client, server_t *server,
                            char **buffer, char *tmp_str)
{
    if (check_if_user_already_exist(server, client->username,
        client) == 0) {
        tmp_str = malloc(sizeof(char) * 37);
        generate_uuid(tmp_str);
        client->uuid = strdup(tmp_str);
        server_event_user_created(client->uuid, client->username);
        free(tmp_str);
        open_file_write_username_and_uuid(server, client->username,
        client->uuid, USERS_FILE);
    }
}

void login(client_t *client, server_t *server, char **buffer)
{
    if (buffer == NULL || check_length_tab(buffer, 2) == 1 &&
        check_length_tab(buffer, 1) == 1) {
        dprintf(client->sock, ERROR_COMMAND);
        fflush(stdout);
        return;
    }
    if (buffer[0] != NULL && strcmp(buffer[0], "") != 0 &&
        client->uuid == NULL && buffer[1] != NULL) {
        client->username = strdup(buffer[1]);
        check_existing_client(client, server, buffer, NULL);
        write_two_strings_to_sock(client->username, client->uuid,
        client->sock);
        fflush(stdout);
        server_event_user_logged_in(client->uuid);
        dprintf(client->sock, LOGIN_SUCCESS);
    } else
        dprintf(client->sock, ERROR_COMMAND);
}