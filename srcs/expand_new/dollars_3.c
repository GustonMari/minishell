/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:56:15 by gmary             #+#    #+#             */
/*   Updated: 2022/03/31 16:43:06 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	*replace_dollar(char *str, char *var_name, int pos, t_to_clean *clean)
{
	char	*new_var;
	char	*ret;

	new_var = NULL;
	ret = NULL;
	new_var = find_val_in_tab(clean->env, var_name);
	if (!new_var)
		return (NULL);
	str = del_dollar(str, var_name, ft_strlen(var_name), clean);
	ret = malloc(sizeof(char) * ((ft_strlen(str) + ft_strlen(new_var) + 1)));
	if (!ret)
	{
		free(str);
		free(var_name);
		return (ft_clean_error_malloc(clean));
	}
	free(var_name);
	if (ft_strlen(str) == 0)
	{
		return (replace_dollar_3(str, new_var, ret));
	}
	return (replace_dollar_2(str, new_var, ret, pos));
}

char	*expand_single_dollar(char **env, char *str, t_to_clean *clean)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = NULL;
	var_name = cut_dollar(&str[i], clean);
	if (!var_name)
		return (NULL);
	if (ft_strlen(str) == 1)
	{
		str = del_dollar(str, var_name, ft_strlen(var_name), clean);
		return (str);
	}
	if (str[i] == '$' && str[i + 1] == '?')
		str = replace_interrogation(str, i, clean, var_name);
	else
	{
		if (ft_find_env_line(env, var_name) && str[i + 1] != '$')
			str = replace_dollar(str, var_name, i, clean);
		else
			str = del_dollar(str, var_name, ft_strlen(var_name), clean);
	}
	return (str);
}

/* Gustave ADD  del del_one_back_slash*/
/*supprime UN backslash a l'endroit ou il est*/

char	*del_one_back_slash(char *str, t_to_clean *clean)
{
	int		done;
	int		i;
	int		j;
	char	*block;

	i = 0;
	j = 0;
	done = 0;
	block = NULL;
	block = allocate_block(block, str, clean);
	while (str[i])
	{
		if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$'
			&& done == 0)
		{
			done = 1;
			i++;
		}
		block[j++] = str[i++];
	}
	block[j] = '\0';
	free(str);
	return (block);
}

/*
		Gustave add
*/

char	*expand_dollar(char *str, t_to_clean *clean)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = NULL;
	while (str[i])
	{
		if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
		{
			str = del_one_back_slash(str, clean);
			i++;
		}
		if (str[i] == '$' && !ft_is_space(str[i + 1])
			&& str[i + 1] != '\0' && str[i + 1] != '$')
		{
			expand_dollar_bis(str, var_name, i, clean);
			i = 0;
		}
		if (str[i] != BACK_SLASH)
			i++;
	}
	return (str);
}

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
