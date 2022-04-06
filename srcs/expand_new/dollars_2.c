/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:04:36 by gmary             #+#    #+#             */
/*   Updated: 2022/04/06 14:14:15 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	replace_interrogation_bis(char *status, char *dest, int *j, int *k)
{
	while (status[*j])
	{
		dest[*k] = status[*j];
		(*j)++;
		(*k)++;
	}
}

void	replace_interrogation_ter(char *str, char *dest, int *i, int *k)
{
	dest[*k] = str[*i];
	(*i)++;
	(*k)++;
}

char	*ft_allocate_itoa(char *status, char *str, char *var_name,
	t_to_clean *clean)
{
	status = ft_itoa(g_status);
	if (!status)
	{
		if (var_name)
			free(var_name);
		var_name = NULL;
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	return (status);
}

char	*ft_allocate_dest(char *str, char *status, char *dest,
		t_to_clean *clean)
{
	dest = malloc(sizeof(char) * (ft_strlen(str) - 1 + ft_strlen(status)));
	if (!dest)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	return (dest);
}

char	*replace_interrogation_end(char *str, char *status,
		char *var_name, char *dest)
{
	if (status)
		free(status);
	if (str)
		free(str);
	if (var_name)
		free(var_name);
	return (dest);
}
