# Source files
SOURCES := server.c client.c
OBJECTS := $(SOURCES:.c=.o)

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -Werror

# Paths
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

# Targets
all: server client ascii

server: server.o $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft

client: client.o $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJECTS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f server client
	make -C $(LIBFT_DIR) fclean

re: fclean all

ascii:
	@echo " ૮ ˶ᵔ ᵕ ᵔ˶ ა YIPPIEEEEE"

.PHONY: all clean fclean re ascii