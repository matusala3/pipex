# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 15:10:47 by magebreh          #+#    #+#              #
#    Updated: 2025/07/11 19:34:55 by magebreh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
RM = rm -f

OBJ_DIR = obj

# Source files
SRC = src/pipex.c src/parse_args.c src/path_utils.c src/exec.c src/cleanup.c

# Library
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ := $(SRC:src/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "Libft with ft_printf and get_next_line compiled."

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "Executable $(NAME) created."

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "Object files cleaned."

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "All files cleaned."

re: fclean all

# Convenience targets for libft
libft:
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "✅ libft build complete"

libft-clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "✅ libft cleaned"

libft-re:
	@$(MAKE) -s -C $(LIBFT_DIR) re
	@echo "✅ libft rebuilt"

libft-info:
	@$(MAKE) -s -C $(LIBFT_DIR) info

.PHONY: all clean fclean re libft libft-clean libft-re libft-info