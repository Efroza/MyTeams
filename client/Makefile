##
## EPITECH PROJECT, 2022
## B-NWP-400-PAR-4-1-myteams-brice.boualavong
## File description:
## Makefile
##

SRC		=	main.c							\
			src/handling_error_client.c		\
			src/init_client.c				\
			src/command.c					\
			src/modify_string.c				\
			src/modify_string_bis.c			\
			src/user.c						\
			src/check_file.c				\
			src/check_last_message.c		\
			src/use.c						\
			src/check_file_bis.c

OBJ		=	$(SRC:.c=.o)

NAME	=	myteams_cli

CFLAGS	+=	-I ../include -L ../libs/myteams -lmyteams

all:		$(NAME)

$(NAME):	$(OBJ)
			gcc -o $(NAME) $(OBJ) $(CFLAGS)
			cp $(NAME) ../

clean:
			rm -f $(OBJ)
			rm -f ../$(NAME)

fclean:		clean
			rm -f $(NAME)

re:			fclean all
