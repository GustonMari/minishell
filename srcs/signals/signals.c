/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:38:07 by gmary             #+#    #+#             */
/*   Updated: 2022/04/04 18:11:10 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	exit_pipe_process(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}

void	signal_in_cmd(void)
{
	if (signal(SIGQUIT, &exit_pipe_process) == SIG_ERR)
		ft_putstr_fd("Signal Error\n", 2);
	if (signal(SIGINT, &exit_pipe_process) == SIG_ERR)
		ft_putstr_fd("Signal Error\n", 2);
}

void	signal_cmd(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_status = 130;
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		g_status = 131;
	}
}

void	signal_manager2(void)
{
	if (signal(SIGINT, &signal_cmd) == SIG_ERR)
	{
		ft_putstr_fd("Error Signal\n", 2);
		return ;
	}
	if (signal(SIGQUIT, &signal_cmd) == SIG_ERR)
	{
		ft_putstr_fd("Error Signal\n", 2);
		return ;
	}
}
