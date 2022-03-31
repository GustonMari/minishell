/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:58:37 by ndormoy           #+#    #+#             */
/*   Updated: 2022/03/31 14:58:38 by ndormoy          ###   ########.fr       */
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
		if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
			i++;
		if (str[i] && str[i] == '=')
			break ;
	}
	return (0);
}
