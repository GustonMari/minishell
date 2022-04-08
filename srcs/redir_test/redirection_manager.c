/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:59:13 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/08 15:02:30 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	erase_file(t_command *all_cmd, char *file_error)
{
	t_command	*tmp;
	int			fd;
	t_command	*previous;

	tmp = all_cmd;
	previous = tmp;
	if (tmp->next)
		tmp = tmp->next;
	while (tmp && tmp->type != PIPE
		&& ft_strcmp(tmp->cmd_to_exec[0], file_error))
	{
		if (tmp->type == WORD && (previous->type == CHV_R
				|| previous->type == D_CHV_R))
		{
			unlink(tmp->cmd_to_exec[0]);
			fd = open(tmp->cmd_to_exec[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			close(fd);
		}
		else
			previous = tmp;
		tmp = tmp->next;
	}
	return (0);
}

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
	char	*file_error;

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

int	remix_redir(t_command **all_cmd)
{
		t_command	*tmp;
	char		*file_name;
	int			ok;

	ok = 0;
	file_name = NULL;
	// if (head->type != CHV_L && head->type != D_CHV_L)
	// 	return (1);
	file_name = find_file_name_double(*all_cmd);
	if (!file_name)
		return (1);
	tmp = *all_cmd;
	while(tmp && tmp->type != PIPE)
	{
		if ((tmp->type == CHV_R || tmp->type == D_CHV_R)&& tmp->next
			&& ft_strcmp(tmp->next->cmd_to_exec[0], file_name) == 0)
			ok = 1;
		if (tmp->type == CHV_L && tmp->next && ok == 1
			&& ft_strcmp(tmp->next->cmd_to_exec[0], file_name) == 0)
			{
				mv_chv_l_cmd(tmp);
				free(file_name);
				return (0);
			}
		tmp = tmp->next;
	}
	
	free(file_name);
	return (1);
}

int	redirection_manager(t_command **all_cmd)
{
	t_command	*tmp;
	t_command	*tmp2;
	int	value;
	int	ret;

	ret = 0;
	value = TRUE;
	tmp = *all_cmd;
	tmp2 = *all_cmd;
	// print_cmd(all_cmd);
	// fprintf(stderr, "------------------\n");
	if (is_file_exist(tmp, tmp2) == 0)
	{
		// print_cmd(all_cmd);
		// fprintf(stderr, "------------------\n");
		//remix_redir(all_cmd);
		//print_cmd(all_cmd);
		ret = manage_chv_r(all_cmd);
		if (ret < 0)
			value = ret;
	}
	ret = manage_chv_l(*all_cmd);
	if (ret < 0)
		value = ret;
	ret = manage_chv_r(all_cmd);
	if (ret < 0)
		value = ret;
	return (value);
}

/* int	redirection_manager(t_command **all_cmd)
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
} */