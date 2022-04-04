/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:22:15 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/04 13:29:10 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

t_to_clean	*clean_init(t_to_clean *clean, char **env, char *line)
{
	clean = malloc(sizeof(clean) * 4);
	if (!clean)
	{
		free(line);
		free(clean);
		exit(errno);
	}
	clean->env = env;
	clean->token_begin = NULL;
	clean->command_begin = NULL;
	return (clean);
}
