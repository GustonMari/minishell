/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:06:24 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/23 15:36:42 by ndormoy          ###   ########.fr       */
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

int	check_edge(t_token *all)
{
	t_token	*tmp;

	tmp = all;
	if (token_is_redir(tmp) && (ft_lstsize(tmp) == 1))
		return (print_cmd_error("newline"));
	else if (tmp->type == PIPE && (ft_lstsize(tmp) == 1))
		return (print_cmd_error("|"));
	else if (tmp->type == PIPE && tmp->next
		&& tmp->next->type == PIPE && (ft_lstsize(tmp) == 2))
		return (print_cmd_error("||"));
	else if (token_is_operator(tmp) && tmp->next && token_is_operator(tmp->next))
		return (print_cmd_error("|"));
	while (tmp->next)
		tmp = tmp->next;
	if (token_is_redir(tmp))
		return (print_cmd_error("newline"));
	else if (tmp->type == PIPE)
	{
		ft_putstr_fd(BRED"minishell: you should have something after pipe\n"CRESET, 2);
		return (-2);
	}
	return (0);
}

int	check_middle(t_token *all)
{
	t_token	*tmp;

	tmp = all;
	while (tmp->next)
	{
		if (tmp->type == PIPE && tmp->next && tmp->next->type == PIPE)
		{
			ft_putstr_fd(BRED "minishell: syntax error near unexpected token `|'\n"CRESET, 2);
			g_status = 2;
			return (-1);
		}
		if (token_is_redir(tmp))
		{
			if (token_is_operator(tmp->next))
			{
				g_status = 2;
				return (print_cmd_error(tmp->next->content));
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_cmd_list(t_token *all)
{
	if (check_edge(all) < 0)
		return (-1);
	if (check_middle(all) < 0)
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
