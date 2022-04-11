/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:00:48 by gmary             #+#    #+#             */
/*   Updated: 2022/04/11 15:48:23 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	**ft_exec_builtin(char **env
	, t_to_clean *clean, char **full_cmd, int builtin)
{
	(void)clean;
	if (builtin == FT_CD)
		ft_cd(full_cmd, env);
	if (builtin == FT_UNSET)
	{
		env = ft_unset(env, full_cmd);
		if (!env)
			return (NULL);
	}
	if (builtin == FT_EXPORT)
		env = manage_export(env, full_cmd);
	if (builtin == FT_PWD)
		ft_pwd();
	if (builtin == FT_ENV)
		ft_print_env(env);
	if (builtin == FT_ECHO)
		ft_echo(full_cmd);
	return (env);
}

int	ft_exec(char **env, t_command *all_cmd, t_to_clean *clean, int out)
{
	int	builtin;

	builtin = is_builtin(all_cmd->cmd_to_exec[0]);
	if (builtin)
		env = ft_exec_builtin(env, clean, all_cmd->cmd_to_exec, builtin);
	else
		return (ft_exec_cmd(env, clean, all_cmd, out));
	return (0);
}
