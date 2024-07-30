/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** handling_error_server
*/

#include "../../include/server.h"
#include "../../include/define_value.h"

int check_args(int argc, char **argv)
{
    int second_arg = 0;

    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        printf("USAGE: ./myteams_server port\n\n\tport ");
        printf("is the port number on which the server socket listens.\n");
        return SUCCESS;
    }
    if (argc != 2)
        return ERROR;
    second_arg = atoi(argv[1]);
    if (second_arg < 1) {
        printf("Wrong argument, try ./myteams_server -help\n");
        return ERROR;
    }
}
