/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:04:23 by gmary             #+#    #+#             */
/*   Updated: 2022/04/06 11:59:30 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*Prend une string qui commence par $, si par exemple on a "$USER pouet"
On commence a i = 1 pour etre sur le debut du nom de la var d'env. On veut copier
USER et le renvoyer.
*/

char	*cut_dollar(char *str, t_to_clean *clean)
{
	int		i;
	char	*var_name;

	i = 1;
	while (str[i] && !ft_is_space(str[i])
		&& is_operator(&str[i]) == 0
		&& str[i] != '$' && str[i] != '\'' && str[i] != '\"'
		&& ft_isalnum(str[i]))
		i++;
	var_name = malloc(sizeof(char) * (i));
	if (!var_name)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	var_name = ft_strncpy(var_name, &str[1], i - 1);
	return (var_name);
}

/*
	permet de supprimer une variable commenceant par $ (var_name)
	dans une string donne
*/

void	del_dollar_2_ter(int *first, int *i, int *len)
{
	{
		(*first) = 1;
		(*i) += (*len) + 1;
	}
}

void	del_dollar_2_bis(char *str, int *i, int *j, int *back)
{
	if (str[*i] == BACK_SLASH)
		*back = 1;
	else
		*back = 0;
	if (str[*i])
		(*i)++;
	(*j)++;
}

char	*del_dollar_2(char *str, char *var_name, char *ret, int len)
{
	int	back;
	int	first;
	int	i;
	int	j;

	back = 0;
	first = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && !ft_is_space(str[i + 1])
			&& first == 0 && back != 1)
		{
			if (!ft_strncmp(&str[i + 1], var_name, len))
				del_dollar_2_ter(&first, &i, &len);
		}
		ret[j] = str[i];
		del_dollar_2_bis(str, &i, &j, &back);
	}
	ret[j] = '\0';
	free(str);
	//WARNINGG
	//PB FREE ICI
	// if (var_name)
	// {
	// 	free(var_name);
	// 	var_name = NULL;
	// }
	return (ret);
}

char	*del_dollar(char *str, char *var_name, int len, t_to_clean *clean)
{
	char	*ret;

	ret = NULL;
	ret = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (!ret)
	{
		if (str)
			free(str);
		// if (var_name)
		// {
		// 	free(var_name);
		// 	var_name = NULL;
		// }
		return (ft_clean_error_malloc(clean));
	}
	return (del_dollar_2(str, var_name, ret, len));
}
