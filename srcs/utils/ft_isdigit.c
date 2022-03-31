/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:32:08 by gmary             #+#    #+#             */
/*   Updated: 2022/03/31 22:31:26 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (1);
	else
		return (0);
}

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == FALSE)
			return (1);
		i++;
	}
	return (0);
}

int	is_str_digit_special(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == FALSE)
			return (1);
		i++;
	}
	return (0);
}
