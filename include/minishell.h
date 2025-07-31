/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:32:16 by moel-mes          #+#    #+#             */
/*   Updated: 2025/07/31 13:29:25 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "error.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

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

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECTION,
}					t_token_type;

typedef enum s_red_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}					t_red_type;

typedef struct s_token
{
	char			*txt;
	int				len;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct s_red
{
	t_red_type		red_type;
	char			*target;
	t_token			*token;
	struct s_red	*next;
}					t_red;

typedef struct s_cmd
{
	char			**argv;
	t_token			*token;
	t_red			*redirection;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	char			**envp;
	char			*name;
	char			*line;
	t_cmd			*cmd_list;
	long			*last_exit_code;
	bool			running;
	char			*path;
}					t_shell;

t_token	*ef_token(t_token *token);
char	*env_get_value(char **env, char *str, int size);
int					valid_key(char *s);
int					size_of_new_token_txt(char **env, t_token *token, int *must_expand);
int					ex_validchar(char c);
int					count_insidequotes(char *s, int *saver);
int					detect_error(char *s);
int					se_token(t_token *token);
void				cd(char *av);
void				ex_token(t_token *token, char **env);
void				free_array(char **array);
void				handle_sigint(int sig);
char				*find_path(t_shell *shell, char **cmd);
void				handle_cd_command(t_shell *shell, char **cmd);
void				prompt(t_shell *shell);
void				handle_child_process(t_shell *shell, pid_t pid);
void				execute_command(t_shell *shell, char **cmd);
void				handle_exit(t_shell *shell, char **cmd);
long				ft_exit_code(char *str);
int					is_valid_number(char *str);
void				handle_sigint(int sig);
bool				is_builtin(t_shell *shell, char **cmd);
void				handle_command(t_shell *shell, char **cmd);
void				handle_pipes(t_shell *shell);
void				get_promt_name(t_shell *shell);
void				handle_script(t_shell *shell, char **cmd);
void				handle_pwd(t_shell *shell);
void				handle_export(t_shell *shell, char **cmd);
void				handle_unset(char **args, t_shell *shell);
void				unset_env_var(const char *var, t_shell *shell);
char				**get_envp(t_shell *shell);
char				*ft_getenv(t_shell *shell, const char *name);
int					find_env_var(char **envp, const char *var, int var_len);
void				handle_env(t_shell *shell);
void				handle_echo(t_shell *shell, char **cmd);
t_cmd				*get_the_parser(char *s);
t_cmd				*make_cmd(t_token *lexer);
void				token_addback(t_token **token, t_token *new_token);
t_token				*get_lexer(char *s, char squotes, char dquotes);
t_token_type		get_token_type(char *s);
t_token				*get_token(char *s, int start, int end);
t_red_type			get_red_type(t_token *token);
void				token_add_back(t_token **token, t_token **lexer);
void				red_add_back(t_red **red, t_token **lexer);
t_red				*make_red(t_token **lexer);
int					hchars(char s, char *c_set);
void				cmd_collect(void *ptr);
void				pro_collect(void *ptr);
void				*pro_malloc(size_t size);
void				*cmd_malloc(size_t size);
void				errorfree(void);
void				gc_free(void **collector);
int					count_word(char *s);
t_token				*split(char *s, int *start, char squotes, char dquotes);
int					p_ciquotes(char **s, char c);
char				**nl_split(char *s);
char				**tokens_to_argv(t_token *token);
void				setup_redirection(t_cmd *cmd);
void				preprocess_all_heredocs(t_shell *shell);
void				p_handle_child_process(t_cmd *cmd, t_shell *shell,
						int input_fd, int pipefd[2]);
char				*create_env_string(const char *var, const char *value);
void				ex_token(t_token *token, char **env);
t_token				*ef_token(t_token *token);

#endif
