# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/10 15:21:05 by mmartin-          #+#    #+#              #
#    Updated: 2020/08/26 03:38:23 by mmartin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FTPTF_MSG	= @echo "\x1b[48;5;90m\x1b[38;5;15m\x1b[1m ft_printf\x1b[0m\x1b[0;90m $(1)\x1b[0m"

FTPTF_SRCS	= $(wildcard srcs/*.c)
FTPTF_OBJS	= $(FTPTF_SRCS:.c=.o)

FTPTF_OUT	:= $(CURDIR)
FTPTF_NAME	= libftprintf.a

FTPTF_LIBFT	= "srcs/libft"

%.o : %.c
					$(call FTPTF_MSG,"Compiling $@...")
					@clang -Wall -Werror -Wextra -I$(FTPTF_LIBFT)/includes -c $< -o $@ -O3 -march=skylake

$(FTPTF_NAME):	$(FTPTF_OBJS)
					@clear
					$(call FTPTF_MSG,"Linking objects into $(FTPTF_OUT)/$(FTPTF_NAME)")
					@ar -rcs $(FTPTF_OUT)/$(FTPTF_NAME) $(FTPTF_OBJS)
					$(call FTPTF_MSG,"Finished linking")
					@(test ! -f $(FTPTF_OUT)/libft.a && \
						make -s -C $(FTPTF_LIBFT) LIBFT_OUT=$(FTPTF_OUT)) || true
					$(call FTPTF_MSG,"Finished compiling every dependency")

all:			$(FTPTF_NAME)

bonus:			$(FTPTF_NAME)

clean:
					$(call FTPTF_MSG,"Deleting all objects...")
					@rm -f $(FTPTF_OBJS)

fclean:			clean
					$(call FTPTF_MSG,"Deleting $(FTPTF_OUT)/$(FTPTF_NAME)...")
					@rm -f $(FTPTF_OUT)/$(FTPTF_NAME)

re:				fclean $(FTPTF_NAME)

.PHONY:			all bonus clean fclean re
