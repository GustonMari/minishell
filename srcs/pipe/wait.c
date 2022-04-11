/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:33:26 by gmary             #+#    #+#             */
/*   Updated: 2022/04/11 15:55:48 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	wait_pipe_2(int pid)
{
	int		status;

	while (waitpid(pid, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
	}
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		ft_putstr_fd("Error Signal\n", 2);
		return (FALSE);
	}
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		ft_putstr_fd("Error\n", 2);
		return (FALSE);
	}
	return (0);
}

int	wait_pipe(void)
{
	while (waitpid(-1, NULL, 0) > 0)
		;
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		ft_putstr_fd("Error Signal\n", 2);
		return (FALSE);
	}
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		ft_putstr_fd("Error\n", 2);
		return (FALSE);
	}
	return (0);
}

int	exit_last(t_command *all)
{	
	t_command	*tmp;
	t_command	*last;

	tmp = all;
	while (tmp)
	{	
		last = tmp;
		tmp = tmp->next;
	}
	if (ft_strcmp("exit", last->cmd_to_exec[0]) == 0)
	{
		if ((ft_count_line(last->cmd_to_exec) >=2))
			g_status = 1;
		if (last->cmd_to_exec[1] && is_str_digit(last->cmd_to_exec[1]))
			g_status = 2;
		return (FALSE);
	}
	return (TRUE);
}

void	wait_last(int pid, t_command *all)
{
	int		status;
	(void)pid;

	if (exit_last(all) == TRUE)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) > 0)
			g_status = (WEXITSTATUS(status));
	}
}
