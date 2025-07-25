# ifndef MINISHELLH_H
# define MINISHELLH_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

# define PIPE 1
# define RED_IN 3
# define RED_OUT 2
# define AND 4
# define S_QUOTE 7
# define D_QUOTE 8
# define S_CHARS 9
# define P_OPEN 6
# define P_CLOSE 5

# define WHITESPACE " \t\n"

#define UNIMPLEMENTED(...)                                                      \
        printf("%s:%d: UNIMPLEMENTED: %s \n", __FILE__, __LINE__, __VA_ARGS__); \
        exit(1);

typedef enum s_red_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}						t_red_type;


typedef struct s_token
{
	char	*txt;
	int	len;
	int	type;
	struct s_token	*next;
}						t_token;

typedef struct s_red
{
	t_red_type	red_type;
	char	*target;
	t_token	*token;
	struct s_red	*next;
}	t_red ;

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECTION,
}						t_token_type;

typedef enum s_ast_type
{
	AST_SIMPLE_CMD,
	AST_CONNECTOR,
	AST_SUBSHELL,
}						t_ast_type;

typedef enum s_connector
{
	CONNECTOR_AND,
	CONNECTOR_PIPE,
	CONNECTOR_OR
}		t_connector;

typedef struct s_cmd
{
	t_ast_type	*type;
	char	**argv;
	union
	{
		t_connector	con;
		t_token		*token;
		struct s_cmd	*sub;
	};
	t_red	*redirection ;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*get_the_parser(char *s);
t_cmd	*make_cmd(t_token *lexer);
void	token_addback(t_token **token, t_token *new_token);
t_token	*get_lexer(char *s);
t_token_type	get_token_type(char *s, int size);
t_token	*get_token(char	*s, int	start, int end);
int	hchars(char s, char *c_set);
void	cmd_collect(void *ptr);
void	pro_collect(void *ptr);
void	*pro_malloc(size_t size);
void	*cmd_malloc(size_t size);
void	errorfree();
void	gc_free(void **collector);
int	count_word(char *s);
t_token	*split(char *s, int *start);
int	p_ciquotes(char **s, char c);
char	**nl_split(char *s);

//#include <>
//
//
//
//
//
//
//
#endif
