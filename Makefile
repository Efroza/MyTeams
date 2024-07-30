##
## EPITECH PROJECT, 2022
## B-NWP-400-PAR-4-1-myteams-brice.boualavong
## File description:
## Makefile
##

all:
			make -C client/
			make -C server/

clean:
			make clean -C client/
			make clean -C server/

fclean:
			make fclean -C client/
			make fclean -C server/

re:
			make clean -C client/
			make clean -C server/
			make re -C client/
			make re -C server/
