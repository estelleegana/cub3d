# === Nom du binaire ===
NAME = cub3D

# === Compilation ===
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)
DEBUGFLAGS = -Wall -Wextra -g -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)

# === Répertoires ===
OBJ_DIR = objs
LIBFT_DIR = includes/libft
MLX_DIR = includes/mlx

# === Sources ===
GNL_SRC = includes/gnl/get_next_line_utils.c \
          includes/gnl/get_next_line.c

SRC = decals_parse.c \
      hook_keys.c \
      hook_rotations.c \
      hook_wasd.c \
      init.c \
      main.c \
      map_parse.c \
      parse.c \
      ray_dda.c \
      ray_draw.c \
      ray_textures.c \
      utils_free.c \
      utils_ray.c \
      utils_struct.c \
      map_check.c \
      $(GNL_SRC)

# === Objets ===
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# === Headers ===
HEADERS = \
    cub3d.h \
    includes/gnl/get_next_line.h \
    includes/libft/libft.h \
    includes/mlx/mlx.h

# === Librairies ===
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# === Cible principale ===
$(NAME): $(OBJ) $(HEADERS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(OBJ) $(CFLAGS) $(LIBS) -o $(NAME)
	@echo "\033[32m✔ Compilation terminée.\033[0m"

# === Règle de compilation des objets ===
$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# === Inclusion des dépendances .d ===
-include $(OBJ:.o=.d)

# === Cibles utiles ===
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
	norminette $(SRC) cub3d.h

re: fclean all