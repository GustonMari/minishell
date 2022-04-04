/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expand_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:45:52 by gmary             #+#    #+#             */
/*   Updated: 2022/04/04 17:09:42 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	*add_echapment(char *str, t_to_clean *clean)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = NULL;
	new = ft_allocate_echapment(str, new, clean);
	while (str[i])
	{
		if (str[i] == '$')
		{
			new[j] = BACK_SLASH;
			j++;
		}
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

char	*ft_allocate_del_back_slash(char *str, char *block, int nb,
	t_to_clean *clean)
{
	block = malloc(sizeof(char) * (ft_strlen(str) + 1 - nb));
	if (!block)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	return (block);
}

/*Supprime tous les backslash devant un dollar dans la string*/

char	*del_back_slash(char *str, t_to_clean *clean)
{
	int		i;
	int		j;
	int		nb;
	char	*block;

	i = 0;
	j = 0;
	nb = 0;
	nb = nb_back_slash(str);
	block = NULL;
	block = ft_allocate_del_back_slash(str, block, nb, clean);
	i = 0;
	while (str[i])
	{
		if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
			i++;
		block[j] = str[i];
		i++;
		j++;
	}
	block[j] = '\0';
	free(str);
	return (block);
}

t_token	*expand_all(t_token *all, t_to_clean *clean)
{
	t_token	*tmp;
	int		expand;

	tmp = NULL;
	expand = 1;
	tmp = all;
	while (tmp)
	{
		if (expand)
		{
			tmp->content = expand_node(tmp->content, clean);
			if (!tmp->content)
				return (NULL);
		}
		expand = 1;
		if (tmp->type == D_CHV_L)
			expand = 0;
		tmp = tmp->next;
	}
	return (all);
}
