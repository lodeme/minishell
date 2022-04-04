/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 12:09:05 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/04/04 16:10:58 by alfred        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	mini_env(t_tools *tools, t_simple_cmds *simple_cmd)
{
	int		i;
	char	*tmp;
	(void) simple_cmd;

	i = 0;
	while (tools->envp[i])
	{
		if (!ft_strncmp(tools->envp[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", tools->pwd);
			free(tools->envp[i]);
			tools->envp[i] = tmp;
		}
		else if (!ft_strncmp(tools->envp[i], "OLDPWD=", 7) && tools->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", tools->old_pwd);
			free(tools->envp[i]);
			tools->envp[i] = tmp;
		}
		ft_putendl_fd(tools->envp[i], tools->out);
		i++;
	}
	return (EXIT_SUCCESS);
}
