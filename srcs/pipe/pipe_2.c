/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:00:59 by gmary             #+#    #+#             */
/*   Updated: 2022/04/03 14:01:09 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	count_all_between_pipe(t_command **all_cmd)
{
	while (*all_cmd && (*all_cmd)->type != PIPE)
		*all_cmd = (*all_cmd)->next;
	if (*all_cmd)
		*all_cmd = (*all_cmd)->next;
	return (0);
}
