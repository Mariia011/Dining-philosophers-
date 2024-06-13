NAME = philo
CC = gcc
# -Wall -Wextra -Werror

CFILES = $(wildcard src/*.c)
OBJS = $(patsubst %.c, %.o, $(CFILES))

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $@

./src/%.o : ./src/%.c
	$(CC) $< -c -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

add : fclean
	git add .
	git commit -m "yay"
	git push

.PHONY : all clean fclean re add
