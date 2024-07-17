NAME = philo
DEBUG = -fsanitize=thread

CC = gcc #$(DEBUG)

# -Wall -Wextra -Werror

SRCSPATH = ./src/
OBJSPATH = ./objs/

CFILES = $(wildcard $(SRCSPATH)*.c)
OBJS = $(patsubst $(SRCSPATH)%.c, $(OBJSPATH)%.o, $(CFILES))

all : $(NAME)

$(NAME) : $(OBJSPATH) $(OBJS)
	$(CC) $(OBJS) -o $@

$(OBJSPATH) :
	mkdir -p objs

$(OBJSPATH)%.o : $(SRCSPATH)%.c
	$(CC) $< -c -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

oda : fclean
	git add .
	git commit -m "oda"
	git push

.PHONY : all clean fclean re oda
