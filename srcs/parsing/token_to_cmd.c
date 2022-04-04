/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:32:04 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/04 13:32:18 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*Trouve la taille du tableau a deux dimmensions 
qui va etre cree pour une commande*/

int	cmd_len(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && !token_is_operator(tokens))
	{
		tokens = tokens->next;
		count++;
	}
	return (count);
}

/* Cree un tab a deux dimmensions avec un NULL
 a la fin pour une commande et ses arguments*/

char	**token_to_tab(t_token *tokens, t_to_clean *clean)
{
	char	**strs;
	int		i;

	i = 0;
	strs = ft_calloc(sizeof(char *), (cmd_len(tokens) + 1));
	if (!strs)
		return (ft_clean_error_malloc(clean));
	while (tokens && !token_is_operator(tokens))
	{
		strs[i] = ft_strdup(tokens->content);
		if (!strs[i])
		{
			strs[i] = NULL;
			ft_free_tab_2d(strs);
			return (ft_clean_error_malloc(clean));
		}
		tokens = tokens->next;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

/* Cree un tab a deux dimmensions avec un NULL a la fin pour un operateur*/

char	**token_op_to_tab(t_token *tokens, t_to_clean *clean)
{
	char	**strs;

	strs = ft_calloc(sizeof(char *), (2));
	if (!strs)
		return (ft_clean_error_malloc(clean));
	strs[0] = ft_strdup(tokens->content);
	if (!strs[0])
	{
		free(strs);
		ft_clean_error_malloc(clean);
	}
	strs[1] = NULL;
	return (strs);
}

/*Cree un Node de cmd, assigne le type 
et fait pointer vers son tab a deux dimmensions*/

t_command	*create_new_cmd_node(char **strs, t_token *all, t_to_clean *clean)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
	{
		ft_free_tab_2d(strs);
		return (ft_clean_error_malloc(clean));
	}
	new_cmd->cmd_to_exec = strs;
	if (!new_cmd->cmd_to_exec)
		return (NULL);
	new_cmd->type = all->type;
	new_cmd->to_del = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	ft_add_back_cmd(t_command **alst, t_command *new)
{
	t_command	*temp;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	temp = *alst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
