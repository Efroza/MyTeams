/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

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
    #include <uuid/uuid.h>
    #include "../libs/myteams/logging_server.h"

typedef struct client_s {
    int sock;
    int checker;
    bool is_connected;
    char *username;
    char *uuid;
    struct client_s *next;
} client_t;

typedef struct users_s {
    char *name;
    char *uuid;
    int connected;
    char *team_use;
    char *channel_use;
    char *thread_use;
    struct users_s *next;
} users_t;

typedef struct server_s {
    int sock;
    int waiting;
    struct sockaddr_in server;
    fd_set fd_selected;
    socklen_t client_len;
    client_t *client;
    users_t *users;
} server_t;

//                    CONNECT SERVER                        //

int check_args(int argc, char **argv);
int init_server(server_t *serv, int port);
void create_clients(int fd, server_t *serv);
client_t *handle_clients(server_t *serv);
int loop_server(server_t *serv);
void chat(client_t *client, server_t *server);
char *remove_space(char *str);
void generate_uuid(char *uuid);
int check_length_tab(char **tab, int x);
void write_two_strings_to_sock(char *username, char *uid, int clientsock);
void write_uuid_and_message_generic(char *uuid, char *message,
        char *file, char *sender_uuid);
void add_new_user_to_struct_users(server_t *serv, char *username, char *uuid);
void print_connection(int sock);


//                     COMMAND                              //

void logout(client_t *client, server_t *server, char **buffer);
void login(client_t *client, server_t *server, char **buffer);
void user(client_t *client, server_t *server, char **buffer);
void do_send(client_t *client, server_t *server, char **buffer);
void users(client_t *client, server_t *server, char **buffer);
void use(client_t *client, server_t *server, char **buffer);
void message(client_t *client, server_t *server, char **buffer);

//                      TAB COMMAND                          //

static const char *command[7] = {"/logout", "/login", "/user", "/send",
                "/users", "/use", "/message"};
static const void *function[7] = {&logout, &login, &user, &do_send,
                &users, &use, &message};

#endif /* !SERVER_H_ */
