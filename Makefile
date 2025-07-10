# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 15:10:47 by magebreh          #+#    #+#              #
#    Updated: 2025/07/08 20:05:31 by magebreh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
AR = ar rcs
RM = rm -f

OBJ_DIR = obj

FT_PRINTF_DIR = libft
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf

OBJ := $(SRC:src/%.c=$(OBJ_DIR)/%.o)

all: $(FT_PRINTF) $(LIBFT) $(NAME)

$(FT_PRINTF):
	@$(MAKE) -s -C $(FT_PRINTF_DIR)
	@echo "ft_printf compiled."

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "Libft compiled."

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) $(FT_PRINTF_DIR) -lft -o $(NAME)
	@echo "Executable $(NAME) created."

clean:
	@$(RM) $(OBJ) $(BONUS_OBJ)	
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "Object files cleaned."

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "All files cleaned."

re: fclean all

.PHONY: all clean fclean re