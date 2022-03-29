/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:13:14 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/23 10:13:26 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	**execute_one_cmd(char **env, t_to_clean *clean, t_command *all)
{
	int	builtin;

	builtin = is_builtin(all->cmd_to_exec[0]);
	if (builtin == FT_CD)
		ft_cd(all->cmd_to_exec, env);
	if (builtin == FT_UNSET)
	{
		env = ft_unset(env, all->cmd_to_exec);
		if (!env)
			return (NULL);
	}
	if (builtin == FT_EXPORT)
		env = manage_export(env, all->cmd_to_exec);
	if (builtin == FT_PWD)
		ft_pwd();
	if (builtin == FT_ENV)
		ft_print_env(env);
	if (builtin == FT_ECHO)
		ft_echo(all->cmd_to_exec);
	if (ft_strcmp(all->cmd_to_exec[0], "exit") == 0)
	{
		//A voir si c'est pas mauvais
		//if (all->cmd_to_exec[1])
		//	g_status = ft_atoi(all->cmd_to_exec[1]);
		ft_exit(all, clean);
	}
		
	return (env);
}
