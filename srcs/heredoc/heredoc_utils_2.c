/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:04:08 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 21:10:12 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*Fonction qui nous permet de savoir si la derniere redirection
est un double chevron a gauche.
Si c'est un Double chevron gauche, ca renvoi 0*/

int	priorities_d_chv_l(t_command *all_cmd)
{
	t_command	*tmp;
	int			type;

	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == D_CHV_L || tmp->type == CHV_L)
			type = (int)tmp->type;
		tmp = tmp->next;
	}
	if (type == D_CHV_L)
		return (0);
	else
		return (1);
}

/*Compte le nombre de D_CHV_L entre deux pipe*/

int	count_nb_d_chv_l_between_pipe(t_command *all_cmd)
{
	t_command	*tmp;
	int			i;

	i = 0;
	tmp = all_cmd;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == D_CHV_L)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
