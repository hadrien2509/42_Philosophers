# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgeissle <hgeissle@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 14:10:57 by hgeissle          #+#    #+#              #
#    Updated: 2023/06/16 14:12:29 by hgeissle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c\
		not_libft/ft_atoi.c\
		not_libft/ft_putstr_fd.c\
		not_libft/ft_strlen.c\
		not_libft/ft_isdigit.c\
		not_libft/ft_putstr.c\

FLAGS = -Wall -Wextra -Werror
RM = rm -f
OBJS = $(SRC:.c=.o)

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

all: $(NAME)

clean:
		$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re