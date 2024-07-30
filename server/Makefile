##
## EPITECH PROJECT, 2022
## B-NWP-400-PAR-4-1-myteams-brice.boualavong
## File description:
## Makefile
##

SRC		=	main.c						\
			src/handling_error_server.c	\
			src/init_server.c			\
			src/handle_clients.c		\
			src/loop_server.c			\
			src/start_chat.c			\
			src/connect.c				\
			src/modify_string.c			\
			src/generate_uuid.c			\
			src/modify_string_bis.c		\
			src/user.c					\
			src/write_file.c			\
			src/use.c					\
			src/message.c				\
			src/norme.c					\
			src/send_function.c

OBJ		=	$(SRC:.c=.o)

NAME	=	myteams_server

CFLAGS	+=	-I ../include -L ../libs/myteams -lmyteams -luuid

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
