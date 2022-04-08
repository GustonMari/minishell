/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_remix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:23:46 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/08 14:48:12 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	mv_word_left_bis_cmd(t_command *tmp, t_command *word)
{
	while (tmp)
	{
		if ((tmp->next == NULL) || (is_operator_type(tmp->next)))
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

/*
	permet de bouger le mot apres le CHV_L
	on est dans le cas wc < ok -l
*/

void	mv_word_left_cmd(t_command *all)
{
	t_command	*tmp;
	t_command	*forward;
	t_command	*word;

	tmp = NULL;
	forward = NULL;
	word = NULL;
	tmp = all;
	forward = tmp->next->next;
	word = tmp->next;
	tmp->next = forward;
	tmp = tmp->next;
	mv_word_left_bis_cmd(tmp, word);
}

void	mv_chv_l_bis_cmd(t_command *tmp, t_command *word)
{
	while (tmp)
	{
		if (tmp->next)
		{
			if ((tmp->next->next == NULL)
				|| (is_operator_type(tmp->next->next)))
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

void	mv_chv_l_cmd(t_command *all)
{
	t_command	*tmp;
	t_command	*forward;
	t_command	*word;

	tmp = NULL;
	forward = NULL;
	word = NULL;
	tmp = all;
	forward = tmp->next->next;
	word = tmp->next;
	tmp->next = forward;
	tmp = tmp->next;
	mv_chv_l_bis_cmd(tmp, word);
}
