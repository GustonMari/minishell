/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remix_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:31:05 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 21:41:39 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*
	fonction de push_swap intervertit 1 et 2
*/
void	ft_sa(t_token **head)
{
	t_token	*temp;
	t_token	*forward;

	temp = *head;
	forward = temp;
	forward = forward->next;
	temp->next = forward->next;
	forward->next = temp;
	*head = forward;
}

void	remix_lexer_bis(t_token **all, t_token *tmp)
{
	t_token	*before_chv_l;

	before_chv_l = *all;
	while (tmp)
	{
		if (token_is_redir(tmp))
		{
			if (count_word_btw_two_op(tmp) > 1)
			{
				mv_word_left(tmp);
				mv_chv_l(before_chv_l);
				while (tmp && !token_is_operator(tmp))
					tmp = tmp->next;
			}
		}
		before_chv_l = tmp;
		tmp = tmp->next;
	}
}

/*
	on cherche ici a resoudre le cas suivant
	wc < ok -l < salut  <=> wc -l < ok < salut .
	la regle consiste asi on rencontre un chevron
	gauche et ensuite deux mots (ou plus),
	decaler le chevron et le premier mots tt a la droite jusquau moment ou 
	lon trouvera un operateur quelconque. Exemple:
	<ok wc -l < salut <=> wc -l < ok < salut
*/

void	remix_lexer(t_token **all)
{
	t_token	*tmp;

	tmp = *all;
	if (token_is_redir(tmp) && (count_word_btw_two_op(tmp) > 1))
	{
		mv_word_left(tmp);
		ft_sa(&tmp);
		if (!remix_size_three(tmp))
			mv_chv_l(tmp);
		*all = tmp;
		return ;
	}
}

/* void	remix_lexer(t_token **all)
{
	t_token	*tmp;
	t_token	*before_chv_l;

	tmp = *all;
	if (token_is_redir(tmp) && (count_word_btw_two_op(tmp) > 1))
	{
		mv_word_left(tmp);
		ft_sa(&tmp);
		if (!remix_size_three(tmp))
			mv_chv_l(tmp);
		*all = tmp;
		return ;
	}
	before_chv_l = *all;
	while (tmp)
	{
		if (token_is_redir(tmp))
		{
			if (count_word_btw_two_op(tmp) > 1)
			{
				mv_word_left(tmp);
				mv_chv_l(before_chv_l);
				while (tmp && !token_is_operator(tmp))
					tmp = tmp->next;
			}
		}
		before_chv_l = tmp;
		tmp = tmp->next;
	}
} */

int	ft_need_remix(t_token **all)
{
	t_token	*tmp;

	tmp = *all;
	while (tmp)
	{
		if (token_is_redir(tmp))
		{
			if (count_word_btw_two_op(tmp) > 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*
	manage le remix 
*/

void	remix_manager(t_token **all)
{
	if (ft_need_remix(all) == 0)
		return ;
	else
	{
		while (ft_need_remix(all) == 1)
			remix_lexer(all);
	}
}
