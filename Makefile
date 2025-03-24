# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mathispeyre <mathispeyre@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/07 09:35:02 by mathispeyre       #+#    #+#              #
#    Updated: 2025/03/24 13:34:32 by mathispeyre      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	  exit/print.c exit/exit.c \
	  game/game.c game/minimap.c game/player.c \
	  render/raycast.c render/texture.c \
	  setup/initialization/init.c setup/initialization/extract_data.c setup/initialization/grid_map.c setup/initialization/init_map.c\
	  setup/initialization/rgb.c setup/initialization/textures.c setup/initialization/player.c setup/initialization/init_player.c \
	  setup/processing/parsing.c setup/processing/file_utils.c setup/processing/checker.c \
	  setup/processing/color_lines.c setup/processing/texture_lines.c setup/processing/map_lines.c \
	  window/hooks.c window/mlx.c window/draw.c \
	  utils/ft.c utils/detection.c utils/conversion.c utils/free.c

SRCDIR = src/
OBJDIR = objects/
SRCS = $(addprefix $(SRCDIR), $(SRC))
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))
NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT_DIR = .libft/
LIBFT = $(LIBFT_DIR)libft.a

# ==== FOR MACOS ====
ifeq ($(shell uname), Darwin)
MLX_DIR = .minilibx_opengl/
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

# ==== FOR LINUX ====
ifeq ($(shell uname), Linux)
MLX_DIR = .minilibx_linux/
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
endif

MLX = $(MLX_DIR)libmlx.a

ORANGE = \033[0;33m
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(OBJDIR) $(LIBFT) $(MLX) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(LIBFT):
	@echo "🛠️ $(ORANGE) Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@echo "🛠️ $(ORANGE) Compiling minilibx...$(RESET)"
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@echo "✅ $(GREEN)./$(NAME) compiled successfully$(RESET)"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@echo "🛠️ $(ORANGE) Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "🗑️ $(RED) Cleaning object files...$(RESET)"
	@$(RM) -r $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@echo "🗑️ $(RED) Cleaning executable...$(RESET)"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
