/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 09:44:12 by gmary             #+#    #+#             */
/*   Updated: 2022/04/06 09:34:13 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	replace_dollar_2_bis(char *ret, char *new_var, int *j, int *k)
{
	while (new_var[*k])
	{
		ret[*j] = new_var[*k];
		(*k)++;
		(*j)++;
	}
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
			replace_dollar_2_bis(ret, new_var, &j, &k);
		ret[j++] = str[i];
		i++;
	}
	if (i == pos)
		replace_dollar_2_bis(ret, new_var, &j, &k);
	ret[j] = '\0';
	free(new_var);
	free(str);
	return (ret);
}

char	*expand_dollar(char **env, char *str, t_to_clean *clean)
{
	int		i;
	char	*var_name;

	(void)env;
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
				str = expand_dollar_six(str, &i, var_name, clean);
			}
		}
		expand_dollar_quin(str, &i);
	}
	return (expand_dollar_bis(str, i, clean));
}

/* char	*expand_dollar(char **env, char *str, t_to_clean *clean)
{
	int		i;
	char	*var_name;

	(void)env;
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
				str = expand_dollar_six(str, &i, var_name, clean);
			}
		}
		expand_dollar_quin(str, &i);
	}
	return (expand_dollar_bis(str, i, clean));
}
 */
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
