# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/28 02:06:40 by mmartin-          #+#    #+#              #
#    Updated: 2020/08/09 16:49:23 by mmartin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ECHO_MSG	= @echo "\x1b[1;107;30mft_printf\x1b[0;90m $(1)...\x1b[0m"

PRINTF_D	= srcs
PRINTF_I	= includes

SRCS		= $(shell find $(PRINTF_D) -type f -name "*.c")
OBJS		= $(SRCS:.c=.o)

PATH		= $(shell pwd)
NAME		= libftprintf.a

%.o : %.c
			@clang -Wall -Werror -Wextra -I$(PATH_LIBFT)/includes -c $< -o $@ -O3 -march=skylake

$(NAME):	$(OBJS)
			$(call ECHO_MSG,"copying and updating indexes")
			@cp $(PATH_LIBFT)/libft.a $(PATH)/$(NAME)
			@ar -rcs $(PATH)/$(NAME) $(OBJS)

all:		$(NAME)

# Deprecated, maintained for project integrity
bonus:		$(NAME)

clean:
			$(call ECHO_MSG,"deleting objects")
			@rm -f $(OBJS)

fclean:		clean
			$(call ECHO_MSG,"deleting library")
			@rm -f $(PATH)/$(NAME)

re:			fclean $(NAME)

.PHONY:		depends all bonus clean fclean re
