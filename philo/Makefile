NAME = philo
CC = gcc
# BONUS = philo_bonus
# PATH = /philo_bonus/main.c

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

oda : fclean
	git add .
	git commit -m "oda"
	git push

# bonus : $(BONUS)
# $(BONUS) : $(CC) $(PATH)

.PHONY : all clean fclean re oda
