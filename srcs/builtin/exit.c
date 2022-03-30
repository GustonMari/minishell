/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:48:33 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/30 11:23:33 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	ft_clean_exit(t_to_clean *clean)
{
	ft_lstclear(&(clean->token_begin), free);
	ft_cmd_clear(&(clean->command_begin));
	ft_free_tab_2d(clean->env);
	free(clean);
	rl_clear_history();
}

void	ft_exit_2(char **full_cmd, t_to_clean *clean)
{
	if (!is_str_digit(full_cmd[1]))
	{
		ft_putstr_fd(BRED"exit\nminishell: exit: too many arguments\n"CRESET, 2);
		if (g_status == 0)
			g_status = 1;
	}
	else
	{
		exit_error(full_cmd[1]);
		g_status = 2;
		ft_clean_exit(clean);
		ft_putstr_fd("exit\n", 2);
		exit(2);
	}
}

int	prio_exit(t_command *all)
{	
	t_command	*tmp;
	t_command	*last;

	tmp = all;
	while (tmp)
	{	
		last = tmp;
		tmp = tmp->next;
	}
	if (ft_strcmp("exit", last->cmd_to_exec[0]) == 0
		&& last->cmd_to_exec[1] && !is_str_digit(last->cmd_to_exec[1])
		&& ft_count_line(last->cmd_to_exec) == 2)
	{
		g_status = ft_atoi(last->cmd_to_exec[1]);
		return (TRUE);
	}
	return (FALSE);
}

void	exit_overflow(char *number, t_to_clean *clean)
{
	long long	num;

	num = ft_atolll(number);

	if (num < 0)
	{
		num %= 256;
		num = 256 - num;
	} 
	else
		num %= 256;
	ft_putstr_fd("exit\n", 2);
	if (ft_strlen(number) > 19)
	{
		ft_putstr_fd(BRED "bash: exit: ", 2);
		ft_putstr_fd(number, 2);
		ft_putstr_fd(": numeric argument required" CRESET, 2);
	}
	ft_clean_exit(clean);
	exit (num);
}

void	ft_exit(t_command *all, t_to_clean *clean)
{
	if (ft_count_line(all->cmd_to_exec) == 1)
	{
		ft_clean_exit(clean);
		ft_putstr_fd("exit\n", 2);
		exit (g_status);
	}
	else if (ft_count_line(all->cmd_to_exec) == 2)
	{
		if (is_str_digit_special(all->cmd_to_exec[1]))
		{
			exit_error(all->cmd_to_exec[1]);
			g_status = 2;
			ft_clean_exit(clean);
			//ft_putstr_fd("exit\n", 2);
			exit(2);
		}
		exit_overflow(all->cmd_to_exec[1], clean);
		//g_status = ft_atoi(all->cmd_to_exec[1]);
		//ft_clean_exit(clean);
		//exit(g_status);
	}
	else
		ft_exit_2(all->cmd_to_exec, clean);
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
