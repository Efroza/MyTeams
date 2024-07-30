/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** generate_uuid
*/

#include "../../include/server.h"

void generate_uuid(char *uuid)
{
    uuid_t tmp;

    uuid_generate(tmp);
    uuid_unparse(tmp, uuid);
}