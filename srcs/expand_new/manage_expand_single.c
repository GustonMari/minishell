/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expand_single.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 09:40:36 by gmary             #+#    #+#             */
/*   Updated: 2022/04/04 15:07:52 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	find_next_single_block_merde(char *str)
{
	int	i;

	i = 0;
	i++;
	while (str[i])
	{
		if (str[i] == QUOTE || str[i] == D_QUOTE || str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

int	find_next_single_block(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == QUOTE || str[i] == D_QUOTE || str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}
