NAME	= webserv

SRCS	 = main.cpp

OBJS	 = ${SRCS:.cpp=.o}
CC_FLAGS = -Werror -Wextra -Wall -std=c++98

CC		= clang++
LIBS	=

all:	${NAME}

debug: CC_FLAGS += -g3
debug: CC_FLAGS += -D DEBUG
debug: all

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re:		fclean all

$(NAME):	${OBJS}
	${CC} ${CC_FLAGS} ${OBJS} -o ${NAME} ${LIBS}

.cpp.o:
	${CC} ${CC_FLAGS} -I. -c $< -o ${<:.cpp=.o}

.PHONY:	all clean fclean re debug
