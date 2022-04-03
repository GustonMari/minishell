/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:04:17 by gmary             #+#    #+#             */
/*   Updated: 2022/04/03 14:17:12 by gmary            ###   ########.fr       */
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
	//WARNING remettre cut_dollar
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
	block = malloc(sizeof(char) * (ft_strlen(str)));
	if (!block)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$' && done == 0)
		{
			done = 1;
			i++;
		}
		block[j] = str[i];
		i++;
		j++;
	}
	block[j] = '\0';
	free(str);
	return (block);
}

char	*expand_dollar(char **env, char *str, t_to_clean *clean)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = NULL;
	while (str[i])
	{
		if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
		{
			i++;
			i++;
		}
		if (str[i] == '$' && !ft_is_space(str[i + 1])
			&& str[i + 1] != '\0' && str[i + 1] != '$')
		{
			if (str[i] == '$' && str[i + 1] == '?')
				str = replace_interrogation(str, i, clean, var_name);
			else
			{
				var_name = cut_dollar(&str[i], clean);
				if (!var_name)
					return (NULL);
				if (ft_find_env_line(env, var_name) && str[i + 1] != '$')
					str = replace_dollar(str, var_name, i, clean);
				else
					str = del_dollar(str, var_name, ft_strlen(var_name), clean);
			}
			// gros doute pour le i = 0 si il faut vraiment lenlever
			//i = 0;
		}
		//ATTENTION
		if (str[i] != BACK_SLASH)
			i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
		{
			str = del_one_back_slash(str, clean);
			i++;
		}
		i++;
	}
	return (str);
}
