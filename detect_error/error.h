/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamel-yo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:30:50 by hamel-yo          #+#    #+#             */
/*   Updated: 2025/07/26 12:57:07 by hamel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ERROR_H
# define ERROR_H

# define SE_PIPE "Syntax error near unexpected token \'|\'\n"
# define SE_REDIN "Syntax error near unexpected token <\n"
# define SE_REDOUT "Syntax error near unexpected token >\n"
# define SE_HEREDOC "Syntax error near unexpected token <<\n"
# define SE_APPEND "Syntax error near unexpected token >>\n"
# define SE_QUOTES "Syntax error unbalanced quotes!\n"

int	ft_error(char *s);
# endif
