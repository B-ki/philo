# BINARY

NAME = philo

# DIRECTORIES

INCLUDES_DIR = includes/ 
SRC_DIR = srcs/
OBJ_DIR = objs/

# NAME

SRC_NAME = main.c				\
		   check.c				\
		   lifespan.c			\
		   parser.c				\
		   utils.c

OBJ_NAME = $(SRC_NAME:.c=.o)

# FILES

SRCS = $(addprefix $(SRC_DIR)/,$(SRC_NAME))
OBJS = $(addprefix $(OBJ_DIR),$(OBJ_NAME))

# FLAGS

CC = gcc -g
INC_PATH = -I$(INCLUDES_DIR)
LFLAGS = -lpthread 
CFLAGS = $(INC_PATH) -Wall -Werror -Wextra
RM = rm -f

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			mkdir $(OBJ_DIR) 2> /dev/null || true
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(OBJS) $(LFLAGS) -o $(NAME)


all:		$(NAME)

clean:
			$(RM) $(OBJS)
			rmdir $(OBJ_DIR) 2> /dev/null || true

fclean:		clean
			$(RM) $(NAME)

re:			fclean	all

.PHONY:		all clean fclean re
