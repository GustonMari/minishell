/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:57:30 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/05 10:46:07 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	manage_check_quote(char *line, t_to_clean *clean)
{
	if (check_quote(line) == FALSE)
	{
		ft_putstr_fd(BRED"minishell: you should close quote\n"CRESET, 2);
		free(clean);
		free(line);
		return (FALSE);
	}
	return (TRUE);
}

char	**manage_line_bis_2(t_command *cmd_all, t_to_clean *clean,
		char **env, t_token *expanded)
{
	remix_2(&cmd_all);
	manage_line_clean(clean, cmd_all, expanded);
	return (env);
}
