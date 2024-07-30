/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** handling_error_client
*/

#include "../../include/client.h"
#include "../../include/define_value.h"

int handle_args(int argc, char **argv)
{
    int third_arg = 0;

    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        printf("./myteams_cli -help\nUSAGE: ./myteams_cli ip port\nip  is");
        printf(" the server ip address on which the server socket listens\np");
        printf("ort  is the port number on which the server socket listens\n");
        return SUCCESS;
    }
    if (argc != 3)
        return ERROR;
    third_arg = atoi(argv[2]);
    if (third_arg < 1) {
        printf("Wrong argument, try ./myteams_cli -help\n");
        return ERROR;
    }
}
