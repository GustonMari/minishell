/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 09:15:34 by gmary             #+#    #+#             */
/*   Updated: 2022/04/04 11:00:07 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"


char	*replace_interrogation(char *str, int pos, t_to_clean *clean,
		char *var_name)
{
	char	*dest;
	char	*status;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	status = NULL;
	dest = NULL;
	status = ft_allocate_itoa(status, str, var_name, clean);
	dest = ft_allocate_dest(str, status, dest, clean);
	while (str[i])
	{
		if (i == pos)
		{
			replace_interrogation_bis(status, dest, &j, &k);
			i += 2;
		}
		else
			replace_interrogation_ter(str, dest, &i, &k);
	}
	dest[k] = '\0';
	return (replace_interrogation_end(str, status, var_name, dest));
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
		if (str[i] != BACK_SLASH || (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] != '$'))
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
