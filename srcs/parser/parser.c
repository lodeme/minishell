/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:28:22 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/24 15:29:45 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_lexor *lexor_list, t_tools *tools)
{
	t_lexor	*tmp;
	int		i;

	i = 0;
	tmp = lexor_list;
	while (tmp && tmp->token != PIPE && tmp->token != PS2)
	{
		i++;
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (tmp->token == PIPE)
			tools->pipes++;
	}
	return (i);
}

int	add_redirection(t_lexor **redirections, t_lexor **lexor_list,
	int *num_redirections)
{
	t_lexor	*node;

	if (!*lexor_list || !(*lexor_list)->token || (*lexor_list)->token == PS2)
		return (0);
	node = ft_lexornew(ft_strdup((*lexor_list)->next->str),
			(*lexor_list)->token);
	if (!*redirections)
		*redirections = node;
	else
		ft_lexoradd_back(redirections, node);
	*lexor_list = (*lexor_list)->next;
	num_redirections++;
	return (1);
}

int	ps2_token(t_lexor **lexor_list)
{
	if (*lexor_list && (*lexor_list)->token == PS2)
	{
		*lexor_list = (*lexor_list)->next;
	}
	return (0);
}

t_simple_cmds	*initialize_cmd(t_lexor *lexor_list, int arg_size)
{
	char	**str;
	int		i;
	t_lexor	*redirections;
	int		num_redirections;

	i = 0;
	num_redirections = 0;
	redirections = NULL;
	str = malloc(sizeof(char **) * arg_size + 1);
	if (!str)
		return (NULL);
	while (arg_size > 0)
	{
		if (add_redirection(&redirections, &lexor_list, &num_redirections))
			arg_size--;
		// else if (ps2_token(&lexor_list))
		// 	printf("test");
		else if (lexor_list->token != PS2)
			str[i++] = ft_strdup(lexor_list->str);
		lexor_list = lexor_list->next;
		arg_size--;
	}
	str[i] = NULL;
	return (ft_simple_cmdsnew(str, builtin_arr(str[0]),
			num_redirections, redirections));
}

//free lexor_list
//handle malloc errors

void	parser(t_lexor *lexor_list, t_tools *tools)
{
	t_simple_cmds	*simple_cmds;
	t_simple_cmds	*node;
	int				arg_size;

	simple_cmds = NULL;
	while (lexor_list)
	{
		if (lexor_list->token == PIPE)
			lexor_list = lexor_list->next;
		else if (lexor_list->token == PS2)
			lexor_list = lexor_list->next;
		arg_size = count_args(lexor_list, tools);
		node = initialize_cmd(lexor_list, arg_size);
		if (!simple_cmds)
			simple_cmds = node;
		else
			ft_simple_cmdsadd_back(&simple_cmds, node);
		while (arg_size--)
			lexor_list = lexor_list->next;
	}
	tools->simple_cmds = simple_cmds;
}

	// int i = 0;
	// while(simple_cmds)
	// {
	// 	printf("\n%i\n", i++);
	// 	while (*simple_cmds->str)
	// 	{
	// 		printf("%s\n", *simple_cmds->str++);
	// 	}
	// 	if (simple_cmds->redirections)
	// 		printf("\tredirections:\n");
	// 	while (simple_cmds->redirections)
	// 	{
	// 		printf("\t%s\t%d\n", simple_cmds->redirections->str, simple_cmds->redirections->token);
	// 		simple_cmds->redirections = simple_cmds->redirections->next;
	// 	}
	// 	if (simple_cmds->builtin)
	// 		printf("BUILTIN :)\n");
	// 	simple_cmds = simple_cmds->next;
	// }
// >> means write over file