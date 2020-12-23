# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/10 15:21:05 by mmartin-          #+#    #+#              #
#    Updated: 2020/12/23 22:22:15 by mmartin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FTPTF_MSG	= @echo "  \x1b[44m\x1b[38;2;16;19;33m\x1b[44m\x1b[01;37m  ft_printf \x1b[0m\x1b[34m\x1b[0m\x1b[0;90m $(1)\x1b[0m"

FTPTF_SRCS	= srcs/ft_printf.c \
			  srcs/sprintf_wrapper.c \
			  srcs/text_handler.c \
			  srcs/digit_handler.c \
			  srcs/pointer_handler.c
FTPTF_OBJS	= $(FTPTF_SRCS:.c=.o)

FTPTF_OUT	= "."
FTPTF_NAME	= libftprintf.a

FTPTF_LIBFT	= "srcs/libft"

%.o : %.c
					@printf "  \x1b[44m\x1b[38;2;16;19;33m\x1b[44m\x1b[01;37m  ft_printf \x1b[0m\x1b[34m\x1b[0m\x1b[0;90m Compiling \x1b[0;34m$@...         \x1b[0m\r"
					@clang -Wall -Werror -Wextra -I$(FTPTF_LIBFT)/includes -c $< -o $@ -O3 -march=skylake

$(FTPTF_NAME):	$(FTPTF_OBJS)
					@echo ""
					$(call FTPTF_MSG,"Linking objects into $(FTPTF_OUT)/$(FTPTF_NAME)","\n")
					@ar -rcs $(FTPTF_OUT)/$(FTPTF_NAME) $(FTPTF_OBJS)
					$(call FTPTF_MSG,"Finished linking","\n")
					@echo ""

all:			$(FTPTF_NAME)

bonus:			$(FTPTF_NAME)

clean:
					@echo ""
					$(call FTPTF_MSG,"Deleting all objects...","\n")
					@rm -f $(FTPTF_OBJS)

fclean:			clean
					$(call FTPTF_MSG,"Deleting $(FTPTF_OUT)/$(FTPTF_NAME)...","\n")
					@rm -f $(FTPTF_OUT)/$(FTPTF_NAME)
					@echo ""

re:				fclean $(FTPTF_NAME)

.PHONY:			all bonus clean fclean re
