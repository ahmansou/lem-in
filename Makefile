# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmansou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/25 12:51:26 by ahmansou          #+#    #+#              #
#    Updated: 2020/02/13 16:13:17 by ahmansou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRCS =  src/get_next_line.c src/main.c src/get_assets.c src/line_misc.c\
		src/get_room.c src/misc.c src/misc_room.c src/get_links.c\
		src/hash_table.c src/solver.c src/get_path.c src/correction.c\
		src/path_misc.c src/antman.c src/free_misc.c src/free_misc2.c

OBJS = $(SRCS:.c=.o) 

FLG = -g -Wall -Werror -Wextra

$(NAME): $(OBJS)
	make -C libft
	make -C ft_printf
	gcc -g -o $(NAME) $(FLG) $(OBJS) libft/libft.a ft_printf/libftprintf.a

$(OBJS): %.o:%.c
	gcc -c $(FLG) $^ -o $@

clean:
	make clean -C libft
	make clean -C ft_printf
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	make fclean -C ft_printf
	rm -f $(NAME) 

re: fclean all

all : $(NAME)
