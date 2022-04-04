/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expand_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:53:16 by gmary             #+#    #+#             */
/*   Updated: 2022/04/04 15:00:08 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	*expand_node_dollar(char *str, char *block, t_to_clean *clean, int *i)
{
	block = cpy_block(&str[*i], find_next_quote(&str[*i]), clean);
	//WARNING add EXPANDED
	if (str[(*i) + 1] != '\0')
		block = expand_single_dollar(clean->env, block, clean);
	block = del_back_slash(block, clean);
	(*i) += find_next_quote(&str[*i]);
	return (block);
}

char	*expand_node_d_quote(char *str, char *block, t_to_clean *clean, int *i)
{
	block = cpy_block(&str[*i], find_next_quote(&str[*i]), clean);
	block = trim_quote(block, i, clean);
	block = expand_dollar(clean->env, block, clean);
	return (block);
}

char	*expand_node_quote(char *str, char *block, t_to_clean *clean, int *i)
{
	block = cpy_block(&str[*i], find_next_quote(&str[*i]), clean);
	block = trim_quote(block, i, clean);
	block = add_echapment(block, clean);
	return (block);
}

char	*ft_allocate_expanded(char *str, char *block, char *expanded,
	t_to_clean *clean)
{
	expanded = ft_strjoin_free(expanded, block, 1);
	if (!expanded)
	{
		free(str);
		free(block);
		return (ft_clean_error_malloc(clean));
	}
	free(block);
	return (expanded);
}
