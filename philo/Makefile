NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
BUILD_DIR = build
SOURCES = \
	announcements.c \
	main.c \
	mutex_funcs.c \
	time.c \
	utils.c \
	utils2.c \
	monitoring.c \
	free.c
OBJECT = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(addprefix $(BUILD_DIR)/, $(OBJECT))
	$(CC) $(CFLAGS) -o $(NAME) $^

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean: 
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all