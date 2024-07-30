/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** main
*/

#include "../include/server.h"
#include "../include/define_value.h"

int main(int argc, char **argv)
{
    server_t server;

    if (check_args(argc, argv) == ERROR)
        return ERROR;
    if (init_server(&server, atoi(argv[1])) == ERROR)
        return ERROR;
    return SUCCESS;
}
