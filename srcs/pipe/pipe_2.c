/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:00:59 by gmary             #+#    #+#             */
/*   Updated: 2022/04/04 13:39:15 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*Compte le nombre de commande entre avant qu'il y ai
une redirection*/

int	count_cmd_between_pipe(t_command *all_cmd)
{
	int			count;
	t_command	*tmp;

	tmp = all_cmd;
	count = 0;
	while (tmp && !is_redirection_type(tmp))
	{
		if (tmp->type == WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	count_cmd_list(t_command *all_cmd)
{
	int			count;
	t_command	*tmp;

	tmp = all_cmd;
	count = 0;
	while (tmp)
	{
		if (tmp->type == WORD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	count_all_between_pipe(t_command **all_cmd)
{
	while (*all_cmd && (*all_cmd)->type != PIPE)
		*all_cmd = (*all_cmd)->next;
	if (*all_cmd)
		*all_cmd = (*all_cmd)->next;
	return (0);
}
