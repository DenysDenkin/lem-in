NAME = lem-in

LIBNAME = libft/libft.a
OBJ = $(SRC:.c=.o)
HDR = lem_in.h libft/libft.h
FLAGS = -Wall -Wextra -Werror
SRC =	main.c \
		src/init.c \
		src/output.c \
		src/parser.c \
		src/t_info_handler.c \
		src/t_path_handler.c \
		src/mainh.c

all: liball $(NAME)

obj: $(OBJ)

$(NAME) : $(LIBNAME) $(OBJ)
		gcc $(FLAGS) $^ -o $(NAME)

%.o: %.c $(HDR)
		gcc $(FLAGS) -o $@ -c $<

clean: libclean
		rm -rf $(OBJ)

fclean: libfclean clean
		rm -rf $(NAME)

re: fclean all

$(LIBNAME): liball

liball:
		@make -C libft/ all

libclean:
		@make -C libft/ clean

libfclean:
		@make -C libft/ fclean

libre: libfclean liball
