/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:05:22 by gmary             #+#    #+#             */
/*   Updated: 2022/03/31 16:46:59 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*
	Gustave add:
	allocate_block
*/

char	*allocate_block(char *block, char *str, t_to_clean *clean)
{
	block = NULL;
	block = malloc(sizeof(char) * (ft_strlen(str)));
	if (!block)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	return (block);
}

/*
	 Gustave add
*/

char	*expand_dollar_bis(char *str, char *var_name, int i, t_to_clean *clean)
{
	if (str[i] == '$' && str[i + 1] == '?')
		str = replace_interrogation(str, i, clean);
	else
	{
		var_name = cut_dollar(&str[i], clean);
		if (!var_name)
			return (NULL);
		if (ft_find_env_line(clean->env, var_name) && str[i + 1] != '$')
			str = replace_dollar(str, var_name, i, clean);
		else
			str = del_dollar(str, var_name, ft_strlen(var_name), clean);
	}
	return (str);
}
