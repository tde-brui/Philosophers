NAME = philo
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
OBJECT = $(SOURCES:.c=.o)
SOURCES = \
	announcements.c \
	main.c \
	mutex_funcs.c \
	time.c \
	utils.c

all: $(NAME)

$(NAME): $(OBJECT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJECT)

fclean: clean
	rm -rf $(NAME)

re: fclean all