

NAME			=	ircserv

CC				=	c++
CCFLAGS			=	-Wall -Wextra -Werror -std=c++98
RM				=	rm -rf

INC				=	-Iserver -Iclient

SRC_DIRS		=	server client
vpath %.cpp $(SRC_DIRS)


SRCS			=	main.cpp \
					Server.cpp

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME):			$(OBJ_DIR) $(OBJS)
					$(CC) $(CCFLAGS) $(OBJS) -o $@

$(OBJ_DIR):
					mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o:		%.cpp
					$(CC) $(INC) $(CCFLAGS) -c $< -o $@

clean:
					$(RM) $(OBJ_DIR)

fclean: 			clean
					$(RM) $(NAME)

re: fclean all

run:
					./ircserv 12345 pass

.PHONY: all clean fclean re run
