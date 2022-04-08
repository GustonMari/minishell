/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_test_right_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:55:18 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/08 15:50:04 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	manage_single_chv_r_bis(int fd, int a)
{
	redirection_error(strerror(errno));
	if (a == 1)
		g_status = errno;
	close(fd);
	return (-2);
}

int	manage_single_chv_r(t_command **all_cmd, char *last_redir)
{
	t_command	*tmp;
	int	fd;

	fd = -1;
	tmp = *all_cmd;
	if (tmp->type != CHV_R && tmp->type != D_CHV_R)
		return (-1);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CHV_R)
		{
			fd = open(tmp->next->cmd_to_exec[0],
					O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd < 0)
				return (manage_single_chv_r_bis(fd, 1));
			if (tmp->next && ft_strcmp(tmp->next->cmd_to_exec[0], last_redir))
				close(fd);
		}
		else if (tmp->type == D_CHV_R)
		{
			fd = open(tmp->next->cmd_to_exec[0],
					O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fd < 0)
				return (manage_single_chv_r_bis(fd, 0));
			if (tmp->next && ft_strcmp(tmp->next->cmd_to_exec[0], last_redir))
				close(fd);
		}
		if (tmp->next && !ft_strcmp(tmp->next->cmd_to_exec[0], last_redir))
			return (fd);
		if (tmp->next && tmp->next->next)
			tmp = tmp->next->next;
		else
			break ;
	}
	return (fd);
}

/* int	manage_single_chv_r(t_command **all_cmd)
{
	int	fd;

	fd = -1;
	if ((*all_cmd)->type == CHV_R)
	{
		fd = open((*all_cmd)->next->cmd_to_exec[0],
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd < 0)
			return (manage_single_chv_r_bis(fd, 1));
		return (fd);
	}
	else if ((*all_cmd)->type == D_CHV_R)
	{
		fd = open((*all_cmd)->next->cmd_to_exec[0],
				O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd < 0)
			return (manage_single_chv_r_bis(fd, 0));
		return (fd);
	}
	return (-1);
} */

int	manage_open_r_bis(t_command *tmp, char *last_redir, int fd)
{
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CHV_R)
		{
			fd = open(tmp->next->cmd_to_exec[0],
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				return (-1);
		}
		else if (tmp->type == D_CHV_R)
		{
			fd = open(tmp->next->cmd_to_exec[0],
					O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
				return (-1);
		}
		if (tmp->next && !ft_strcmp(tmp->next->cmd_to_exec[0], last_redir))
			return (fd);
		if (tmp->next && tmp->next->next)
			tmp = tmp->next->next;
		else
			break ;
	}
	return (fd);
}

int	manage_open_r(t_command **all_cmd, char *last_redir)
{
	t_command	*tmp;
	int			fd;

	fd = -1;
	fd = manage_single_chv_r(all_cmd, last_redir);
	if (fd != -1 || fd == -2)
		return (fd);
	tmp = *all_cmd;
	//WARNING
	if (tmp && tmp->next && tmp->type == WORD)
		tmp = tmp->next;
	return (manage_open_r_bis(tmp, last_redir, fd));
}

/* 
int	manage_open_r(t_command **all_cmd, char *last_redir)
{
	t_command	*tmp;
	int			fd;

	fd = -1;
	fd = manage_single_chv_r(all_cmd, last_redir);
	if (fd != -1 || fd == -2)
		return (fd);
	tmp = *all_cmd;
	tmp = tmp->next;
	return (manage_open_r_bis(tmp, last_redir, fd));
} */