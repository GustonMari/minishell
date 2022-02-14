/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:27:59 by gmary             #+#    #+#             */
/*   Updated: 2022/02/14 19:37:43 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "function.h"

t_env	*ft_lstnew(char *content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->content = malloc(sizeof(char) * ft_strlen(content) + 1);
	if (!new->content)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_env **alst, t_env *new)
{
	t_env	*temp;

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
