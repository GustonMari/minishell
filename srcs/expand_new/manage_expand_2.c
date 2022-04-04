/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expand_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:35:57 by gmary             #+#    #+#             */
/*   Updated: 2022/04/04 13:46:25 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*
		permet de copier une block, par exemple un block entre "" ou ''
*/

char	*cpy_block(char	*str, int size, t_to_clean *clean)
{
	char	*block;

	block = malloc(sizeof(char) * (size + 2));
	if (!block)
		return (ft_clean_error_malloc(clean));
	block = ft_strncpy(block, str, (unsigned int)size);
	return (block);
}

/*Trouve le prochain block qui commence 
par un $ ou Quote ou DQuote ou se termine par '\0'
et renvoie sa position*/

int	find_next_block(char *str)
{
	int	i;

	i = 0;
	if (str[0] && str[0] == '$')
		i++;
	while (str[i])
	{
		if (str[i] == QUOTE || str[i] == D_QUOTE
			|| str[i] == '$' || str[i] == BACK_SLASH)
			return (i);
		i++;
	}
	return (i);
}

int	nb_back_slash(char *str)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
			nb ++;
		i++;
	}
	return (nb);
}

int	nb_dollar(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '$')
			nb++;
		i++;
	}
	return (nb);
}

char	*ft_allocate_echapment(char *str, char *new, t_to_clean *clean)
{
	new = malloc(sizeof(char) * (ft_strlen(str) + nb_dollar(str) + 1));
	if (!new)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	return (new);
}
