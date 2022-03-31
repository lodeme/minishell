/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 13:35:26 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/03/31 16:22:13 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	loop_if_dollar_sign(t_tools *tools, char *arr_tmp, int j, int i)
{
	int		k;
	int		ret;
	char	*tmp;
	char	*tmp2;

	k = 0;
	ret = 0;
	while (tools->envp[k])
	{
		if (ft_strncmp(arr_tmp + j + 1,
				tools->envp[k], equal_sign(tools->envp[k]) - 1) == 0
			&& after_dollar_lenght(arr_tmp, j) - j
			== equal_sign(tools->envp[k]))
		{
			tmp2 = ft_strdup(tools->envp[k] + equal_sign(tools->envp[k]));
			tmp = ft_strjoin(tools->simple_cmds->str[i], tmp2);
			free_things(tmp2, tools, i);
			tools->simple_cmds->str[i] = tmp;
			ret = equal_sign(tools->envp[k]);
		}
		k++;
	}
	if (ret == 0)
		ret = after_dollar_lenght(arr_tmp, j) - j;
	return (ret);
}

char	*detect_dollar_sign(t_tools *tools, char *str, int i)
{
	int		j;
	char	*arr_tmp;
	char	*tmp;
	char	*tmp2;

	j = 0;
	arr_tmp = ft_strdup(str);
	while (arr_tmp[j])
	{
		init_stri(i, j, tools);
		if (arr_tmp[j] == '$')
			j += loop_if_dollar_sign(tools, arr_tmp, j, i);
		else
		{
			tmp2 = char_to_str(arr_tmp[j]);
			tmp = ft_strjoin(tools->simple_cmds->str[i], tmp2);
			free_things(tmp2, tools, i);
			tools->simple_cmds->str[i] = tmp;
			str = tmp;
			j++;
		}
	}
	free(arr_tmp);
	return (tools->simple_cmds->str[i]);
}

void	expander(t_tools *tools)
{
	t_simple_cmds	*tmp;
	int				i;

	i = 0;
	tmp = tools->simple_cmds;
	while (tmp)
	{
		while (tmp->str[i])
		{
			if (tmp->str[i][0] != '\''
				&& tmp->str[i][ft_strlen(tmp->str[i])] != '\'')
				detect_dollar_sign(tools, tmp->str[i], i);
			i++;
		}
		tmp = tmp->next;
	}
}
