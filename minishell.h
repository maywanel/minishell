/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-mes <moel-mes@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:32:16 by moel-mes          #+#    #+#             */
/*   Updated: 2025/04/21 15:32:16 by moel-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <readline/readline.h>     // readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>      // add_history, rl_clear_history
# include <stdio.h>                 // printf, perror
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


#endif
