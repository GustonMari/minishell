/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:57:20 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 14:58:50 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	**manage_export(char **env, char **full_cmd)
{
	int	i;

	i = 1;
	g_status = 0;
	if (ft_count_line(full_cmd) == 1)
	{
		ft_export_no_arg(env);
		return (env);
	}
	while (full_cmd[i])
	{
		env = ft_export(env, full_cmd[i]);
		i++;
	}
	return (env);
}
