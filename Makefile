NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I./include
LREADLINE = -lreadline
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
SRCS = $(wildcard src/*.c) \
		$(wildcard tokenizer/*.c) \
		$(wildcard detect_error/*.c) \
		$(wildcard expand/*.c) \
		$(wildcard garbage_collector/*.c)
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT) minishell.c
	$(CC) minishell.c $(CFLAGS) $(LREADLINE) $(OBJS) $(LIBFT) -o $(NAME) -fsanitize=address -g3

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean test-clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

# Testing rules
test: all test-clean
	@echo "Running minishell tests..."
	@./tests/tester.sh --minishell ./minishell --tests tests/tests.txt

test-python: all test-clean
	@echo "Running Python tester..."
	@python3 tests/tester.py --minishell ./minishell --tests tests/tests.txt --report

test-category: all test-clean
	@echo "Usage: make test-category CATEGORY=ECHO"
	@if [ -n "$(CATEGORY)" ]; then \
		python3 tests/extract_tester.py --minishell ./minishell --tests tests/tests.txt --category "$(CATEGORY)"; \
	else \
		echo "Please specify CATEGORY=<category_name>"; \
		echo "Available categories: ECHO, EXPORT, CD, WILDCARD, SYNTAXE"; \
	fi

test-quick: all test-clean
	@echo "Running first 20 tests..."
	@python3 tests/extract_tester.py --minishell ./minishell --tests tests/tests.txt --max 20

test-extract: all test-clean
	@echo "Running enhanced extractor tester..."
	@python3 tests/extract_tester.py --minishell ./minishell --tests tests/tests.txt

test-simple: all test-clean
	@echo "Running simple functionality tests..."
	@cd tests && ./simple_tester.sh

test-categories:
	@echo "🔍 Available test categories:"
	@echo "============================"
	@grep -o '[A-Z][A-Z ]*[🌦🎉🛰0️⃣1️⃣🏦💿🖕⛔🚬⏮️⭐🛫🛬]' tests/tests.txt | sort | uniq | head -10
	@echo ""
	@echo "Usage examples:"
	@echo "  make test-category CATEGORY=ECHO"
	@echo "  make test-category CATEGORY=EXPORT" 
	@echo "  make test-category CATEGORY=WILDCARD"

test-clean:
	@echo "Cleaning test files..."
	@# Remove test logs and temporary files
	@rm -f /tmp/minishell_out /tmp/test_out /tmp/test_append
	@rm -rf /tmp/minishell_test
	@find /tmp -name "tmp*minishell*" -delete 2>/dev/null || true
	@find /tmp -name "*test*" -user $(USER) -mtime -1 -delete 2>/dev/null || true
	@# Remove common test files that might be created
	@rm -f test_file* output_file* input_file* result* 2>/dev/null || true
	@rm -f here_doc* heredoc* .here_doc* 2>/dev/null || true
	@rm -rf test_dir* temp_dir* 2>/dev/null || true
	@rm -f .test* .temp* 2>/dev/null || true
	@# Remove single letter files and directories (common in tests)
	@for f in a b c d e f g h i j k l m n o p q r s t u v w x y z; do rm -rf $$f 2>/dev/null || true; done
	@# Remove number files
	@for f in 0 1 2 3 4 5 6 7 8 9; do rm -f $$f 2>/dev/null || true; done
	@# Remove command name files (created by tests)
	@rm -f cat cd echo env exit export ls pwd unset whereis whoami 2>/dev/null || true
	@rm -f ech hola ifconfig sleep time lss 2>/dev/null || true
	@# Remove files with special characters
	@rm -f ';' '(ls' '(lss' '(pwd' '*' '$$' 2>/dev/null || true
	@rm -f '[*' '2[BONUS]' ']' 2>/dev/null || true
	@# Remove numbered files
	@rm -f file1 file2 file3 file4 file5 file* 2>/dev/null || true
	@rm -f out1 out2 out3 out* 2>/dev/null || true
	@echo "Test files cleaned."

test-safe-clean:
	@echo "Safely cleaning test files..."
	@rm -f /tmp/minishell_out /tmp/test_out /tmp/test_append
	@rm -rf /tmp/minishell_test
	@find /tmp -name "tmp*minishell*" -delete 2>/dev/null || true
	@echo "Safe test cleanup completed."

.PHONY: all clean fclean re test test-python test-category test-quick test-extract test-simple test-clean test-safe-clean test-categories
