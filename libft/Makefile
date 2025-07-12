# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aisaev <aisaev@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 17:34:39 by aisaev            #+#    #+#              #
#    Updated: 2025/05/24 15:32:18 by aisaev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

NAME = libft.a

SRCS = ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
ft_isprint.c ft_isascii.c ft_memset.c ft_memcpy.c ft_memmove.c \
ft_atof.c ft_bzero.c ft_calloc.c ft_itoa.c ft_memchr.c ft_memcmp.c \
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strmapi.c ft_strcmp.c ft_strnstr.c ft_strrchr.c \
ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_printf.c \
ft_putchar.c ft_puthex.c ft_putnbr.c ft_putpointer.c ft_putstr.c ft_putunsigned.c
OBJS = $(SRCS:.c=.o)

BONUS_SRCS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -I . -c $< -o $@

bonus: $(NAME) $(BONUS_OBJS)
	@$(AR) $(NAME) $(BONUS_OBJS)

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	@$(RM) $(NAME) $(bonus)

re: fclean all

.PHONY: clean fclean re all bonus

