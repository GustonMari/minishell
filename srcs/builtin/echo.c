/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:46:57 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/29 16:38:16 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	ft_echo_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	manage_echo_n(char **full_cmd)
{
	int	i;

	i = 1;
	while (full_cmd[i])
	{
		if (ft_echo_n(full_cmd[i]) == 1)
			break ;
		i++;
	}
	return (i);
}

void	ft_echo(char **full_cmd)
{
	int	i;
	int	j;
	int	n;

	g_status = 0;
	if (ft_count_line(full_cmd) == 1)
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	i = 0;
	i = manage_echo_n(full_cmd);
	n = i;
	while (full_cmd[i])
	{
		j = 0;
		while (full_cmd[i][j])
		{
			if (full_cmd[i][j] == BACK_SLASH && full_cmd[i][j + 1]
				&& full_cmd[i][j + 1] == '$')
				j++;
			ft_putchar_fd(full_cmd[i][j], 1);
			if (full_cmd[i][j])
				j++;
		}
		if (full_cmd[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (n == 1)
		ft_putchar_fd('\n', 1);
}
