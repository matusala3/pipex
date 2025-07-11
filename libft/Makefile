# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/24 11:49:18 by magebreh          #+#    #+#              #
#    Updated: 2025/07/11 19:14:02 by magebreh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

AR = ar rcs
RM = rm -f

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
      ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
      ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
      ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
      ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
      ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
      ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
      ft_printf/ft_printf.c ft_printf/print_char.c ft_printf/print_string.c \
      ft_printf/print_int.c ft_printf/print_unsigned.c ft_printf/print_hex.c \
      ft_printf/print_pointer.c get_next_line/get_next_line.c \
      get_next_line/get_next_line_utils.c
OBJ = $(SRC:.c=.o)

SRC_BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
            ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c \
            ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstsize_bonus.c \
            ft_lstnew_bonus.c
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

bonus: .bonus 

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

.bonus: $(OBJ_BONUS) $(NAME)
	@$(AR) $(NAME) $(OBJ_BONUS)
	touch .bonus

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)
	$(RM) ft_printf/*.o get_next_line/*.o

fclean: clean
	$(RM) $(NAME) $(OBJ) $(OBJ_BONUS) .bonus

re: fclean all

.PHONY: all bonus clean fclean re
