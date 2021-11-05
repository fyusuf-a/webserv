SRC = 	test.cpp\
	middlewares/CheckSyntax.cpp\
	Request/Request.cpp\
	Request/requestParsing.cpp\
	Request/checkIncompleteRequest.cpp\
	Response/Response.cpp

INC = 	includes

NAME = test
CC = g++
CFLAGS = -Wall -Wextra -std=c++98 -g

O_FILES = $(SRC:.cpp=.o)


$(NAME) : $(O_FILES)
	$(CC) -I$(INC) $(CFLAGS) $^ -o $(NAME)
	@echo "\033[33;32mCompilation...\t""\033[33;31mDONE 🙃"

clean :
	@echo "\033[33;36mDeleting - *.o..."

fclean : clean
	rm -rf $(NAME) $(NAME).dSYM
	@echo "\033[33;36mDeleting - exec..."

re : fclean all
