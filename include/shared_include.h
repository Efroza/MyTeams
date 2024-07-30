/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** shared_include
*/

#ifndef SHARED_INCLUDE_H_
    #define SHARED_INCLUDE_H_

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

char **get_arguments(char *str, char token);
char **check_buffer(char *buffer, const char *command);
char **check_tab(char **tab, const char *command);
char *str_remove(char *str, const char *sub);
void free_tab(char **tab);
char *remove_space(char *str);
char *remove_token(char *str, char token);

#endif /* !SHARED_INCLUDE_H_ */
