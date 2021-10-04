SRC = 	main.cpp\
		srcs/parsingConf/parsingConf.cpp\
		srcs/server/server.cpp\
		srcs/server/serverConfig.cpp\
		srcs/server/serverLocation.cpp\
		srcs/utils/utils.cpp\
		srcs/webserv/webserv.cpp\



NAME = Webserv
HEADERS = includes
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address
O_FILES = $(SRC:.cpp=.o)


.PHONY: clean fclean re

all : $(NAME)


$(NAME) : $(O_FILES)
	$(CC) $(CFLAGS) $^ -o $(NAME)
	@echo "\033[33;32mCompilation...\t""\033[33;31mDONE 🙃"

clean :
	@echo "\033[33;36mDeleting - *.o..."

fclean : clean
	rm -f $(NAME)
	@echo "\033[33;36mDeleting - exec..."

re : fclean all
