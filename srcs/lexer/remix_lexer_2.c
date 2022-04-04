/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remix_lexer_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:06:26 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/04 13:10:40 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*
fonction qui permet de check si il y a plus dun mots
apres un CHV_L et avant le prochain op
ex:
< ok wc -l < yes => ici on a trois WORD
*/

int	count_word_btw_two_op(t_token *all)
{
	t_token	*tmp;
	int		count;

	tmp = all;
	count = 0;
	tmp = tmp->next;
	while (tmp && !token_is_operator(tmp))
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

/*
	permet de bouger le mot apres le CHV_L
	on est dans le cas wc < ok -l
*/

void	mv_word_left(t_token *all)
{
	t_token	*tmp;
	t_token	*forward;
	t_token	*word;

	tmp = all;
	forward = tmp->next->next;
	word = tmp->next;
	tmp->next = forward;
	tmp = tmp->next;
	while (tmp)
	{
		if ((tmp->next == NULL) || (token_is_operator(tmp->next)))
		{
			if (tmp->next)
				word->next = tmp->next;
			else
				word->next = NULL;
			tmp->next = word;
			break ;
		}
		tmp = tmp->next;
	}
}

void	mv_chv_l_bis(t_token *tmp, t_token *word)
{
	while (tmp)
	{
		if (tmp->next)
		{
			if ((tmp->next->next == NULL)
				|| (token_is_operator(tmp->next->next)))
			{
				if (tmp->next)
					word->next = tmp->next;
				else
					word->next = NULL;
				tmp->next = word;
				break ;
			}
		}
		tmp = tmp->next;
	}
}

/*
	deplace chv_l avant le mot
*/

void	mv_chv_l(t_token *all)
{
	t_token	*tmp;
	t_token	*forward;
	t_token	*word;

	tmp = all;
	forward = tmp->next->next;
	word = tmp->next;
	tmp->next = forward;
	tmp = tmp->next;
	mv_chv_l_bis(tmp, word);
}
