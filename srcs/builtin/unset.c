/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 09:46:12 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/07 07:42:26 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*Permet de savoir si la variable to_del existe
dans la chaine de caractere str
renvoie 0 si a la fin de la variable on a un \0
ou si on a un =*/

int	is_var_in_line_unset(char *str, char *to_del, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (str[i] && str[i] == to_del[i] && i < n - 1)
		i++;
	if (((unsigned char)str[i] - (unsigned char)to_del[i] == 0)
		&& ((str[i + 1] == '\0') || (str[i + 1] == '=')))
		return (0);
	else
		return (1);
}

/*
	copie tt le tab en sautant une ligne indique au prealable
	 (supprime la variable env envoye en param)
	et return le nouveau tab d'env
*/

char	**ft_unset_line_bis(char **env, char *to_del, int line)
{
	char	**dest;
	int		i;
	int		j;

	i = 0;
	dest = malloc(sizeof(char *) * (line));
	if (!dest)
		return (NULL);
	j = -1;
	while (++j < line)
	{
		if (is_var_in_line_unset(env[j], to_del, ft_strlen(to_del)))
		{	
			dest[i] = ft_strdup(env[j]);
			if (!dest[i])
				return (NULL);
			i++;
		}
	}
	dest[i] = NULL;
	return (dest);
}

char	**ft_unset_line(char **env, char *to_del)
{
	int		line;
	char	**dest;

	line = ft_count_line(env);
	if (check_already_exists(env, to_del, ft_strlen(to_del)) == FALSE)
		return (env);
	dest = ft_unset_line_bis(env, to_del, line);
	if (!dest)
		return (NULL);
	ft_free_tab_2d(env);
	return (dest);
}

int	ft_check_unset(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((!ft_isalnum_export(str[i])) || (str[0] >= '0' && str[0] <= '9'))
		{
			ft_putstr_fd(BRED"minishell: unset: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("\': not a valid identifier\n"CRESET, 2);
			g_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

char	**ft_unset(char **env, char **full_cmd)
{
	int	i;

	i = 1;
	g_status = 0;
	if (ft_count_line(full_cmd) == 1)
		return (env);
	while (full_cmd[i])
	{
		ft_check_unset(full_cmd[i]);
		env = ft_unset_line(env, full_cmd[i]);
		if (!env)
			return (NULL);
		i++;
	}
	return (env);
}
