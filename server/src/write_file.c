/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** write_file
*/

#include "../../include/server.h"
#include "../../include/define_value.h"
#include "../../include/shared_include.h"

char *remove_substring(char *str, char *substring)
{
    char *new_str = str;
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == *substring) {
            str[i] = '\0';
            new_str = str + i + 1;
            break;
        }
        i++;
    }
    return new_str;
}

void write_uuid_and_message_alone(char *uuid, char *message,
    char *file, char *sender_uuid)
{
    FILE *fd = fopen(strcat(file, ".txt"), "a+");

    if (fd == NULL)
        return;
    fprintf(fd, "%s %s %s\n", remove_substring(uuid, ".txt"),
        sender_uuid, message);
    fclose(fd);
}

void write_uuid_and_message_generic(char *uuid, char *message,
        char *file, char *sender_uuid)
{
    FILE *fd = fopen(file, "a+");
    char *tmp = malloc(sizeof(char) * (strlen(message) + 2));
    time_t t;

    time(&t);
    sprintf(tmp, "%s", message);
    if (fd == NULL)
        return;
    fprintf(fd, "%s %s \"%s\" \"%s\"\n", uuid, sender_uuid, message,
        remove_token(ctime(&t), '\n'));
    fclose(fd);
    write_uuid_and_message_alone(uuid, tmp, uuid, sender_uuid);
    free(tmp);
}