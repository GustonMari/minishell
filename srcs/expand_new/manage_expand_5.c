/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expand_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:59:29 by gmary             #+#    #+#             */
/*   Updated: 2022/04/12 13:54:22 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	*expand_node_backslash(char *str, char *block, t_to_clean *clean,
		int *i)
{
	(*i)++;
	block = cpy_block_special(&str[*i], find_next_block(&str[*i]), clean);
	(*i) += find_next_block(&str[*i]);
	return (block);
}

int	find_next_block_modif(char *str)
{
	int	i;

	i = 0;
	if (str[0] && (str[0] == '$' || str[0] == BACK_SLASH))
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

char	*expand_node_else(char *str, char *block, t_to_clean *clean, int *i)
{
	block = cpy_block(&str[*i], find_next_block_modif(&str[*i]), clean);
	(*i) += find_next_block_modif(&str[*i]);
	return (block);
}

/*Expand un maillon */

char	*expand_node(char *str, t_to_clean *clean)
{
	int		i;
	char	*block;
	char	*expanded;

	block = NULL;
	expanded = ft_strdup("");
	if (!expanded)
		return (ft_clean_error_malloc(clean));
	i = 0;
	while (str[i])
	{
		if (str[i] == QUOTE)
			block = expand_node_quote(str, block, clean, &i);
		else if (str[i] == D_QUOTE)
			block = expand_node_d_quote(str, block, clean, &i);
		else if (str[i] == '$')
			block = expand_node_dollar(str, block, clean, &i);
		else if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
			block = expand_node_dollar(str, block, clean, &i);
		else
			block = expand_node_else(str, block, clean, &i);
		expanded = ft_allocate_expanded(str, block, expanded, clean);
	}
	free(str);
	return (expanded);
}
