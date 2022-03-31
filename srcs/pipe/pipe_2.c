/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 23:35:57 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 23:36:13 by ndormoy          ###   ########.fr       */
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
