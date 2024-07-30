/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** main
*/

#include "../include/client.h"
#include "../include/define_value.h"

int main(int argc, char** argv)
{
    client_t client;

    if (handle_args(argc, argv) == ERROR)
        return ERROR;
    client.username = NULL;
    client.uuid = NULL;
    if (connect_client_to_server(&client, argv[1], atoi(argv[2])) == ERROR)
        return ERROR;
    return SUCCESS;
}
