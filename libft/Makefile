# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wta <wta@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/28 20:09:26 by wta               #+#    #+#              #
#    Updated: 2019/10/10 12:18:58 by wta              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAG = -Wall -Wextra -Werror
CC = gcc

INC_PATH = includes/
INC = $(addprefix -I, $(INC_PATH))
OBJ_PATH = objs/
SRCS_PATH =	srcs/

CHAR_PATH = char/
CHAR_SRCS =			\
	ft_isalnum.c	\
	ft_isalpha.c	\
	ft_isascii.c	\
	ft_isdigit.c	\
	ft_isprint.c	\
	ft_tolower.c	\
	ft_toupper.c

INTEGER_PATH = integer/
INTEGER_SRCS =			\
	ft_atoi.c					\
	ft_intlen_base.c	\
	ft_itoa.c

IO_PATH = io/
IO_SRCS =						\
	ft_putchar.c			\
	ft_putchar_fd.c		\
	ft_putendl.c			\
	ft_putendl_fd.c		\
	ft_putnbr.c				\
	ft_putnbr_fd.c		\
	ft_putstr.c				\
	ft_putstr_fd.c

LST_PATH = lst/
LST_SRCS =								\
	ft_delnode.c						\
	ft_listdel.c						\
	ft_lstadd.c							\
	ft_lstappend.c					\
	ft_lstdel.c							\
	ft_lstdelone.c					\
	ft_lstiter.c						\
	ft_lstmap.c							\
	ft_lstnew.c							\
	ft_lstnew_mallocfree.c	\
	ft_pushback.c						\
	ft_pushfront.c			

MEM_PATH = mem/
MEM_SRCS =			\
	ft_bzero.c		\
	ft_memalloc.c	\
	ft_memccpy.c	\
	ft_memchr.c		\
	ft_memcmp.c		\
	ft_memcpy.c		\
	ft_memdel.c		\
	ft_memmove.c	\
	ft_memset.c	

READ_PATH = read/
READ_SRCS =	get_next_line.c

STR_PATH = str/
STR_SRCS =					\
	ft_strcat.c				\
	ft_strchr.c				\
	ft_strclr.c				\
	ft_strcmp.c				\
	ft_strcpy.c				\
	ft_strdel.c				\
	ft_strdup.c				\
	ft_strdupdel.c		\
	ft_strequ.c				\
	ft_striter.c			\
	ft_striteri.c			\
	ft_strjoin.c			\
	ft_strjoindel.c		\
	ft_strjoinfree.c	\
	ft_strlcat.c			\
	ft_strlen.c				\
	ft_strmap.c				\
	ft_strmapi.c			\
	ft_strncat.c			\
	ft_strncmp.c			\
	ft_strncpy.c			\
	ft_strndup.c			\
	ft_strndupfree.c	\
	ft_strnequ.c			\
	ft_strnew.c				\
	ft_strnstr.c			\
	ft_strrchr.c			\
	ft_strsplit.c			\
	ft_strstr.c				\
	ft_strsub.c				\
	ft_strtrim.c			\
	ft_wdcpy.c				\
	ft_word_count.c		\
	ft_word_len.c			\

FT_PRINTF_PATH = ft_printf/
FT_PRINTF_SRCS = \
	ft_convert.c		\
	ft_convert_c.c		\
	ft_convert_d.c		\
	ft_convert_f.c		\
	ft_convert_hex.c	\
	ft_convert_o.c		\
	ft_convert_p.c		\
	ft_convert_per.c	\
	ft_convert_s.c		\
	ft_convert_u.c		\
	ft_lst_pf.c			\
	ft_parse_pf.c		\
	ft_printf.c			\
	ft_utils.c			\
	ft_utils2.c

BUILD_PATH =				\
	$(SRCS_PATH)			\
	$(CHAR_PATH)			\
	$(INTEGER_PATH)		\
	$(IO_PATH)				\
	$(LST_PATH)				\
	$(MEM_PATH)				\
	$(READ_PATH)			\
	$(STR_PATH)				\
	$(FT_PRINTF_PATH)

SRCS =																					\
	$(addprefix $(CHAR_PATH),$(CHAR_SRCS)) 				\
	$(addprefix $(INTEGER_PATH),$(INTEGER_SRCS))	\
	$(addprefix $(IO_PATH),$(IO_SRCS))						\
	$(addprefix $(LST_PATH),$(LST_SRCS))					\
	$(addprefix $(MEM_PATH),$(MEM_SRCS))					\
	$(addprefix $(READ_PATH),$(READ_SRCS))				\
	$(addprefix $(STR_PATH),$(STR_SRCS))				\
	$(addprefix $(FT_PRINTF_PATH),$(FT_PRINTF_SRCS))

OBJ = $(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_PATH) | $(OBJ)
	ar rc $(NAME) $(OBJ)

$(OBJ_PATH):
	mkdir -p $(addprefix $(OBJ_PATH), $(BUILD_PATH))

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c
	$(CC) $(CFLAG) $(INC) -c -o $@ $<

clean:
	/bin/rm -rf $(OBJ)
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
