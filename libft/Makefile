# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bihattay <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/09 12:43:23 by bihattay          #+#    #+#              #
#    Updated: 2020/10/05 14:23:52 by araout           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

HEADERS = libft.h

NAME = libft.a

SOURCES = 	ft_atoi.c\
			ft_bzero.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isprint.c\
			ft_memalloc.c\
			ft_memccpy.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memdel.c\
			ft_memmove.c\
			ft_memset.c\
			ft_strcat.c\
			ft_strchr.c\
			ft_strclr.c\
			ft_strcmp.c\
			ft_strcpy.c\
			ft_strdel.c\
			ft_strdup.c\
			ft_strequ.c\
			ft_striter.c\
			ft_striteri.c\
			ft_strlcat.c\
			ft_strlen.c\
			ft_strmap.c\
			ft_strmapi.c\
			ft_strncat.c\
			ft_strnequ.c\
			ft_strncmp.c\
			ft_strncpy.c\
			ft_print_hex.c\
			ft_putnstr.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_strstr.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_strsub.c\
			ft_strjoin.c\
			ft_atoi_base.c\
			ft_strtrim.c\
			ft_strsplit.c\
			ft_itoa.c\
			ft_putchar.c\
			ft_putstr.c\
			ft_putendl.c\
			ft_putnbr.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_putchar_error.c\
			ft_putnbr_error.c\
			ft_strdup_if.c\
			ft_strnew.c\
			ft_ishex.c\
			ft_lstnew.c\
			ft_lstdelone.c\
			ft_lstdel.c\
			ft_lstadd.c\
			ft_lstiter.c\
			ft_strjoin_if.c\
			ft_strlen_if.c\
			ft_floor.c\
			ft_adv_memcmp.c\
			ft_putnstr_non_printable.c\
			ft_lstmap.c\
			ft_str_is_alpha.c\
			ft_str_is_numeric.c\
			ft_list_size.c\
			ft_printbits.c\
			get_next_line.c\
			ft_sqrt.c\
			ft_get_bits.c\
			ft_print_error.c\
			read_memory_unsigned_int.c\
			read_memory_int.c\
			colors.c flags.c flags_utils.c ft_printf.c function_pointers.c \
			get_nbr_len.c list.c nbr_utils.c print_base.c print_floats.c  \
			print_numbers.c print_numbers2.c  print_strings.c \
			print_unicode_strings.c specifiers.c utils.c buffer.c \




OBJECT = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	@ar rc $(NAME) $(OBJECT)
	@ranlib $(NAME)

clean:
	@rm -rf $(OBJECT)

fclean: clean
	@rm -fr $(NAME)

re: fclean all
