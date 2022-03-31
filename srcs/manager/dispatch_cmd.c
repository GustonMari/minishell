/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 23:20:06 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 23:38:15 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	**ft_dispatch(t_command *all, t_to_clean *clean, char **env)
{
	t_command	*tmp;

	tmp = all;
	if (count_cmd_list(tmp) == 1 && (is_builtin(tmp->cmd_to_exec[0])
			|| ft_strcmp(tmp->cmd_to_exec[0], "exit") == 0))
		env = execute_one_cmd(env, clean, all);
	else
		execute_pipe(tmp, clean, env);
	return (env);
}
