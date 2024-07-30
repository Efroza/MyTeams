/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/stat.h>
    #include <sys/wait.h>
    #include <sys/types.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <signal.h>
    #include <errno.h>
    #include <sys/select.h>
    #include <sys/time.h>
    #include <pwd.h>
    #include <stdbool.h>
    #include "../libs/myteams/logging_client.h"

typedef struct client_s {
    int sockfd;
    struct sockaddr_in server;
    char *username;
    char *uuid;
} client_t;

//                  CONNECT CLIENT                        //
int connect_client_to_server(client_t *client, char *ip, int port);
int handle_args(int argc, char **argv);
void check_for_message_in_file(client_t *client, char *file);
void get_last_message(client_t *client, char *file);
char *convert_twodim_to_onedim(char **tab, char *str, int i);
char *copy_string(char *str);
char *replace_token_by_new_token(char *str, char token, char new_token);

//                  MODIFY STRING                        //
char *remove_space(char *str);

//                 CLIENT FUNCTIONS                      //
void logout(client_t *client, char **buffer);
void login(client_t *client, char **buffer);
void user(client_t *client, char **tab);
void _send(client_t *client, char **tab);
void users(client_t *client, char **tab);
void use(client_t *client, char **tab);
void message(client_t *client, char **tab);

static const char *command[7] = {"/logout", "/login", "/user", "/send",
                                "/users", "/use", "/message"};
static const void *function[7] = {&logout, &login, &user, &_send,
                                &users, &use, &message};

#endif /* !CLIENT_H_ */
