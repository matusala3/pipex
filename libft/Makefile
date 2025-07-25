# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/24 11:49:18 by magebreh          #+#    #+#              #
#    Updated: 2025/07/11 19:36:35 by magebreh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

AR = ar rcs
RM = rm -f

# Object directory
OBJ_DIR = obj

# Core libft sources
LIBFT_SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
            ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
            ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
            ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
            ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
            ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
            ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

# ft_printf sources  
PRINTF_SRC = ft_printf/ft_printf.c ft_printf/print_char.c ft_printf/print_string.c \
             ft_printf/print_int.c ft_printf/print_unsigned.c ft_printf/print_hex.c \
             ft_printf/print_pointer.c

# get_next_line sources
GNL_SRC = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

# Combined sources
SRC = $(LIBFT_SRC) $(PRINTF_SRC) $(GNL_SRC)
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Bonus sources
SRC_BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
            ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c \
            ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstsize_bonus.c \
            ft_lstnew_bonus.c
OBJ_BONUS = $(SRC_BONUS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

bonus: .bonus 

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "✅ libft.a created with integrated ft_printf and get_next_line"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

.bonus: $(OBJ_BONUS) $(NAME)
	@$(AR) $(NAME) $(OBJ_BONUS)
	@touch .bonus
	@echo "✅ Bonus functions added to libft.a"

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(RM) .bonus
	@echo "🧹 Object files cleaned"

fclean: clean
	@$(RM) $(NAME)
	@echo "🧹 All files cleaned"

re: fclean all

info:
	@echo "📊 Library Statistics:"
	@echo "   Library: $(NAME)"
	@if [ -f $(NAME) ]; then \
		echo "   Size: $$(ls -lh $(NAME) | awk '{print $$5}')"; \
		echo "   Functions: $$(nm $(NAME) | grep -c ' T ' || echo 0)"; \
	else \
		echo "   Library not built yet"; \
	fi

.PHONY: all bonus clean fclean re info
