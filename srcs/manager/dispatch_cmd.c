/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:24:53 by gmary             #+#    #+#             */
/*   Updated: 2022/04/03 13:25:48 by gmary            ###   ########.fr       */
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
		execute_pipe(tmp, clean, env, STDIN_FILENO);
	return (env);
}
