/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:32:16 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/28 16:13:59 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
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

typedef struct s_cmd
{
	char			**argv;
	char			*infile;
	char			*outfile;
	bool			append;
	bool			heredoc;
	char			*delimiter;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	char			**envp;
	char			*name;
	char			*line;
	t_cmd			*cmd_list;
	long			last_exit_code;
	bool			running;
	char			*path;
}					t_shell;

void				cd(char *av);
void				free_array(char **array);
void				handle_sigint(int sig);
char				*find_path(t_shell *shell, char **cmd);
void				handle_cd_command(t_shell *shell, char **cmd);
void				prompt(t_shell *shell);
void				handle_child_process(t_shell *shell, pid_t pid);
void				execute_command(t_shell *shell, char **cmd);
void				handle_exit(t_shell *shell);
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

#endif
