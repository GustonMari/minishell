/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:00:48 by gmary             #+#    #+#             */
/*   Updated: 2022/02/18 15:06:49 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "function.h"

char	*find_path_cmd(char *cmd, char *tmp)
{
	int		i;
	char	*path;
	char	**all_cmd_path;


	all_cmd_path = ft_split(tmp, ':');
	if (!all_cmd_path)
		return (NULL);
	free(tmp);
	i = 0;
	while (all_cmd_path[i++])
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
	ft_free_tab_2d(all_cmd_path);
	return (NULL);
}

int	ft_exec_cmd(char **env, char *cmd, char **full_cmd)
{
	char	*new_cmd;
	char	*path;
	char	*tmp;

	tmp = find_val_in_tab(env, "PATH");
	if (!tmp)
		return (-1);
	new_cmd = ft_strjoin("/", cmd);
	if (!new_cmd)
		return (-1);
	path = find_path_cmd(new_cmd, tmp);
	if(execve(path, full_cmd, env) < 0)
		perror("execve");
	ft_free_tab_2d(full_cmd);
	free(path);
	return (0);
}


int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char **test = malloc (3 * sizeof(char *));
	test[0] = "ls";
	test[1] = "-la";
	test[2] = NULL;

	ft_exec_cmd(env, test[0], test);

	return (0);
}