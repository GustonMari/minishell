/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 09:44:12 by gmary             #+#    #+#             */
/*   Updated: 2022/04/04 09:47:08 by gmary            ###   ########.fr       */
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
