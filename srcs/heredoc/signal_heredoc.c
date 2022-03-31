/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:52:21 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 21:10:22 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	signal_heredoc(void)
{
	if (signal(SIGINT, &manage_heredoc_signal) == SIG_ERR)
		return (1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (1);
	return (0);
}

int	signal_launch_heredoc(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}
