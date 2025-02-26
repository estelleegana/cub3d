#nom de l'executable 
NAME = cub3d

#compilateur
CC = gcc

#flags
FLAGS = -Wall -Werror -Wextra

#include
INCLUDELIBFT = -L ./libft -lft
INCLUDEMINILIBX = minilibx-linux/libmlx_Linux.a -lmlx -lXext -lX11 -Lminilibx-linux
INCLUDEMATHS = -lm
#fichiers sources
SRCS = main.c \

#creation d'objets
OBJS = $(SRCS:.c=.o)

#compilation de l'executable
$(NAME) : $(OBJS)
	make -C libft/
	# make -C minilibx-linux/
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(INCLUDELIBFT) $(INCLUDEMATHS) $(INCLUDEMINILIBX)

all : $(NAME)

clean:
	rm -rf $(OBJS)
	make -C libft/ clean
	# make -C minilibx-linux/ clean


fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean
	# make -C minilibx-linux/ fclean

re: fclean all

bonus: