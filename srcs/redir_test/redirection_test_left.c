/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_test_left.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:50:34 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/08 10:36:42 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/* Count le nombre de redirections gauche qu'il y a entre deux pipe*/

int	count_redir_l(t_command *all_cmd)
{
	t_command	*tmp;
	int			nb_redir;

	nb_redir = 0;
	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CHV_L)
			nb_redir++;
		tmp = tmp->next;
	}
	return (nb_redir);
}

/* Trouve la derniere redirection gauche
et renvoi le nom du fichier correspondant a la derniere redirection
(cmd plutot ?)*/

char	*find_last_redir_l(t_command *all_cmd)
{
	t_command	*tmp;
	char		*file_name;
	int			is_redir_l;

	is_redir_l = 0;
	file_name = NULL;
	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CHV_L)
			is_redir_l = 1;
		if (tmp->type == WORD && is_redir_l == 1)
		{
			free(file_name);
			file_name = ft_strdup(tmp->cmd_to_exec[0]);
			if (!file_name)
				return (NULL);
			is_redir_l = 0;
		}
		tmp = tmp->next;
	}
	return (file_name);
}

char	*find_file_name_double(t_command *all_cmd)
{
	t_command	*tmp;
	t_command	*same;
	char		*file_name;

	file_name = NULL;
	tmp = all_cmd;
	same = all_cmd;
	while (same && same->type != PIPE)
	{
		if (all_cmd->next)
			tmp = all_cmd->next;
		while (tmp && tmp->type != PIPE)
		{
			if (!ft_strcmp(tmp->cmd_to_exec[0], same->cmd_to_exec[0])
				&& tmp->type == WORD
					&& (count_cmd_list(tmp) != count_cmd_list(same)))
				return (ft_strdup(same->cmd_to_exec[0]));
			tmp = tmp->next;
		}
		same = same->next;
	}
	return (file_name);
}

int	is_file_exist(t_command *all_cmd, t_command *head)
{
	t_command	*tmp;
	char		*file_name;
	int			ok;

	ok = 0;
	file_name = NULL;
	if (head->type != CHV_L && head->type != D_CHV_L)
		return (1);
	file_name = find_file_name_double(all_cmd);
	if (!file_name)
		return (1);
	tmp = head;
	while(tmp && tmp->type != PIPE)
	{
		if ((tmp->type == CHV_R || tmp->type == D_CHV_R)&& tmp->next
			&& ft_strcmp(tmp->next->cmd_to_exec[0], file_name) == 0)
			ok = 1;
		if (tmp->type == CHV_L && tmp->next && ok == 1
			&& ft_strcmp(tmp->next->cmd_to_exec[0], file_name) == 0)
			{
				free(file_name);
				return (0);
			}
		tmp = tmp->next;
	}
	free(file_name);
	return (1);
}

int	manage_single_chv_l(t_command *all_cmd)
{
	if (all_cmd->type == CHV_L)
	{
		if (all_cmd->next
			&& (access((all_cmd->next->cmd_to_exec[0]), F_OK | R_OK) < 0))
		{
			ft_putstr_fd(BRED"minishell: ", 2);
			ft_putstr_fd(all_cmd->next->cmd_to_exec[0], 2);
			ft_putstr_fd(BRED": No such file or directory\n"CRESET, 2);
			return (-1);
		}
	}
	return (0);
}

int	manage_chv_l(t_command *all_cmd)
{
	t_command	*head;
	char		*file_name;
	int			fd;

	head = all_cmd;
	file_name = NULL;
	if (count_redir_l(all_cmd) == 0)
		return (1);
	file_name = find_last_redir_l(all_cmd);
	if (!file_name)
		return (-1);
	if (manage_single_chv_l(all_cmd) < 0)
		return (-2);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 00777);
		dup2(fd, 1);
		close(fd);
		if (is_file_exist(all_cmd, head) == FALSE)
			redirection_error(file_name);
		return (-2);
	}
	dup2(fd, 0);
	close(fd);
	free(file_name);
	return (0);
}
