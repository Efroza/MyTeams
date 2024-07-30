/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** use
*/

#include "../../include/client.h"
#include "../../include/define_value.h"
#include "../../include/shared_include.h"

void use(client_t *client, char **tab)
{
    char buffer[1024];
    int nb_read = 0;
    char **user_tab = NULL;

    if (client->uuid == NULL) {
        client_error_unauthorized();
        return;
    }
}