/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 09:32:39 by gmary             #+#    #+#             */
/*   Updated: 2022/04/06 14:08:44 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	del_dollar_2_quin(char *var_name)
{
	if (var_name)
	{
		free(var_name);
		var_name = NULL;
	}
}

int	ft_isalnum_interogation(int c)
{
	if ((c < 48) || (c > 57 && c < 63) || (c == 64)
		|| ((c > 90) && (c < 97)) || (c > 122))
		return (0);
	else
		return (1);
}

void	dont_expand_special_char(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '$' && !ft_is_space(str[*i + 1])
			&& str[*i + 1] != '\0' && str[*i + 1] != '$'
			&& !ft_isalnum_interogation(str[*i + 1]))
			(*i)++;
		else
			break ;
	}
}
