/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:01:13 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/04 14:07:31 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	**bubble_sort_tab_2d(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (++i < ft_count_line(tab))
	{
		j = i;
		while (++j < ft_count_line(tab))
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				tmp = ft_strdup(tab[i]);
				if (!tmp)
					return (NULL);
				free(tab[i]);
				tab[i] = ft_strdup(tab[j]);
				if (!tab[i])
					return (NULL);
				free(tab[j]);
				tab[j] = tmp;
			}
		}
	}
	return (tab);
}

/* Trouve le nom de la variable d'environemment passe en parametre
exemple : si str --> PWD=lolilol
on va retourner PWD */

char	*find_name_val(char *str)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	while ((str[i] && str[i] != '+' && str[i + 1] && str[i + 1] != '='))
		i++;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
			break ;
		i++;
	}
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	j = -1;
	while (++j < i)
		name[j] = str[j];
	name[j] = '\0';
	return (name);
}

/* char	*find_name_val(char *str)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	while ((str[i] && str[i] != '+' && str[i + 1] && str[i + 1] != '='))
		i++;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
			break ;
		i++;
	}
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	while (j < i)
	{
		name[j] = str[j];
		j++;
	}
	name[j] = '\0';
	return (name);
} */

/* Cette fonction va renvoyer la valeur d'une ligne d'une
variable d'environnement donnee, exemple :
str --> PWD=lolilol
ON renvoie --> lolilol*/

char	*find_val_in_line(char *str)
{
	int		i;
	int		j;
	char	*val;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	val = malloc(sizeof(char) * (ft_strlen(&str[i]) + 2));
	if (!val)
		return (NULL);
	while (str[i])
	{
		val[j] = str[i];
		i++;
		j++;
	}
	val[j] = '\0';
	return (val);
}
