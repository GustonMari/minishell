/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:48:33 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/23 09:50:12 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	ft_exit_2(char **full_cmd)
{
	if (!is_str_digit(full_cmd[1]))
	{
		ft_putstr_fd(BRED"exit\nminishell: exit: too many arguments\n"CRESET, 2);
		if (g_status == 0)
			g_status = 1;
		printf("g_status = %d\n", g_status);
	}
	else
	{
		exit_error(full_cmd[1]);
		g_status = 2;
		printf("g_status = %d\n", g_status);
		exit(2);
	}
}

void	ft_exit(char **full_cmd, t_to_clean *clean)
{
	if (ft_count_line(full_cmd) == 1)
	{
		printf("g_status = %d\n", g_status);
		exit (g_status);
	}
	else if (ft_count_line(full_cmd) == 2)
	{
		if (is_str_digit(full_cmd[1]))
		{
			exit_error(full_cmd[1]);
			g_status = 2;
			printf("g_status = %d\n", g_status);
			ft_lstclear(&(clean->token_begin), free);
			ft_cmd_clear(&(clean->command_begin));
			exit(2);
		}
		g_status = ft_atoi(full_cmd[1]);
		printf("g_status = %d\n", g_status);
		exit(g_status);
	}
	else
		ft_exit_2(full_cmd);
	return ;
}

/* int	g_status;

int	main()
{
	char *tab[] ={"exit", "90", "400", NULL};

	ft_exit(tab);
	while(1);
	return (0);
} */

