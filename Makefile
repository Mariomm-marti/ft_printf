# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/28 02:06:40 by mmartin-          #+#    #+#              #
#    Updated: 2020/07/18 07:05:34 by mmartin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PRINT_D	= srcs
PRINT_I	= includes
LIBFT_D	= srcs/libft
LIBFT_I	= srcs/libft/includes

SRCS	= $(shell find $(PRINT_D) -type f -name "*.c")
OBJS	= ${SRCS:.c=.o}

NAME	= libftprintf.a

%.o : %.c
			@clang -Wall -Werror -Wextra -I $(PRINT_I) -I $(LIBFT_I) -c $< -o $@

$(NAME):	$(OBJS)
			@make -s -C $(LIBFT_D) bonus
			@echo ">>> Dependency 'libft' is ready"
			@cp $(LIBFT_D)/libft.a $(NAME)
			@echo ">>> Compiling 'libftprintf'"
			@ar -rcs $(NAME) ${OBJS}
			@ranlib $(NAME)
			@echo ">>> Library 'libftprintf' is ready to use"

all:		$(NAME)

bonus:		all

clean:
			@make -s -C $(LIBFT_D) clean
			@rm -f $(OBJS)

fclean:		clean
			@make -s -C $(LIBFT_D) fclean
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
