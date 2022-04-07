/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:23:21 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/07 08:56:17 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

/*Trouve si la cmd en parametre est une cmd
avec un chemin absolut*/

char	*find_absolute_path_cmd(char *cmd, char *tmp)
{
	int		i;
	char	**all_cmd_path;

	(void)tmp;
	all_cmd_path = ft_split(getenv("PATH="), ':');
	if (!all_cmd_path)
		return (NULL);
	i = -1;
	while (all_cmd_path[++i])
	{
		if (access(cmd, F_OK | X_OK) == 0)
		{
			ft_free_tab_2d(all_cmd_path);
			return (ft_strdup(cmd));
		}
	}
	ft_free_tab_2d(all_cmd_path);
	return (NULL);
}

char	*find_path_cmd_bis(char *cmd_to_join)
{
	char	*cmd;

	if (ft_strncmp(cmd_to_join, "./", 2) == TRUE)
		return (NULL);
	cmd = ft_strjoin("/", cmd_to_join);
	if (!cmd)
		return (NULL);
	return (cmd);
}

/*Trouve si la cmd en parametre est une cmd
avec un chemin relatif*/

char	*find_path_cmd(char *cmd_to_join, char *tmp)
{
	int		i;
	char	*path;
	char	**all_cmd_path;
	char	*cmd;

	cmd = find_path_cmd_bis(cmd_to_join);
	if (!cmd)
		return (NULL);
	all_cmd_path = ft_split(tmp, ':');
	if (!all_cmd_path)
		return (NULL);
	i = -1;
	while (all_cmd_path[++i])
	{
		path = ft_strjoin(all_cmd_path[i], cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			free(cmd);
			ft_free_tab_2d(all_cmd_path);
			return (path);
		}
		free(path);
	}
	free(cmd);
	return (ft_free_tab_2d(all_cmd_path));
}

/*Va regarder si la commande est une commande
avec un chemin absolut ou relatif, renvoi le path
si il y avait un chemin absolut ou relatif, renvoie
NULL si il n'y avait aucun des deux*/

char	*chose_ath_cmd(char *cmd, char *tmp)
{
	char	*path;

	path = find_path_cmd(cmd, tmp);
	if (path == NULL)
		path = find_absolute_path_cmd(cmd, tmp);
	free(tmp);
	return (path);
}
