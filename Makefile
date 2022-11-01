# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melkholy <melkholy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 01:48:25 by melkholy          #+#    #+#              #
#    Updated: 2022/11/01 19:34:34 by melkholy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = push_swap
BNAME = checker
CDIR = .
PRINTFDIR = ./ft_printf/
LIBFTPRINTF = ./ft_printf/libftprintf.a
CFLAGS = -Wall -Werror -Wextra

CFILES = ./utils.c ./actions.c ./indexing.c \
			./push_swap.c ./operations.c ./sort_stack.c \
			./check_input.c ./small_stack.c ./helper_funcs.c

BFILES = ./checker_bonus/actions_bonus.c \
			./checker_bonus/utils_bonus.c \
			./checker_bonus/operations_bonus.c \
			./checker_bonus/checker_bonus.c \
			./checker_bonus/check_input_bonus.c

all : $(NAME)

$(NAME) : $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(CFILES) -I$(PRINTFDIR) $(LIBFTPRINTF) -o $(NAME)

bonus : $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(BFILES) -I$(PRINTFDIR) $(LIBFTPRINTF) -o $(BNAME)

$(LIBFTPRINTF) :
	make -C ./ft_printf

clean :
	make clean -C $(PRINTFDIR)

fclean : clean
	make fclean -C $(PRINTFDIR)
	rm -f $(NAME) $(BNAME)

re : fclean all

.PHONY : all bonus clean fclean re
