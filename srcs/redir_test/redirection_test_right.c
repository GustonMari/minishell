/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_test_right.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:39:43 by gmary             #+#    #+#             */
/*   Updated: 2022/04/07 07:47:46 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	is_redirection_type(t_command *op)
{
	if (op->type == CHV_L)
		return (1);
	if (op->type == D_CHV_L)
		return (1);
	if (op->type == CHV_R)
		return (1);
	if (op->type == D_CHV_R)
		return (1);
	return (0);
}

int	count_redir_r(t_command *all_cmd)
{
	t_command	*tmp;
	int			nb_redir;

	nb_redir = 0;
	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CHV_R || tmp->type == D_CHV_R)
			nb_redir++;
		tmp = tmp->next;
	}
	return (nb_redir);
}

char	*find_last_redir_r(t_command *all_cmd)
{
	t_command	*tmp;
	char		*file_name;
	int			is_redir_r;

	is_redir_r = 0;
	file_name = NULL;
	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CHV_R || tmp->type == D_CHV_R)
			is_redir_r = 1;
		if (tmp->type == WORD && is_redir_r == 1)
		{
			free(file_name);
			file_name = ft_strdup(tmp->cmd_to_exec[0]);
			if (!file_name)
				return (NULL);
			is_redir_r = 0;
		}
		tmp = tmp->next;
	}
	return (file_name);
}

//faire gestion derreur

int	manage_chv_r(t_command **all_cmd)
{
	char		*file_name;
	int			fd;

	file_name = NULL;
	if (count_redir_r(*all_cmd) == 0)
		return (1);
	file_name = find_last_redir_r(*all_cmd);
	if (!file_name)
		return (-1);
	fd = manage_open_r(all_cmd, file_name);
	if (fd == -1)
	{
		redirection_error(file_name);
		return (-2);
	}
	dup2(fd, 1);
	close(fd);
	free(file_name);
	return (0);
}
