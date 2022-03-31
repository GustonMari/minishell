/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expand_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:15:02 by gmary             #+#    #+#             */
/*   Updated: 2022/03/31 17:23:45 by gmary            ###   ########.fr       */
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

/*
Trouve le prochain block qui commence par un $ 
ou Quote ou DQuote ou se termine par '\0'
et renvoie sa position
*/

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

t_token	*expand_all(char **env, t_token *all, t_to_clean *clean)
{
	t_token	*tmp;
	int		expand;

	tmp = NULL;
	expand = 1;
	tmp = all;
	while (tmp)
	{
		if (expand)
		{
			tmp->content = expand_node(env, tmp->content, clean);
			if (!tmp->content)
				return (NULL);
		}
		expand = 1;
		if (tmp->type == D_CHV_L)
			expand = 0;
		tmp = tmp->next;
	}
	return (all);
}
