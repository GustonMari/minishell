/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:38:03 by gmary             #+#    #+#             */
/*   Updated: 2022/03/31 15:58:55 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*
	leaks => ici status est alloue et jamais free
*/

char	*replace_interrogation_ter(char *dest, char *str, int *i, int *k)
{
	dest[*k] = str[*i];
	(*i)++;
	(*k)++;
	return (dest);
}

char	*replace_interrogation_bis(char *dest, char *str, int pos, char *status)
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
			while (status[j])
			{
				dest[k] = status[j];
				j++;
				k++;
			}
			i += 2;
		}
		else
			replace_interrogation_ter(dest, str, &i, &k);
	}
	dest[k] = '\0';
	return (dest);
}

char	*replace_interrogation(char *str, int pos, t_to_clean *clean)
{
	char	*dest;
	char	*status;

	status = ft_itoa(g_status);
	if (!status)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	dest = malloc(sizeof(char) * (ft_strlen(str) - 1 + ft_strlen(status)));
	if (!dest)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	return (replace_interrogation_bis(dest, str, pos, status));
}

/* 

		Gustave Add

char	*replace_interrogation(char *str, int pos, t_to_clean *clean)
{
	char	*dest;
	char	*status;

	status = ft_itoa(g_status);
	if (!status)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	dest = malloc(sizeof(char) * (ft_strlen(str) - 1 + ft_strlen(status)));
	if (!dest)
	{
		free(str);
		return (ft_clean_error_malloc(clean));
	}
	//while (str[i])
	//{
	//	if (i == pos)
	//	{
	//		while (status[j])
	//		{
	//			dest[k] = status[j];
	//			j++;
	//			k++;
	//		}
	//		i += 2;
	//	}
	//	else
	//	{
	//		dest[k] = str[i];
	//		i++;
	//		k++;
	//	}
	//}
	//dest[k] = '\0';
	//return (dest);
} */