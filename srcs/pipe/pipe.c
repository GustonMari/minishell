/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 23:34:46 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 23:37:08 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

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

void	ft_pipe(int first, int last, int *sortie)
{
	int	pfd[2];

	if (!first)
	{
		dup2(*sortie, 0);
		close(*sortie);
	}
	if (!last)
	{
		if (pipe(pfd) == -1)
			ft_putstr_fd("Erreur pipe\n", 2);
		else
		{
			dup2(pfd[1], 1);
			close(pfd[1]);
			*sortie = pfd[0];
		}
	}
}

/*Retourne 1 si c'est la derniere commande et qu'il n'y a pas de chevron droit
*/

int	is_last_cmd(t_command *all_cmd)
{
	t_command	*tmp;

	tmp = all_cmd;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == CHV_R || tmp->type == D_CHV_R)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	execute_pipe(t_command *all_cmd, t_to_clean *clean, char **env)
{
	int		out;
	int		i;
	int		save[2];
	int		ret;

	ret = -1;
	i = 0;
	if (!all_cmd)
		return (0);
	out = -1;
	while (all_cmd)
	{
		save[0] = dup(0);
		save[1] = dup(1);
		ft_pipe(i == 0, is_last_cmd(all_cmd), &out);
		ret = redirection_manager(&all_cmd);
		if (ret == -1)
		{
			dup2(save[0], 0);
			close(save[0]);
			dup2(save[1], 1);
			close(save[1]);
			exit(1);
		}
		else if (ret == -2)
		{
			dup2(save[0], 0);
			close(save[0]);
			dup2(save[1], 1);
			close(save[1]);
			g_status = 1;
		}
		else if (all_cmd && all_cmd->type != CHV_R && all_cmd->type != D_CHV_R
			&& all_cmd->type != CHV_L && all_cmd->type != D_CHV_L)
			ft_exec(env, all_cmd, clean, out);
		redirection_clean(all_cmd);
		count_all_between_pipe(&all_cmd);
		dup2(save[0], 0);
		close(save[0]);
		dup2(save[1], 1);
		close(save[1]);
		i++;
	}
	wait_pipe();
	return (0);
}
