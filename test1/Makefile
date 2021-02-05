CXX=clang++
CXXFLAGS=-Wall -Wextra -Werror -fsanitize=address -std=c++98
SRCS =	main.cpp \
		main_queue.cpp \
		main_stack.cpp \
		main_map.cpp \
		main_list.cpp \
		main_vector.cpp

OBJS = $(SRCS:%.cpp=%.o)
NAME=ft_containers

.PHONY: run all clean fclean re

all: clean run

run: $(NAME)
	./ft_containers

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

