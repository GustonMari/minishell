/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:50:23 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/30 13:20:39 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*Renvoi 0 si on trouve un = dans str*/

int	is_equal_in_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

/*Va checker si on a un += dans str, si oui, on va joinvar et new_val
pour pouvoir faire un join dans le cas --> export lol+=salut par exemple*/

char	*join_export(char *var, char *new_val, char *str, int *change)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
		{
			var = ft_strjoin_free(var, new_val, 1);
			if (!var)
				return (NULL);
			*change = 1;
		}
		i++;
	}
	fprintf(stderr, "nouvellleeeeee var = %s\n", var);
	return (var);
}


char	*ft_rpl_val_var_env_export(char *var, char *new_val, char *str)
{
	int		i;
	char	*ret;
	int		change;

	change = 0;
	i = 0;
	if (is_equal_in_line(var) == 0)
	{
		fprintf(stderr, "var = %s\nnew_val = %s\n", var, new_val);
		var = join_export(var ,new_val, str, &change);
		if (change == 0)
		{
			while (var[i] != '=')
			i++;
			var[i + 1] = '\0';
			ret = ft_strjoin(var, new_val);
		}
		else
			ret = ft_strdup(var);
		
	}
	else
	{
		ret = ft_strjoin(var, "=");
		ret = ft_strjoin_free(ret, new_val, 1);
	}
	free(var);
	return (ret);
}

int	ft_change_env_val_export(char **env, char *var, char *new_val, char *str)
{
	int		i;
	(void)str;

	i = 0;
	while (env[i])
	{
		if (!is_var_in_line_unset(env[i], var, ft_strlen(var)))
		{
			env[i] = ft_rpl_val_var_env_export(env[i], new_val, str);
			return (0);
		}
		i++;
	}
	return (1);
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
