/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** check_last_message
*/

#include "../../include/client.h"
#include "../../include/define_value.h"
#include "../../include/shared_include.h"

void print_last_message(FILE *fd)
{
    char line[MAX_BODY_LENGTH];
    char **tab;
    char *tmp_str;

    while (fgets(line, sizeof(line), fd)) {
        tab = get_arguments(line, ' ');
        if (tab == NULL)
            return;
        tmp_str = malloc(sizeof(char) * (strlen(tab[0]) + strlen(tab[1])));
        if (tmp_str == NULL)
            return;
        tmp_str = convert_twodim_to_onedim(tab, tmp_str, 2);
        client_event_private_message_received(tab[1], tmp_str);
        free(tmp_str);
        free(tab);
    }
}

void print_actual_directory(char *file, char *name)
{
    DIR *dir = opendir(file);
    struct dirent *dirent;

    if (dir == NULL)
        return;
    while ((dirent = readdir(dir)) != NULL) {
        if (dirent->d_name[0] != '.' && strcmp(dirent->d_name, name) != 0) {
            printf("%s\n", dirent->d_name);
            printf("%d\n", strcmp(dirent->d_name, name));
            printf("%s\n", name);
        }
    }
    closedir(dir);
}

char *copy_string(char *str)
{
    char *new_str = malloc(sizeof(char) * (strlen(str) + 1));

    if (new_str == NULL)
        return NULL;
    strcpy(new_str, str);
    return new_str;
}

void get_last_message(client_t *client, char *file)
{
    FILE *fd;
    char *tmp = copy_string(file);

    if (client->uuid == NULL || file == NULL ||
        access(strcat(file, ".txt"), F_OK) == -1)
        return;
    fd = fopen(file, "r");
    if (fd == NULL) {
        return;
    }
    print_last_message(fd);
    remove(file);
}