/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:48:33 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/11 14:43:58 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	ft_exit(t_command *all, t_to_clean *clean)
{
	if (ft_lstsize_cmd(clean->command_begin) == 1)
		ft_putstr_fd("exit\n", 2);
	if (ft_count_line(all->cmd_to_exec) == 1)
	{
		prio_exit(all);
		ft_clean_exit(clean);
		exit (g_status);
	}
	else if (ft_count_line(all->cmd_to_exec) == 2)
	{
		if (is_str_digit_special(all->cmd_to_exec[1]))
		{
			exit_error(all->cmd_to_exec[1]);
			if (prio_exit(clean->command_begin) == FALSE
				&& ft_lstsize_cmd_pipe(clean->command_begin) == 0)
					g_status = 2;
			ft_clean_exit(clean);
			
			exit(g_status);
		}
		exit_overflow(all->cmd_to_exec[1], clean);
	}
	else
		ft_exit_2(all->cmd_to_exec, clean);
	return ;
}
