/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:29:31 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 21:29:44 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	create_op_bis(t_to_clean *clean, t_token **begin, int op)
{
	if (op == D_CHV_R)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup(">>"), D_CHV_R, clean));
		return (2);
	}
	else if (op == D_CHV_L)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup("<<"), D_CHV_L, clean));
		return (2);
	}
	return (0);
}

int	create_op(t_to_clean *clean, t_token **begin, int op)
{
	if (op == PIPE)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup("|"), PIPE, clean));
		return (1);
	}
	else if (op == CHV_R)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup(">"), CHV_R, clean));
		return (1);
	}
	else if (op == CHV_L)
	{
		ft_lstadd_back(begin, ft_lstnew(ft_strdup("<"), CHV_L, clean));
		return (1);
	}
	if (create_op_bis(clean, begin, op) == 2)
		return (2);
	return (0);
}
