NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)
SRC = decals_parse.c \
	hook_keys.c\
	hook_rotations.c \
	hook_wasd.c \
	init.c \
	main.c \
	map_parse.c\
	parse.c\
	ray_dda.c\
	ray_textures.c\
	utils_free.c\
	utils_ray.c \
	utils_struct.c\
	includes/gnl/get_next_line_utils.c \
	includes/gnl/get_next_line.c\

OBJ_DIR = objs
LIBFT_DIR = includes/libft
MLX_DIR = includes/mlx

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@$(CC) $(OBJ) $(CFLAGS) $(LIBS) -o $(NAME)
	@echo "Compilation terminée."

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@echo "Fichiers objets supprimés."

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "Exécutable supprimé."

norm :
	norminette $(SRC)

re: fclean all

.PHONY: all clean fclean re
