/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expand_single_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:07:18 by gmary             #+#    #+#             */
/*   Updated: 2022/04/12 10:44:47 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	*expand_node_single_quote(char *str, t_to_clean *clean, int *i,
		char *expanded)
{
	char	*block;

	block = cpy_block(&str[*i], find_next_quote(&str[*i]), clean);
	if (!block)
		return (exit_expand_node_single(clean, clean->env, str, expanded));
	(*i) += find_next_quote(&str[*i]);
	return (block);
}

char	*expand_node_single_d_quote(char *str, t_to_clean *clean, int *i,
		char *expanded)
{
	char	*block;

	block = cpy_block(&str[*i], find_next_quote(&str[*i]), clean);
	if (!block)
		return (exit_expand_node_single(clean, clean->env, str, expanded));
	(*i) += find_next_quote(&str[*i]);
	return (block);
}

char	*expand_node_single_dollar(char *str, t_to_clean *clean, int *i,
		char *expanded)
{
	char	*block;

	block = cpy_block(&str[*i], find_next_single_block_merde(&str[*i]), clean);
	if (!block)
		return (exit_expand_node_single(clean, clean->env, str, expanded));
	return (block);
}

char	*expand_node_single_backlash(char *str, t_to_clean *clean, int *i,
		char *expanded)
{
	char	*block;

	(*i)++;
	block = cpy_block(&str[*i], find_next_block(&str[*i]), clean);
	if (!block)
		return (exit_expand_node_single(clean, clean->env, str, expanded));
	i += find_next_block(&str[*i]);
	return (block);
}

char	*expand_node_single_else(char *str, t_to_clean *clean, int *i,
		char *expanded)
{
	char	*block;

	block = cpy_block(&str[*i], find_next_block_single_else(&str[*i]), clean);
	if (!block)
		return (exit_expand_node_single(clean, clean->env, str, expanded));
	return (block);
}

/* char	*expand_node_single_else(char *str, t_to_clean *clean, int *i,
		char *expanded)
{
	char	*block;

	block = cpy_block(&str[*i], find_next_block(&str[*i]), clean);
	if (!block)
		return (exit_expand_node_single(clean, clean->env, str, expanded));
	return (block);
} */