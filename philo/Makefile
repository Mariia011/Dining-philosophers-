NAME = philo
CC = gcc
# -Wall -Wextra -Werror
CFILES =                                                     osophers.c ./src/utils.c
OBJS = $(CFILES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) Makefile
	$(CC) $(OBJS) -o $@

$(OBJS) : $(CFILES)
	$(CC) $(CFILES)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re :
	fclean all
add : fclean
	git add .
	git commit -m "yay"
	git push

.PHONY : all clean fclean re add
