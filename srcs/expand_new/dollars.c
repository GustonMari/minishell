/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:53:32 by gmary             #+#    #+#             */
/*   Updated: 2022/03/31 15:37:31 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*
	permet de supprimer une variable commenceant par $ (var_name)
	dans une string donne
*/

/* 
   changer par gugus pour la norme:  i += len + 1;
*/

char	*del_dollar_2(char *str, char *var_name, char *ret, int len)
{
	int	first;
	int	i;
	int	j;

	first = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && !ft_is_space(str[i + 1]) && first == 0)
		{
			if (!strncmp(&str[i + 1], var_name, len))
			{
				first = 1;
				i += len + 1;
			}
		}
		ret[j] = str[i];
		if (str[i])
			i++;
		j++;
	}
	ret[j] = '\0';
	free(str);
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
		if (var_name)
			free(var_name);
		return (ft_clean_error_malloc(clean));
	}
	return (del_dollar_2(str, var_name, ret, len));
}

/*
	replace_dollar_3 sert seulment dans le cas ou str est null
*/
char	*replace_dollar_3(char *str, char *new_var, char *ret)
{
	int	i;

	i = 0;
	while (new_var[i])
	{
		ret[i] = new_var[i];
		i++;
	}
	ret[i] = '\0';
	free(new_var);
	free(str);
	return (ret);
}

char	*replace_dollar_2_bis(char *new_var, char *ret, int *j, int *k)
{
	while (new_var[*k])
	{
		ret[*j] = new_var[*k];
		(*k)++;
		(*j)++;
	}
	return (new_var);
}

char	*replace_dollar_2(char *str, char *new_var, char *ret, int pos)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (i == pos)
			replace_dollar_2_bis(new_var, ret, &j, &k);
		ret[j++] = str[i];
		i++;
	}
	if (i == pos)
		replace_dollar_2_bis(new_var, ret, &j, &k);
	ret[j] = '\0';
	free(new_var);
	free(str);
	return (ret);
}

/* 
	Gustave add
*/

/* char	*replace_dollar_2(char *str, char *new_var, char *ret, int pos)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (i == pos)
		{
			replace_dollar_2_bis(new_var, ret, &j, &k);
			//while (new_var[k])
			//{
			//	ret[j] = new_var[k];
			//	k++;
			//	j++;
			//}
		}
		ret[j++] = str[i];
		i++;
	}
	if (i == pos)
	{
		while (new_var[k])
		{
			ret[j] = new_var[k];
			k++;
			j++;
		}
	}
	ret[j] = '\0';
	free(new_var);
	free(str);
	return (ret);
} */