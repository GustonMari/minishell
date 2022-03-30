/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remix_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:26:18 by gmary             #+#    #+#             */
/*   Updated: 2022/03/29 10:44:58 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

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
			if ((access((tmp->cmd_to_exec[0]), F_OK | R_OK) < 0 && previous->type == CHV_L))
				return (tmp);
			else if (access((tmp->cmd_to_exec[0]), F_OK) >= 0 && (previous->type == CHV_R
					|| previous->type == D_CHV_R))
				if (access((tmp->cmd_to_exec[0]), W_OK) < 0)
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
	on enverra TOUJOURS le noeud precedent afin de pouvoir raccorde avec la suite
*/

void	suppress_one(t_command **all_cmd)
{
	t_command	*prev_node;
	t_command	*next_node;

	prev_node = *all_cmd;
	next_node = ft_cmdclear_between_pipe(&(*all_cmd)->next);
	//need to do something else for next node
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