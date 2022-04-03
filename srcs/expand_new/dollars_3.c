/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:04:17 by gmary             #+#    #+#             */
/*   Updated: 2022/04/03 15:57:20 by gmary            ###   ########.fr       */
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

char	*ft_allocate_block(char *str, char *block, t_to_clean *clean)
{
	block = malloc(sizeof(char) * (ft_strlen(str)));
	if (!block)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	return (block);
}

char	*del_one_back_slash_bis(char *str, char *block, int j)
{
	block[j] = '\0';
	free(str);
	return (block);
}

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
	block = ft_allocate_block(str, block, clean);
	i = 0;
	while (str[i])
	{
		if (str[i] == BACK_SLASH && str[i + 1]
			&& str[i + 1] == '$' && done == 0)
		{
			done = 1;
			i++;
		}
		block[j] = str[i];
		i++;
		j++;
	}
	return (del_one_back_slash_bis(str, block, j));
}

char	*expand_dollar_bis(char *str, int i, t_to_clean *clean)
{
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


void	expand_dollar_ter(char *str, int *i)
{
	if (str[*i] == BACK_SLASH && str[*i + 1] && str[*i + 1] == '$')
	{
		(*i)++;
		(*i)++;
	}
}

char	*expand_dollar(char **env, char *str, t_to_clean *clean)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = NULL;
	while (str[i])
	{
		expand_dollar_ter(str, &i);
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
	return (expand_dollar_bis(str, i, clean));
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
		{
			while (new_var[k])
			{
				ret[j] = new_var[k];
				k++;
				j++;
			}
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
}
