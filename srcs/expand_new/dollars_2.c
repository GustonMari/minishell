/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:04:36 by gmary             #+#    #+#             */
/*   Updated: 2022/04/03 15:27:58 by gmary            ###   ########.fr       */
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
		//WARNING
		free(var_name);
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

char	*replace_interrogation_end(char *str, char *status, char *var_name)
{
	//WARNING status et str ETTTTTTT VAR_NAME 
	free(status);
	free(str);
	if (var_name)
		free(var_name);
}

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
	replace_interrogation_end(str, status, var_name);
	return (dest);
}
