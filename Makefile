# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/20 16:17:13 by tfarenga          #+#    #+#              #
#    Updated: 2021/01/22 15:32:12 by tfarenga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers
CXX=clang++
CXXFLAGS=-Wall -Wextra -Werror -O0
OBJECTS=Test.o main.o Test_list.o

.PHONY: run all clean fclean re

all: clean run

run: $(NAME)
	./test_all

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
