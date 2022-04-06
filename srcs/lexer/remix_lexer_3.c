/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remix_lexer_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:07:00 by gmary             #+#    #+#             */
/*   Updated: 2022/04/06 16:08:09 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*
	manage le remix 
*/

void	remix_manager(t_token **all)
{
	if (ft_need_remix(all) == 0)
		return ;
	else
	{
		while (ft_need_remix(all) == 1)
			remix_lexer(all);
	}
}
