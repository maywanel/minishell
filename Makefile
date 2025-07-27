NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I./include
LREADLINE = -lreadline
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
SRCS = $(wildcard src/*.c) \
		$(wildcard tokenizer/*.c) \
		$(wildcard garbage_collector/*.c) \
		$(wildcard detect_error/*.c)
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME) clean

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT) minishell.c
	$(CC) minishell.c $(CFLAGS) $(LREADLINE) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
