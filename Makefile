# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/10 15:21:05 by mmartin-          #+#    #+#              #
#    Updated: 2020/09/01 17:58:39 by mmartin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FTPTF_MSG	= @echo "\x1b[48;5;90m\x1b[38;5;15m\x1b[1m ft_printf\x1b[0m\x1b[0;90m $(1)\x1b[0m"

FTPTF_SRCS	= $(wildcard srcs/*)
FTPTF_OBJS	= $(FTPTF_SRCS:.c=.o)

FTPTF_OUT	= "."
FTPTF_NAME	= libftprintf.a

FTPTF_LIBFT	= "srcs/libft"

%.o : %.c
					@printf "\x1b[48;5;90m\x1b[38;5;15m\x1b[1m ft_printf\x1b[0m\x1b[0;90m Compiling $@...       \x1b[0m\r"
					@clang -Wall -Werror -Wextra -I$(FTPTF_LIBFT)/includes -c $< -o $@ -O3 -march=skylake

$(FTPTF_NAME):	$(FTPTF_OBJS)
					$(call FTPTF_MSG,"Linking objects into $(FTPTF_OUT)/$(FTPTF_NAME)","\n")
					@ar -rcs $(FTPTF_OUT)/$(FTPTF_NAME) $(FTPTF_OBJS)
					$(call FTPTF_MSG,"Finished linking","\n")

all:			$(FTPTF_NAME)

bonus:			$(FTPTF_NAME)

clean:
					$(call FTPTF_MSG,"Deleting all objects...","\n")
					@rm -f $(FTPTF_OBJS)

fclean:			clean
					$(call FTPTF_MSG,"Deleting $(FTPTF_OUT)/$(FTPTF_NAME)...","\n")
					@rm -f $(FTPTF_OUT)/$(FTPTF_NAME)

re:				fclean $(FTPTF_NAME)

.PHONY:			all bonus clean fclean re
