/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:18:03 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 21:29:40 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	*cpy_word(char *arg, int end)
{
	char	*to_cpy;
	char	*word;

	to_cpy = ft_strdup(arg);
	if (!to_cpy)
		return (NULL);
	to_cpy[end] = '\0';
	word = ft_strdup(to_cpy);
	if (!word)
		return (NULL);
	free(to_cpy);
	return (word);
}

int	create_word(char *arg, t_token **begin, t_to_clean *clean)
{
	int		i;
	char	*word;

	i = 0;
	while (arg[i] && !is_operator(&arg[i]) && !ft_is_space(arg[i]))
	{
		if (((arg[i] == '\"') || (arg[i] == '\'')))
			i += find_next_quote(&arg[i]);
		else
			i++;
	}
	word = cpy_word(arg, i);
	ft_lstadd_back(begin, ft_lstnew(word, WORD, clean));
	return (i);
}

t_token	*lexer_bis(t_to_clean *clean, char *arg)
{
	t_token	*begin;
	int		i;
	int		op;

	i = 0;
	begin = NULL;
	while (arg[i])
	{
		op = is_operator(&arg[i]);
		if (op)
			i += create_op(clean, &begin, op);
		else if (!op && (!ft_is_space(arg[i])))
			i += create_word(&arg[i], &begin, clean);
		else if (ft_is_space(arg[i]))
			i++;
	}
	free(arg);
	return (begin);
}

t_token	*lexer(t_to_clean *clean, char *arg)
{
	t_token	*begin;

	begin = NULL;
	if (check_quote(arg))
	{
		ft_putstr_fd(BRED"minishell: you should close quote\n"CRESET, 2);
		g_status = 1;
		return (NULL);
	}
	begin = lexer_bis(clean, arg);
	return (begin);
}
