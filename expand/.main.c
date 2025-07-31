#include "../include/minishell.h"

int main (int c, char **av, char **env)
{
	c = 1;
	av = NULL;
	char *str;
	t_token	*token;
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	while (1)
	{
		str = readline(">>");
		if (str == NULL)
			return(0);
		add_history(str);
		token = get_lexer(str);
		ex_token(token, env);
		while (token != NULL)
		{
			printf("%d ||| %s \n", token->len, token->txt);
			token = token->next;
		}
	}
}
