/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:33:26 by gmary             #+#    #+#             */
/*   Updated: 2022/04/08 16:43:01 by ndormoy          ###   ########.fr       */
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
	int		status;
	
	while (waitpid(-1, &status, 0) != -1)
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
