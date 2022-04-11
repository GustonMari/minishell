/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 09:15:34 by gmary             #+#    #+#             */
/*   Updated: 2022/04/11 17:35:48 by ndormoy          ###   ########.fr       */
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
	//WARNINGULTRA
	(void)clean;
	i = 0;
	while (str[i])
	{
		if (str[i] == BACK_SLASH && str[i + 1] && str[i + 1] == '$')
		{
			//str = del_one_back_slash(str, clean);
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
	dont_expand_special_char(str, i);
}

void	expand_dollar_quin(char *str, int *i)
{
	if (str[*i] != BACK_SLASH
		|| (str[*i] == BACK_SLASH && str[(*i) + 1] && str[(*i) + 1] != '$'))
		(*i)++;
}

char	*expand_dollar_six(char *str, int *i, char *var_name, t_to_clean *clean)
{
	if (ft_find_env_line(clean->env, var_name) && str[(*i) + 1] != '$')
		str = replace_dollar(str, var_name, *i, clean);
	else
		str = del_dollar(str, var_name, ft_strlen(var_name), clean);
	return (str);
}
