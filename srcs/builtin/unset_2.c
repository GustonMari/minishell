/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:53:34 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 14:53:42 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*Permet de savoir si la variable existe dans l'environnement,
on retourne 0 si elle existe*/

int	check_already_exists(char **env, char *to_del, size_t n)
{
	int		j;
	int		line;

	j = -1;
	line = ft_count_line(env);
	while (++j < line)
	{
		if (!is_var_in_line_unset(env[j], to_del, n))
			return (TRUE);
	}
	return (FALSE);
}
