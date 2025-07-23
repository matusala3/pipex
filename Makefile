# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 15:10:47 by magebreh          #+#    #+#              #
#    Updated: 2025/07/23 14:01:20 by magebreh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iinclude -I./libft

SRC_DIR = src
BONUS_DIR = bonus
OBJ_DIR = obj
LIBFT_DIR = libft

RM = rm -f

SRC = ${SRC_DIR}/pipex.c ${SRC_DIR}/utils.c ${SRC_DIR}/helper.c
BONUS_SRC = ${BONUS_DIR}/pipex_bonus.c ${BONUS_DIR}/utils_bonus.c ${BONUS_DIR}/exec_bonus.c ${BONUS_DIR}/helper_bonus.c

LIBFT = $(LIBFT_DIR)/libft.a

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJ = $(BONUS_SRC:$(BONUS_DIR)/%.c=$(OBJ_DIR)/%.o)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully.$(RESET)"

bonus: $(LIBFT) $(BONUS_OBJ)
	@$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW) compiling: $<$(RESET)"

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ Libft compiled."

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "$(YELLOW)✅ Object files cleaned."

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "$(YELLOW)✅ All files cleaned."

re: fclean all

.PHONY: all clean fclean re bonus