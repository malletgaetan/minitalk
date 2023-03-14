NAME = minitalk
BONUS = bonus
CC = gcc
SRCSDIR = srcs/
LIBFTDIR = libft/
LIBFT = $(LIBFTDIR)/libft.a
LIBFTFLAGS = -L $(LIBFTDIR) -l ft
CFLAGS = -Wall -Werror -Wextra $(LIBFTFLAGS) -I $(LIBFTDIR)/includes
SERVER = server
CLIENT = client
SERVER_BONUS = $(SERVER)_bonus
CLIENT_BONUS = $(CLIENT)_bonus

.PHONY: all $(NAME) $(BONUS) clean fclean

all: $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)

$(SERVER): srcs/server.c
	gcc $^ $(CFLAGS) -o $@

$(CLIENT): srcs/client.c
	gcc $^ $(CFLAGS) -o $@

$(NAME): $(LIBFT) $(SERVER) $(CLIENT)

$(SERVER_BONUS): srcs/server.c
	gcc $^ $(CFLAGS) -o $@

$(CLIENT_BONUS): srcs/client.c
	gcc $^ $(CFLAGS) -o $@

$(BONUS): $(LIBFT) $(SERVER_BONUS) $(CLIENT_BONUS)

clean:

fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)


re: fclean all
