/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:16:18 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/04 11:38:06 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	ft_export_no_arg(char **env)
{
	char	**env_sorted;

	env_sorted = bubble_sort_tab_2d(ft_strdup_2d(env));
	if (!env_sorted)
		return ;
	ft_print_export_no_arg(env_sorted);
	ft_free_tab_2d(env_sorted);
}

/*Affiche une ligne de export en ajoutant des quotes pour
la valeur des variables d'env pour reproduire export.
(n'ajoute pas de quotes si la variable n'a pas de valeur)*/

void	ft_putstr_export_no_arg(char *str)
{
	int	i;
	int	first_equal;

	i = 0;
	first_equal = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		if ((str[i] == '=') && first_equal == 0)
		{
			write(1, "\"", 1);
			first_equal = 1;
		}
		i++;
	}
	if (first_equal == 1)
		write(1, "\"", 1);
}

/*Affiche export quand on ne met aucun argument devant
(c'est l'environnement printe avec quelques modifs)*/

int	ft_print_export_no_arg(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_export_no_arg(env[i]);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
