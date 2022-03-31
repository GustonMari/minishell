/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 22:31:41 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 23:03:04 by ndormoy          ###   ########.fr       */
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
		ft_putstr_fd(current->content, 1);
		ft_putstr_fd("\n", 1);
		current = current->next;
	}
}

/* void	print_token(t_token **begin_list)
{
	t_token	*current;

	current = *begin_list;
	while (current)
	{
		printf("%s\n", current->content);
		//ft_putstr_fd(current->content, 1);
		//printf("\ntype = %d\n", (int)current->type);
		//ft_putchar_fd('\n', 1);
		current = current->next;
	}
} */

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

/* void	print_cmd(t_command **begin_list)
{
	t_command	*current;

	current = *begin_list;
	while (current)
	{
		//printf("%s\n", current->cmd_to_exec);
		print_tab_2d(current->cmd_to_exec);
		//fprintf(stderr,"\ntype = %d\n", (int)current->type);
		fprintf(stderr,"---------------------------------\n");
		current = current->next;
	}
} */
