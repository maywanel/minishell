#include "../include/minishell.h"

int main (int c, char **av, char *env[])
{
	c = 1;
	av = NULL;
	char *str;
	char	**strs;
	t_token	*token;
	int	i;

	i = 0;
	env[0] = "ls=";
	env[1] = "jk= \t*\n";
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
		token = get_lexer(str, '\'', '\"');
		ex_token(token, env);
		token = ef_token(token);
		token = get_wild_card(token);
		strs = convert_to_ptr(token);
		while (*strs)
		{
			printf("%s|||||\n", *strs);
			strs++;
		}
		/*while (token != NULL)
		{
			if (token->txt != NULL)
				printf("  ||| %d ||| %s \n", token->len, token->txt);
			token = token->next;
		}
		while (fs_token != NULL)
		{
			printf("  ||| %d ||| %.*s \n", fs_token->len, fs_token->len, fs_token->txt);
			fs_token = fs_token->next;
		}*/
	}
}
