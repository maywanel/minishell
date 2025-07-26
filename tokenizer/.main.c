#include "../include/minishellh.h"


char *get_red_name(t_red_type type)
{
	if (REDIR_IN == type)
		return ("IN");
	if (REDIR_OUT == type)
		return ("OUT");
	if (REDIR_APPEND == type)
		return ("APPAND");
	else
		return ("HEREDOC");
}

char *get_token_name(t_token_type type)
{
	if (TOKEN_WORD == type)
		return ("TOKEN_WORD");
	if (TOKEN_PIPE == type)
		return ("TOKEN_PIPE");
	if (TOKEN_REDIRECTION == type)
		return ("TOKEN_REDIRECTION");
	else
		return ("lah in3l zaml book ali is the writer");
}

t_token	*split_tokenw(t_token **lexer);

void	print_node(t_cmd *cmd)
{
	t_token	*token;
	t_red	*red;

	token = cmd->token;
	red = cmd->redirection;
	while (red != NULL)
	{
		printf(" red = %s \n", get_red_name(red->red_type));
		red = red->next;
	}
	printf("{{{{}}}}");
	while (token != NULL)
	{
		printf("%.*s ||| %s \n", token->len, token->txt, get_token_name(token->type));
		token = token->next;
	}
}

int main ()
{
	t_token	*token;
	t_cmd	*lexer;
	char	*s;

	while (1)
	{
		s = readline("no :");
		if (s == NULL)
			exit(1);
		add_history(s);
		lexer = get_the_parser(s);
		print_node(lexer);
	}
}
