CXX=clang++
CXXFLAGS=-Wall -Wextra -Werror -fsanitize=address
OBJECTS=Test.o main.o main_vector.o main_list.o main_stack.o main_queue.o main_map.o
NAME=test

.PHONY: run all clean fclean re

all: clean run

run: $(NAME)
	./test

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
