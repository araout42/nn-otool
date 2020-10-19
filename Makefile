# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: araout <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/01 04:38:21 by araout            #+#    #+#              #
#    Updated: 2020/10/12 18:42:52 by araout           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NM = ft_nm
OTOOL = ft_otool

NM_SRC = srcs/ft_nm/ft_nm.c srcs/ft_nm/manage_lst.c srcs/ft_nm/segment_64.c \
		 srcs/ft_nm/symtab64.c srcs/ft_nm/ft_nm32.c srcs/ft_nm/print_output.c \
		 srcs/ft_nm/ft_nm_fat32.c srcs/ft_nm/ft_nm_fat64.c srcs/ft_nm/endian.c \

OTOOL_SRC = srcs/ft_otool/ft_otool.c

NM_OBJ = $(NM_SRC:.c=.o)
OTOOL_OBJ = $(OTOOL_SRC:.c=.o)

LIBFT = libft

LIB = $(LIBFT)/libft.a

NM_HEADERS =  includes/ft_nm.h
OTOOL_HEADERS = includes/ft_otool.h


INCLUDES = -Iincludes -I$(LIBFT)

NM_DEPEN = $(NM_OBJ) Makefile $(NM_HEADERS)
OTOOL_DEPEN = $(OTOOL_OBJ) Makefile $(OTOOL_HEADERS)

CC = gcc

CFLAGS += -g -Wall -Wextra -Werror $(INCLUDES)

all: lib $(NM) $(OTOOL)

$(NM): $(NM_DEPEN)
	$(CC)  $(CFLAG)  $(NM_OBJ) $(LIB) -o $(NM)

$(OTOOL): $(OTOOL_DEPEN)
	$(CC) $(CFLAGS) $(OTOOL_OBJ) $(LIB) -o $(OTOOL)

lib:
	make -C $(LIBFT) all

clean:
	make clean -C $(LIBFT)
	rm -f $(NM_OBJ)
	rm -f $(OTOOL_OBJ)

fclean: clean
	make fclean -C $(LIBFT)
	/bin/rm -f $(NM_OBJ)
	/bin/rm -f $(OTOOL_OBJ)
	/bin/rm -f ./$(NM)
	/bin/rm -f ./$(OTOOL)

re:
	make fclean
	make all
