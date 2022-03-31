/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:45:47 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 22:08:03 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/* Count le nombre de redirection qu'il y a entre deux pipe*/

int	count_redir(t_command *all_cmd)
{
	t_command	*tmp;
	int			nb_redir;

	nb_redir = 0;
	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (is_redirection_type(tmp))
			nb_redir++;
		tmp = tmp->next;
	}
	return (nb_redir);
}

int	redirection_clean_bis(t_command *tmp, t_command *previous)
{
	char		*file_error;

	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
		{
			if ((access((tmp->cmd_to_exec[0]), F_OK | R_OK) < 0
					&& previous->type == CHV_L)
				|| (access((tmp->cmd_to_exec[0]), R_OK) < 0
					&& (previous->type == CHV_R
						|| previous->type == D_CHV_R)))
			{
				file_error = ft_strdup((tmp->cmd_to_exec[0]));
				if (!file_error)
					return (-1);
				free(file_error);
				return (1);
			}
		}
		else
			previous = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	redirection_clean(t_command *all_cmd)
{
	t_command	*tmp;
	t_command	*previous;

	if (count_redir(all_cmd) == 0)
		return (0);
	tmp = all_cmd;
	previous = tmp;
	if (tmp->next)
		tmp = tmp->next;
	else
		return (0);
	return (redirection_clean_bis(tmp, previous));
}

/* int	redirection_clean(t_command *all_cmd)
{
	t_command	*tmp;
	char		*file_error;
	t_command	*previous;

	if (count_redir(all_cmd) == 0)
		return (0);
	tmp = all_cmd;
	previous = tmp;
	if (tmp->next)
		tmp = tmp->next;
	else
		return (0);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
		{
			if ((access((tmp->cmd_to_exec[0]), F_OK | R_OK) < 0
					&& previous->type == CHV_L)
				|| (access((tmp->cmd_to_exec[0]), R_OK) < 0
					&& (previous->type == CHV_R
						|| previous->type == D_CHV_R)))
			{
				file_error = ft_strdup((tmp->cmd_to_exec[0]));
				if (!file_error)
					return (-1);
				free(file_error);
				return (1);
			}
		}
		else
			previous = tmp;
		tmp = tmp->next;
	}
	return (0);
} */

int	redirection_manager(t_command **all_cmd)
{
	int	value;
	int	ret;

	ret = 0;
	value = TRUE;
	ret = manage_chv_l(*all_cmd);
	if (ret < 0)
		value = ret;
	ret = manage_chv_r(all_cmd);
	if (ret < 0)
		value = ret;
	return (value);
}
