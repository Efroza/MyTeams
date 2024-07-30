/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-brice.boualavong
** File description:
** define_value
*/

#ifndef DEFINE_VALUE_H_
    #define DEFINE_VALUE_H_

    #define WRITE_MESSAGE(fd, message) write(fd, message, strlen(message))
    #define ONE 1
    #define SUCCESS 0
    #define ERROR 84
    #define MAX_BODY_LENGTH 512
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define LOGOUT_SUCCESS "202: Logout Successfully.\n"
    #define LOGIN_SUCCESS "200: Login Successfully.\n"
    #define ERROR_COMMAND "500: Unauthorized command.\n"
    #define ACTION_SUCCESS "200: Action Successfull.\n"
    #define ACTION_FAILED "501: Action Failed.\n"
    #define USERS_FILE "users.txt"
    #define MESSAGE_FILE "message.txt"

#endif /* !DEFINE_VALUE_H_ */
