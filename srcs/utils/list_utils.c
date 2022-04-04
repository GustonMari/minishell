/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:01:59 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/04 14:02:16 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	ft_lstadd_back(t_token **alst, t_token *new)
{
	t_token	*temp;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	temp = *alst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_token	*ft_lstnew(char *content, t_tokentype param, t_to_clean *clean)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (ft_clean_error_malloc(clean));
	new->content = content;
	if (!new->content)
		return (NULL);
	new->type = param;
	new->next = NULL;
	return (new);
}

void	print_token(t_token **begin_list)
{
	t_token	*current;

	current = *begin_list;
	while (current)
	{
		printf("%s\n", current->content);
		current = current->next;
	}
}

void	print_cmd(t_command **begin_list)
{
	t_command	*current;

	current = *begin_list;
	while (current)
	{
		print_tab_2d(current->cmd_to_exec);
		current = current->next;
	}
}
