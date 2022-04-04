/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expand_single_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:49:23 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/04 16:49:49 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"


char	*ft_allocate_exp_single_node(char *expanded, char *block,
			char * str, t_to_clean *clean)
{
	expanded = ft_strjoin_free(expanded, block, 1);
	if (!expanded)
	{
		free(block);
		return (exit_expand_node_single(clean, clean->env, str, expanded));
	}
	free(block);
	return (expanded);
}

char	*expand_node_single_bis(char *expanded,
			char *str, t_to_clean *clean, int *i)
{
	char	*block;

	block = NULL;
	if (str[*i] == QUOTE)
		block = expand_node_single_quote(str, clean, i, expanded);
	else if (str[*i] == D_QUOTE)
		block = expand_node_single_d_quote(str, clean, i, expanded);
	else if (str[*i] == '$')
	{
		block = expand_node_single_dollar(str, clean, i, expanded);
		if (str[*i + 1] != '\0'
			&& clean->not_expand == 0 && !ft_is_space(str[*i + 1]))
			block = expand_single_dollar(clean->env, block, clean);
		clean->not_expand = 0;
		*i += find_next_single_block_merde(&str[*i]);
	}
	else if (str[*i] == BACK_SLASH && str[*i + 1] && str[*i + 1] == '$')
		block = expand_node_single_backlash(str, clean, i, expanded);
	else
	{
		block = expand_node_single_else(str, clean, i, expanded);
		if (ft_find_d_chv_l_str(block, "<<", 2) == TRUE)
			clean->not_expand = 1;
		*i += find_next_single_block(&str[*i]);
	}
	return (block);
}

char	*expand_node_single(t_to_clean *clean, char **env, char *str)
{
	int		i;
	char	*block;
	char	*expanded;

	block = NULL;
	clean->not_expand = 0;
	expanded = ft_strdup("");
	if (!expanded)
		return (exit_expand_node_single(clean, env, str, expanded));
	i = 0;
	while (str[i])
	{
		block = expand_node_single_bis(expanded, str, clean, &i);
		expanded = ft_allocate_exp_single_node(expanded, block, str, clean);
	}
	free(str);
	return (expanded);
}
