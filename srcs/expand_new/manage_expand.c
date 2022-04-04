/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:27:11 by gmary             #+#    #+#             */
/*   Updated: 2022/04/04 16:58:19 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	*ft_allocate_del_quote(char *ret, char *str)
{
	ret = ft_calloc(sizeof(char), (ft_strlen(str) + 2));
	if (!ret)
	{
		free(str);
		return (NULL);
	}
	return (ret);
}

char	*del_quote_end(char *ret, char *str, int j)
{
	ret[j] = '\0';
	if (str)
		free(str);
	return (ret);
}

char	*del_quote(char *str, int pos_a, int pos_b)
{
	int		i;
	int		j;
	char	*ret;

	ret = NULL;
	i = 0;
	j = 0;
	ret = ft_allocate_del_quote(ret, str);
	while (str[i])
	{
		if (i == pos_a && str[i])
			i++;
		if (i == pos_b && str[i])
		{
			i++;
			j++;
			break ;
		}
		ret[j] = str[i];
		if (str[i])
			i++;
		j++;
	}
	return (del_quote_end(ret, str, j));
}

char	*trim_quote(char *str, int *i, t_to_clean *clean)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	if (str[k] == QUOTE || str[k] == D_QUOTE)
	{
		j = find_next_quote(str);
		str = del_quote(str, k, (j + k - 1));
		if (!str)
			return (ft_clean_error_malloc(clean));
		*i += (j);
	}
	return (str);
}

char	*cpy_block_special(char	*str, int size, t_to_clean *clean)
{
	char	*block;

	block = malloc(sizeof(char) * ((size) + 1));
	if (!block)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	block = ft_strncpy(block, str, ((unsigned int)size));
	return (block);
}
