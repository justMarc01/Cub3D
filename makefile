# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oabdelka <oabdelka@student.42.fr>          +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025/02/14 19:00:00 by oabdelka          #+#    #+#             #
#    Updated: 2025/02/14 20:00:00 by oabdelka         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

# ==== COMPILER & FLAGS ====
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
MLX_FLAGS	= -L ./minilibx-linux -lmlx -lXext -lX11 -lm
RM			= rm -rf

# ==== TARGET EXECUTABLE ====
NAME		= cub3d

# ==== DIRECTORIES ====
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include

# ==== SOURCE FILES ====
SRC_FILES	= parse_cub_file.c \
			  parse_texture.c \
			  parse_utils.c \
			  parse_color.c \
			  parsing_map.c \
			  cub3d.c \
			  cub3d_utils.c \
			  cub3d_utils_1.c \
			  cub3d_utils_2.c \
			  valid_map.c \
			  valid_map_utils.c \
			  ray_casting.c \
			  ray_catsing_1.c \
			  ray_casting_2.c \
			  movements.c \
			  mov_utils.c \
			  main.c \
			  utils.c \
			  get_next_line.c \
			  get_next_line_utils.c

SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ==== COLORS ====
GREEN		= \033[0;32m
BLUE		= \033[0;34m
RED			= \033[0;31m
RESET		= \033[0m

# ==== RULES ====

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Compiling Cub3D...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)
	@echo "$(BLUE)Build complete! Run ./cub3d <map.cub>$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) $(OBJ_DIR)/*.o

fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	@$(RM) $(NAME)

re: fclean all

# ==== DEBUGGING ====
valgrind: re
	@echo "$(BLUE)Running with Valgrind...$(RESET)"
	valgrind --leak-check=full ./$(NAME) map.cub

norm:
	@echo "$(BLUE)Checking Norminette...$(RESET)"
	norminette $(SRC) $(INC_DIR)/*.h

run: all
	@./$(NAME) map.cub

.PHONY: all clean fclean re valgrind norm run
