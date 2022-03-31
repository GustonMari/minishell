/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:59:40 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 22:59:53 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	*ft_free_tab_2d(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

t_command	*ft_cmdclear_between_pipe(t_command **lst)
{
	t_command	*previous;
	t_command	*current;		

	current = NULL;
	if (lst && *lst)
	{
		current = *lst;
		while (current && current->type != PIPE)
		{
			previous = current;
			current = current->next;
			if (current && current->to_del == 1)
				unlink(current->cmd_to_exec[0]);
			ft_free_tab_2d(previous->cmd_to_exec);
			free(previous);
		}
		*lst = NULL;
	}
	return (current);
}

void	ft_lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*previous;
	t_token	*current;

	if (lst && *lst && del)
	{
		current = *lst;
		while (current)
		{
			previous = current;
			current = current->next;
			(*del)(previous->content);
			free(previous);
		}
		*lst = NULL;
	}
}

void	ft_cmd_clear(t_command **lst)
{
	t_command	*previous;
	t_command	*current;

	if (lst && *lst)
	{
		current = *lst;
		while (current)
		{
			previous = current;
			current = current->next;
			ft_free_tab_2d(previous->cmd_to_exec);
			free(previous);
		}
		*lst = NULL;
	}
}
