/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_diff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:41:51 by gmary             #+#    #+#             */
/*   Updated: 2022/04/06 14:43:41 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

char	*replace_interrogation_end_diff(char *str, char *status,
		char *var_name, char *dest)
{
	if (status)
		free(status);
	if (str)
		free(str);
	(void)var_name;
	if (var_name)
		free(var_name);
	return (dest);
}

char	*replace_interrogation_diff(char *str, int pos, t_to_clean *clean,
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
	return (replace_interrogation_end_diff(str, status, var_name, dest));
}

char	*expand_single_dollar_diff(char **env, char *str, t_to_clean *clean)
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
		del_dollar_2_quin(var_name);
		return (str);
	}
	if (str[i] == '$' && str[i + 1] == '?')
		str = replace_interrogation_diff(str, i, clean, var_name);
	else
	{
		if (ft_find_env_line(env, var_name) && str[i + 1] != '$')
			str = replace_dollar(str, var_name, i, clean);
		else
			str = del_dollar(str, var_name, ft_strlen(var_name), clean);
	}
	return (str);
}
