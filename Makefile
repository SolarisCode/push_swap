# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 01:48:25 by melkholy          #+#    #+#              #
#    Updated: 2022/10/31 02:42:19 by melkholy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = push_swap
CDIR = .
PRINTFDIR = ./ft_printf/
LIBFTPRINTF = ./ft_printf/libftprintf.a
CFLAGS = -Wall -Werror -Wextra

CFILES = main_errorhandling.c

all : $(NAME)

$(NAME) : $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(CFILES) -I$(PRINTFDIR) $(LIBFTPRINTF) -o $(NAME)

$(LIBFTPRINTF) :
	make -C ./ft_printf

clean :
	make clean -C $(PRINTFDIR)

fclean : clean
	make fclean -C $(PRINTFDIR)
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
