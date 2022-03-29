/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:30:06 by gmary             #+#    #+#             */
/*   Updated: 2022/03/14 17:28:11 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	ft_lennum(int n)
{
	int		count;
	long	nbr;

	nbr = (long)n;
	count = 1;
	if (nbr < 0)
	{
		nbr *= -1;
		count++;
	}
	while (nbr >= 10)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

static char	*ft_zero(char *str)
{
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static char	*ft_conv(char *str, long nbr, int n)
{
	int	len;

	len = ft_lennum(n);
	if (n < 0)
	{
		str[0] = '-';
		while (--len > 0)
		{
			str[len] = (nbr % 10) + '0';
			nbr = nbr / 10;
		}
	}
	else
	{
		while (--len >= 0)
		{
			str[len] = (nbr % 10) + '0';
			nbr = nbr / 10;
		}
	}
	str[ft_lennum(n)] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*str;

	nbr = (long)n;
	str = malloc(sizeof(char) * (ft_lennum(n) + 1));
	if (!str)
		return (NULL);
	if (nbr == 0)
		return (ft_zero(str));
	if (nbr < 0)
		nbr *= -1;
	return (ft_conv(str, nbr, n));
}
