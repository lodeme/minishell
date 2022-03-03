/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 13:46:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/03/03 12:17:45 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "pipex.h"
# include "parser.h"
# include "utils.h"
# include "lexor.h"
# include "builtins.h"
# include "executor.h"

int		parse_envp(t_tools *tools);
int		find_pwd(t_tools *tools);

//builtins
int	(*builtin_arr(char *str))(t_tools *tools);

#endif