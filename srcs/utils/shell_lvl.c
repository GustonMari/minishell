/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:49:44 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 22:50:04 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	**shell_lvl(char **envp)
{
	char	*number;
	char	*ret;
	char	*to_export;
	char	**env;

	ret = find_val_in_tab(envp, "SHLVL");
	if (ret == NULL)
	{
		number = ft_itoa(0);
		if (!number)
			return (NULL);
	}
	else
	{
		number = ft_itoa(ft_atoi(ret) + 1);
		if (!number)
			return (NULL);
	}
	to_export = ft_strjoin_free("SHLVL=", number, 2);
	if (!to_export)
		return (NULL);
	free(ret);
	env = ft_export(envp, to_export);
	free(to_export);
	return (env);
}
