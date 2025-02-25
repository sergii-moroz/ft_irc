

NAME			=	ircserv

CC				=	c++
CCFLAGS			=	-Wall -Wextra -Werror -std=c++98
RM				=	rm -rf

SRC_DIRS		=	server user lexer command token commandHandler utils channel
vpath %.cpp $(SRC_DIRS)

INC				=	$(addprefix -I, $(SRC_DIRS))

SRCS			=	main.cpp \
					User.cpp \
					Token.cpp Lexer.cpp Command.cpp \
					CommandHandler.cpp handleCAP.cpp handleNumeric.cpp \
					Channel.cpp \
					handlePASS.cpp handleNICK.cpp handleUSER.cpp handlePING.cpp handlePONG.cpp handlePRIVMSG.cpp handleJOIN.cpp handleKICK.cpp\
					Utils.cpp \
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
