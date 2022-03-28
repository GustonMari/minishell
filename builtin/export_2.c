/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:50:23 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/28 10:21:22 by gmary            ###   ########.fr       */
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

char	*ft_rpl_val_var_env_export(char *var, char *new_val)
{
	int		i;
	char	*ret;

	i = 0;
	if (is_equal_in_line(var) == 0)
	{
		while (var[i] != '=')
		i++;
		var[i + 1] = '\0';
		ret = ft_strjoin(var, new_val);
	}
	else
	{
		ret = ft_strjoin(var, "=");
		ret = ft_strjoin_free(ret, new_val, 1);
	}
	free(var);
	return (ret);
}

int	ft_change_env_val_export(char **env, char *var, char *new_val)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!is_var_in_line_unset(env[i], var, ft_strlen(var)))
		{
			env[i] = ft_rpl_val_var_env_export(env[i], new_val);
			return (0);
		}
		i++;
	}
	return (1);
}

/*Permet de savoir si la variable var existe dans la chaine str
et qu'elle n'a pas de valeur, si elle existe et qu'elle n'a pas de valeur
on retourne 0*/

int	is_var_in_line_export(char *str, char *var, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (str[i] && str[i] == var[i] && i < n - 1)
		i++;
	if (((unsigned char)str[i] - (unsigned char)var[i] == 0)
		&& (str[i + 1] == '\0'))
		return (0);
	else
		return (1);
}

int	is_var_in_env_export_2(char **env, char *var, size_t n)
{
	int		j;
	int		line;

	j = -1;
	line = ft_count_line(env);
	while (++j < line)
	{
		if (!is_var_in_line_unset(env[j], var, n))
			return (0);
	}
	return (1);
}

/*Permet de savoir si la variable var existe dans l'env*/

int	is_var_in_env_export(char **env, char *var, size_t n)
{
	int		j;
	int		line;

	j = -1;
	line = ft_count_line(env);
	while (++j < line)
	{
		if (!is_var_in_line_export(env[j], var, n))
			return (0);
	}
	return (1);
}

/*Check dans str si avant le = il n'y a que des caracteres
alphanum, sinon on retourne 1 en affichant un message d'erreur*/

int	ft_check_export(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((!ft_isalnum(str[i])))
		{
			ft_putstr_fd(BRED"minishell: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\': not a valid identifier\n"CRESET, 2);
			g_status = 1;
			return (1);
		}
		i++;
		if (str[i] && str[i] == '=')
			break ;
	}
	return (0);
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
