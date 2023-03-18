CC						=					c++

CFLAGS					=					-Wall -Werror -Wextra -std=c++98 -g -I./dir

CDEPS					=					RPN.hpp

NAME					=					RPN

SRC						=					main RPN

OBJ						=					$(SRC:=.o)

%.o: %.cpp $(CDEPS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME) 

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
	
purge: fclean
	rm -f $(NAME).log
	rm -f $(NAME).diff
	rm -rf $(NAME).dSYM

log-leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --log-file=$(NAME).log ./$(NAME)

.PHONY: all clean fclean re purge log-leaks