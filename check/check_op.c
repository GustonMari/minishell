/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:06:24 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/23 10:36:48 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

int	is_operator_type(t_command *op)
{
	if (op->type == PIPE)
		return (1);
	if (op->type == CHV_L)
		return (1);
	if (op->type == D_CHV_L)
		return (1);
	if (op->type == CHV_R)
		return (1);
	if (op->type == D_CHV_R)
		return (1);
	return (0);
}

int	check_cmd_list(t_token *all)
{
	t_token	*tmp;

	tmp = all;
	if (token_is_operator(tmp))
		return (-1);
	while (tmp->next)
	{
		if (token_is_operator(tmp))
		{
			if (token_is_operator(tmp->next))
			{
				ft_print_error(1, NULL,
					"syntax error near unexpected token ", tmp->next->content);
				g_status = 2;
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	if (token_is_operator(tmp))
		return (-1);
	return (0);
}

/* int	check_cmd_list(t_token *all)
{
	t_token	*tmp;

	tmp = all;
	if (token_is_operator(tmp))
		return (-1);
	while (tmp->next)
	{
		if (token_is_operator(tmp))
		{
			if (token_is_operator(tmp->next))
			{
				ft_print_error(1, NULL,
					"syntax error near unexpected token ", tmp->next->content);
				g_status = 2;
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	if (token_is_operator(tmp))
		return (-1);
	return (0);
} */

/* int	check_cmd_list(t_command *all)
{
	t_command	*tmp;

	tmp = all;
	if (is_operator_type(tmp))
		return (-1);
	while (tmp->next)
	{
		if (is_operator_type(tmp))
		{
			if (is_operator_type(tmp->next))
			{
				ft_print_error(1, NULL,
					"syntax error near unexpected token ", tmp->cmd_to_exec[0]);
				g_status = 2;
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	if (is_operator_type(tmp))
		return (-1);
	return (0);
}
 */