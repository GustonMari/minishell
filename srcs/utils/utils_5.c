/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:12:22 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/05 16:05:52 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	print_tab_2d(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		ft_putstr_fd(strs[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
}

int	condition_if_exit(t_command *all)
{
	t_command	*tmp;

	tmp = all;
	if (ft_strcmp(tmp->cmd_to_exec[0], "exit") != TRUE)
		return (FALSE);
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}
