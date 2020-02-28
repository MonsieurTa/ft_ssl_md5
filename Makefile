# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wta <wta@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/28 20:09:26 by wta               #+#    #+#              #
#    Updated: 2020/02/28 18:10:21 by wta              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
CC = cc -O2

INC_DIR = include
OBJ_DIR = objs
SRCS_DIR =	srcs
LIBFT = libft

HEADERS =		\
ft_ssl.h		\
md5.h			\
option.h		\
sha.h

SRCS =				\
des/pbkdf2.c		\
des/setters.c		\
md5/md5.c			\
sha/setters.c		\
sha/sha1.c			\
sha/sha224.c		\
sha/sha256.c		\
utils/array.c		\
utils/buffer.c		\
utils/bytes.c		\
utils/digest.c		\
utils/io.c			\
utils/math.c		\
cmd.c				\
error.c				\
format.c			\
main.c				\
option.c			\
read.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/, $(OBJ))
	$(MAKE) -j10 -C libft
	$(CC) $(CFLAGS) $^ -L $(LIBFT) -lft -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/des
	mkdir -p $(OBJ_DIR)/md5
	mkdir -p $(OBJ_DIR)/sha
	mkdir -p $(OBJ_DIR)/utils

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c $(addprefix $(INC_DIR)/, $(HEADERS)) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(addprefix $(LIBFT)/, $(INC_DIR)) -c -o $@ $<

clean:
	$(MAKE) -C libft clean
	/bin/rm -rf $(OBJ)
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all $(LIBFT) clean fclean re
