/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:32:16 by moel-mes          #+#    #+#             */
/*   Updated: 2025/05/04 12:03:37 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>                 // printf, perror
# include <readline/readline.h>     // readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>      // add_history, rl_clear_history
# include <stdlib.h>                // malloc, free, exit
# include <unistd.h>                // write, access, read, close, fork, chdir, getcwd, dup, dup2, pipe, isatty, ttyname, ttyslot, execve
# include <fcntl.h>                 // open, unlink
# include <sys/types.h>             // pid_t, opendir, readdir
# include <sys/wait.h>              // wait, waitpid, wait3, wait4
# include <signal.h>                // signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>              // stat, lstat, fstat
# include <dirent.h>                // opendir, readdir, closedir
# include <string.h>                // strerror
# include <termios.h>               // tcsetattr, tcgetattr
# include <sys/ioctl.h>             // ioctl
# include <curses.h>                // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs (can also come from <termcap.h> or <term.h>)
# include <termcap.h>               // Alternative to <curses.h> for tgetent, etc.

typedef struct s_cmd
{
	char			**argv;       // command + args, e.g. ["ls", "-l", NULL]
	char			*infile;      // for redirection: <
	char			*outfile;     // for redirection: > or >>
	bool			append;       // true if >>, false if >
	bool			heredoc;      // true if <<
	char			*delimiter;   // heredoc delimiter
	struct s_cmd	*next;        // next command in pipeline
}	t_cmd;

typedef struct s_shell
{
	char	**envp;          // environment variables
	char    *name;		  	// shell name
	char	*line;           // full input line
	t_cmd	*cmd_list;       // parsed command list
	long		last_exit_code;  // exit code of last executed command
	bool	running;         // shell loop control
	char 	*path;
}	t_shell;

void cd(char *av);
void free_array(char **array);
void handle_sigint(int sig);
char *find_path(char **cmd);
void handle_cd_command(t_shell *shell, char **cmd);
void prompt(t_shell *shell);
void handle_child_process(t_shell *shell, pid_t pid);
void execute_command(t_shell *shell, char **cmd);
void handle_exit(t_shell *shell);
void handle_sigint(int sig);
bool is_builtin(t_shell *shell, char **cmd);
void handle_command(t_shell *shell, char **cmd);
void handle_pipes(t_shell *shell);

#endif
