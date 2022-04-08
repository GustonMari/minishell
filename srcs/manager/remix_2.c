/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remix_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:26:18 by gmary             #+#    #+#             */
/*   Updated: 2022/04/08 15:27:06 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	check_file_valid_bis(t_command *tmp, t_command *previous)
{
	if ((access((tmp->cmd_to_exec[0]), F_OK | R_OK) < 0
			&& previous->type == CHV_L))
		return (TRUE);
	else if (access((tmp->cmd_to_exec[0]), F_OK) >= 0
		&& (previous->type == CHV_R
			|| previous->type == D_CHV_R))
		if (access((tmp->cmd_to_exec[0]), W_OK) < 0)
			return (TRUE);
	return (FALSE);
}

int	find_file_name_double_here(t_command *head, t_command *actual)
{
	t_command	*tmp;

	tmp = head;
	while (tmp && tmp->type != PIPE)
	{
		if (!ft_strcmp(tmp->cmd_to_exec[0], actual->cmd_to_exec[0])
			&& tmp->type == WORD
				&& (count_cmd_list(tmp) != count_cmd_list(actual)))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	is_file_exist_here(t_command *head, t_command *actual)
{
	t_command	*tmp;
	int			ok;

	ok = 0;
	tmp = head;
	if (find_file_name_double_here(head, actual) == 1)
		return (1);
	while(tmp && tmp->type != PIPE)
	{
		if ((tmp->type == CHV_R || tmp->type == D_CHV_R)&& tmp->next
			&& ft_strcmp(tmp->next->cmd_to_exec[0], actual->cmd_to_exec[0]) == 0)
			ok = 1;
		if (tmp->type == CHV_L && tmp->next && ok == 1
			&& ft_strcmp(tmp->next->cmd_to_exec[0], actual->cmd_to_exec[0]) == 0)
				return (0);
		tmp = tmp->next;
	}
	return (1);
}

t_command	*check_file_valid(t_command **all_cmd)
{
	t_command	*tmp;
	t_command	*previous;

	if (count_redir(*all_cmd) == 0)
		return (0);
	tmp = *all_cmd;
	previous = tmp;
	if (tmp->next)
		tmp = tmp->next;
	else
		return (0);
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (check_file_valid_bis(tmp, previous) == TRUE
				&& is_file_exist_here(*all_cmd, tmp) == 1)
				return (tmp);
		}
		else
			previous = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

/*
	Permet de upprimer un noeud de la chaine,
	on enverra TOUJOURS le noeud precedent afin
	de pouvoir raccorde avec la suite
*/

void	suppress_one(t_command **all_cmd)
{
	t_command	*prev_node;
	t_command	*next_node;

	prev_node = *all_cmd;
	next_node = ft_cmdclear_between_pipe(&(*all_cmd)->next);
	prev_node->next = next_node;
}

void	remix_2(t_command **all_cmd)
{
	t_command	*error;
	t_command	*tmp;

	tmp = *all_cmd;
	while (42)
	{
		error = check_file_valid(&tmp);
		if (!error)
			return ;
		else
		{
			if (error->next)
				suppress_one(&error);
		}
		if (error == NULL)
			break ;
		else
			count_all_between_pipe(&tmp);
	}
}
