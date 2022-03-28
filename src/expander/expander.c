/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 13:35:26 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/03/28 15:35:09 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

size_t	dollar_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

void	expander_loop(t_tools *tools, t_simple_cmds *tmp, int i)
{
	int		j;
	int		k;
	char	*arr_tmp;
	char	*before;
	char	*after;

	j = 0;
	k = 0;
	arr_tmp = tmp->str[i];
	while (arr_tmp[j])
	{
		if (arr_tmp[j] == '$')
		{
			while (tools->envp[k])
			{
				if (ft_strncmp(arr_tmp + j + 1,
						tools->envp[k], equal_sign(tools->envp[k]) - 1) == 0
					&& (arr_tmp[equal_sign(tools->envp[k])] == '\0'
						|| arr_tmp[equal_sign(tools->envp[k])] == '$'))
				{
					
					// if (j == 0)
					// {
					// 	free(tmp->str[i]);
					// 	tmp->str[i] = ft_substr(tools->envp[k],
					// 			equal_sign(tools->envp[k]),
					// 			ft_strlen(tools->envp[k]));
					// }
					// // // printf("test\n");
					// // // before = ft_substr(arr_tmp, 0, dollar_sign(arr_tmp));
					// else
					// {
					// 	before = tmp->str[i];
					// 	free(tmp->str[i]);
					// 	tmp->str[i] = ft_strjoin(before, ft_substr(tools->envp[j],
					// 			equal_sign(tools->envp[j]),
					// 			ft_strlen(tools->envp[j])));
					// }
					printf("%s\n\n", arr_tmp);
				}
				k++;
			}
		}
		j++;
	}
}

void	expander(t_tools *tools, t_simple_cmds *simple_cmds)
{
	t_simple_cmds	*tmp;
	int				i;

	i = 0;
	tmp = simple_cmds;
	while (tmp)
	{
		while (tmp->str[i])
		{
			expander_loop(tools, tmp, i);
			i++;
		}
		tmp = tmp->next;
	}
}
